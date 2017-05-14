#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class PaintState;
@class PaintPanGestureRecognizer;

@interface PaintInput : NSObject

@property (nonatomic, assign) CGAffineTransform transform;

- (void)gestureBegan:(PaintPanGestureRecognizer *)recognizer;
- (void)gestureMoved:(PaintPanGestureRecognizer *)recognizer;
- (void)gestureEnded:(PaintPanGestureRecognizer *)recognizer;
- (void)gestureCanceled:(PaintPanGestureRecognizer *)recognizer;

@end
