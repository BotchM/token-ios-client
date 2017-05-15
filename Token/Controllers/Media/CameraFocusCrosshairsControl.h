#import <UIKit/UIKit.h>

@class CameraPreviewView;

@interface CameraFocusCrosshairsControl : UIControl

@property (nonatomic, weak) CameraPreviewView *previewView;
@property (nonatomic, copy) void(^focusPOIChanged)(CGPoint point);

@property (nonatomic, copy) void(^beganExposureChange)(void);
@property (nonatomic, copy) void(^exposureChanged)(CGFloat value);
@property (nonatomic, copy) void(^endedExposureChange)(void);

@property (nonatomic, assign) bool stopAutomatically;
@property (nonatomic, assign) bool active;
@property (nonatomic, assign) bool ignoreAutofocusing;

- (void)playAutoFocusAnimation;
- (void)stopAutoFocusAnimation;

- (void)reset;

- (void)setInterfaceOrientation:(UIInterfaceOrientation)orientation animated:(bool)animated;

@end
