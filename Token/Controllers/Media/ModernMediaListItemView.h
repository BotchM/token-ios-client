#import <UIKit/UIKit.h>

#import "ModernMediaListItemContentView.h"

@interface ModernMediaListItemView : UICollectionViewCell

@property (nonatomic, copy) void (^recycleItemContentView)(ModernMediaListItemContentView *);

@property (nonatomic, strong) ModernMediaListItemContentView *itemContentView;

- (ModernMediaListItemContentView *)_takeItemContentView;

@end
