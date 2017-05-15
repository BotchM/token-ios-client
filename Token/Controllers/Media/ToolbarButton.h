#import <UIKit/UIKit.h>

//#import "TGNavigationController.h"

typedef enum {
    ToolbarButtonTypeGeneric = 0,
    ToolbarButtonTypeBack = 1,
    ToolbarButtonTypeDone = 2,
    ToolbarButtonTypeDoneBlack = 3,
    ToolbarButtonTypeImage = 4,
    ToolbarButtonTypeDelete = 5,
    ToolbarButtonTypeCustom = 6
} ToolbarButtonType;

@interface ToolbarButton : UIButton 

@property (nonatomic) ToolbarButtonType type;

@property (nonatomic) CGSize touchInset;

@property (nonatomic) int minWidth;
@property (nonatomic) float paddingLeft;
@property (nonatomic) float paddingRight;

@property (nonatomic, retain) NSString *text;
@property (nonatomic, retain) UIImage *image;
@property (nonatomic, retain) UIImage *imageLandscape;
@property (nonatomic, retain) UIImage *imageHighlighted;

@property (nonatomic, retain) UILabel *buttonLabelView;
@property (nonatomic, retain) UIImageView *buttonImageView;

@property (nonatomic) bool isLandscape;
@property (nonatomic) int landscapeOffset;

@property (nonatomic) bool backSemantics;

- (id)initWithType:(ToolbarButtonType)type;
- (id)initWithCustomImages:(UIImage *)imageNormal imageNormalHighlighted:(UIImage *)imageNormalHighlighted imageLandscape:(UIImage *)imageLandscape imageLandscapeHighlighted:(UIImage *)imageLandscapeHighlighted textColor:(UIColor *)textColor shadowColor:(UIColor *)shadowColor;

@end
