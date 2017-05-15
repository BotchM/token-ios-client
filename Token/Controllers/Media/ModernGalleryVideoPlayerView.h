#import <UIKit/UIKit.h>
#import "PIPAblePlayerView.h"
#import "ModernGalleryVideoPlayerState.h"

@interface ModernGalleryVideoPlayerView : UIView <PIPAblePlayerView>

@property (nonatomic, readonly) ModernGalleryVideoPlayerState *state;
@property (nonatomic, readonly, getter=isLoaded) bool loaded;

- (void)loadImageWithUri:(NSString *)uri update:(bool)update synchronously:(bool)synchronously;
- (void)loadImageWithSignal:(SSignal *)signal;
- (void)setVideoPath:(NSString *)videoPath duration:(NSTimeInterval)duration;

- (void)reset;
- (void)stop;

- (void)disposeAudioSession;

@end
