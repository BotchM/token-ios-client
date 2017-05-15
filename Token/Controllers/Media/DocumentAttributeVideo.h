#import "PSCoding.h"
#import <UIKit/UIKit.h>

@interface DocumentAttributeVideo : NSObject <PSCoding, NSCoding>

@property (nonatomic, readonly) CGSize size;
@property (nonatomic, readonly) int32_t duration;

- (instancetype)initWithSize:(CGSize)size duration:(int32_t)duration;

@end
