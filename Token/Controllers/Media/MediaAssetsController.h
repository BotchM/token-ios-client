
#import "MediaAssetsLibrary.h"
#import "SuggestionContext.h"

@class MediaAssetsPickerController;

typedef NS_ENUM(NSUInteger, MediaAssetsControllerIntent) {
    MediaAssetsControllerIntentSendMedia,
    MediaAssetsControllerIntentSendFile,
    MediaAssetsControllerIntentSetProfilePhoto,
    MediaAssetsControllerIntentSetCustomWallpaper
}NS_SWIFT_NAME(MediaAssetsControllerIntent);

@interface MediaAssetsController : UINavigationController

@property (nonatomic, strong) SuggestionContext *suggestionContext;
@property (nonatomic, assign) bool localMediaCacheEnabled;
@property (nonatomic, assign) bool captionsEnabled;
@property (nonatomic, assign) bool inhibitDocumentCaptions;
@property (nonatomic, assign) bool shouldStoreAssets;

@property (nonatomic, strong, readonly) NSMutableArray *selectedItems;

@property (nonatomic, assign) bool liveVideoUploadEnabled;
@property (nonatomic, assign) bool shouldShowFileTipIfNeeded;

@property (nonatomic, copy) NSDictionary *(^descriptionGenerator)(id, NSString *, NSString *);
@property (nonatomic, copy) void (^avatarCompletionBlock)(UIImage *image);
@property (nonatomic, copy) void (^completionBlock)(NSArray *signals);
@property (nonatomic, copy) void (^dismissalBlock)(void);

@property (nonatomic, readonly) MediaAssetsPickerController *pickerController;

- (UIBarButtonItem *)rightBarButtonItem;

+ (NSMutableArray <UIImage *> *)selectedItemmsss;

- (NSArray *)resultSignalsWithCurrentItem:(MediaAsset *)currentItem descriptionGenerator:(id (^)(id, NSString *, NSString *))descriptionGenerator;

- (void)completeWithAvatarImage:(UIImage *)image;
- (void)completeWithCurrentItem:(MediaAsset *)currentItem;

+ (instancetype)controllerWithAssetGroup:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent;

- (instancetype)initWithAssetGroup:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent
NS_SWIFT_NAME(init(assetGroup:intent:));

+ (MediaAssetType)assetTypeForIntent:(MediaAssetsControllerIntent)intent;

+ (NSArray *)resultSignalsForSelectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext intent:(MediaAssetsControllerIntent)intent currentItem:(MediaAsset *)currentItem storeAssets:(bool)storeAssets useMediaCache:(bool)useMediaCache descriptionGenerator:(id (^)(id, NSString *, NSString *))descriptionGenerator;

@end
