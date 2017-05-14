#import "PhotoEditorItem.h"
#import "PhotoProcessPass.h"

@class PhotoToolComposer;

typedef enum
{
    PhotoToolTypePass,
    PhotoToolTypeShader
} PhotoToolType;

@protocol CustomToolValue <NSObject>

- (id<CustomToolValue>)cleanValue;

@end

@interface PhotoTool : NSObject <PhotoEditorItem>
{
    PhotoProcessPass *_pass;
    
    NSString *_identifier;
    PhotoToolType _type;
    NSInteger _order;
    
    NSArray *_parameters;
    NSArray *_constants;
    
    CGFloat _minimumValue;
    CGFloat _maximumValue;
    CGFloat _defaultValue;
}

@property (nonatomic, readonly) PhotoToolType type;
@property (nonatomic, readonly) NSInteger order;
@property (nonatomic, readonly) UIImage *image;

@property (nonatomic, readonly) bool isHidden;

@property (nonatomic, readonly) NSString *shaderString;
@property (nonatomic, readonly) NSString *ancillaryShaderString;
@property (nonatomic, readonly) PhotoProcessPass *pass;

@property (nonatomic, weak) PhotoToolComposer *toolComposer;

- (void)invalidate;

- (NSString *)stringValue;

@end
