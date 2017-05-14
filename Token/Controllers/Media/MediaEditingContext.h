#import <SSignalKit/SSignalKit.h>
#import <UIKit/UIKit.h>

@protocol MediaEditableItem <NSObject>

@property (nonatomic, readonly) NSString *uniqueIdentifier;

@optional
@property (nonatomic, readonly) CGSize originalSize;

- (SSignal *)thumbnailImageSignal;
- (SSignal *)screenImageSignal:(NSTimeInterval)position;
- (SSignal *)originalImageSignal:(NSTimeInterval)position;

@end


@class PaintingData;

@protocol MediaEditAdjustments <NSObject>

@property (nonatomic, readonly) CGSize originalSize;
@property (nonatomic, readonly) CGRect cropRect;
@property (nonatomic, readonly) UIImageOrientation cropOrientation;
@property (nonatomic, readonly) CGFloat cropLockedAspectRatio;
@property (nonatomic, readonly) bool cropMirrored;
@property (nonatomic, readonly) PaintingData *paintingData;

- (bool)hasPainting;

- (bool)cropAppliedForAvatar:(bool)forAvatar;
- (bool)isDefaultValuesForAvatar:(bool)forAvatar;

- (bool)isCropEqualWith:(id<MediaEditAdjustments>)adjusments;

@end


@interface MediaEditingContext : NSObject

@property (nonatomic, readonly) bool inhibitEditing;

+ (instancetype)contextForCaptionsOnly;

- (SSignal *)imageSignalForItem:(NSObject<MediaEditableItem> *)item;
- (SSignal *)imageSignalForItem:(NSObject<MediaEditableItem> *)item withUpdates:(bool)withUpdates;
- (SSignal *)thumbnailImageSignalForItem:(NSObject<MediaEditableItem> *)item;
- (SSignal *)thumbnailImageSignalForItem:(id<MediaEditableItem>)item withUpdates:(bool)withUpdates synchronous:(bool)synchronous;
- (SSignal *)fastImageSignalForItem:(NSObject<MediaEditableItem> *)item withUpdates:(bool)withUpdates;

- (void)setImage:(UIImage *)image thumbnailImage:(UIImage *)thumbnailImage forItem:(id<MediaEditableItem>)item synchronous:(bool)synchronous;
- (void)setFullSizeImage:(UIImage *)image forItem:(id<MediaEditableItem>)item;

- (void)setTemporaryRep:(id)rep forItem:(id<MediaEditableItem>)item;

- (SSignal *)fullSizeImageUrlForItem:(id<MediaEditableItem>)item;

- (NSString *)captionForItem:(NSObject<MediaEditableItem> *)item;
- (SSignal *)captionSignalForItem:(NSObject<MediaEditableItem> *)item;
- (void)setCaption:(NSString *)caption forItem:(NSObject<MediaEditableItem> *)item;

- (NSObject<MediaEditAdjustments> *)adjustmentsForItem:(NSObject<MediaEditableItem> *)item;
- (SSignal *)adjustmentsSignalForItem:(NSObject<MediaEditableItem> *)item;
- (void)setAdjustments:(NSObject<MediaEditAdjustments> *)adjustments forItem:(NSObject<MediaEditableItem> *)item;

- (UIImage *)paintingImageForItem:(NSObject<MediaEditableItem> *)item;
- (bool)setPaintingData:(NSData *)data image:(UIImage *)image forItem:(NSObject<MediaEditableItem> *)item dataUrl:(NSURL **)dataOutUrl imageUrl:(NSURL **)imageOutUrl forVideo:(bool)video;
- (void)clearPaintingData;

- (SSignal *)facesForItem:(NSObject<MediaEditableItem> *)item;
- (void)setFaces:(NSArray *)faces forItem:(NSObject<MediaEditableItem> *)item;

- (SSignal *)cropAdjustmentsUpdatedSignal;

- (void)requestOriginalThumbnailImageForItem:(id<MediaEditableItem>)item completion:(void (^)(UIImage *))completion;
- (void)requestOriginalImageForItem:(id<MediaEditableItem>)itemId completion:(void (^)(UIImage *image))completion;
- (void)setOriginalImage:(UIImage *)image forItem:(id<MediaEditableItem>)item synchronous:(bool)synchronous;

@end
