#import "OverlayControllerWindow.h"

#import "ViewController.h"
#import "OverlayController.h"

#import "Common.h"

//#import "TGAppDelegate.h"

@implementation OverlayWindowViewController

- (UIViewController *)statusBarAppearanceSourceController
{
    
    UIViewController *topViewController = nil;// TGAppDelegateInstance.rootController.viewControllers.lastObject;
    
    if ([topViewController isKindOfClass:[UITabBarController class]])
        topViewController = [(UITabBarController *)topViewController selectedViewController];
    if ([topViewController isKindOfClass:[ViewController class]])
    {
        ViewController *concreteTopViewController = (ViewController *)topViewController;
        if (concreteTopViewController.associatedWindowStack.count != 0)
        {
            for (UIWindow *window in concreteTopViewController.associatedWindowStack.reverseObjectEnumerator)
            {
                if (window.rootViewController != nil && window.rootViewController != self)
                {
                    topViewController = window.rootViewController;
                    break;
                }
            }
        }
    }
    
    return topViewController;
}

//- (UIViewController *)autorotationSourceController
//{
//    UIViewController *topViewController = TGAppDelegateInstance.rootController.viewControllers.lastObject;
//    
//    if ([topViewController isKindOfClass:[UITabBarController class]])
//        topViewController = [(UITabBarController *)topViewController selectedViewController];
//    
//    return topViewController;
//}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    UIStatusBarStyle style = [[self statusBarAppearanceSourceController] preferredStatusBarStyle];
    return style;
}

- (BOOL)prefersStatusBarHidden
{
    bool value = [[self statusBarAppearanceSourceController] prefersStatusBarHidden];
    return value;
}

- (BOOL)shouldAutorotate
{
    static NSArray *nonRotateableWindowClasses = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
    {
        NSMutableArray *array = [[NSMutableArray alloc] init];
        Class alertClass = NSClassFromString(TGEncodeText(@"`VJBmfsuPwfsmbzXjoepx", -1));
        if (alertClass != nil)
            [array addObject:alertClass];
        
        nonRotateableWindowClasses = array;
    });
    
    for (UIWindow *window in [UIApplication sharedApplication].windows.reverseObjectEnumerator)
    {
        for (Class classInfo in nonRotateableWindowClasses)
        {
            if ([window isKindOfClass:classInfo])
                return false;
        }
    }
//    
//    if (TGAppDelegateInstance.rootController.presentedViewController != nil)
//        return [TGAppDelegateInstance.rootController.presentedViewController shouldAutorotate];
    
//    if ([self autorotationSourceController] != nil)
//        return [[self autorotationSourceController] shouldAutorotate];
    
    return true;
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [super willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
    
    [self.view.window.layer removeAnimationForKey:@"backgroundColor"];
    [CATransaction begin];
    [CATransaction setDisableActions:true];
    self.view.window.layer.backgroundColor = [UIColor clearColor].CGColor;
    [CATransaction commit];
    
    for (UIView *view in self.view.window.subviews)
    {
        if (view != self.view)
        {
            [view removeFromSuperview];
            break;
        }
    }
}

- (void)loadView
{
    [super loadView];
    
    self.view.userInteractionEnabled = false;
    self.view.opaque = false;
    self.view.backgroundColor = [UIColor clearColor];
}

@end


@interface OverlayControllerWindow ()
{
    __weak ViewController *_parentController;
}

@end

@implementation OverlayControllerWindow

- (instancetype)initWithParentController:(ViewController *)parentController contentController:(OverlayController *)contentController
{
    return [self initWithParentController:parentController contentController:contentController keepKeyboard:false];
}

- (instancetype)initWithParentController:(ViewController *)parentController contentController:(OverlayController *)contentController keepKeyboard:(bool)keepKeyboard
{
    _keepKeyboard = keepKeyboard;
    
    self = [super initWithFrame:[UIScreen mainScreen].bounds];
    if (self != nil)
    {
        self.windowLevel = UIWindowLevelStatusBar - 0.001f;
        
        _parentController = parentController;
        //[parentController.associatedWindowStack addObject:self];
        
        contentController.overlayWindow = self;
        self.rootViewController = contentController;
    }
    return self;
}

- (void)dealloc
{

}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    return [super hitTest:point withEvent:event];
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    if (iosMajorVersion() < 8 && !self.hidden)
        return true;
    
    return [super pointInside:point withEvent:event];
}

- (void)dismiss
{
    ViewController *parentController = _parentController;
    [parentController.associatedWindowStack removeObject:self];
    [self.rootViewController viewWillDisappear:false];
    self.hidden = true;
    [self.rootViewController viewDidDisappear:false];
    self.rootViewController = nil;
}

- (void)setHidden:(BOOL)hidden {
    [super setHidden:hidden];
    
//    if (!hidden && !_keepKeyboard)
//        [TGAppDelegateInstance.window endEditing:true];
}

@end
