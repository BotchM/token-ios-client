#import "PhotoEditorTabController.h"

@class CameraShotMetadata;
@class PhotoEditor;
@class PhotoEditorPreviewView;

@interface PhotoCropController : PhotoEditorTabController

@property (nonatomic, readonly) bool switching;
@property (nonatomic, readonly) UIImageOrientation cropOrientation;

@property (nonatomic, copy) void (^finishedPhotoProcessing)(void);
@property (nonatomic, copy) void (^cropReset)(void);

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView metadata:(CameraShotMetadata *)metadata forVideo:(bool)forVideo;

- (void)setAutorotationAngle:(CGFloat)autorotationAngle;

- (void)rotate;

- (void)setImage:(UIImage *)image;
- (void)setSnapshotImage:(UIImage *)snapshotImage;
- (void)setSnapshotView:(UIView *)snapshotView;

@end
