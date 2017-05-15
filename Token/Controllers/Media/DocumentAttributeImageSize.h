#import "PSCoding.h"
#import <CoreGraphics/CoreGraphics.h>

@interface DocumentAttributeImageSize : NSObject <PSCoding, NSCoding>

@property (nonatomic, readonly) CGSize size;

- (instancetype)initWithSize:(CGSize)size;

@end
