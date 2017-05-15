#import <Foundation/Foundation.h>

@class VTPlayerView;

@interface VTPlayer : NSObject

- (instancetype)initWithUrl:(NSURL *)url;

- (void)play;
- (void)stop;

- (void)_setOutput:(VTPlayerView *)playerView;

@end
