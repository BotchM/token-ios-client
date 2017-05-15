#import "ModernMediaListModel.h"
#import "Common.h"
#import <UIKit/UIKit.h>

@implementation ModernMediaListModel

- (void)_replaceItems:(NSArray *)items totalCount:(NSUInteger)totalCount
{
    DispatchOnMainThread(^
    {
        _totalCount = totalCount;
        _items = items;
 
        if (_itemsUpdated)
            _itemsUpdated();
    });
}

- (void)_transitionCompleted
{
}

- (ModernGalleryController *)createGalleryControllerForItem:(id<ModernMediaListItem>)__unused item hideItem:(void (^)(id<ModernMediaListItem>))__unused hideItem referenceViewForItem:(UIView *(^)(id<ModernMediaListItem>))__unused referenceViewForItem
{
    return nil;
}

@end
