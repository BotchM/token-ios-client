#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface PaintSwatch : NSObject

@property (nonatomic, readonly) UIColor *color;
@property (nonatomic, readonly) CGFloat colorLocaton;
@property (nonatomic, readonly) CGFloat brushWeight;

+ (instancetype)swatchWithColor:(UIColor *)color colorLocation:(CGFloat)colorLocation brushWeight:(CGFloat)brushWeight;

@end
