#import <UIKit/UIKit.h>

@interface MediaPickerGalleryVideoScrubberThumbnailView : UIView

- (instancetype)initWithImage:(UIImage *)image originalSize:(CGSize)originalSize cropRect:(CGRect)cropRect cropOrientation:(UIImageOrientation)cropOrientation cropMirrored:(bool)cropMirrored;

@end
