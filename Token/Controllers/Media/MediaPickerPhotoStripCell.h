#import <UIKit/UIKit.h>

@class SSignal;
@class MediaSelectionContext;
@class MediaEditingContext;
@protocol MediaSelectableItem;

@interface MediaPickerPhotoStripCell : UICollectionViewCell

@property (nonatomic, strong) MediaSelectionContext *selectionContext;
@property (nonatomic, strong) MediaEditingContext *editingContext;
@property (nonatomic, copy) void (^itemSelected)(id<MediaSelectableItem> item, bool selected, id sender);

- (void)setItem:(NSObject *)item signal:(SSignal *)signal;

@end

extern NSString *const MediaPickerPhotoStripCellKind;
