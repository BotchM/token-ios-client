#import "ModernViewModel.h"

#import <SSignalKit/SSignalKit.h>

@interface InlineVideoModel : ModernViewModel

@property (nonatomic, strong) SSignal *videoPathSignal;

@end
