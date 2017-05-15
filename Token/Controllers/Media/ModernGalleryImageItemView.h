#import "ModernGalleryZoomableItemView.h"

@class ModernGalleryImageItemImageView;

@interface ModernGalleryImageItemView : ModernGalleryZoomableItemView

@property (nonatomic) CGSize imageSize;

@property (nonatomic, strong) ModernGalleryImageItemImageView *imageView;

@end
