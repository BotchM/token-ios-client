#import "SignalImageView.h"

@interface SignalImageViewWithProgress : SignalImageView

@property (nonatomic) bool manualProgress;

- (CGFloat)progress;
- (void)setProgress:(CGFloat)progress;
- (void)setProgress:(CGFloat)progress animated:(bool)animated;
- (void)setDownload;
- (void)setNone;
- (void)setPlay;

@end
