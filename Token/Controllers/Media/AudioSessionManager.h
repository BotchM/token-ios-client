#import <Foundation/Foundation.h>
#import <SSignalKit/SSignalKit.h>
#import <AVFoundation/AVFoundation.h>

typedef enum {
    AudioSessionTypePlayVoice,
    AudioSessionTypePlayMusic,
    AudioSessionTypePlayVideo,
    AudioSessionTypePlayAndRecord,
    AudioSessionTypePlayAndRecordHeadphones,
    AudioSessionTypeCall
} AudioSessionType;


typedef enum {
    AudioSessionRouteChangePause,
    AudioSessionRouteChangeResume
} AudioSessionRouteChange;

@class AudioRoute;

@interface AudioSessionManager : NSObject

+ (AudioSessionManager *)instance;

- (id<SDisposable>)requestSessionWithType:(AudioSessionType)type interrupted:(void (^)())interrupted;
- (void)cancelCurrentSession;
+ (SSignal *)routeChange;

- (void)applyRoute:(AudioRoute *)route;

@end


@interface AudioRoute : NSObject

@property (nonatomic, readonly) NSString *uid;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) bool isBuiltIn;
@property (nonatomic, readonly) bool isLoudspeaker;
@property (nonatomic, readonly) bool isBluetooth;
@property (nonatomic, readonly) bool isHeadphones;

@property (nonatomic, readonly) AVAudioSessionPortDescription *device;

+ (instancetype)routeWithDescription:(AVAudioSessionPortDescription *)description;
+ (instancetype)routeForBuiltIn:(bool)headphones;
+ (instancetype)routeForSpeaker;

@end
