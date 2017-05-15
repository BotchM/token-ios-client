#import "MediaAssetsPickerController.h"
#import "MediaAssetsMomentsController.h"
#import "MediaGroupsController.h"
//#import "TGWebSearchController.h"
//#import "TGGenericModernConversationCompanion.h"
#import "Common.h"
#import "MediaAssetMomentList.h"

//#import "TGAppDelegate.h"
#import "FileUtils.h"
#import "ImageUtils.h"
#import "PhotoEditorUtils.h"
#import "PaintUtils.h"
#import "UIImage+TG.h"
//#import "TGGifConverter.h"
#import <CommonCrypto/CommonDigest.h>

//#import "TGNavigationBar.h"
//#import "ModernBarButton.h"
#import "MediaPickerToolbarView.h"
//#import "MediaAssetsTipView.h"

//#import "MediaAsset+MediaEditableItem.h"
#import "MediaAssetImageSignals.h"
//
//#import "ImageDownloadActor.h"

#import "PhotoEditorController.h"

#import "VideoEditAdjustments.h"
#import "PaintingData.h"

@interface MediaAssetsController () <UINavigationControllerDelegate>
{
    MediaAssetsControllerIntent _intent;
    
    MediaPickerToolbarView *_toolbarView;
    MediaSelectionContext *_selectionContext;
    MediaEditingContext *_editingContext;
    
    SMetaDisposable *_selectionChangedDisposable;
    UIView *_searchSnapshotView;
}

@property (nonatomic, readonly) MediaAssetsLibrary *assetsLibrary;

@end

@implementation MediaAssetsController

+ (NSMutableArray <UIImage *> *)selectedItemmsss
{
    static NSMutableArray <UIImage *> *items = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        items = [[NSMutableArray alloc] init];
    });
    return items;
}

+ (instancetype)controllerWithAssetGroup:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent
{
    return [MediaAssetsController __commonInitWith:assetGroup intent:intent];
}

- (instancetype)initWithAssetGroup:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent
{
    return [MediaAssetsController __commonInitWith:assetGroup intent:intent];
}

+ (MediaAssetsController *)__commonInitWith:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent
{
    MediaAssetsController *assetsController = [[MediaAssetsController alloc] initWithIntent:intent];
    
    __weak MediaAssetsController *weakController = assetsController;
    void (^catchToolbarView)(bool) = ^(bool enabled)
    {
        __strong MediaAssetsController *strongController = weakController;
        if (strongController == nil)
            return;
        
        UIView *toolbarView = strongController->_toolbarView;
        if (enabled)
        {
            if (toolbarView.superview != strongController.view)
                return;
            
            [strongController.pickerController.view addSubview:toolbarView];
        }
        else
        {
            if (toolbarView.superview == strongController.view)
                return;
            
            [strongController.view addSubview:toolbarView];
        }
    };
    
    MediaGroupsController *groupsController = [[MediaGroupsController alloc] initWithAssetsLibrary:assetsController.assetsLibrary intent:intent];
    groupsController.openAssetGroup = ^(id group)
    {
        __strong MediaAssetsController *strongController = weakController;
        if (strongController == nil)
            return;
        
        MediaAssetsPickerController *pickerController = nil;
        
        if ([group isKindOfClass:[MediaAssetGroup class]])
        {
            pickerController = [[MediaAssetsPickerController alloc] initWithAssetsLibrary:strongController.assetsLibrary assetGroup:group intent:intent selectionContext:strongController->_selectionContext editingContext:strongController->_editingContext];
        }
        else if ([group isKindOfClass:[MediaAssetMomentList class]])
        {
            pickerController = [[MediaAssetsMomentsController alloc] initWithAssetsLibrary:strongController.assetsLibrary momentList:group intent:intent selectionContext:strongController->_selectionContext editingContext:strongController->_editingContext];
        }
        pickerController.suggestionContext = strongController.suggestionContext;
        pickerController.localMediaCacheEnabled = strongController.localMediaCacheEnabled;
        pickerController.captionsEnabled = strongController.captionsEnabled;
        pickerController.inhibitDocumentCaptions = strongController.inhibitDocumentCaptions;
        pickerController.liveVideoUploadEnabled = strongController.liveVideoUploadEnabled;
        pickerController.catchToolbarView = catchToolbarView;
        [strongController pushViewController:pickerController animated:true];
    };
    [groupsController loadViewIfNeeded];
    
    MediaAssetsPickerController *pickerController = [[MediaAssetsPickerController alloc] initWithAssetsLibrary:assetsController.assetsLibrary assetGroup:assetGroup intent:intent selectionContext:assetsController->_selectionContext editingContext:assetsController->_editingContext];
    pickerController.catchToolbarView = catchToolbarView;
    
    [groupsController setIsFirstInStack:true];
    [pickerController setIsFirstInStack:false];
    
    [assetsController setViewControllers:@[groupsController, pickerController]];
    return assetsController;
}

- (void)setSuggestionContext:(SuggestionContext *)suggestionContext
{
    _suggestionContext = suggestionContext;
    self.pickerController.suggestionContext = suggestionContext;
}

- (void)setCaptionsEnabled:(bool)captionsEnabled
{
    _captionsEnabled = captionsEnabled;
    self.pickerController.captionsEnabled = captionsEnabled;
}

- (void)setInhibitDocumentCaptions:(bool)inhibitDocumentCaptions
{
    _inhibitDocumentCaptions = inhibitDocumentCaptions;
    self.pickerController.inhibitDocumentCaptions = inhibitDocumentCaptions;
}

- (void)setLiveVideoUploadEnabled:(bool)liveVideoUploadEnabled
{
    _liveVideoUploadEnabled = liveVideoUploadEnabled;
    self.pickerController.liveVideoUploadEnabled = liveVideoUploadEnabled;
}

- (void)setLocalMediaCacheEnabled:(bool)localMediaCacheEnabled
{
    _localMediaCacheEnabled = localMediaCacheEnabled;
    self.pickerController.localMediaCacheEnabled = localMediaCacheEnabled;
}

- (void)setShouldStoreAssets:(bool)shouldStoreAssets
{
    _shouldStoreAssets = shouldStoreAssets;
    self.pickerController.shouldStoreAssets = shouldStoreAssets;
}

- (MediaAssetsPickerController *)pickerController
{
    MediaAssetsPickerController *pickerController = nil;
    for (ViewController *viewController in self.viewControllers)
    {
        if ([viewController isKindOfClass:[MediaAssetsPickerController class]])
        {
            pickerController = (MediaAssetsPickerController *)viewController;
            break;
        }
    }
    return pickerController;
}

- (instancetype)initWithIntent:(MediaAssetsControllerIntent)intent
{
    self = [super initWithNavigationBarClass:[UINavigationBar class] toolbarClass:[UIToolbar class]];
    if (self != nil)
    {
        self.delegate = self;
        _intent = intent;
        _assetsLibrary = [MediaAssetsLibrary libraryForAssetType:[MediaAssetsController assetTypeForIntent:intent]];
        
        __weak MediaAssetsController *weakSelf = self;
        _selectionContext = [[MediaSelectionContext alloc] init];
        [_selectionContext setItemSourceUpdatedSignal:[_assetsLibrary libraryChanged]];
        _selectionContext.updatedItemsSignal = ^SSignal *(NSArray *items)
        {
            __strong MediaAssetsController *strongSelf = weakSelf;
            if (strongSelf == nil)
                return nil;
            
            return [strongSelf->_assetsLibrary updatedAssetsForAssets:items];
        };
        
        _selectionChangedDisposable = [[SMetaDisposable alloc] init];
        [_selectionChangedDisposable setDisposable:[[_selectionContext selectionChangedSignal] startWithNext:^(__unused id next)
        {
            __strong MediaAssetsController *strongSelf = weakSelf;
            if (strongSelf == nil)
                return;
            
            [strongSelf->_toolbarView setSelectedCount:strongSelf->_selectionContext.count animated:true];
            [strongSelf->_toolbarView setRightButtonEnabled:strongSelf->_selectionContext.count > 0 animated:false];
        }]];
        
        if (intent == MediaAssetsControllerIntentSendMedia || intent == MediaAssetsControllerIntentSetProfilePhoto)
            _editingContext = [[MediaEditingContext alloc] init];
        else if (intent == MediaAssetsControllerIntentSendFile)
            _editingContext = [MediaEditingContext contextForCaptionsOnly];
    }
    return self;
}

- (void)dealloc
{
    self.delegate = nil;
    [_selectionChangedDisposable dispose];
}

- (void)loadView
{
    [super loadView];
    
    _toolbarView = [[MediaPickerToolbarView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - MediaPickerToolbarHeight, self.view.frame.size.width, MediaPickerToolbarHeight)];
    _toolbarView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
    if (_intent != MediaAssetsControllerIntentSendFile && _intent != MediaAssetsControllerIntentSendMedia)
        [_toolbarView setRightButtonHidden:true];
    [self.view addSubview:_toolbarView];
}

- (void)viewDidLoad
{
    __weak MediaAssetsController *weakSelf = self;
    _toolbarView.leftPressed = ^
    {
        __strong MediaAssetsController *strongSelf = weakSelf;
        if (strongSelf == nil)
            return;
        
        [strongSelf dismiss];
    };
    
    _toolbarView.rightPressed = ^
    {
        __strong MediaAssetsController *strongSelf = weakSelf;
        if (strongSelf != nil)
            [strongSelf completeWithCurrentItem:nil];
    };
}

- (void)dismiss
{
    if (self.dismissalBlock != nil)
        self.dismissalBlock();
    
    [_editingContext clearPaintingData];
}


#pragma mark -

- (void)completeWithAvatarImage:(UIImage *)image
{
    if (self.avatarCompletionBlock != nil)
        self.avatarCompletionBlock(image);
}

- (void)completeWithCurrentItem:(MediaAsset *)currentItem
{
    [[MediaAssetsController selectedItemmsss] removeAllObjects];
    NSArray *assets = [_selectionContext selectedItems];
    
    for (MediaAsset *asset in assets) {
        
        [[MediaAssetImageSignals imageForAsset:asset imageType:MediaAssetImageTypeFullSize size:[UIScreen mainScreen].bounds.size] startWithNext:^(UIImage *next) {
            [[MediaAssetsController selectedItemmsss] addObject:next];
            
            if ([MediaAssetsController selectedItemmsss].count == assets.count) {
                if (self.completionBlock != nil)
                    self.completionBlock();
            }
        }];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    if (_intent == MediaAssetsControllerIntentSendFile && self.shouldShowFileTipIfNeeded && iosMajorVersion() >= 7)
    {
        if (![[[NSUserDefaults standardUserDefaults] objectForKey:@"didShowDocumentPickerTip_v2"] boolValue])
        {
            [[NSUserDefaults standardUserDefaults] setObject:@true forKey:@"didShowDocumentPickerTip_v2"];
            
//            MediaAssetsTipView *tipView = [[MediaAssetsTipView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.view.bounds.size.width, self.view.bounds.size.height)];
//            tipView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
//            [self.navigationController.view addSubview:tipView];
        }
    }
}

- (UIView *)_findBackArrow:(UIView *)view
{
    Class backArrowClass = NSClassFromString(TGEncodeText(@"`VJObwjhbujpoCbsCbdlJoejdbupsWjfx", -1));
    
    if ([view isKindOfClass:backArrowClass])
        return view;
    
    for (UIView *subview in view.subviews)
    {
        UIView *result = [self _findBackArrow:subview];
        if (result != nil)
            return result;
    }
    
    return nil;
}

- (UIView *)_findBackButton:(UIView *)view parentView:(UIView *)parentView
{
    Class backButtonClass = NSClassFromString(TGEncodeText(@"VJObwjhbujpoJufnCvuupoWjfx", -1));
    
    if ([view isKindOfClass:backButtonClass])
    {
        if (view.center.x < parentView.frame.size.width / 2.0f)
            return view;
    }
    
    for (UIView *subview in view.subviews)
    {
        UIView *result = [self _findBackButton:subview parentView:parentView];
        if (result != nil)
            return result;
    }
    
    return nil;
}

#pragma mark -

+ (MediaAssetType)assetTypeForIntent:(MediaAssetsControllerIntent)intent
{
    MediaAssetType assetType = MediaAssetAnyType;
    
    switch (intent)
    {
        case MediaAssetsControllerIntentSetProfilePhoto:
        case MediaAssetsControllerIntentSetCustomWallpaper:
            assetType = MediaAssetPhotoType;
            break;
            
        case MediaAssetsControllerIntentSendMedia:
            assetType = MediaAssetAnyType;
            break;
            
        default:
            break;
    }
    
    return assetType;
}

@end
