#import <UIKit/UIKit.h>

typedef enum {
    PhotoCropViewGridModeNone,
    PhotoCropViewGridModeMajor,
    PhotoCropViewGridModeMinor
} PhotoCropViewGridMode;

@interface PhotoCropGridView : UIView

@property (nonatomic, readonly) PhotoCropViewGridMode mode;

- (instancetype)initWithMode:(PhotoCropViewGridMode)mode;

- (void)setHidden:(bool)hidden animated:(bool)animated duration:(CGFloat)duration delay:(CGFloat)delay;

@end
