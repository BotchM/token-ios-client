#import <UIKit/UIKit.h>
#import "PhotoPaintSettingsView.h"

@class PaintBrush;
@class PaintBrushPreview;

@interface PhotoBrushSettingsView : UIView <PhotoPaintPanelView>

@property (nonatomic, copy) void (^brushChanged)(PaintBrush *brush);

@property (nonatomic, strong) PaintBrush *brush;

- (instancetype)initWithBrushes:(NSArray *)brushes preview:(PaintBrushPreview *)preview;

@end
