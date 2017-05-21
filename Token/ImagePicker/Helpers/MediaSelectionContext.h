#import <SSignalKit/SSignalKit.h>

@protocol MediaSelectableItem

@property (nonatomic, readonly) NSString *uniqueIdentifier;

@end

@interface MediaSelectionContext : NSObject

@property (nonatomic, copy) SSignal *(^updatedItemsSignal)(NSArray *items);
- (void)setItemSourceUpdatedSignal:(SSignal *)signal;

- (void)setItem:(id<MediaSelectableItem>)item selected:(bool)selected;
- (void)setItem:(id<MediaSelectableItem>)item selected:(bool)selected animated:(bool)animated sender:(id)sender;

- (bool)toggleItemSelection:(id<MediaSelectableItem>)item;
- (bool)toggleItemSelection:(id<MediaSelectableItem>)item animated:(bool)animated sender:(id)sender;

- (void)clear;

- (bool)isItemSelected:(id<MediaSelectableItem>)item;

- (SSignal *)itemSelectedSignal:(id<MediaSelectableItem>)item;
- (SSignal *)itemInformativeSelectedSignal:(id<MediaSelectableItem>)item;
- (SSignal *)selectionChangedSignal;

- (void)enumerateSelectedItems:(void (^)(id<MediaSelectableItem>))enumerationBlock;

- (NSOrderedSet *)selectedItemsIdentifiers;
- (NSArray *)selectedItems;

- (NSUInteger)count;

+ (SSignal *)combinedSelectionChangedSignalForContexts:(NSArray *)contexts;

@end


@interface MediaSelectionChange : NSObject

@property (nonatomic, readonly) id<MediaSelectableItem> item;
@property (nonatomic, readonly) bool selected;
@property (nonatomic, readonly) bool animated;
@property (nonatomic, readonly, strong) id sender;

@end
