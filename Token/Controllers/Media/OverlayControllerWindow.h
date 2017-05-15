#import <UIKit/UIKit.h>

@class ViewController;
@class OverlayController;

@interface OverlayWindowViewController : UIViewController

@end

@interface OverlayControllerWindow : UIWindow

@property (nonatomic) bool keepKeyboard;
@property (nonatomic) bool dismissByMenuSheet;

- (instancetype)initWithParentController:(UIViewController *)parentController contentController:(UIViewController *)contentController
NS_SWIFT_NAME(init(parentController:contentController:));


- (instancetype)initWithParentController:(ViewController *)parentController contentController:(OverlayController *)contentController keepKeyboard:(bool)keepKeyboard
NS_SWIFT_NAME(init(parentController:contentController:keepKeyboard:));

- (void)dismiss;

@end
