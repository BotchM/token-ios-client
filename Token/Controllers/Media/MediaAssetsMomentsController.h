#import "MediaAssetsPickerController.h"

@class MediaAssetMomentList;

@interface MediaAssetsMomentsController : MediaAssetsPickerController

- (instancetype)initWithAssetsLibrary:(MediaAssetsLibrary *)assetsLibrary momentList:(MediaAssetMomentList *)momentList intent:(MediaAssetsControllerIntent)intent selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext;

@end
