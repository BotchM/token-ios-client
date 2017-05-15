#import "ModernGalleryModel.h"

#import "MediaPickerGalleryInterfaceView.h"
#import "ModernGalleryController.h"

#import "PhotoEditorController.h"

@class ModernGalleryController;
@class MediaPickerGallerySelectedItemsModel;
@protocol MediaEditAdjustments;

@class MediaSelectionContext;
@protocol MediaSelectableItem;

@class SuggestionContext;

@interface MediaPickerGalleryModel : ModernGalleryModel

@property (nonatomic, copy) void (^willFinishEditingItem)(id<MediaEditableItem> item, id<MediaEditAdjustments> adjustments, id temporaryRep, bool hasChanges);
@property (nonatomic, copy) void (^didFinishEditingItem)(id<MediaEditableItem>item, id<MediaEditAdjustments> adjustments, UIImage *resultImage, UIImage *thumbnailImage);
@property (nonatomic, copy) void (^didFinishRenderingFullSizeImage)(id<MediaEditableItem> item, UIImage *fullSizeImage);

@property (nonatomic, copy) void (^saveItemCaption)(id<MediaEditableItem> item, NSString *caption);

@property (nonatomic, copy) void (^storeOriginalImageForItem)(id<MediaEditableItem> item, UIImage *originalImage);

@property (nonatomic, copy) id<MediaEditAdjustments> (^requestAdjustments)(id<MediaEditableItem> item);

@property (nonatomic, copy) void (^editorOpened)(void);
@property (nonatomic, copy) void (^editorClosed)(void);

@property (nonatomic, assign) bool useGalleryImageAsEditableItemImage;
@property (nonatomic, weak) ModernGalleryController *controller;

@property (nonatomic, readonly, strong) MediaPickerGalleryInterfaceView *interfaceView;
@property (nonatomic, readonly, strong) MediaPickerGallerySelectedItemsModel *selectedItemsModel;

@property (nonatomic, copy) NSInteger (^externalSelectionCount)(void);

@property (nonatomic, readonly) MediaSelectionContext *selectionContext;
@property (nonatomic, strong) SuggestionContext *suggestionContext;

- (instancetype)initWithItems:(NSArray *)items focusItem:(id<ModernGalleryItem>)focusItem selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext hasCaptions:(bool)hasCaptions inhibitDocumentCaptions:(bool)inhibitDocumentCaptions hasSelectionPanel:(bool)hasSelectionPanel;

- (void)setCurrentItem:(id<MediaSelectableItem>)item direction:(ModernGalleryScrollAnimationDirection)direction;

@end
