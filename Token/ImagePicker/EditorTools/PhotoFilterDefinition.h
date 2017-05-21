#import <Foundation/Foundation.h>

typedef enum {
    PhotoFilterTypePassThrough,
    PhotoFilterTypeLookup,
    PhotoFilterTypeCustom
} PhotoFilterType;

@interface PhotoFilterDefinition : NSObject

@property (readonly, nonatomic) NSString *identifier;
@property (readonly, nonatomic) NSString *title;
@property (readonly, nonatomic) PhotoFilterType type;
@property (readonly, nonatomic) NSString *lookupFilename;
@property (readonly, nonatomic) NSString *shaderFilename;
@property (readonly, nonatomic) NSArray *textureFilenames;

+ (PhotoFilterDefinition *)originalFilterDefinition;
+ (PhotoFilterDefinition *)definitionWithDictionary:(NSDictionary *)dictionary;

@end
