#import <UIKit/UIKit.h>
#import "PhotoPaintSettingsView.h"
#import "PhotoPaintFont.h"

@interface PhotoTextSettingsView : UIView <PhotoPaintPanelView>

@property (nonatomic, copy) void (^fontChanged)(PhotoPaintFont *font);
@property (nonatomic, copy) void (^strokeChanged)(bool stroke);

@property (nonatomic, strong) PhotoPaintFont *font;
@property (nonatomic, assign) bool stroke;

- (instancetype)initWithFonts:(NSArray *)fonts selectedFont:(PhotoPaintFont *)font selectedStroke:(bool)selectedStroke;

@end
