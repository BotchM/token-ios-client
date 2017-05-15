#import <Foundation/Foundation.h>
#import "MediaPickerGalleryModel.h"
#import "ModernGalleryController.h"

@class MediaSelectionContext;
@class MediaEditingContext;
@class SuggestionContext;
@class MediaPickerGalleryItem;
@class MediaAssetFetchResult;
@class MediaAssetMomentList;

@interface MediaPickerModernGalleryMixin : NSObject

@property (nonatomic, weak, readonly) MediaPickerGalleryModel *galleryModel;

@property (nonatomic, copy) void (^itemFocused)(MediaPickerGalleryItem *);

@property (nonatomic, copy) void (^willTransitionIn)();
@property (nonatomic, copy) void (^willTransitionOut)();
@property (nonatomic, copy) void (^didTransitionOut)();
@property (nonatomic, copy) UIView *(^referenceViewForItem)(MediaPickerGalleryItem *);

@property (nonatomic, copy) void (^completeWithItem)(MediaPickerGalleryItem *item);

@property (nonatomic, copy) void (^editorOpened)(void);
@property (nonatomic, copy) void (^editorClosed)(void);

- (instancetype)initWithItem:(id)item fetchResult:(MediaAssetFetchResult *)fetchResult parentController:(ViewController *)parentController thumbnailImage:(UIImage *)thumbnailImage selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext suggestionContext:(SuggestionContext *)suggestionContext hasCaptions:(bool)hasCaptions inhibitDocumentCaptions:(bool)inhibitDocumentCaptions asFile:(bool)asFile itemsLimit:(NSUInteger)itemsLimit;

- (instancetype)initWithItem:(id)item momentList:(MediaAssetMomentList *)momentList parentController:(ViewController *)parentController thumbnailImage:(UIImage *)thumbnailImage selectionContext:(MediaSelectionContext *)selectionContext editingContext:(MediaEditingContext *)editingContext suggestionContext:(SuggestionContext *)suggestionContext hasCaptions:(bool)hasCaptions inhibitDocumentCaptions:(bool)inhibitDocumentCaptions asFile:(bool)asFile itemsLimit:(NSUInteger)itemsLimit;

- (void)present;
- (void)updateWithFetchResult:(MediaAssetFetchResult *)fetchResult;

- (UIView *)currentReferenceView;

- (void)setThumbnailSignalForItem:(SSignal *(^)(id))thumbnailSignalForItem;

- (UIViewController *)galleryController;
- (void)setPreviewMode;

@end
