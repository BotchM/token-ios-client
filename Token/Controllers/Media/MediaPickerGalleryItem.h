#import "ModernGalleryImageItem.h"
#import "MediaAsset.h"

@interface MediaPickerGalleryItem : NSObject <ModernGalleryItem>

@property (nonatomic, strong) MediaAsset *asset;
@property (nonatomic, strong) UIImage *immediateThumbnailImage;
@property (nonatomic, assign) bool asFile;

- (instancetype)initWithAsset:(MediaAsset *)asset;

@end
