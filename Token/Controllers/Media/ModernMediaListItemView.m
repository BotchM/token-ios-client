#import "ModernMediaListItemView.h"

@implementation ModernMediaListItemView

- (void)prepareForReuse
{
    [self _recycleItemContentView];
}

- (void)_recycleItemContentView
{
    if (_itemContentView != nil)
    {
        [_itemContentView removeFromSuperview];
        
        if (_recycleItemContentView)
            _recycleItemContentView(_itemContentView);
        
        _itemContentView = nil;
    }
}

- (ModernMediaListItemContentView *)_takeItemContentView
{
    if (_itemContentView != nil)
    {
        [_itemContentView removeFromSuperview];
        ModernMediaListItemContentView *result = _itemContentView;
        _itemContentView = nil;
        
        return result;
    }
    
    return nil;
}

- (void)setItemContentView:(ModernMediaListItemContentView *)itemContentView
{
    [self _recycleItemContentView];
    
    _itemContentView = itemContentView;
    
    if (_itemContentView != nil)
    {
        [self addSubview:_itemContentView];
        _itemContentView.frame = self.bounds;
    }
}

- (void)layoutSubviews
{
    _itemContentView.frame = self.bounds;
}

@end
