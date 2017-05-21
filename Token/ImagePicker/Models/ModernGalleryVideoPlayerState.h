#import "PIPAblePlayerView.h"

@interface ModernGalleryVideoPlayerState : NSObject <TGPIPAblePlayerState>

+ (instancetype)stateWithPlaying:(bool)playing duration:(NSTimeInterval)duration position:(NSTimeInterval)position;

@end
