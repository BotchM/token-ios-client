#import <Foundation/Foundation.h>

#import "MemoryImageCache.h"
#import <SSignalKit/SSignalKit.h>
#import "ModernCache.h"
#import "EMInMemoryImageCache.h"

@interface SharedMediaUtils : NSObject

+ (MemoryImageCache *)sharedMediaMemoryImageCache;
+ (EMInMemoryImageCache *)inMemoryImageCache;
+ (SThreadPool *)sharedMediaImageProcessingThreadPool;
+ (ModernCache *)sharedMediaTemporaryPersistentCache;

@end
