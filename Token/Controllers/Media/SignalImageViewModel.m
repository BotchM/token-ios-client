#import "SignalImageViewModel.h"

#import "SignalImageView.h"
#import "SignalImageViewWithProgress.h"

typedef enum {
    SignalImageViewModelOverlayNone = 0,
    SignalImageViewModelOverlayProgress,
    SignalImageViewModelOverlayDownload,
    SignalImageViewModelOverlayPlay
} SignalImageViewModelOverlay;

@interface SignalImageViewModel ()
{
    SSignal *(^_signalGenerator)();
    NSString *_identifier;
    CGFloat _progress;
    
    SignalImageViewModelOverlay _overlay;
}

@end

@implementation SignalImageViewModel

- (instancetype)init
{
    self = [super init];
    if (self != nil)
    {
        _progress = -1.0f;
    }
    return self;
}

- (Class)viewClass
{
    return (_showProgress || _manualProgress) ? [SignalImageViewWithProgress class] : [SignalImageView class];
}

- (void)setSignalGenerator:(SSignal *(^)())signalGenerator identifier:(NSString *)identifier
{
    _signalGenerator = [signalGenerator copy];
    _identifier = identifier;
}

- (void)_updateViewStateIdentifier
{
    self.viewStateIdentifier = [[NSString alloc] initWithFormat:@"SignalImageView/%@", _identifier];
}

- (void)bindViewToContainer:(UIView *)container viewStorage:(ModernViewStorage *)viewStorage
{
    [self _updateViewStateIdentifier];
    
    [super bindViewToContainer:container viewStorage:viewStorage];
    
    if (_manualProgress) {
        if ([[self boundView] isKindOfClass:[SignalImageViewWithProgress class]]) {
            ((SignalImageViewWithProgress *)self.boundView).manualProgress = _manualProgress;
            
            switch (_overlay) {
                case SignalImageViewModelOverlayProgress:
                    ((SignalImageViewWithProgress *)self.boundView).progress = _progress;
                    break;
                case SignalImageViewModelOverlayDownload:
                    [((SignalImageViewWithProgress *)self.boundView) setDownload];
                    break;
                case SignalImageViewModelOverlayNone:
                    [((SignalImageViewWithProgress *)self.boundView) setNone];
                    break;
                case SignalImageViewModelOverlayPlay:
                    [((SignalImageViewWithProgress *)self.boundView) setPlay];
                    break;
            }
        }
    } else {
        if (_showProgress)
            ((SignalImageViewWithProgress *)self.boundView).progress = _progress;
    }
    
    ((SignalImageView *)self.boundView).transitionContentRect = _transitionContentRect;
    
    if (_signalGenerator)
        [((SignalImageView *)self.boundView) setSignal:_signalGenerator()];
}

- (void)unbindView:(ModernViewStorage *)viewStorage
{
    if (_showProgress)
        _progress = ((SignalImageViewWithProgress *)self.boundView).progress;
    
    [super unbindView:viewStorage];
}

- (void)setProgress:(float)progress animated:(bool)animated {
    _progress = progress;
    
    _overlay = SignalImageViewModelOverlayProgress;
    if ([[self boundView] isKindOfClass:[SignalImageViewWithProgress class]]) {
        [((SignalImageViewWithProgress *)self.boundView) setProgress:progress animated:animated];
    }
}

- (void)setDownload {
    _overlay = SignalImageViewModelOverlayDownload;
    if ([[self boundView] isKindOfClass:[SignalImageViewWithProgress class]]) {
        [((SignalImageViewWithProgress *)self.boundView) setDownload];
    }
}

- (void)setNone {
    _overlay = SignalImageViewModelOverlayNone;
    if ([[self boundView] isKindOfClass:[SignalImageViewWithProgress class]]) {
        [((SignalImageViewWithProgress *)self.boundView) setNone];
    }
}

- (void)setPlay {
    _overlay = SignalImageViewModelOverlayPlay;
    if ([[self boundView] isKindOfClass:[SignalImageViewWithProgress class]]) {
        [((SignalImageViewWithProgress *)self.boundView) setPlay];
    }
}

- (void)reload {
    if (_signalGenerator) {
        [((SignalImageView *)self.boundView) setSignal:_signalGenerator()];
    }
}

- (void)setVideoPathSignal:(SSignal *)videoPathSignal {
    [((SignalImageView *)self.boundView) setVideoPathSignal:videoPathSignal];
}

@end
