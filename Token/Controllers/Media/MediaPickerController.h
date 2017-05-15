#import "ViewController.h"
#import "SuggestionContext.h"

@class MediaPickerLayoutMetrics;
@class MediaSelectionContext;
@class MediaEditingContext;
@class MediaPickerSelectionGestureRecognizer;

@interface MediaPickerController : ViewController <UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout>
{
    MediaPickerLayoutMetrics *_layoutMetrics;
    CGFloat _collectionViewWidth;
    UICollectionView *_collectionView;
    UIView *_wrapperView;
    MediaPickerSelectionGestureRecognizer *_selectionGestureRecognizer;
}

@property (nonatomic, strong) SuggestionContext *suggestionContext;
@property (nonatomic, assign) bool localMediaCacheEnabled;
@property (nonatomic, assign) bool captionsEnabled;
@property (nonatomic, assign) bool inhibitDocumentCaptions;
@property (nonatomic, assign) bool shouldStoreAssets;

@property (nonatomic, readonly) MediaSelectionContext *selectionContext;
@property (nonatomic, readonly) MediaEditingContext *editingContext;

@property (nonatomic, copy) void (^catchToolbarView)(bool enabled);

- (instancetype)initWithSelectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext;

- (NSUInteger)_numberOfItems;
- (id)_itemAtIndexPath:(NSIndexPath *)indexPath;
- (SSignal *)_signalForItem:(id)item;
- (NSString *)_cellKindForItem:(id)item;
- (Class)_collectionViewClass;
- (UICollectionViewLayout *)_collectionLayout;

- (void)_hideCellForItem:(id)item animated:(bool)animated;
- (void)_adjustContentOffsetToBottom;

- (void)_setupSelectionGesture;
- (void)_cancelSelectionGestureRecognizer;

@end
