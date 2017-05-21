#import "PhotoTool.h"
#import "PhotoBlurPass.h"

@interface BlurToolValue : NSObject <NSCopying>

@property (nonatomic, assign) BlurToolType type;
@property (nonatomic, assign) CGPoint point;
@property (nonatomic, assign) CGFloat size;
@property (nonatomic, assign) CGFloat falloff;
@property (nonatomic, assign) CGFloat angle;

@property (nonatomic, assign) CGFloat intensity;
@property (nonatomic, assign) bool editingIntensity;

@end

@interface BlurTool : PhotoTool

@property (nonatomic, readonly) NSString *intensityEditingTitle;

@end
