#import "InlineVideoModel.h"

#import "InlineVideoView.h"

@implementation InlineVideoModel

- (Class)viewClass {
    return [InlineVideoView class];
}

- (void)bindViewToContainer:(UIView *)container viewStorage:(ModernViewStorage *)viewStorage {
    [super bindViewToContainer:container viewStorage:viewStorage];
    
    InlineVideoView *view = (InlineVideoView *)[self boundView];
    [view setVideoPathSignal:_videoPathSignal];
}

- (void)unbindView:(ModernViewStorage *)viewStorage {
    [(InlineVideoView *)[self boundView] setVideoPathSignal:nil];
    
    [super unbindView:viewStorage];
}

- (void)setVideoPathSignal:(SSignal *)videoPathSignal {
    _videoPathSignal = videoPathSignal;
    
    [(InlineVideoView *)[self boundView] setVideoPathSignal:videoPathSignal];
}

@end
