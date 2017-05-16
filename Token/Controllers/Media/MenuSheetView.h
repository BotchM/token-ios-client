#import "MenuSheetItemView.h"

@interface MenuSheetScrollView : UIScrollView

@end

@interface MenuSheetView : UIView

@property (nonatomic, readonly) NSArray *itemViews;

@property (nonatomic, readonly) UIEdgeInsets edgeInsets;
@property (nonatomic, readonly) CGFloat interSectionSpacing;

@property (nonatomic, assign) CGFloat menuWidth;
@property (nonatomic, readonly) CGFloat menuHeight;
@property (nonatomic, readonly) CGSize menuSize;
@property (nonatomic, assign) CGFloat maxHeight;

@property (nonatomic, assign) CGFloat keyboardOffset;

@property (nonatomic, readonly) NSValue *mainFrame;
@property (nonatomic, readonly) NSValue *headerFrame;
@property (nonatomic, readonly) NSValue *footerFrame;

@property (nonatomic, copy) bool (^tapDismissalAllowed)(void);

@property (nonatomic, copy) void (^menuRelayout)(void);

@property (nonatomic, copy) void (^handleInternalPan)(UIPanGestureRecognizer *);

- (instancetype)initWithItemViews:(NSArray *)itemViews sizeClass:(UIUserInterfaceSizeClass)sizeClass;

- (void)menuWillAppearAnimated:(bool)animated;
- (void)menuDidAppearAnimated:(bool)animated;
- (void)menuWillDisappearAnimated:(bool)animated;
- (void)menuDidDisappearAnimated:(bool)animated;

- (void)updateTraitsWithSizeClass:(UIUserInterfaceSizeClass)sizeClass;

- (CGRect)activePanRect;
- (bool)passPanOffset:(CGFloat)offset;

- (void)didChangeAbsoluteFrame;

@end

extern const UIEdgeInsets MenuSheetPhoneEdgeInsets;
extern const CGFloat MenuSheetCornerRadius;
extern const bool MenuSheetUseEffectView;