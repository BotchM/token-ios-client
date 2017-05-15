#import <UIKit/UIKit.h>

typedef enum
{
    CheckButtonStyleDefault,
    CheckButtonStyleBar,
    CheckButtonStyleMedia,
    CheckButtonStyleGallery,
    CheckButtonStyleShare
} CheckButtonStyle;

@interface CheckButtonView : UIButton

- (instancetype)initWithStyle:(CheckButtonStyle)style;

- (void)setSelected:(bool)selected animated:(bool)animated;
- (void)setSelected:(bool)selected animated:(bool)animated bump:(bool)bump;

@end
