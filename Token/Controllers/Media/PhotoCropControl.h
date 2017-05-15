#import <UIKit/UIKit.h>

@interface PhotoCropControl : UIControl

@property (nonatomic, copy) bool(^shouldBeginResizing)(PhotoCropControl *sender);
@property (nonatomic, copy) void(^didBeginResizing)(PhotoCropControl *sender);
@property (nonatomic, copy) void(^didResize)(PhotoCropControl *sender, CGPoint translation);
@property (nonatomic, copy) void(^didEndResizing)(PhotoCropControl *sender);

@end
