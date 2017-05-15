#import <UIKit/UIKit.h>

@interface DoubleTapGestureRecognizer : UIGestureRecognizer

@property (nonatomic) bool consumeSingleTap;
@property (nonatomic) bool doubleTapped;
@property (nonatomic) bool longTapped;
@property (nonatomic) bool avoidControls;

- (bool)canScrollViewStealTouches;

@end

@protocol DoubleTapGestureRecognizerDelegate <NSObject>

@optional

- (int)gestureRecognizer:(DoubleTapGestureRecognizer *)recognizer shouldFailTap:(CGPoint)point;
- (void)gestureRecognizer:(DoubleTapGestureRecognizer *)recognizer shouldBeginAtPoint:(CGPoint)point;
- (void)gestureRecognizer:(DoubleTapGestureRecognizer *)recognizer didBeginAtPoint:(CGPoint)point;
- (void)gestureRecognizerDidFail:(DoubleTapGestureRecognizer *)recognizer;
- (bool)gestureRecognizerShouldHandleLongTap:(DoubleTapGestureRecognizer *)recognizer;
- (void)doubleTapGestureRecognizerSingleTapped:(DoubleTapGestureRecognizer *)recognizer;
- (bool)gestureRecognizerShouldLetScrollViewStealTouches:(DoubleTapGestureRecognizer *)recognizer;
- (bool)gestureRecognizerShouldFailOnMove:(DoubleTapGestureRecognizer *)recognizer;

@end
