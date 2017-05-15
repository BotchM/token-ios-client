#import <UIKit/UIKit.h>

@class StaticBackdropAreaData;

@interface MessageImageViewTimestampView : UIView

- (instancetype)initWithFrame:(CGRect)frame;

- (void)setBackdropArea:(StaticBackdropAreaData *)backdropArea transitionDuration:(NSTimeInterval)transitionDuration;
- (void)setTimestampColor:(UIColor *)timestampColor;
- (void)setTimestampString:(NSString *)timestampString signatureString:(NSString *)signatureString displayCheckmarks:(bool)displayCheckmarks checkmarkValue:(int)checkmarkValue displayViews:(bool)displayViews viewsValue:(int)viewsValue animated:(bool)animated;
- (void)setDisplayProgress:(bool)displayProgress;
- (void)setIsBroadcast:(bool)setIsBroadcast;
- (void)setTransparent:(bool)transparent;
- (CGSize)sizeForMaxWidth:(CGFloat)maxWidth;

@end
