#import <UIKit/UIKit.h>

#import "ASWatcher.h"

@interface MenuButtonView : UIButton
@end

@interface MenuView : UIView

@property (nonatomic, assign) bool buttonHighlightDisabled;

@property (nonatomic, strong) NSDictionary *userInfo;
@property (nonatomic, assign) bool multiline;
@property (nonatomic, assign) bool forceArrowOnTop;
@property (nonatomic, assign) CGFloat maxWidth;

- (void)setButtonsAndActions:(NSArray *)buttonsAndActions watcherHandle:(ASHandle *)watcherHandle;

- (void)sizeToFitToWidth:(CGFloat)maxWidth;

@end

@interface MenuContainerView : UIView

@property (nonatomic, strong) MenuView *menuView;

@property (nonatomic, readonly) bool isShowingMenu;
@property (nonatomic) CGRect showingMenuFromRect;

- (void)showMenuFromRect:(CGRect)rect;
- (void)showMenuFromRect:(CGRect)rect animated:(bool)animated;
- (void)hideMenu;

@end
