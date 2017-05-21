#import <UIKit/UIKit.h>

@interface VTAcceleratedVideoView : UIView

@property (nonatomic) CGSize videoSize;

- (void)setPath:(NSString *)path;
- (void)prepareForRecycle;

@end
