#import "ModernGalleryItem.h"
#import <UIKit/UIKit.h>
#import <SSignalKit/SSignalKit.h>

@class ImageInfo;
@class ImageView;

@interface ModernGalleryImageItem : NSObject <ModernGalleryItem>

@property (nonatomic, readonly) NSString *uri;
@property (nonatomic, copy, readonly) dispatch_block_t (^loader)(ImageView *, bool);

@property (nonatomic, readonly) CGSize imageSize;
@property (nonatomic, strong) NSArray *embeddedStickerDocuments;
@property (nonatomic) bool hasStickers;
@property (nonatomic) int64_t imageId;
@property (nonatomic) int64_t accessHash;

- (instancetype)initWithUri:(NSString *)uri imageSize:(CGSize)imageSize;
- (instancetype)initWithLoader:(dispatch_block_t (^)(ImageView *, bool))loader imageSize:(CGSize)imageSize;
- (instancetype)initWithSignal:(SSignal *)signal imageSize:(CGSize)imageSize;

@end
