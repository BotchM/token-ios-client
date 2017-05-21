#import <UIKit/UIKit.h>

@protocol ModernGalleryScrollViewDelegate <NSObject>

- (bool)scrollViewShouldScrollWithTouchAtPoint:(CGPoint)point;
- (void)scrollViewBoundsChanged:(CGRect)bounds;

@end

@interface ModernGalleryScrollView : UIScrollView

@property (nonatomic, weak) id<ModernGalleryScrollViewDelegate> scrollDelegate;

- (void)setFrameAndBoundsInTransaction:(CGRect)frame bounds:(CGRect)bounds;

@end
