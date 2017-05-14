#import <UIKit/UIKit.h>

@interface PaintPanGestureRecognizer : UIPanGestureRecognizer

@property (nonatomic, copy) bool (^shouldRecognizeTap)(void);
@property (nonatomic) NSSet *touches;

@end
