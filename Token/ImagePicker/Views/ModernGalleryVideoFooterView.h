#import <UIKit/UIKit.h>

@interface ModernGalleryVideoFooterView : UIView

@property (nonatomic, copy) void (^playPressed)();
@property (nonatomic, copy) void (^pausePressed)();

@property (nonatomic) bool isPlaying;

@end
