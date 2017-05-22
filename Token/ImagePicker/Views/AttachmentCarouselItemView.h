#import "MenuSheetItemView.h"
#import "MediaAsset.h"
#import "OverlayController.h"

@class MediaSelectionContext;
@class MediaEditingContext;
@class SuggestionContext;
@class ViewController;
@class AttachmentCameraView;

@interface AttachmentCarouselCollectionView : UICollectionView

@end

@interface AttachmentCarouselItemView : MenuSheetItemView

@property (nonatomic, weak) OverlayController *parentController;

@property (nonatomic, readonly) MediaSelectionContext *selectionContext;
@property (nonatomic, readonly) MediaEditingContext *editingContext;
@property (nonatomic, strong) SuggestionContext *suggestionContext;
@property (nonatomic) bool allowCaptions;
@property (nonatomic) bool inhibitDocumentCaptions;

@property (nonatomic, strong) NSArray *underlyingViews;
@property (nonatomic, assign) bool openEditor;

@property (nonatomic, copy) void (^cameraPressed)(AttachmentCameraView *cameraView);
@property (nonatomic, copy) void (^sendPressed)(MediaAsset *currentItem, bool asFiles);
@property (nonatomic, copy) void (^avatarCompletionBlock)(UIImage *image);

@property (nonatomic, copy) void (^editorOpened)(void);
@property (nonatomic, copy) void (^editorClosed)(void);
@property (nonatomic, copy) void (^didSelectImage)(UIImage *, MediaAsset *asset, UIView *fromView);

@property (nonatomic, assign) CGFloat remainingHeight;
@property (nonatomic, assign) bool condensed;

- (instancetype)initWithCamera:(bool)hasCamera selfPortrait:(bool)selfPortrait forProfilePhoto:(bool)forProfilePhoto assetType:(MediaAssetType)assetType
NS_SWIFT_NAME(init(camera:selfPortrait:forProfilePhoto:assetType:));

- (void)updateVisibleItems;
- (void)updateCameraView;

@end
