#import <UIKit/UIKit.h>
#import "Camera.h"

@interface CameraModeControl : UIControl

@property (nonatomic, copy) void(^modeChanged)(PGCameraMode mode, PGCameraMode previousMode);

@property (nonatomic, assign) PGCameraMode cameraMode;
- (void)setCameraMode:(PGCameraMode)mode animated:(bool)animated;

- (void)setHidden:(bool)hidden animated:(bool)animated;

@end
