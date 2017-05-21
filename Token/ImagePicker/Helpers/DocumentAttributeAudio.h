#import <Foundation/Foundation.h>

#import "PSCoding.h"

#import "AudioWaveform.h"

@interface DocumentAttributeAudio : NSObject <NSCoding, PSCoding>

@property (nonatomic, readonly) bool isVoice;
@property (nonatomic, strong, readonly) NSString *title;
@property (nonatomic, strong, readonly) NSString *performer;
@property (nonatomic, readonly) int32_t duration;
@property (nonatomic, strong, readonly) AudioWaveform *waveform;

- (instancetype)initWithIsVoice:(bool)isVoice title:(NSString *)title performer:(NSString *)performer duration:(int32_t)duration waveform:(AudioWaveform *)waveform;

@end
