#import "MediaEditingContext.h"

@class PaintingData;

@interface PhotoEditorValues : NSObject <MediaEditAdjustments>

@property (nonatomic, readonly) CGFloat cropRotation;
@property (nonatomic, readonly) NSDictionary *toolValues;

- (bool)toolsApplied;

+ (instancetype)editorValuesWithOriginalSize:(CGSize)originalSize cropRect:(CGRect)cropRect cropRotation:(CGFloat)cropRotation cropOrientation:(UIImageOrientation)cropOrientation cropLockedAspectRatio:(CGFloat)cropLockedAspectRatio cropMirrored:(bool)cropMirrored toolValues:(NSDictionary *)toolValues paintingData:(PaintingData *)paintingData;

@end
