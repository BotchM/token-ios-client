#import "SignalImageView.h"

#import "ModernGalleryTransitionView.h"

#import "InlineVideoView.h"

@interface SignalImageView () <ModernGalleryTransitionView>
{
    InlineVideoView *_inlineVideoView;
}

@property (nonatomic, strong) NSString *viewIdentifier;
@property (nonatomic, strong) NSString *viewStateIdentifier;

@end

@implementation SignalImageView

- (void)willBecomeRecycled
{
    [self reset];
    
    [_inlineVideoView setVideoPathSignal:nil];
    
    [_inlineVideoView removeFromSuperview];
    _inlineVideoView = nil;
}

- (UIImage *)transitionImage
{
    return self.image;
}

- (CGRect)transitionContentRect
{
    return _transitionContentRect;
}

- (void)setVideoPathSignal:(SSignal *)videoPathSignal {
    if (_inlineVideoView == nil) {
        _inlineVideoView = [[InlineVideoView alloc] initWithFrame:self.bounds];
        _inlineVideoView.cornerRadius = 4.0f;
        _inlineVideoView.insets = UIEdgeInsetsZero;
        [self insertSubview:_inlineVideoView atIndex:0];
    }
    [_inlineVideoView setVideoPathSignal:videoPathSignal];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    _inlineVideoView.frame = self.bounds;
}

@end
