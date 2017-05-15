#import "ModernGalleryInterfaceView.h"
#import "ModernGalleryItem.h"

#import "PhotoToolbarView.h"

@class MediaSelectionContext;
@class MediaEditingContext;
@class SuggestionContext;
@class MediaPickerGallerySelectedItemsModel;

@interface MediaPickerGalleryInterfaceView : UIView <ModernGalleryInterfaceView>

@property (nonatomic, copy) void (^captionSet)(id<ModernGalleryItem>, NSString *);
@property (nonatomic, copy) void (^donePressed)(id<ModernGalleryItem>);

@property (nonatomic, copy) void (^photoStripItemSelected)(NSInteger index);

@property (nonatomic, assign) bool hasCaptions;
@property (nonatomic, assign) bool inhibitDocumentCaptions;
@property (nonatomic, assign) bool usesSimpleLayout;
@property (nonatomic, assign) bool hasSwipeGesture;
@property (nonatomic, assign) bool usesFadeOutForDismissal;

@property (nonatomic, readonly) PhotoEditorTab currentTabs;

- (instancetype)initWithFocusItem:(id<ModernGalleryItem>)focusItem selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext hasSelectionPanel:(bool)hasSelectionPanel;

- (void)setSelectedItemsModel:(MediaPickerGallerySelectedItemsModel *)selectedItemsModel;
- (void)setEditorTabPressed:(void (^)(PhotoEditorTab tab))editorTabPressed;
- (void)setSuggestionContext:(SuggestionContext *)suggestionContext;

- (void)setThumbnailSignalForItem:(SSignal *(^)(id))thumbnailSignalForItem;

- (void)updateSelectionInterface:(NSUInteger)selectedCount counterVisible:(bool)counterVisible animated:(bool)animated;
- (void)updateSelectedPhotosView:(bool)reload incremental:(bool)incremental add:(bool)add index:(NSInteger)index;
- (void)setSelectionInterfaceHidden:(bool)hidden animated:(bool)animated;

- (void)editorTransitionIn;
- (void)editorTransitionOut;

- (void)setToolbarsHidden:(bool)hidden animated:(bool)animated;

- (void)setTabBarUserInteractionEnabled:(bool)enabled;

@end
