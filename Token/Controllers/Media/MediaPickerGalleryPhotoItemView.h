#import "ModernGalleryZoomableItemView.h"
#import "ModernGalleryEditableItemView.h"
#import "ModernGalleryImageItemImageView.h"

@interface MediaPickerGalleryPhotoItemView : ModernGalleryZoomableItemView <ModernGalleryEditableItemView>

@property (nonatomic) CGSize imageSize;

@property (nonatomic, strong) ModernGalleryImageItemImageView *imageView;

@end
