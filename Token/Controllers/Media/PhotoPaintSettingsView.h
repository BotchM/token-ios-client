#import <UIKit/UIKit.h>

@class PaintSwatch;

typedef enum
{
    PhotoPaintSettingsViewIconBrush,
    PhotoPaintSettingsViewIconText,
    PhotoPaintSettingsViewIconMirror
} PhotoPaintSettingsViewIcon;

@interface PhotoPaintSettingsView : UIView

@property (nonatomic, copy) void (^beganColorPicking)(void);
@property (nonatomic, copy) void (^changedColor)(PhotoPaintSettingsView *sender, PaintSwatch *swatch);
@property (nonatomic, copy) void (^finishedColorPicking)(PhotoPaintSettingsView *sender, PaintSwatch *swatch);

@property (nonatomic, copy) void (^settingsPressed)(void);
@property (nonatomic, readonly) UIButton *settingsButton;

@property (nonatomic, strong) PaintSwatch *swatch;
@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;

- (void)setIcon:(PhotoPaintSettingsViewIcon)icon animated:(bool)animated;
- (void)setHighlighted:(bool)highlighted;

+ (UIImage *)landscapeLeftBackgroundImage;
+ (UIImage *)landscapeRightBackgroundImage;
+ (UIImage *)portraitBackgroundImage;

@end

@protocol PhotoPaintPanelView

@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;

- (void)present;
- (void)dismissWithCompletion:(void (^)(void))completion;

@end
