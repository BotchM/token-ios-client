#import "PhotoPaintEntityView.h"
#import "PhotoPaintTextEntity.h"

@class PaintSwatch;

@interface PhotoTextSelectionView : PhotoPaintEntitySelectionView

@end


@interface PhotoTextEntityView : PhotoPaintEntityView

@property (nonatomic, readonly) PhotoPaintTextEntity *entity;

@property (nonatomic, readonly) bool isEmpty;

@property (nonatomic, copy) void (^beganEditing)(PhotoTextEntityView *);
@property (nonatomic, copy) void (^finishedEditing)(PhotoTextEntityView *);

- (instancetype)initWithEntity:(PhotoPaintTextEntity *)entity;
- (void)setFont:(PhotoPaintFont *)font;
- (void)setSwatch:(PaintSwatch *)swatch;
- (void)setStroke:(bool)stroke;

@property (nonatomic, readonly) bool isEditing;
- (void)beginEditing;
- (void)endEditing;

@end


@interface PhotoTextView : UITextView

@property (nonatomic, strong) UIColor *strokeColor;
@property (nonatomic, assign) CGFloat strokeWidth;
@property (nonatomic, assign) CGPoint strokeOffset;

@end
