#import "ModernViewModel.h"

#import <SSignalKit/SSignalKit.h>

@interface SignalImageViewModel : ModernViewModel

@property (nonatomic) bool showProgress;
@property (nonatomic) bool manualProgress;

@property (nonatomic) CGRect transitionContentRect;

- (void)setSignalGenerator:(SSignal *(^)())signalGenerator identifier:(NSString *)identifier;

- (void)setProgress:(float)progress animated:(bool)animated;
- (void)setDownload;
- (void)setNone;
- (void)setPlay;

- (void)reload;

- (void)setVideoPathSignal:(SSignal *)videoPathSignal;

@end
