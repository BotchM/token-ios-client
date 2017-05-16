#import "PSCoding.h"

@interface DocumentAttributeFilename : NSObject <PSCoding, NSCoding>

@property (nonatomic, strong, readonly) NSString *filename;

- (instancetype)initWithFilename:(NSString *)filename
NS_SWIFT_NAME(init(fileName: String?));

@end
