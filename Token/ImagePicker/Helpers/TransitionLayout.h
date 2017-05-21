#import <UIKit/UIKit.h>
#import "UICollectionView+Transitioning.h"

@interface TransitionLayout : UICollectionViewTransitionLayout <TGTransitionAnimatorLayout>

@property (nonatomic) CGPoint toContentOffset;
@property (nonatomic, strong) void(^progressChanged)(CGFloat progress);
@property (nonatomic, strong) void(^transitionAlmostFinished)();

@end
