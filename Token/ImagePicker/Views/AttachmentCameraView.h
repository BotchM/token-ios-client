#import <UIKit/UIKit.h>

@class CameraPreviewView;

@interface AttachmentCameraView : UIView

@property (nonatomic, copy) void (^pressed)(void);

- (instancetype)initForSelfPortrait:(bool)selfPortrait;

@property (nonatomic, readonly) bool previewViewAttached;
- (void)detachPreviewView;
- (void)attachPreviewViewAnimated:(bool)animated;
- (void)willAttachPreviewView;

- (void)startPreview;
- (void)stopPreview;
- (void)resumePreview;
- (void)pausePreview;

- (void)setZoomedProgress:(CGFloat)progress;

- (CameraPreviewView *)previewView;

@end
