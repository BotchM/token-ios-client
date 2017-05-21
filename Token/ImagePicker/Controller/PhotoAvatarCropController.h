#import "PhotoEditorTabController.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;

@interface PhotoAvatarCropController : PhotoEditorTabController

@property (nonatomic, readonly) UIView *transitionParentView;

@property (nonatomic, assign) bool switching;
@property (nonatomic, assign) bool skipTransitionIn;
@property (nonatomic, assign) bool fromCamera;

@property (nonatomic, copy) void (^finishedPhotoProcessing)(void);

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView;

- (void)setImage:(UIImage *)image;
- (void)setSnapshotImage:(UIImage *)snapshotImage;
- (void)setSnapshotView:(UIView *)snapshotView;

- (void)_finishedTransitionIn;

@end
