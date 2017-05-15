#import "ImageView.h"
#import "CheckButtonView.h"

@class MediaSelectionContext;
@class MediaEditingContext;

@interface MediaPickerCell : UICollectionViewCell
{
    CheckButtonView *_checkButton;
}

@property (nonatomic, readonly) ImageView *imageView;
- (void)setHidden:(bool)hidden animated:(bool)animated;

@property (nonatomic, strong) MediaSelectionContext *selectionContext;
@property (nonatomic, strong) MediaEditingContext *editingContext;

@property (nonatomic, readonly) NSObject *item;
- (void)setItem:(NSObject *)item signal:(SSignal *)signal;

@end
