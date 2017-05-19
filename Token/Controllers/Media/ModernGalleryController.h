#import "OverlayController.h"

@class ModernGalleryModel;
@protocol ModernGalleryItem;
@class ModernGalleryItemView;

typedef enum {
    ModernGalleryScrollAnimationDirectionDefault,
    ModernGalleryScrollAnimationDirectionLeft,
    ModernGalleryScrollAnimationDirectionRight
} ModernGalleryScrollAnimationDirection;

@interface ModernGalleryController : OverlayController

@property (nonatomic) UIStatusBarStyle defaultStatusBarStyle;
@property (nonatomic) bool shouldAnimateStatusBarStyleTransition;

@property (nonatomic, strong) ModernGalleryModel *model;
@property (nonatomic, assign) bool animateTransition;
@property (nonatomic, assign) bool asyncTransitionIn;
@property (nonatomic, assign) bool showInterface;
@property (nonatomic, assign) bool adjustsStatusBarVisibility;
@property (nonatomic, assign) bool hasFadeOutTransition;
@property (nonatomic, assign) bool previewMode;
 
@property (nonatomic, copy) void (^itemFocused)(id<ModernGalleryItem>);
@property (nonatomic, copy) UIView *(^beginTransitionIn)(id<ModernGalleryItem>, ModernGalleryItemView *);
@property (nonatomic, copy) void (^startedTransitionIn)();
@property (nonatomic, copy) void (^finishedTransitionIn)(id<ModernGalleryItem>, ModernGalleryItemView *);
@property (nonatomic, copy) UIView *(^beginTransitionOut)(id<ModernGalleryItem>, ModernGalleryItemView *);
@property (nonatomic, copy) void (^completedTransitionOut)();

@property (nonatomic, copy) void (^completionBlock)();


- (NSArray *)visibleItemViews;
- (ModernGalleryItemView *)itemViewForItem:(id<ModernGalleryItem>)item;
- (id<ModernGalleryItem>)currentItem;

- (void)setCurrentItemIndex:(NSUInteger)index animated:(bool)animated;
- (void)setCurrentItemIndex:(NSUInteger)index direction:(ModernGalleryScrollAnimationDirection)direction animated:(bool)animated;

- (void)dismissWhenReady;

- (bool)isFullyOpaque;

@end
