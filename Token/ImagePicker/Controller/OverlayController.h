#import "ViewController.h"

@class OverlayControllerWindow;

@interface OverlayController : ViewController

@property (nonatomic, weak) OverlayControllerWindow *overlayWindow;
@property (nonatomic, assign) bool isImportant;

- (void)dismiss;

@end
