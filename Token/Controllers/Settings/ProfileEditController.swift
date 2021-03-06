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
import SweetFoundation
import Formulaic
import ImagePicker

/// Edit user profile info. It's sent to the ID server on saveAndDismiss. Updates local session as well.
open class ProfileEditController: UIViewController {

    lazy var dataSource: FormDataSource = {
        let dataSource = FormDataSource(delegate: nil)
        let usernameValidator = TextInputValidator(minLength: 2, maxLength: 60, validationPattern: IDAPIClient.usernameValidationPattern)

        dataSource.items = [
            FormItem(title: "Username", value: TokenUser.current?.username, fieldName: "username", type: .input, textInputValidator: usernameValidator),
            FormItem(title: "Display name", value: TokenUser.current?.name, fieldName: "name", type: .input),
            FormItem(title: "About", value: TokenUser.current?.about, fieldName: "about", type: .input),
            FormItem(title: "Location", value: TokenUser.current?.location, fieldName: "location", type: .input),
        ]

        return dataSource
    }()

    fileprivate var idAPIClient: IDAPIClient {
        return IDAPIClient.shared
    }

    fileprivate lazy var avatarImageView: AvatarImageView = {
        let view = AvatarImageView(withAutoLayout: true)

        return view
    }()

    fileprivate lazy var changeAvatarButton: UIButton = {
        let view = UIButton(withAutoLayout: true)

        let title = NSAttributedString(string: "Change picture", attributes: [NSForegroundColorAttributeName: Theme.tintColor, NSFontAttributeName: Theme.regular(size: 16)])
        view.setAttributedTitle(title, for: .normal)
        view.addTarget(self, action: #selector(updateAvatar), for: .touchUpInside)

        return view
    }()

    fileprivate lazy var tableView: UITableView = {
        let view = UITableView(withAutoLayout: true)
        view.delegate = self
        view.dataSource = self
        view.separatorStyle = .none
        view.register(ProfileItemCell.self)
        view.layer.borderWidth = Theme.borderHeight
        view.layer.borderColor = Theme.borderColor.cgColor
        view.alwaysBounceVertical = true

        return view
    }()

    open override var canBecomeFirstResponder: Bool {
        return true
    }

    open override func viewDidLoad() {
        super.viewDidLoad()

        self.view.backgroundColor = Theme.navigationBarColor
        self.addSubviewsAndConstraints()

        guard let user = TokenUser.current else { return }
        self.avatarImageView.image = user.avatar

        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(self.didTapView))
        self.view.addGestureRecognizer(tapGesture)

        self.navigationItem.leftBarButtonItem = UIBarButtonItem(barButtonSystemItem: .cancel, target: self, action: #selector(self.cancelAndDismiss))
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(self.saveAndDismiss))
    }

    func addSubviewsAndConstraints() {
        self.view.addSubview(self.avatarImageView)
        self.view.addSubview(self.changeAvatarButton)
        self.view.addSubview(self.tableView)

        self.avatarImageView.set(height: 80)
        self.avatarImageView.set(width: 80)
        self.avatarImageView.topAnchor.constraint(equalTo: self.topLayoutGuide.bottomAnchor, constant: 24).isActive = true
        self.avatarImageView.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true

        self.changeAvatarButton.set(height: 38)
        self.changeAvatarButton.topAnchor.constraint(equalTo: self.avatarImageView.bottomAnchor, constant: 12).isActive = true
        self.changeAvatarButton.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true

        self.tableView.topAnchor.constraint(equalTo: self.changeAvatarButton.bottomAnchor, constant: 24).isActive = true
        self.tableView.leftAnchor.constraint(equalTo: self.view.leftAnchor).isActive = true
        self.tableView.rightAnchor.constraint(equalTo: self.view.rightAnchor).isActive = true
        self.tableView.bottomAnchor.constraint(equalTo: self.view.bottomAnchor).isActive = true
    }

    func updateAvatar() {
        let picker = ImagePickerController()
        picker.delegate = self
        picker.configuration.allowMultiplePhotoSelection = false

        self.present(picker, animated: true)
    }

    func cancelAndDismiss() {
        self.navigationController?.popViewController(animated: true)
    }

    func saveAndDismiss() {
        guard let user = TokenUser.current else { return }

        var username: String?
        var name: String?
        var about: String?
        var location: String?

        for item in self.dataSource.items {
            if item.fieldName == "username" {
                if item.validate() {
                    username = item.value as? String ?? TokenUser.current!.username
                } else {
                    let alert = UIAlertController.dismissableAlert(title: "Error", message: "Username is invalid! Use numbers, letters, and underscores only.")
                    self.present(alert, animated: true)
                    return
                }
            } else if item.fieldName == "name" {
                name = item.value as? String ?? ""
            } else if item.fieldName == "about" {
                about = item.value as? String ?? ""
            } else if item.fieldName == "location" {
                location = item.value as? String ?? ""
            }
        }

        user.update(username: username, name: name, about: about, location: location)

        self.idAPIClient.updateUser(user) { success, message in
            if !success {
                let alert = UIAlertController.dismissableAlert(title: "Error", message: message)
                self.present(alert, animated: true)
            } else {
                self.navigationController?.popViewController(animated: true)
            }
        }
    }

    @objc private func didTapView(sender: UITapGestureRecognizer) {
        if sender.state == .recognized {
            self.becomeFirstResponder()
        }
    }
}

extension ProfileEditController: ImagePickerDelegate {

    public func wrapperDidPress(_: ImagePickerController, images _: [UIImage]) {
    }

    public func doneButtonDidPress(_: ImagePickerController, images: [UIImage]) {
        defer { self.dismiss(animated: true) }
        guard let image = images.first else { return }

        let scaledImage = image.resized(toHeight: 320)

        self.idAPIClient.updateAvatar(scaledImage) { _ in
            self.avatarImageView.image = scaledImage
        }
    }

    public func cancelButtonDidPress(_: ImagePickerController) {
        self.dismiss(animated: true)
    }
}

extension ProfileEditController: UITableViewDelegate {

    public func tableView(_: UITableView, estimatedHeightForRowAt _: IndexPath) -> CGFloat {
        return UITableViewAutomaticDimension
    }

    public func tableView(_: UITableView, heightForRowAt _: IndexPath) -> CGFloat {
        return UITableViewAutomaticDimension
    }
}

extension ProfileEditController: UITableViewDataSource {

    public func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        return self.dataSource.count
    }

    public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeue(ProfileItemCell.self, for: indexPath)
        let formItem = self.dataSource.item(at: indexPath)
        cell.selectionStyle = UITableViewCellSelectionStyle.none
        cell.formItem = formItem

        return cell
    }
}
