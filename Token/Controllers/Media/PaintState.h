#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class PaintBrush;

@interface PaintState : NSObject

@property (nonatomic, strong) UIColor *color;
@property (nonatomic, assign, getter=isEraser) bool eraser;
@property (nonatomic, assign) CGFloat weight;
@property (nonatomic, strong) PaintBrush *brush;

@end
