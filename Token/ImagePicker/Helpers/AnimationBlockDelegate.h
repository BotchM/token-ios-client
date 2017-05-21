#import <QuartzCore/QuartzCore.h>

@interface AnimationBlockDelegate : NSObject

@property (nonatomic) bool removeLayerOnCompletion;
@property (nonatomic) NSNumber *opacityOnCompletion;
@property (nonatomic, weak) CALayer *layer;
@property (nonatomic, copy) void (^completion)(BOOL finished);

- (instancetype)initWithLayer:(CALayer *)layer;

@end
