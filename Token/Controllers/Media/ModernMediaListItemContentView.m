
#import "ModernMediaListItemContentView.h"

@implementation ModernMediaListItemContentView

- (void)prepareForReuse
{
}

- (void)updateItem
{
}

- (void)setItem:(id<ModernMediaListItem>)item
{
    [self setItem:item synchronously:false];
}

- (void)setItem:(id<ModernMediaListItem>)item synchronously:(bool)__unused synchronously
{
    _item = item;
}

- (void)setHidden:(bool)__unused hidden animated:(bool)__unused animated {
}

@end
