#import <Foundation/Foundation.h>

#import "PSCoding.h"

@interface AudioWaveform : NSObject <NSCoding, PSCoding>

@property (nonatomic, strong, readonly) NSData *samples;
@property (nonatomic, readonly) int32_t peak;

- (instancetype)initWithSamples:(NSData *)samples peak:(int32_t)peak;
- (instancetype)initWithBitstream:(NSData *)bitstream bitsPerSample:(NSUInteger)bitsPerSample;

- (NSData *)bitstream;

@end