#import "AttachmentMenuCell.h"
#import "ImageView.h"
#import "CheckButtonView.h"

@class MediaAsset;
@class MediaSelectionContext;
@class MediaEditingContext;

@interface AttachmentAssetCell : AttachmentMenuCell
{
    CheckButtonView *_checkButton;
    
    UIImageView *_iconView;
    UIImageView *_gradientView;
}

@property (nonatomic, readonly) ImageView *imageView;
- (void)setHidden:(bool)hidden animated:(bool)animated;

@property (nonatomic, readonly) MediaAsset *asset;
- (void)setAsset:(MediaAsset *)asset signal:(SSignal *)signal;
- (void)setSignal:(SSignal *)signal;

@property (nonatomic, assign) bool isZoomed;

@property (nonatomic, strong) MediaSelectionContext *selectionContext;
@property (nonatomic, strong) MediaEditingContext *editingContext;

@end
