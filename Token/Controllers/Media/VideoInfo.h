#import <Foundation/Foundation.h>

@interface VideoInfo : NSObject <NSCoding>

- (void)addVideoWithQuality:(int)quality url:(NSString *)url size:(int)size;
- (NSString *)urlWithQuality:(int)quality actualQuality:(int *)actualQuality actualSize:(int *)actualSize;

- (void)serialize:(NSMutableData *)data;
+ (VideoInfo *)deserialize:(NSInputStream *)is;

@end
