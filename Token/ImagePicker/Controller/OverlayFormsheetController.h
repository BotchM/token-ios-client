#import <UIKit/UIKit.h>

@class OverlayFormsheetWindow;

@interface OverlayFormsheetController : UIViewController

@property (nonatomic, weak) OverlayFormsheetWindow *formSheetWindow;
@property (nonatomic, readonly) UIViewController *viewController;

- (instancetype)initWithContentController:(UIViewController *)viewController;
- (void)setContentController:(UIViewController *)viewController;

- (void)animateInWithCompletion:(void (^)(void))completion;
- (void)animateOutWithCompletion:(void (^)(void))completion;

@end
