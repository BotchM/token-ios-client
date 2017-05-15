#import <SSignalKit/SSignalKit.h>

@class AudioWaveform;

@interface AudioWaveformSignal : NSObject

+ (AudioWaveform *)waveformForPath:(NSString *)path;
+ (SSignal *)audioWaveformForFileAtPath:(NSString *)path duration:(NSTimeInterval)duration;

@end
