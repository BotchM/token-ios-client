#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ModernMediaListItem.h"

@class ModernGalleryController;

@interface ModernMediaListModel : NSObject

@property (nonatomic, copy) void (^itemsUpdated)();
@property (nonatomic, copy) void (^itemUpdated)(id<ModernMediaListItem>);

@property (nonatomic, readonly) NSUInteger totalCount;
@property (nonatomic, strong, readonly) NSArray *items;

- (void)_replaceItems:(NSArray *)items totalCount:(NSUInteger)totalCount;
- (void)_transitionCompleted;

- (ModernGalleryController *)createGalleryControllerForItem:(id<ModernMediaListItem>)item hideItem:(void (^)(id<ModernMediaListItem>))hideItem referenceViewForItem:(UIView *(^)(id<ModernMediaListItem>))referenceViewForItem;

@end
