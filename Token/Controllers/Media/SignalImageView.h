#import "ImageView.h"

#import "ModernView.h"

#import <SSignalKit/SSignalKit.h>

@interface SignalImageView : ImageView <ModernView>

@property (nonatomic) CGRect transitionContentRect;

- (void)setVideoPathSignal:(SSignal *)videoPathSignal;

@end
