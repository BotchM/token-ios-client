#import <Foundation/Foundation.h>
#import "MediaSelectionContext.h"

@protocol ModernMediaListItem;

@protocol ModernMediaListSelectableItem <ModernMediaListItem, NSCopying>

@property (nonatomic, strong) MediaSelectionContext *selectionContext;

- (id<MediaSelectableItem>)selectableMediaItem;

@end
