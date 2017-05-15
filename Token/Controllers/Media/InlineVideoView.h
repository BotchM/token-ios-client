#import <UIKit/UIKit.h>
#import <SSignalKit/SSignalKit.h>

#import "ModernView.h"

@interface InlineVideoView : UIView <ModernView>

@property (nonatomic) CGFloat cornerRadius;
@property (nonatomic) UIEdgeInsets insets;
@property (nonatomic) CGSize videoSize;

- (void)setVideoPathSignal:(SSignal *)signal;

@end
