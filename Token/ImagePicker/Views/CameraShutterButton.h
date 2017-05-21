#import <UIKit/UIKit.h>

typedef enum
{
    CameraShutterButtonNormalMode,
    CameraShutterButtonVideoMode,
    CameraShutterButtonRecordingMode
} CameraShutterButtonMode;

@interface CameraShutterButton : UIControl

- (void)setButtonMode:(CameraShutterButtonMode)mode animated:(bool)animated;
- (void)setEnabled:(bool)enabled animated:(bool)animated;

- (void)setHighlighted:(bool)highlighted animated:(bool)animated;

@end
