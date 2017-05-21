#import <UIKit/UIKit.h>

@class StaticBackdropAreaData;

@interface MessageImageAdditionalDataView : UIView

- (void)setBackdropArea:(StaticBackdropAreaData *)backdropArea transitionDuration:(NSTimeInterval)transitionDuration;
- (void)setText:(NSString *)text;

@end
