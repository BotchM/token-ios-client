#import "MediaSelectionContext.h"
#import <UIKit/UIKit.h>

@interface MediaPickerSelectionGestureRecognizer : NSObject

@property (nonatomic, copy) bool (^isItemSelected)(NSIndexPath *);
@property (nonatomic, copy) void (^toggleItemSelection)(NSIndexPath *);

- (instancetype)initForCollectionView:(UICollectionView *)collectionView;
- (void)cancel;

@end
