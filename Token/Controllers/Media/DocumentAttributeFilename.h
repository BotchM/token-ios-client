#import "PSCoding.h"

@interface DocumentAttributeFilename : NSObject <PSCoding, NSCoding>

@property (nonatomic, strong, readonly) NSString *filename;

- (instancetype)initWithFilename:(NSString *)filename;

@end
