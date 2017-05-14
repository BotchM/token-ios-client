#import <UIKit/UIKit.h>

@class Painting;
@class PaintBrush;
@class PaintState;

@interface PaintCanvas : UIView

@property (nonatomic, strong) Painting *painting;
@property (nonatomic, readonly) PaintState *state;

@property (nonatomic, assign) CGRect cropRect;
@property (nonatomic, assign) UIImageOrientation cropOrientation;
@property (nonatomic, assign) CGSize originalSize;

@property (nonatomic, copy) bool (^shouldDrawOnSingleTap)(void);

@property (nonatomic, copy) bool (^shouldDraw)(void);
@property (nonatomic, copy) void (^strokeBegan)(void);
@property (nonatomic, copy) void (^strokeCommited)(void);
@property (nonatomic, copy) UIView *(^hitTest)(CGPoint point, UIEvent *event);
@property (nonatomic, copy) bool (^pointInsideContainer)(CGPoint point);

@property (nonatomic, readonly) bool isTracking;

- (void)draw;

- (void)setBrush:(PaintBrush *)brush;
- (void)setBrushWeight:(CGFloat)brushWeight;
- (void)setBrushColor:(UIColor *)color;
- (void)setEraser:(bool)eraser;

@end
