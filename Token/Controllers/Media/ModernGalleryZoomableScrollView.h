#import <UIKit/UIKit.h>

@interface ModernGalleryZoomableScrollView : UIScrollView

@property (nonatomic) CGFloat normalZoomScale;

@property (nonatomic, copy) void (^singleTapped)();
@property (nonatomic, copy) void (^doubleTapped)(CGPoint point);

@end
