#import <UIKit/UIKit.h>

#import "ModernGalleryInterfaceView.h"

@class ModernGalleryScrollView;

@interface ModernGalleryView : UIView

@property (nonatomic, copy) bool (^transitionOut)(CGFloat velocity);

@property (nonatomic, strong, readonly) UIView<ModernGalleryInterfaceView> *interfaceView;
@property (nonatomic, strong, readonly) ModernGalleryScrollView *scrollView;

@property (nonatomic, copy) void (^closePressed)();

- (instancetype)initWithFrame:(CGRect)frame itemPadding:(CGFloat)itemPadding interfaceView:(UIView<ModernGalleryInterfaceView> *)interfaceView previewMode:(bool)previewMode previewSize:(CGSize)previewSize;

- (bool)shouldAutorotate;

- (void)showHideInterface;
- (void)hideInterfaceAnimated;
- (void)updateInterfaceVisibility;

- (void)addItemHeaderView:(UIView *)itemHeaderView;
- (void)removeItemHeaderView:(UIView *)itemHeaderView;
- (void)addItemFooterView:(UIView *)itemFooterView;
- (void)removeItemFooterView:(UIView *)itemFooterView;

- (void)simpleTransitionOutWithVelocity:(CGFloat)velocity completion:(void (^)())completion;
- (void)transitionInWithDuration:(NSTimeInterval)duration;
- (void)transitionOutWithDuration:(NSTimeInterval)duration;

- (void)fadeOutWithDuration:(NSTimeInterval)duration completion:(void (^)(void))completion;

- (void)setScrollViewVerticalOffset:(CGFloat)offset;

- (void)setPreviewMode:(bool)previewMode;

@end
