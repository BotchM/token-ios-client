#import <UIKit/UIKit.h>

@class MenuSheetView;

@interface MenuSheetDimView : UIButton

- (instancetype)initWithActionMenuView:(MenuSheetView *)menuView;

- (void)setTheaterMode:(bool)theaterMode animated:(bool)animated;

+ (UIColor *)backgroundColor;
+ (UIColor *)theaterBackgroundColor;

@end
