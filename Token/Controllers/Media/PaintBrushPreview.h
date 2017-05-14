#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

@class Painting;
@class PaintBrush;

@interface PaintBrushPreview : NSObject

- (UIImage *)imageForBrush:(PaintBrush *)brush size:(CGSize)size;

@end
