#import "SignalImageViewWithProgress.h"

#import "MessageImageViewOverlayView.h"

@interface SignalImageViewWithProgress ()
{
    MessageImageViewOverlayView *_overlayView;
    CGFloat _progress;
}

@end

@implementation SignalImageViewWithProgress

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self != nil)
    {
        self.legacyAutomaticProgress = false;
        _overlayView = [[MessageImageViewOverlayView alloc] initWithFrame:CGRectMake(floor((frame.size.width - 50.0f) / 2.0f), floor((frame.size.height - 50.0f) / 2.0f), 50.0f, 50.0f)];
        [_overlayView setOverlayStyle:MessageImageViewOverlayStyleDefault];
        [_overlayView setRadius:50.0f];
        [self addSubview:_overlayView];
        _overlayView.hidden = true;
        _progress = -1.0f;
    }
    return self;
}

- (void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    _overlayView.frame = CGRectMake(floor((frame.size.width - 50.0f) / 2.0f), floor((frame.size.height - 50.0f) / 2.0f), 50.0f, 50.0f);
}

- (void)_updateProgress:(float)value
{
    [super _updateProgress:value];
 
    if (!_manualProgress) {
        _progress = value;
        if (_progress < -FLT_EPSILON || _progress > 1.0f + FLT_EPSILON)
        {
            [_overlayView setProgress:1.0f cancelEnabled:false animated:true];
            [UIView animateWithDuration:0.2 animations:^
            {
                _overlayView.alpha = 0.0f;
            } completion:^(BOOL finished)
            {
                if (finished)
                {
                    _overlayView.hidden = true;
                    [_overlayView setNone];
                }
            }];
        }
        else
        {
            _overlayView.hidden = false;
            _overlayView.alpha = 1.0f;
            [_overlayView setProgress:value cancelEnabled:false animated:true];
        }
    }
}

- (CGFloat)progress
{
    return _progress;
}

- (void)setProgress:(CGFloat)progress
{
    [self setProgress:progress animated:false];
}

- (void)setProgress:(CGFloat)progress animated:(bool)animated {
    _progress = progress;
    if (_progress < -FLT_EPSILON || _progress > 1.0f + FLT_EPSILON)
    {
        _overlayView.hidden = true;
        [_overlayView setNone];
    }
    else
    {
        _overlayView.hidden = false;
        _overlayView.alpha = 1.0f;
        [_overlayView setProgress:progress cancelEnabled:_manualProgress animated:animated];
    }
}

- (void)setDownload {
    _overlayView.hidden = false;
    _progress = -1.0f;
    [_overlayView setDownload];
    _overlayView.alpha = 1.0f;
}

- (void)setNone {
    _progress = -1.0f;
    _overlayView.hidden = true;
    [_overlayView setNone];
}

- (void)setPlay {
    _overlayView.hidden = false;
    _progress = -1.0f;
    [_overlayView setPlay];
    _overlayView.alpha = 1.0f;
}

@end
