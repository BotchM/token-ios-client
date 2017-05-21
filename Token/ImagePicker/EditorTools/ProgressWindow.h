#import <UIKit/UIKit.h>

@interface ProgressWindow : UIWindow

@property (nonatomic, assign) bool skipMakeKeyWindowOnDismiss;

- (void)show:(bool)animated;
- (void)showWithDelay:(NSTimeInterval)delay;

- (void)showAnimated;
- (void)dismiss:(bool)animated;
- (void)dismissWithSuccess;

@end

