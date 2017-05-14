#import "GPUImageFilter.h"

typedef enum
{
    PGPhotoEnhanceColorConversionRGBToHSVMode,
    PGPhotoEnhanceColorConversionHSVToRGBMode
} PGPhotoEnhanceColorConversionMode;

@interface PhotoEnhanceColorConversionFilter : GPUImageFilter

- (instancetype)initWithMode:(PGPhotoEnhanceColorConversionMode)mode;

@end
