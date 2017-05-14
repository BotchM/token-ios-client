#import "PhotoProcessPass.h"

typedef enum
{
    BlurToolTypeNone,
    BlurToolTypeRadial,
    BlurToolTypeLinear
} BlurToolType;

@interface PhotoBlurPass : PhotoProcessPass

@property (nonatomic, assign) BlurToolType type;
@property (nonatomic, assign) CGFloat size;
@property (nonatomic, assign) CGFloat falloff;
@property (nonatomic, assign) CGPoint point;
@property (nonatomic, assign) CGFloat angle;

@end
