#import <UIKit/UIKit.h>

@interface MediaPickerGalleryVideoTrimView : UIControl

@property (nonatomic, copy) void(^didBeginEditing)(bool start);
@property (nonatomic, copy) void(^startHandleMoved)(CGPoint translation);
@property (nonatomic, copy) void(^endHandleMoved)(CGPoint translation);
@property (nonatomic, copy) void(^didEndEditing)(void);

@property (nonatomic, assign) bool trimmingEnabled;

- (void)setTrimming:(bool)trimming animated:(bool)animated;

@end
