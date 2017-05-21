#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ViewController;

@interface OverlayFormsheetWindow : UIWindow

- (instancetype)initWithParentController:(ViewController *)parentController contentController:(UIViewController *)contentController;

- (void)showAnimated:(bool)animated;
- (void)dismissAnimated:(bool)animated;

@end
