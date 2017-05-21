#import <UIKit/UIKit.h>

typedef enum {
    MessageImageViewOverlayStyleDefault = 0,
    MessageImageViewOverlayStyleAccent = 1,
    MessageImageViewOverlayStyleList = 2,
    MessageImageViewOverlayStyleIncoming = 3,
    MessageImageViewOverlayStyleOutgoing = 4
} MessageImageViewOverlayStyle;

@interface MessageImageViewOverlayView : UIView

@property (nonatomic, readonly) CGFloat progress;

- (void)setRadius:(CGFloat)radius;
- (void)setOverlayBackgroundColorHint:(UIColor *)overlayBackgroundColorHint;
- (void)setOverlayStyle:(MessageImageViewOverlayStyle)overlayStyle;
- (void)setBlurredBackgroundImage:(UIImage *)blurredBackgroundImage;
- (void)setDownload;
- (void)setProgress:(CGFloat)progress animated:(bool)animated;
- (void)setSecretProgress:(CGFloat)progress completeDuration:(NSTimeInterval)completeDuration animated:(bool)animated;
- (void)setProgress:(CGFloat)progress cancelEnabled:(bool)cancelEnabled animated:(bool)animated;
- (void)setProgressAnimated:(CGFloat)progress duration:(NSTimeInterval)duration cancelEnabled:(bool)cancelEnabled;
- (void)setPlay;
- (void)setPlayMedia;
- (void)setPauseMedia;
- (void)setSecret:(bool)isViewed;
- (void)setNone;

@end
