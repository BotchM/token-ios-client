#import "ModernView.h"
#import "ModernButton.h"

@interface ModernButtonView : ModernButton <ModernView>

- (void)setBackgroundImage:(UIImage *)backgroundImage;
- (void)setHighlightedBackgroundImage:(UIImage *)highlightedBackgroundImage;
- (void)setTitle:(NSString *)title;
- (void)setTitleFont:(UIFont *)titleFont;
- (void)setImage:(UIImage *)image;
- (void)setSupplementaryIcon:(UIImage *)supplementaryIcon;
- (void)setDisplayProgress:(bool)displayProgress animated:(bool)animated;

@end
