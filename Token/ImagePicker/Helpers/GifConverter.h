#import <Foundation/Foundation.h>
#import <SSignalKit/SSignalKit.h>

@interface GifConverter : NSObject

+ (SSignal *)convertGifToMp4:(NSData *)data;

@end
