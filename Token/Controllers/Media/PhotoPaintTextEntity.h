#import "PhotoPaintEntity.h"
#import "PaintSwatch.h"
#import "PhotoPaintFont.h"

@interface PhotoPaintTextEntity : PhotoPaintEntity

@property (nonatomic, strong) NSString *text;
@property (nonatomic, strong) PhotoPaintFont *font;
@property (nonatomic, strong) PaintSwatch *swatch;
@property (nonatomic, assign) CGFloat baseFontSize;
@property (nonatomic, assign) CGFloat maxWidth;
@property (nonatomic, assign) bool stroke;

- (instancetype)initWithText:(NSString *)text font:(PhotoPaintFont *)font swatch:(PaintSwatch *)swatch baseFontSize:(CGFloat)baseFontSize maxWidth:(CGFloat)maxWidth stroke:(bool)stroke;

@end
