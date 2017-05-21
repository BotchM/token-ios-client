#import "ModernGalleryImageItemView.h"

#import "ModernGalleryImageItem.h"

#import "ImageInfo.h"
#import "ImageView.h"

#import "Font.h"

#import "ModernGalleryImageItemImageView.h"
#import "ModernGalleryZoomableScrollView.h"

#import "MessageImageViewOverlayView.h"
#import "Common.h"

//#import "ModernGalleryEmbeddedStickersHeaderView.h"

#import "DocumentMediaAttachment.h"

//#import "TGStickersMenu.h"
//#import "TGDownloadMessagesSignal.h"
#import "ImageMediaAttachment.h"

#import "MenuSheetController.h"
//#import "TGMultipleStickerPacksCollectionItemView.h"

@interface ModernGalleryImageItemView ()
{
    MessageImageViewOverlayView *_progressView;
    dispatch_block_t _resetBlock;
    
    bool _progressVisible;
    void (^_currentAvailabilityObserver)(bool);
    
   // ModernGalleryEmbeddedStickersHeaderView *_stickersHeaderView;
    
    SMetaDisposable *_stickersInfoDisposable;
    //SVariable *_stickersInfo;
    bool _requestedStickersInfo;
}

@end

@implementation ModernGalleryImageItemView

- (UIImage *)shadowImage
{
    static UIImage *image = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
    {
        
    });
    return image;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self != nil)
    {
        __weak ModernGalleryImageItemView *weakSelf = self;
        _imageView = [[ModernGalleryImageItemImageView alloc] init];
        _imageView.progressChanged = ^(CGFloat value)
        {
            __strong ModernGalleryImageItemView *strongSelf = weakSelf;
            [strongSelf setProgressVisible:value < 1.0f - FLT_EPSILON value:value animated:true];
        };
        _imageView.availabilityStateChanged = ^(bool available)
        {
            __strong ModernGalleryImageItemView *strongSelf = weakSelf;
            if (strongSelf != nil)
            {
                if (strongSelf->_currentAvailabilityObserver)
                    strongSelf->_currentAvailabilityObserver(available);
            }
        };
        [self.scrollView addSubview:_imageView];
        
//        _stickersInfoDisposable = [[SMetaDisposable alloc] init];
//        _stickersInfo = [[SVariable alloc] init];
    }
    return self;
}

- (void)dealloc {
//    [_stickersInfoDisposable dispose];
//    [_stickersInfo set:[SSignal single:nil]];
}

- (void)prepareForRecycle
{
    [_imageView reset];
    if (_resetBlock)
    {
        _resetBlock();
        _resetBlock = nil;
    }
    [self setProgressVisible:false value:0.0f animated:false];
//    [_stickersInfoDisposable setDisposable:nil];
//    [_stickersInfo set:[SSignal single:nil]];
    _requestedStickersInfo = false;
}

- (UIView *)headerView {
    if ([self.item isKindOfClass:[ModernGalleryImageItem class]] && ((ModernGalleryImageItem *)self.item).hasStickers) {
//        if (_stickersHeaderView == nil) {
//            _stickersHeaderView = [[ModernGalleryEmbeddedStickersHeaderView alloc] init];
//            __weak ModernGalleryImageItemView *weakSelf = self;
//            _stickersHeaderView.showEmbeddedStickers = ^{
//                __strong ModernGalleryImageItemView *strongSelf = weakSelf;
//                if (strongSelf != nil) {
//                    [strongSelf showEmbeddedStickerPacks];
//                }
//            };
        //}
       // return _stickersHeaderView;
    }
    
    return nil;
}

- (void)setItem:(ModernGalleryImageItem *)item synchronously:(bool)synchronously
{
    [super setItem:item synchronously:synchronously];
    
    _imageSize = item.imageSize;
    if (item.loader != nil)
        _resetBlock = [item.loader(_imageView, synchronously) copy];
    else if (item.uri == nil)
        [_imageView reset];
    else
        [_imageView loadUri:item.uri withOptions:@{ImageViewOptionSynchronous: @(synchronously)}];
    
    [self reset];
}

- (SSignal *)contentAvailabilityStateSignal
{
    __weak ModernGalleryImageItemView *weakSelf = self;
    return [[SSignal alloc] initWithGenerator:^id<SDisposable>(SSubscriber *subscriber)
    {
        __strong ModernGalleryImageItemView *strongSelf = weakSelf;
        if (strongSelf != nil)
        {
            [subscriber putNext:@([strongSelf->_imageView isAvailableNow])];
            strongSelf->_currentAvailabilityObserver = ^(bool available)
            {
                [subscriber putNext:@(available)];
            };
        }
        
        return nil;
    }];
}

- (CGSize)contentSize
{
    return _imageSize;
}

- (UIView *)contentView
{
    return _imageView;
}

- (UIView *)transitionView
{
    return self.containerView;
}

- (CGRect)transitionViewContentRect
{
    return [_imageView convertRect:_imageView.bounds toView:[self transitionView]];
}

- (void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    if (_progressView != nil)
    {
        _progressView.frame = (CGRect){{CGFloor((frame.size.width - _progressView.frame.size.width) / 2.0f), CGFloor((frame.size.height - _progressView.frame.size.height) / 2.0f)}, _progressView.frame.size};
    }
}

- (void)setProgressVisible:(bool)progressVisible value:(CGFloat)value animated:(bool)animated
{
    _progressVisible = progressVisible;
    
    if (progressVisible && _progressView == nil)
    {
        _progressView = [[MessageImageViewOverlayView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 50.0f, 50.0f)];
        _progressView.userInteractionEnabled = false;
        
        _progressView.frame = (CGRect){{CGFloor((self.frame.size.width - _progressView.frame.size.width) / 2.0f), CGFloor((self.frame.size.height - _progressView.frame.size.height) / 2.0f)}, _progressView.frame.size};
    }
    
    if (progressVisible)
    {
        if (_progressView.superview == nil)
            [self.containerView addSubview:_progressView];
        
        _progressView.alpha = 1.0f;
    }
    else if (_progressView.superview != nil)
    {
        if (animated)
        {
            [UIView animateWithDuration:0.3 delay:0.0 options:UIViewAnimationOptionBeginFromCurrentState animations:^
             {
                 _progressView.alpha = 0.0f;
             } completion:^(BOOL finished)
             {
                 if (finished)
                     [_progressView removeFromSuperview];
             }];
        }
        else
            [_progressView removeFromSuperview];
    }
    
    [_progressView setProgress:value cancelEnabled:false animated:animated];
}

//- (void)showEmbeddedStickerPacks {
//    if ([self.item isKindOfClass:[ModernGalleryImageItem class]] && ((ModernGalleryImageItem *)self.item).hasStickers) {
//        NSMutableArray *stickerPackReferences = [[NSMutableArray alloc] init];
//        for (DocumentMediaAttachment *document in ((ModernGalleryImageItem *)self.item).embeddedStickerDocuments) {
//            for (id attribute in document.attributes) {
//                if ([attribute isKindOfClass:[DocumentAttributeSticker class]]) {
//                    if (((DocumentAttributeSticker *)attribute).packReference != nil) {
//                        if (![stickerPackReferences containsObject:((DocumentAttributeSticker *)attribute).packReference]) {
//                            [stickerPackReferences addObject:((DocumentAttributeSticker *)attribute).packReference];
//                        }
//                    }
//                }
//            }
//        }
//        
//        ViewController *controller = [self.delegate parentControllerForPresentation];
//        if (controller != nil) {
//            CGRect sourceRect = _stickersHeaderView.bounds;
//            if (stickerPackReferences.count == 1) {
//                [TGStickersMenu presentInParentController:controller stickerPackReference:stickerPackReferences[0] showShareAction:false sendSticker:nil stickerPackRemoved:nil stickerPackHidden:nil sourceView:_stickersHeaderView sourceRect:^CGRect
//                 {
//                     return sourceRect;
//                 }];
//            } else if (stickerPackReferences.count != 0) {
//                
//            } else if (((ModernGalleryImageItem *)self.item).imageId != 0) {
//                if (!_requestedStickersInfo) {
//                    _requestedStickersInfo = true;
//                    ImageMediaAttachment *imageMedia = [[ImageMediaAttachment alloc] init];
//                    imageMedia.imageId = ((ModernGalleryImageItem *)self.item).imageId;
//                    imageMedia.accessHash = ((ModernGalleryImageItem *)self.item).accessHash;
//                    [_stickersInfo set:[TGDownloadMessagesSignal mediaStickerpacks:imageMedia]];
//                }
//                
//                __weak ModernGalleryImageItemView *weakSelf = self;
//                [_stickersInfoDisposable setDisposable:[[[[[_stickersInfo signal] filter:^bool(id next) {
//                    return next != nil;
//                }] take:1] deliverOn:[SQueue mainQueue]] startWithNext:^(NSArray<TGStickerPack *> *stickerPacks) {
//                    __strong ModernGalleryImageItemView *strongSelf = weakSelf;
//                    if (strongSelf != nil) {
//                        if (stickerPacks.count == 1) {
//                            ViewController *controller = [strongSelf.delegate parentControllerForPresentation];
//                            [TGStickersMenu presentInParentController:controller stickerPack:stickerPacks[0] showShareAction:false sendSticker:nil stickerPackRemoved:nil stickerPackHidden:nil stickerPackArchived:false stickerPackIsMask:stickerPacks[0].isMask sourceView:strongSelf->_stickersHeaderView sourceRect:^CGRect{
//                                return sourceRect;
//                            }];
//                        } else if (stickerPacks.count != 0) {
//                            [strongSelf previewMultipleStickerPacks:stickerPacks];
//                        }
//                    }
//                }]];
//            }
//        }
//    }
//}

//- (void)previewStickerPack:(TGStickerPack *)stickerPack inMenuController:(MenuSheetController *)menuController {
//    ViewController *controller = [self.delegate parentControllerForPresentation];
//    if (controller != nil) {
//        CGRect sourceRect = _stickersHeaderView.bounds;
//        [TGStickersMenu presentWithParentController:controller packReference:nil stickerPack:stickerPack showShareAction:false sendSticker:nil stickerPackRemoved:nil stickerPackHidden:nil stickerPackArchived:false stickerPackIsMask:stickerPack.isMask sourceView:_stickersHeaderView sourceRect:^CGRect{
//            return sourceRect;
//        } centered:true existingController:menuController];
//    }
//}

//- (void)previewMultipleStickerPacks:(NSArray<TGStickerPack *> *)stickerPacks {
//    MenuSheetController *controller = [[MenuSheetController alloc] init];
//    __weak MenuSheetController *weakController = controller;
//    controller.dismissesByOutsideTap = true;
//    controller.hasSwipeGesture = true;
//    controller.narrowInLandscape = true;
//    CGRect sourceRect = [_stickersHeaderView convertRect:_stickersHeaderView.bounds toView:self];;
//    controller.sourceRect = ^CGRect { return sourceRect; };
//    controller.permittedArrowDirections = 0;
//    
//    NSMutableArray *itemViews = [[NSMutableArray alloc] init];
//    TGMultipleStickerPacksCollectionItemView *collectionItem = [[TGMultipleStickerPacksCollectionItemView alloc] init];
//    [itemViews addObject:collectionItem];
//    __weak ModernGalleryImageItemView *weakSelf = self;
//    collectionItem.previewPack = ^(TGStickerPack *pack, __unused id<TGStickerPackReference> packReference) {
//        __strong MenuSheetController *strongController = weakController;
//        if (strongController == nil)
//            return;
//        
//        //[strongController dismissAnimated:true manual:true];
//        
//        if (pack != nil) {
//            __strong ModernGalleryImageItemView *strongSelf = weakSelf;
//            if (strongSelf != nil) {
//                [strongSelf previewStickerPack:pack inMenuController:strongController];
//            }
//        }
//    };
//    [collectionItem setStickerPacks:stickerPacks animated:false];
//    
//    collectionItem.collapseInLandscape = false;
//    
//    MenuSheetButtonItemView *cancelButton = [[MenuSheetButtonItemView alloc] initWithTitle:TGLocalized(@"Cancel") type:MenuSheetButtonTypeCancel action:^
//    {
//        __strong MenuSheetController *strongController = weakController;
//        if (strongController == nil)
//            return;
//        
//        [strongController dismissAnimated:true manual:true];
//    }];
//    [itemViews addObject:cancelButton];
//    
//    [controller setItemViews:itemViews];
//    
//    ViewController *parentController = [self.delegate parentControllerForPresentation];
//    if (parentController != nil) {
//        [controller presentInViewController:parentController sourceView:parentController.view animated:true];
//    }
//}

@end
