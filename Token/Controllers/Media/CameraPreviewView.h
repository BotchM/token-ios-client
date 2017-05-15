#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@class Camera;

@interface CameraPreviewView : UIView

@property (nonatomic, readonly) Camera *camera;
@property (nonatomic, readonly) AVCaptureConnection *captureConnection;

- (void)setupWithCamera:(Camera *)camera;
- (void)invalidate;

- (void)beginTransitionWithSnapshotImage:(UIImage *)image animated:(bool)animated;
- (void)endTransitionAnimated:(bool)animated;

- (void)beginResetTransitionAnimated:(bool)animated;
- (void)endResetTransitionAnimated:(bool)animated;

- (void)fadeInAnimated:(bool)animated;
- (void)fadeOutAnimated:(bool)animated;

- (CGPoint)devicePointOfInterestForPoint:(CGPoint)point;

@end
