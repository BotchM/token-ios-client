#import <UIKit/UIKit.h>

@class PaintSwatch;

@interface PhotoPaintColorPicker : UIControl

@property (nonatomic, copy) void (^beganPicking)(void);
@property (nonatomic, copy) void (^valueChanged)(void);
@property (nonatomic, copy) void (^finishedPicking)(void);

@property (nonatomic, strong) PaintSwatch *swatch;
@property (nonatomic, assign) UIInterfaceOrientation orientation;

@end
