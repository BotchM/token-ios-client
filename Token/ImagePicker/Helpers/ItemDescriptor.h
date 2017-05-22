#import <Foundation/Foundation.h>

@interface ItemDescriptor : NSObject

+ (NSDictionary *)descriptionForItem:(id)item caption:(NSString *)caption hash:(NSString *)hash;

@end
