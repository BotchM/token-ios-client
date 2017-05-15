#import "PhotoCropGridView.h"

@interface PhotoCropAreaView : UIControl

@property (nonatomic, copy) bool(^shouldBeginEditing)(void);
@property (nonatomic, copy) void(^didBeginEditing)(void);
@property (nonatomic, copy) void(^areaChanged)(void);
@property (nonatomic, copy) void(^didEndEditing)(void);

@property (nonatomic, assign) CGFloat aspectRatio;
@property (nonatomic, assign) bool lockAspectRatio;

@property (nonatomic, readonly) bool isTracking;

@property (nonatomic, assign) PhotoCropViewGridMode gridMode;

- (void)setGridMode:(PhotoCropViewGridMode)gridMode animated:(bool)animated;

@end

extern const CGSize PhotoCropCornerControlSize;
