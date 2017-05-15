#import <Foundation/Foundation.h>
#import "MediaSelectionContext.h"

@class MediaSelectionContext;

@interface MediaPickerGallerySelectedItemsModel : NSObject

@property (nonatomic, copy) void (^selectionUpdated)(bool reload, bool incremental, bool add, NSInteger index);

@property (nonatomic, readonly) NSArray *items;
@property (nonatomic, readonly) NSArray *selectedItems;

@property (nonatomic, readonly) NSInteger totalCount;
@property (nonatomic, readonly) NSInteger selectedCount;

- (instancetype)initWithSelectionContext:(MediaSelectionContext *)selectionContext;

@end
