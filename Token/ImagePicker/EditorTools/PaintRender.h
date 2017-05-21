#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class PaintPath;

@interface PaintRenderState : NSObject

- (void)reset;

@end

@interface PaintRender : NSObject

+ (CGRect)renderPath:(PaintPath *)path renderState:(PaintRenderState *)renderState;

@end
