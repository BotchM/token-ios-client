#import <AVFoundation/AVFoundation.h>
#import "MediaSelectionContext.h"
#import "MediaEditingContext.h"

@interface AVURLAsset (MediaItem) <MediaSelectableItem, MediaEditableItem>

@end
