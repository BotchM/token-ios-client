#import <UIKit/UIKit.h>

#import "ModernMediaListItem.h"

@interface ModernMediaListItemContentView : UIView

@property (nonatomic, strong) id<ModernMediaListItem> item;
@property (nonatomic) bool isHidden;

- (void)prepareForReuse;
- (void)updateItem;

- (void)setItem:(id<ModernMediaListItem>)item synchronously:(bool)synchronously;

- (void)setHidden:(bool)hidden animated:(bool)animated;

@end
