#import "ModernViewModel.h"

@interface ModernButtonViewModel : ModernViewModel

@property (nonatomic, copy) void (^pressed)();

@property (nonatomic, strong) UIImage *supplementaryIcon;
@property (nonatomic, strong) UIImage *backgroundImage;
@property (nonatomic, strong) UIImage *highlightedBackgroundImage;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSArray *possibleTitles;
@property (nonatomic, strong) UIFont *font;
@property (nonatomic, strong) UIImage *image;
@property (nonatomic) UIEdgeInsets extendedEdgeInsets;

@property (nonatomic) UIEdgeInsets titleInset;

@property (nonatomic) bool modernHighlight;
@property (nonatomic) bool displayProgress;

- (void)setDisplayProgress:(bool)displayProgress animated:(bool)animated;

@end
