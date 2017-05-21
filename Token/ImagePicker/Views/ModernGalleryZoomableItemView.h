#import "ModernGalleryItemView.h"

@class ModernGalleryZoomableScrollView;

@interface ModernGalleryZoomableItemView : ModernGalleryItemView

@property (nonatomic, strong) UIView *containerView;
@property (nonatomic, strong) ModernGalleryZoomableScrollView *scrollView;

- (CGSize)contentSize;
- (UIView *)contentView;
- (UIView *)transitionContentView;

- (void)reset;

- (void)forceUpdateLayout;

@end
