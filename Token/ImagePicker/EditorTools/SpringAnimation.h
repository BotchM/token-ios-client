#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface SpringAnimation : NSObject

+ (CAKeyframeAnimation *)animationWithKeypath:(NSString *)keypath duration:(CFTimeInterval)duration usingSpringWithDamping:(CGFloat)usingSpringWithDamping initialSpringVelocity:(CGFloat)initialSpringVelocity fromPosition:(CGPoint)fromPosition toPosition:(CGPoint)toPosition;

@end
