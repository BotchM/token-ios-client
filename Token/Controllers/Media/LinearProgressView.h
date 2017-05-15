#import <UIKit/UIKit.h>

@interface LinearProgressView : UIView

@property (nonatomic) CGFloat progress;
@property (nonatomic) bool alwaysShowMinimum;

- (id)initWithBackgroundImage:(UIImage *)backgroundImage progressImage:(UIImage *)progressImage;

- (void)setProgress:(CGFloat)progress animationDuration:(NSTimeInterval)animationDuration;

@end
