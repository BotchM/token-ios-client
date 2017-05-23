// Copyright (c) 2017 Token Browser, Inc
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

import UIKit
import SweetUIKit
import NoChat
import MobileCoreServices
import ImagePicker
import AVFoundation

class ChatController: MessagesCollectionViewController { // OverlayController (!)
    
    fileprivate var etherAPIClient: EthereumAPIClient {
        return EthereumAPIClient.shared
    }
    
    fileprivate var idAPIClient: IDAPIClient {
        return IDAPIClient.shared
    }
    
    fileprivate var chatAPIClient: ChatAPIClient {
        return ChatAPIClient.shared
    }
    
    fileprivate var ethereumAPIClient: EthereumAPIClient {
        return EthereumAPIClient.shared
    }
    
    lazy var disposable: SMetaDisposable = {
        let disposable = SMetaDisposable()
        return disposable
    }()
    
    lazy var processMediaDisposable: SMetaDisposable = {
        let disposable = SMetaDisposable()
        return disposable
    }()

    fileprivate var textLayoutQueue = DispatchQueue(label: "com.tokenbrowser.token.layout", qos: DispatchQoS(qosClass: .default, relativePriority: 0))

    fileprivate lazy var avatarImageView: AvatarImageView = {
        let avatar = AvatarImageView(image: UIImage())
        avatar.bounds.size = CGSize(width: 34, height: 34)
        avatar.isUserInteractionEnabled = true

        let tap = UITapGestureRecognizer(target: self, action: #selector(self.showContactProfile))
        avatar.addGestureRecognizer(tap)

        return avatar
    }()

    fileprivate var messages = [Message]() {
        didSet {
            let current = Set(self.messages)
            let previous = Set(oldValue)
            let new = current.subtracting(previous).sorted { (message1, message2) -> Bool in
                // so far the only case where this is true to the milisecond is when
                // signal splits a media message into two, with the same dates. That means that one of them has attachments
                // but the other one doesn't. We want the one with attachments on top.
                if message1.date.compare(message2.date) == .orderedSame {
                    return message1.signalMessage.hasAttachments()
                }
                
                // otherwise, resume regular date comparison
                return message1.date.compare(message2.date) == .orderedAscending
            }
            
            let displayables = new.filter { (message) -> Bool in
                return message.isDisplayable
            }
            
            // Only animate if we're adding one message, for bulk-insert we want them instant.
            // let isAnimated = displayables.count == 1
            self.addMessages(displayables, scrollToBottom: true)
        }
    }

    fileprivate var visibleMessages: [Message] {
        return self.messages.filter { (message) -> Bool in
            message.isDisplayable
        }
    }

    fileprivate var contact: TokenUser {
        return self.contactsManager.tokenContact(forAddress: self.thread.contactIdentifier())!
    }

    fileprivate lazy var mappings: YapDatabaseViewMappings = {
        let mappings = YapDatabaseViewMappings(groups: [self.thread.uniqueId], view: TSMessageDatabaseViewExtensionName)
        mappings.setIsReversed(true, forGroup: TSInboxGroup)
        
        return mappings
    }()

    fileprivate lazy var uiDatabaseConnection: YapDatabaseConnection = {
        let database = TSStorageManager.shared().database()!
        let dbConnection = database.newConnection()
        dbConnection.beginLongLivedReadTransaction()
        
        return dbConnection
    }()

    fileprivate lazy var editingDatabaseConnection: YapDatabaseConnection = {
        self.storageManager.newDatabaseConnection()
    }()
    
    fileprivate var menuSheetController: MenuSheetController?
    
    var thread: TSThread

    fileprivate var messageSender: MessageSender

    fileprivate var contactsManager: ContactsManager

    fileprivate var contactsUpdater: ContactsUpdater

    fileprivate var storageManager: TSStorageManager

    fileprivate lazy var ethereumPromptView: ChatsFloatingHeaderView = {
        let view = ChatsFloatingHeaderView(withAutoLayout: true)
        view.delegate = self
        
        return view
    }()
    
    deinit {
        disposable.dispose()
        processMediaDisposable.dispose()
    }
    
    // MARK: - Class overrides
    
    override class func cellLayoutClass(forItemType type: String) -> AnyClass? {
        if type == "Text" {
            return MessageCellLayout.self
        } else if type == "Actionable" {
            return ActionableMessageCellLayout.self
        } else if type == "Image" {
            return ImageMessageCellLayout.self
        } else {
            return nil
        }
    }
    
    // MARK: - Init
    
    init(thread: TSThread) {
        self.thread = thread
        
        guard let appDelegate = UIApplication.shared.delegate as? AppDelegate else { fatalError("Could not retrieve app delegate") }
        
        self.messageSender = appDelegate.messageSender
        self.contactsManager = appDelegate.contactsManager
        self.contactsUpdater = appDelegate.contactsUpdater
        self.storageManager = TSStorageManager.shared()
        
        super.init(nibName: nil, bundle: nil)
        
        self.hidesBottomBarWhenPushed = true
        self.title = thread.cachedContactIdentifier
        
        self.registerNotifications()
        
        self.additionalContentInsets.top = 48
    }
    
    required init?(coder _: NSCoder) {
        fatalError()
    }
    
    // MARK: View life-cycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.view.backgroundColor = Theme.messageViewBackgroundColor
        self.containerView?.backgroundColor = nil
        
        self.view.addSubview(self.ethereumPromptView)
        self.ethereumPromptView.heightAnchor.constraint(equalToConstant: ChatsFloatingHeaderView.height).isActive = true
        self.ethereumPromptView.topAnchor.constraint(equalTo: self.topLayoutGuide.bottomAnchor).isActive = true
        self.ethereumPromptView.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        self.ethereumPromptView.rightAnchor.constraint(equalTo: self.view.rightAnchor).isActive = true
        
        self.collectionView.keyboardDismissMode = .interactive
        self.collectionView.backgroundColor = nil

        self.fetchAndUpdateBalance()
        self.loadMessages()
        
        self.view.addSubview(self.textInputView)
        
        NSLayoutConstraint.activate([
            self.textInputView.leftAnchor.constraint(equalTo: self.view.leftAnchor),
            self.textInputView.rightAnchor.constraint(equalTo: self.view.rightAnchor),

            self.textInputViewBottom,
            self.textInputViewHeight,
        ])

        self.navigationItem.rightBarButtonItem = UIBarButtonItem(customView: self.avatarImageView)
    }
    
    func checkMicrophoneAccess() {
        if AVAudioSession.sharedInstance().recordPermission().contains(.undetermined) {
            
            AVAudioSession.sharedInstance().requestRecordPermission({ granted in
                
            })
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.reloadDraft()
        self.view.layoutIfNeeded()

        self.avatarImageView.image = self.thread.image()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        self.thread.markAllAsRead()
        SignalNotificationManager.updateApplicationBadgeNumber()
        self.title = self.thread.cachedContactIdentifier

        if self.contact.isApp && self.messages.isEmpty {
            // If contact is an app, and there are no messages between current user and contact
            // we send the app an empty regular sofa message. This ensures that Signal won't display it,
            // but at the same time, most bots will reply with a greeting.
            self.sendMessage(sofaWrapper: SofaMessage(body: ""))
        }
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.saveDraft()
        
        self.thread.markAllAsRead()
        SignalNotificationManager.updateApplicationBadgeNumber()
    }

    fileprivate func fetchAndUpdateBalance() {

        self.ethereumAPIClient.getBalance(address: Cereal.shared.paymentAddress) { balance, error in
            if let error = error {
                let alertController = UIAlertController.errorAlert(error as NSError)
                self.present(alertController, animated: true, completion: nil)
            } else {
                self.set(balance: balance)
            }
        }
    }

    @objc
    fileprivate func handleBalanceUpdate(notification: Notification) {
        guard notification.name == .ethereumBalanceUpdateNotification, let balance = notification.object as? NSDecimalNumber else { return }
        self.set(balance: balance)
    }

    fileprivate func set(balance: NSDecimalNumber) {
        self.ethereumPromptView.balance = balance
    }

    fileprivate func saveDraft() {

        let thread = self.thread
        guard let text = self.textInputView.text else { return }
        
        self.editingDatabaseConnection.asyncReadWrite { transaction in
            thread.setDraft(text, transaction: transaction)
        }
    }

    fileprivate func reloadDraft() {
        let thread = self.thread
        var placeholder: String?
        
        self.editingDatabaseConnection.asyncReadWrite({ transaction in
            placeholder = thread.currentDraft(with: transaction)
        }, completionBlock: {
            DispatchQueue.main.async {
                self.textInputView.text = placeholder
            }
        })
    }
    
    override func registerChatItemCells() {
        self.collectionView.register(MessageCell.self, forCellWithReuseIdentifier: MessageCell.reuseIdentifier())
        self.collectionView.register(ActionableMessageCell.self, forCellWithReuseIdentifier: ActionableMessageCell.reuseIdentifier())
        self.collectionView.register(ImageMessageCell.self, forCellWithReuseIdentifier: ImageMessageCell.reuseIdentifier())
    }

    // MARK: Load initial messages

    fileprivate func loadMessages() {
        self.uiDatabaseConnection.asyncRead { transaction in
            self.mappings.update(with: transaction)
            
            var messages = [Message]()
            
            for i in 0 ..< self.mappings.numberOfItems(inSection: 0) {
                let indexPath = IndexPath(row: Int(i), section: 0)
                guard let dbExtension = transaction.ext(TSMessageDatabaseViewExtensionName) as? YapDatabaseViewTransaction else { fatalError() }
                guard let interaction = dbExtension.object(at: indexPath, with: self.mappings) as? TSInteraction else { fatalError() }
                
                DispatchQueue.main.async {
                    var shouldProcess = false
                    if let message = interaction as? TSMessage, SofaType(sofa: message.body ?? "") == .paymentRequest {
                        shouldProcess = true
                    }
                    
                    messages.append(self.handleInteraction(interaction, shouldProcessCommands: shouldProcess))
                }
            }
            
            DispatchQueue.main.async {
                UIView.performWithoutAnimation {
                    self.messages = messages
                    self.collectionView.reloadData()
                    self.scrollToBottom(animated: false)
                }
            }
        }
    }
    
    // Mark: Handle new messages

    fileprivate func showFingerprint(with _: Data, signalId _: String) {
        // Postpone this for now
        print("Should display fingerprint comparison UI.")
        //        let builder = OWSFingerprintBuilder(storageManager: self.storageManager, contactsManager: self.contactsManager)
        //        let fingerprint = builder.fingerprint(withTheirSignalId: signalId, theirIdentityKey: identityKey)
        //
        //        let fingerprintController = FingerprintViewController(fingerprint: fingerprint)
        //        self.present(fingerprintController, animated: true)
    }

    fileprivate func handleInvalidKeyError(_ errorMessage: TSInvalidIdentityKeyErrorMessage) {
        let keyOwner = self.contactsManager.displayName(forPhoneIdentifier: errorMessage.theirSignalId())
        let titleText = "Your safety number with \(keyOwner) has changed. You may wish to verify it."
        
        let actionSheetController = UIAlertController(title: titleText, message: nil, preferredStyle: .actionSheet)
        
        let dismissAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        actionSheetController.addAction(dismissAction)
        
        let showSafteyNumberAction = UIAlertAction(title: NSLocalizedString("Compare fingerprints.", comment: "Action sheet item"), style: .default) { (_: UIAlertAction) -> Void in
            
            self.showFingerprint(with: errorMessage.newIdentityKey(), signalId: errorMessage.theirSignalId())
        }
        actionSheetController.addAction(showSafteyNumberAction)
        
        let acceptSafetyNumberAction = UIAlertAction(title: NSLocalizedString("Accept the new contact identity.", comment: "Action sheet item"), style: .default) { (_: UIAlertAction) -> Void in
            
            errorMessage.acceptNewIdentityKey()
            if errorMessage is TSInvalidIdentityKeySendingErrorMessage {
                self.messageSender.resendMessage(fromKeyError: (errorMessage as! TSInvalidIdentityKeySendingErrorMessage), success: { () -> Void in
                    print("Got it!")
                }, failure: { (_ error: Error) -> Void in
                    print(error)
                })
            }
        }
        actionSheetController.addAction(acceptSafetyNumberAction)

        self.present(actionSheetController, animated: true, completion: nil)
    }
    
    /// Handle incoming interactions or previous messages when restoring a conversation.
    ///
    /// - Parameters:
    ///   - interaction: the interaction to handle. Incoming/outgoing messages, wrapping SOFA structures.
    ///   - shouldProcessCommands: If true, will process a sofa wrapper. This means replying to requests, displaying payment UI etc.
    ///
    fileprivate func handleInteraction(_ interaction: TSInteraction, shouldProcessCommands: Bool = false) -> Message {
        if let interaction = interaction as? TSInvalidIdentityKeySendingErrorMessage {
            DispatchQueue.main.async {
                self.handleInvalidKeyError(interaction)
            }
            
            return Message(sofaWrapper: nil, signalMessage: interaction, date: interaction.date(), isOutgoing: false)
        }
        
        if let message = interaction as? TSMessage, shouldProcessCommands {
            let type = SofaType(sofa: message.body)
            switch type {
            case .metadataRequest:
                let metadataResponse = SofaMetadataResponse(metadataRequest: SofaMetadataRequest(content: message.body!))
                self.sendMessage(sofaWrapper: metadataResponse)
            default:
                break
            }
        }
        
        /// TODO: Simplify how we deal with interactions vs text messages.
        /// Since now we know we can expande the TSInteraction stored properties, maybe we can merge some of this together.
        if let interaction = interaction as? TSOutgoingMessage {
            let sofaWrapper = SofaWrapper.wrapper(content: interaction.body!)
            let message = Message(sofaWrapper: sofaWrapper, signalMessage: interaction, date: interaction.date(), isOutgoing: true)
            
            if interaction.hasAttachments() {
                message.messageType = "Image"
            } else if let payment = SofaWrapper.wrapper(content: interaction.body ?? "") as? SofaPayment {
                message.messageType = "Actionable"
                message.attributedTitle = NSAttributedString(string: "Payment sent", attributes: [NSForegroundColorAttributeName: Theme.outgoingMessageTextColor, NSFontAttributeName: Theme.medium(size: 17)])
                message.attributedSubtitle = NSAttributedString(string: EthereumConverter.balanceAttributedString(forWei: payment.value).string, attributes: [NSForegroundColorAttributeName: Theme.outgoingMessageTextColor, NSFontAttributeName: Theme.regular(size: 15)])
            }
            
            return message
        } else if let interaction = interaction as? TSIncomingMessage {
            let sofaWrapper = SofaWrapper.wrapper(content: interaction.body!)
            let message = Message(sofaWrapper: sofaWrapper, signalMessage: interaction, date: interaction.date(), isOutgoing: false, shouldProcess: shouldProcessCommands && interaction.paymentState == .none)
            
            if interaction.hasAttachments() {
                message.messageType = "Image"
            } else if let sofaMessage = sofaWrapper as? SofaMessage {
                buttons = sofaMessage.buttons
            } else if let paymentRequest = sofaWrapper as? SofaPaymentRequest {
                message.messageType = "Actionable"
                message.title = "Payment request"
                message.attributedSubtitle = EthereumConverter.balanceAttributedString(forWei: paymentRequest.value)
            } else if let payment = sofaWrapper as? SofaPayment {
                message.messageType = "Actionable"
                message.attributedTitle = NSAttributedString(string: "Payment received", attributes: [NSForegroundColorAttributeName: Theme.incomingMessageTextColor, NSFontAttributeName: Theme.medium(size: 17)])
                message.attributedSubtitle = NSAttributedString(string: EthereumConverter.balanceAttributedString(forWei: payment.value).string, attributes: [NSForegroundColorAttributeName: Theme.incomingMessageTextColor, NSFontAttributeName: Theme.regular(size: 15)])
            }
            
            return message
        } else {
            return Message(sofaWrapper: nil, signalMessage: interaction as! TSMessage, date: interaction.date(), isOutgoing: false)
        }
    }
    
    // MARK: Add displayable messages
    
    private func addMessages(_ messages: [Message], scrollToBottom: Bool) {
        self.textLayoutQueue.async {
            let indexes = IndexSet(integersIn: 0 ..< messages.count)
            
            DispatchQueue.main.async {
                var layouts = [NOCChatItemCellLayout]()
                
                for message in messages {
                    let layout = self.createLayout(with: message)!
                    layouts.append(layout)
                }
                
                if !layouts.isEmpty {
                    self.insertLayouts(layouts.reversed(), at: indexes, animated: true)
                }
                if scrollToBottom {
                    self.scrollToBottom(animated: true)
                    
                }
                
                self.collectionView.contentInset = UIEdgeInsets(top: 0.0, left: 0.0, bottom: 51.0, right: 0.0)
            }
        }
    }
    
    // MARK: - Helper methods

    fileprivate func visibleMessage(at indexPath: IndexPath) -> Message {
        return self.visibleMessages[indexPath.row]
    }

    fileprivate func message(at indexPath: IndexPath) -> Message {
        return self.messages[indexPath.row]
    }

    fileprivate func registerNotifications() {
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(yapDatabaseDidChange(notification:)), name: .YapDatabaseModified, object: nil)
        notificationCenter.addObserver(self, selector: #selector(self.handleBalanceUpdate(notification:)), name: .ethereumBalanceUpdateNotification, object: nil)
    }

    fileprivate func reversedIndexPath(_ indexPath: IndexPath) -> IndexPath {
        let row = (self.visibleMessages.count - 1) - indexPath.item
        return IndexPath(row: row, section: indexPath.section)
    }
    
    // MARK: Handle database changes
    @objc
    fileprivate func yapDatabaseDidChange(notification _: NSNotification) {
        let notifications = self.uiDatabaseConnection.beginLongLivedReadTransaction()
        
        // If changes do not affect current view, update and return without updating collection view
        // TODO: Since this is used in more than one place, we should look into abstracting this away, into our own
        // table/collection view backing model.
        let viewConnection = self.uiDatabaseConnection.ext(TSMessageDatabaseViewExtensionName) as! YapDatabaseViewConnection
        let hasChangesForCurrentView = viewConnection.hasChanges(for: notifications)
        if !hasChangesForCurrentView {
            self.uiDatabaseConnection.read { transaction in
                self.mappings.update(with: transaction)
            }
            
            return
        }
        
        // HACK to work around radar #28167779
        // "UICollectionView performBatchUpdates can trigger a crash if the collection view is flagged for layout"
        // more: https://github.com/PSPDFKit-labs/radar.apple.com/tree/master/28167779%20-%20CollectionViewBatchingIssue
        // This was our #2 crash, and much exacerbated by the refactoring somewhere between 2.6.2.0-2.6.3.8
        self.collectionView.layoutIfNeeded() // ENDHACK to work around radar #28167779
        
        var messageRowChanges = NSArray()
        var sectionChanges = NSArray()
        
        viewConnection.getSectionChanges(&sectionChanges, rowChanges: &messageRowChanges, for: notifications, with: self.mappings)
        
        if messageRowChanges.count == 0 {
            return
        }
        
        self.uiDatabaseConnection.asyncRead { transaction in
            for change in messageRowChanges as! [YapDatabaseViewRowChange] {
                guard let dbExtension = transaction.ext(TSMessageDatabaseViewExtensionName) as? YapDatabaseViewTransaction else { fatalError() }
                
                switch change.type {
                case .insert:
                    guard let interaction = dbExtension.object(at: change.newIndexPath, with: self.mappings) as? TSInteraction else { fatalError("woot") }
                    
                    DispatchQueue.main.async {
                        let result = self.handleInteraction(interaction, shouldProcessCommands: true)
                        self.messages.append(result)
                        
                        if result.isOutgoing {
                            if result.sofaWrapper?.type == .paymentRequest {
                                SoundPlayer.playSound(type: .requestPayment)
                            } else if result.sofaWrapper?.type == .payment {
                                SoundPlayer.playSound(type: .paymentSend)
                            } else {
                                SoundPlayer.playSound(type: .messageSent)
                            }
                        } else {
                            SoundPlayer.playSound(type: .messageReceived)
                        }
                        
                        if let incoming = interaction as? TSIncomingMessage, !incoming.wasRead {
                            incoming.markAsReadLocally()
                        }
                    }
                case .update:
                    let indexPath = change.indexPath
                    guard let interaction = dbExtension.object(at: indexPath, with: self.mappings) as? TSMessage else { return }
                    
                    DispatchQueue.main.async {
                        guard self.visibleMessages.count == self.layouts.count else {
                            print("Called before colection view had a chance to insert message.")
                            
                            return
                        }
                        
                        let message = self.message(at: indexPath)
                        guard let visibleIndex = self.visibleMessages.index(of: message) else { return }
                        let reversedIndex = self.reversedIndexPath(IndexPath(row: visibleIndex, section: 0)).row
                        guard let layout = self.layouts[reversedIndex] as? MessageCellLayout else { return }
                        
                        // commented out until we can prevent it from triggering an update
                        if let signalMessage = layout.message.signalMessage as? TSOutgoingMessage, let newSignalMessage = interaction as? TSOutgoingMessage {
                            signalMessage.setState(newSignalMessage.messageState)
                        }
                        
                        layout.calculate()
                        
                        self.updateLayout(at: UInt(reversedIndex), to: layout, animated: true)
                    }
                default:
                    break
                }
            }
        }
    }
    
    // MARK: Send messages

    fileprivate func sendMessage(sofaWrapper: SofaWrapper, date: Date = Date()) {
        let timestamp = NSDate.ows_millisecondsSince1970(for: date)
        let outgoingMessage = TSOutgoingMessage(timestamp: timestamp, in: self.thread, messageBody: sofaWrapper.content)
        
        self.messageSender.send(outgoingMessage, success: {
            print("message sent")
        }, failure: { error in
            print(error)
        })
    }
    
    // MARK: - Collection view overrides
    
    override func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = super.collectionView(collectionView, cellForItemAt: indexPath)
        
        if let cell = cell as? ActionableMessageCell {
            cell.actionsDelegate = self
        }
        
        return cell
    }
    
    // MARK: - Control handling
    
    override func didTapControlButton(_ button: SofaMessage.Button) {
        guard button.value != nil else {
            print("Implement handling actions. action: \(button.action ?? "nil")")
            
            return
        }
        
        // clear the buttons
        self.buttons = []
        let command = SofaCommand(button: button)
        self.controlsViewDelegateDatasource.controlsCollectionView?.isUserInteractionEnabled = false
        self.sendMessage(sofaWrapper: command)
    }

    @objc
    fileprivate func showContactProfile(_ sender: UITapGestureRecognizer) {
        if sender.state == .ended {
            let contactController = ContactController(contact: self.contact)
            self.navigationController?.pushViewController(contactController, animated: true)
        }
    }
}

extension ChatController: ActionableCellDelegate {
    
    func didTapRejectButton(_ messageCell: ActionableMessageCell) {
        guard let indexPath = self.collectionView.indexPath(for: messageCell) else { return }
        let visibleMessageIndexPath = reversedIndexPath(indexPath)
        
        let message = visibleMessage(at: visibleMessageIndexPath)
        message.isActionable = false
        
        let layout = self.layouts[indexPath.item] as? MessageCellLayout
        layout?.chatItem = message
        layout?.calculate()
        
        let interaction = message.signalMessage
        interaction.paymentState = .rejected
        interaction.save()
    }
    
    func didTapApproveButton(_ messageCell: ActionableMessageCell) {
        guard let indexPath = self.collectionView.indexPath(for: messageCell) else { return }
        let visibleMessageIndexPath = reversedIndexPath(indexPath)
        
        let message = visibleMessage(at: visibleMessageIndexPath)
        message.isActionable = false
        
        let layout = self.layouts[indexPath.item] as? MessageCellLayout
        layout?.chatItem = message
        layout?.calculate()
        
        let interaction = message.signalMessage
        interaction.paymentState = .pendingConfirmation
        interaction.save()
        
        guard let paymentRequest = message.sofaWrapper as? SofaPaymentRequest else { fatalError("Could not retrieve payment request for approval.") }
        
        let value = paymentRequest.value
        guard let destination = paymentRequest.destinationAddress else { return }
        
        // TODO: prevent concurrent calls
        // Also, extract this.
        self.etherAPIClient.createUnsignedTransaction(to: destination, value: value) { transaction, error in
            let signedTransaction = "0x\(Cereal.shared.signWithWallet(hex: transaction!))"
            
            self.etherAPIClient.sendSignedTransaction(originalTransaction: transaction!, transactionSignature: signedTransaction) { json, error in
                if error != nil {
                    guard let json = json?.dictionary else { fatalError("!") }
                    
                    let alert = UIAlertController.dismissableAlert(title: "Error completing transaction", message: json["message"] as? String)
                    self.present(alert, animated: true)
                } else if let json = json?.dictionary {
                    // update payment request message
                    message.isActionable = false
                    
                    let interaction = message.signalMessage
                    interaction.paymentState = .pendingConfirmation
                    interaction.save()
                    
                    // send payment message
                    guard let txHash = json["tx_hash"] as? String else { fatalError("Error recovering transaction hash.") }
                    let payment = SofaPayment(txHash: txHash, valueHex: value.toHexString)
                    
                    self.sendMessage(sofaWrapper: payment)
                }
            }
        }
    }
}

extension ChatController: ChatInputTextPanelDelegate {
    
    func inputTextPanel(_: ChatInputTextPanel, requestSendText text: String) {
        let wrapper = SofaMessage(content: ["body": text])
        sendMessage(sofaWrapper: wrapper)
    }
    
    private func asyncProcess(signals: [SSignal]) {
        let queue = SQueue()
        var combinedSignal: SSignal?
        
        for signal in signals {
            if combinedSignal == nil {
                combinedSignal = signal.start(on: queue)
            } else {
                combinedSignal = combinedSignal?.then(signal).start(on: queue)
            }
        }
        
        let array = [Any]()
        let signal = combinedSignal?.reduceLeft(array, with: { itemDescriptions, item in
            if var descriptions = itemDescriptions as?  [[String: Any]] {
                if let description = item as? [String: Any] {
                    descriptions.append(description)
                }
                
                return descriptions
            }
            
            return nil
            
        }).deliver(on: SQueue.main()).start(next: { itemDescriptions in
            
            var mediaDescriptions = [[String: Any]]()
            
            if let itemDescriptions = itemDescriptions as? [Dictionary<String, Any>] {
                itemDescriptions.forEach ({
                    if $0["localImage"] != nil ||  $0["remoteImage"] != nil ||  $0["downloadImage"] != nil ||  $0["downloadDocument"] != nil ||  $0["downloadExternalGif"] != nil ||  $0["downloadExternalImage"] != nil || $0["remoteDocument"] != nil || $0["remoteCachedDocument"] != nil || $0["assetImage"] != nil || $0["assetVideo"] != nil {
                        mediaDescriptions.append($0)
                    }
                })
            }
            
            if mediaDescriptions.count > 0 {
                for description in mediaDescriptions {
                    if let assetImage = description["assetImage"] as? [String: Any] {
                        let timestamp = NSDate.ows_millisecondsSince1970(for: Date())
                        
                        if let imageData = assetImage["thumbnailData"] as? Data {
                            let outgoingMessage = TSOutgoingMessage(timestamp: timestamp, in: self.thread, messageBody: "")
                            self.messageSender.sendAttachmentData(imageData, contentType: "image/jpeg", filename: "Image.jpeg", in: outgoingMessage, success: {
                                print("Success")
                            }, failure: { error in
                                print("Failure: \(error)")
                            })
                        }
                    }
                    
                    // VIDEO HANDLING
                }
            }
        })
        
        if let signal = signal as SDisposable? {
            self.processMediaDisposable.setDisposable(signal)
        }
    }
    
    func inputTextPanelrequestSendAttachment(_: ChatInputTextPanel) {
        
        self.view.endEditing(true)
        
        self.menuSheetController = MenuSheetController()
        self.menuSheetController?.dismissesByOutsideTap = true
        self.menuSheetController?.hasSwipeGesture = true
        self.menuSheetController?.maxHeight = 445 - MenuSheetButtonItemViewHeight
        var itemViews = [UIView]()
        
        checkMicrophoneAccess()
        
        let carouselItem = AttachmentCarouselItemView(camera:Camera.cameraAvailable(), selfPortrait:false, forProfilePhoto:false, assetType:MediaAssetAnyType)!
        carouselItem.condensed = false
        //carouselItem.parentController = self // TO MERGE
        carouselItem.allowCaptions = true
        carouselItem.inhibitDocumentCaptions = true
        carouselItem.suggestionContext = SuggestionContext()
        carouselItem.cameraPressed = { cameraView in
            guard AccessChecker.checkCameraAuthorizationStatus(alertDismissComlpetion: nil) == true else { return }
            
            self.displayCamera(from: cameraView, menu: self.menuSheetController!, carouselItem: carouselItem)
        }
        
        carouselItem.didSelectImage = { image, asset, fromView in
            
            let editorController = PhotoEditorController(item:asset as! MediaEditableItem, intent:PhotoEditorControllerAvatarIntent, adjustments:nil, caption:nil, screenImage:image, availbaleTabs:PhotoEditorController.defaultTabsForAvatarIntent(), selectedTab:PhotoEditorCropTab)!
            
            editorController.requestOriginalFullSizeImage = { editableItem, position in
                return editableItem?.originalImageSignal?(position)
            }
            
            editorController.didFinishRenderingFullSizeImage = { image in
                carouselItem.updateVisibleItems()
            }
            
            editorController.didFinishEditing = { adjustments, resultImage, thumbnailImage, hasChanges in
                carouselItem.updateVisibleItems()
            }
            
            editorController.requestOriginalScreenSizeImage = { editableItem, position in
                return editableItem?.screenImageSignal?(position)
            }
            
            editorController.requestThumbnailImage = { editableItem in
                return editableItem?.thumbnailImageSignal?()
            }
            
            self.present(editorController, animated: true, completion: nil)
        }
        
        carouselItem.sendPressed = { [unowned self] currentItem, asFiles in
            self.menuSheetController?.dismiss(animated: true, manual: false) {
                
                let intent: MediaAssetsControllerIntent = asFiles == true ? .sendFile : .sendMedia
                
                if let signals = MediaAssetsController.resultSignals(selectionContext:carouselItem.selectionContext, editingContext:carouselItem.editingContext, intent:intent, currentItem: currentItem, storeAssets:true, useMediaCache:true) as? [SSignal] {
                    self.asyncProcess(signals: signals)
                }
            }
        }
        
        itemViews.append(carouselItem)
        
        let galleryItem = MenuSheetButtonItemView.init(title:"Photo or Video", type:MenuSheetButtonTypeDefault, action:{ [unowned self] in
            
            self.menuSheetController?.dismiss(animated: true)
            self.displayMediaPicker(forFile: false, fromFileMenu: false)
        })!
        
        itemViews.append(galleryItem)
        
        carouselItem.underlyingViews = [galleryItem]
        
        let cancelItem = MenuSheetButtonItemView.init(title: "Cancel", type: MenuSheetButtonTypeCancel, action: {
            self.menuSheetController?.dismiss(animated: true)
        })!
        
        itemViews.append(cancelItem)
        self.menuSheetController?.setItemViews(itemViews)
        carouselItem.remainingHeight = MenuSheetButtonItemViewHeight * CGFloat(itemViews.count - 1)
        
        self.menuSheetController?.present(in: self, sourceView:self.view, animated:true)
    }
    
    func displayCamera(from cameraView: AttachmentCameraView?, menu: MenuSheetController, carouselItem: AttachmentCarouselItemView) {
        var controller: CameraController
        let screenSize = TGScreenSize()
        
        if let previewView = cameraView?.previewView() as CameraPreviewView? {
            controller = CameraController(camera:previewView.camera, previewView: previewView, intent: CameraControllerGenericIntent)!
        } else {
            controller = CameraController()
        }
        
        controller.isImportant = true
        controller.shouldStoreCapturedAssets = true
        controller.allowCaptions = true
        
       // let controllerWindow = CameraControllerWindow(parentController: self, contentController: controller)
        //controllerWindow.isHidden = false
        
       // controllerWindow.frame = CGRect(x: 0, y: 0, width: screenSize.width, height: screenSize.height)
        
        var standalone = true
        var startFrame = CGRect(x: 0, y: screenSize.height, width: screenSize.width, height: screenSize.height)
        
        if let cameraView = cameraView as AttachmentCameraView?, let frame = cameraView.previewView().frame as CGRect? {
            standalone = false
            startFrame = controller.view.convert(frame, from: cameraView)
        }
        
        cameraView?.detachPreviewView()
        
        controller.beginTransitionOut = {
            
            if let cameraView = cameraView as AttachmentCameraView? {

                cameraView.willAttachPreviewView()
                return controller.view.convert(cameraView.frame, from:cameraView.superview)
            }
            
            return CGRect.zero
        }
        
        controller.finishedTransitionOut = {
            cameraView?.attachPreviewView(animated: true)
        }
        
        controller.finishedWithPhoto = { resultImage, caption, stickers in
            print("do what needed with added images")
            
            menu.dismiss(animated: true)
            if let image = resultImage as UIImage? {
                self.send(image: image)
            }
        }
        
        controller.finishedWithVideo = { videoURL, previewImage, duration, dimensions, adjustments, caption, stickers in
            print("do what needed with recorded video")
            menu.dismiss(animated: false)
        }
        
        // TO MERGE
        //
        //
        //  let controllerWindow = CameraControllerWindow(parentController: self, contentController: controller)
        // controllerWindow?.isHidden = false
        //
        
        if UIDevice.current.userInterfaceIdiom == .phone {
            //  controllerWindow?.frame = CGRect(x: 0.0, y: 0.0, width: screenSize.width, height: screenSize.height)
        }
    }
    
    func send(image: UIImage) {
        self.menuSheetController?.dismiss(animated: true)
        
        guard let imageData = UIImageJPEGRepresentation(image, 0.6) else { return }
        
        let timestamp = NSDate.ows_millisecondsSince1970(for: Date())
        let outgoingMessage = TSOutgoingMessage(timestamp: timestamp, in: self.thread, messageBody: "")
        
        self.messageSender.sendAttachmentData(imageData, contentType: "image/jpeg", filename: "image.jpeg", in: outgoingMessage, success: {
            print("Success")
        }, failure: { error in
            print("Failure: \(error)")
        })
    }
    
    func inputTextPanelDidChangeHeight(_ height: CGFloat) {
        self.textInputHeight = height
    }
    
    private func displayMediaPicker(forFile: Bool, fromFileMenu:Bool) {
        
        guard AccessChecker.checkPhotoAuthorizationStatus(intent: PhotoAccessIntentRead, alertDismissCompletion: nil) else { return }
        let dismissBlock = { [unowned self] in
            self.dismiss(animated: true, completion: nil)
        }
        
        let showMediaPickerBlock: ((MediaAssetGroup?) -> ()) = { [unowned self] group in
            let intent: MediaAssetsControllerIntent = .sendMedia //forFile ? MediaAssetsControllerIntentSendMedia : MediaAssetsControllerIntentSendMedia
            let assetsController = MediaAssetsController(assetGroup: group, intent:intent)!
            assetsController.captionsEnabled = true
            assetsController.inhibitDocumentCaptions = true
            assetsController.suggestionContext = SuggestionContext()
            assetsController.dismissalBlock = dismissBlock
            assetsController.localMediaCacheEnabled = false
            assetsController.shouldStoreAssets = false
            assetsController.shouldShowFileTipIfNeeded = false
            
            assetsController.completionBlock = { signals in
                
                assetsController.dismiss(animated: true, completion: nil)
                
                if let signals = signals as? [SSignal] {
                    self.asyncProcess(signals: signals)
                }
            }
            
            self.present(assetsController, animated: true, completion: nil)
            
        }
        
        
        
        if MediaAssetsLibrary.authorizationStatus() == MediaLibraryAuthorizationStatusNotDetermined {
            MediaAssetsLibrary.requestAuthorization(for: MediaAssetAnyType) { (status, cameraRollGroup) -> Void in
                
                let photoAllowed = AccessChecker.checkPhotoAuthorizationStatus(intent: PhotoAccessIntentRead, alertDismissCompletion: nil)
                let microphoneAllowed = AccessChecker.checkMicrophoneAuthorizationStatus(for: MicrophoneAccessIntentVideo, alertDismissCompletion: nil)
                
                if photoAllowed == false || microphoneAllowed == false {
                    return;
                }
                
                showMediaPickerBlock(cameraRollGroup);
            }
        }
        
        showMediaPickerBlock(nil)
    }
}

extension ChatController: ImagePickerDelegate {
    func cancelButtonDidPress(_ imagePicker: ImagePickerController) {
        self.dismiss(animated: true)
    }
    
    func doneButtonDidPress(_ imagePicker: ImagePickerController, images: [UIImage]) {
        self.dismiss(animated: true) {
            for image in images {
                guard let imageData = UIImageJPEGRepresentation(image, 0.6) else { return }
                
                let timestamp = NSDate.ows_millisecondsSince1970(for: Date())
                let outgoingMessage = TSOutgoingMessage(timestamp: timestamp, in: self.thread, messageBody: "")
                
                self.messageSender.sendAttachmentData(imageData, contentType: "image/jpeg", filename: "image.jpeg", in: outgoingMessage, success: {
                    print("Success")
                }, failure: { error in
                    print("Failure: \(error)")
                })
            }
        }
    }
    
    func wrapperDidPress(_ imagePicker: ImagePickerController, images: [UIImage]) {
        
    }
}

extension ChatController: ChatsFloatingHeaderViewDelegate {
    
    func messagesFloatingView(_: ChatsFloatingHeaderView, didPressRequestButton _: UIButton) {
        let paymentRequestController = PaymentRequestController()
        paymentRequestController.delegate = self
        self.present(paymentRequestController, animated: true)
    }
    
    func messagesFloatingView(_: ChatsFloatingHeaderView, didPressPayButton _: UIButton) {
        let paymentSendController = PaymentSendController()
        paymentSendController.delegate = self

        self.present(paymentSendController, animated: true)
    }
}

extension ChatController: PaymentSendControllerDelegate {
    
    func paymentSendControllerDidFinish(valueInWei: NSDecimalNumber?) {
        defer {
            self.dismiss(animated: true)
        }
        
        guard let value = valueInWei else {
            return
        }
        
        // TODO: prevent concurrent calls
        // Also, extract this.
        guard let tokenId = self.thread.contactIdentifier() else {
            return
        }
        
        self.idAPIClient.retrieveContact(username: tokenId) { user in
            guard let user = user else { return }

            self.etherAPIClient.createUnsignedTransaction(to: user.paymentAddress, value: value) { transaction, error in
                let signedTransaction = "0x\(Cereal.shared.signWithWallet(hex: transaction!))"

                self.etherAPIClient.sendSignedTransaction(originalTransaction: transaction!, transactionSignature: signedTransaction) { json, error in
                    if error != nil {
                        guard let json = json?.dictionary else { fatalError("!") }

                        let alert = UIAlertController.dismissableAlert(title: "Error completing transaction", message: json["message"] as? String)
                        self.present(alert, animated: true)
                    } else if let json = json?.dictionary {
                        guard let txHash = json["tx_hash"] as? String else { fatalError("Error recovering transaction hash.") }
                        let payment = SofaPayment(txHash: txHash, valueHex: value.toHexString)
                        self.sendMessage(sofaWrapper: payment)
                    }
                }
            }
        }
    }
}

extension ChatController: PaymentRequestControllerDelegate {

    func paymentRequestControllerDidFinish(valueInWei: NSDecimalNumber?) {
        defer {
            self.dismiss(animated: true)
        }

        guard let valueInWei = valueInWei else {
            return
        }

        let request: [String: Any] = [
            "body": "Payment request: \(EthereumConverter.balanceAttributedString(forWei: valueInWei).string).",
            "value": valueInWei.toHexString,
            "destinationAddress": Cereal.shared.paymentAddress,
        ]

        let paymentRequest = SofaPaymentRequest(content: request)

        self.sendMessage(sofaWrapper: paymentRequest)
    }
}
