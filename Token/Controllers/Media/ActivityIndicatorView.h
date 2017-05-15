#import <UIKit/UIKit.h>

typedef enum {
    ActivityIndicatorViewStyleSmall = 0,
    ActivityIndicatorViewStyleLarge = 1,
    ActivityIndicatorViewStyleSmallWhite = 2
} ActivityIndicatorViewStyle;

@interface ActivityIndicatorView : UIImageView

- (id)init;
- (id)initWithStyle:(ActivityIndicatorViewStyle)style;

@end
