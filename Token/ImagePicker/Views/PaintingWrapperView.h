#import <UIKit/UIKit.h>

@interface PaintingWrapperView : UIView

@property (nonatomic, copy) bool (^shouldReceiveTouch)(void);

@end
