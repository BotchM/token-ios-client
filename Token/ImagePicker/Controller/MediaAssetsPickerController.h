#import "MediaPickerController.h"
#import "MediaAssetsController.h"

@class MediaAssetsPreheatMixin;
@class MediaPickerModernGalleryMixin;

@interface MediaAssetsPickerController : MediaPickerController
{
    MediaAssetsPreheatMixin *_preheatMixin;
}

@property (nonatomic, assign) bool liveVideoUploadEnabled;
@property (nonatomic, readonly) MediaAssetGroup *assetGroup;

- (instancetype)initWithAssetsLibrary:(MediaAssetsLibrary *)assetsLibrary assetGroup:(MediaAssetGroup *)assetGroup intent:(MediaAssetsControllerIntent)intent selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext;

@end
