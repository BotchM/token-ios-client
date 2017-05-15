#import "PhotoProcessPass.h"

@class PhotoTool;

@interface PhotoToolComposer : PhotoProcessPass

@property (nonatomic, readonly) NSArray *tools;
@property (nonatomic, readonly) NSArray *advancedTools;
@property (nonatomic, readonly) bool shouldBeSkipped;
@property (nonatomic, assign) CGSize imageSize;

- (void)addPhotoTool:(PhotoTool *)tool;
- (void)addPhotoTools:(NSArray *)tools;
- (void)compose;

@end
