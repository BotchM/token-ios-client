#import "ModernViewModel.h"

typedef enum {
    ModernClockProgressTypeOutgoingClock = 0,
    ModernClockProgressTypeOutgoingMediaClock = 1,
    ModernClockProgressTypeIncomingClock = 2
} ModernClockProgressType;

@class ModernClockProgressView;

@interface ModernClockProgressViewModel : ModernViewModel

- (instancetype)initWithType:(ModernClockProgressType)type;

+ (void)setupView:(ModernClockProgressView *)view forType:(ModernClockProgressType)type;

@end
