#import "ModernGalleryItem.h"
#import "PhotoToolbarView.h"

@protocol MediaEditableItem;
@class MediaEditingContext;

@protocol ModernGalleryEditableItem <ModernGalleryItem>

@property (nonatomic, strong) MediaEditingContext *editingContext;

- (id<MediaEditableItem>)editableMediaItem;
- (PhotoEditorTab)toolbarTabs;
- (NSString *)uniqueId;

@end
