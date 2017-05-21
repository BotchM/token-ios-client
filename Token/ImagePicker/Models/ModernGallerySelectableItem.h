#import "ModernGalleryItem.h"

@protocol MediaSelectableItem;
@class MediaSelectionContext;

@protocol ModernGallerySelectableItem <ModernGalleryItem>

@property (nonatomic, strong) MediaSelectionContext *selectionContext;

- (id<MediaSelectableItem>)selectableMediaItem;
- (NSString *)uniqueId;

@end
