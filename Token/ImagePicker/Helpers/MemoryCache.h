#import <Foundation/Foundation.h>

@interface MemoryCache : NSObject

- (void)setValue:(id)value forKey:(NSString *)key;
- (id)valueForKey:(NSString *)key;

@end
