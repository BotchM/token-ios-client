#import <UIKit/UIKit.h>

#import "StaticBackdropAreaData.h"

extern NSString *StaticBackdropMessageActionCircle;
extern NSString *StaticBackdropMessageTimestamp;
extern NSString *StaticBackdropMessageAdditionalData;

@interface StaticBackdropImageData : NSObject

- (StaticBackdropAreaData *)backdropAreaForKey:(NSString *)key;
- (void)setBackdropArea:(StaticBackdropAreaData *)backdropArea forKey:(NSString *)key;

@end
