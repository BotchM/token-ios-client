#import <UIKit/UIKit.h>

@class SSignal;
@class MediaPickerGallerySelectedItemsModel;
@class MediaSelectionContext;
@class MediaEditingContext;

@interface MediaPickerPhotoStripView : UIView

@property (nonatomic, weak) MediaPickerGallerySelectedItemsModel *selectedItemsModel;
@property (nonatomic, strong) MediaSelectionContext *selectionContext;
@property (nonatomic, strong) MediaEditingContext *editingContext;
@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;
@property (nonatomic, readonly) bool isAnimating;

@property (nonatomic, copy) void (^itemSelected)(NSInteger index);
@property (nonatomic, copy) SSignal *(^thumbnailSignalForItem)(id item);

- (void)setHidden:(bool)hidden animated:(bool)animated;

- (void)reloadData;
- (void)insertItemAtIndex:(NSInteger)index;
- (void)deleteItemAtIndex:(NSInteger)index;

@end
