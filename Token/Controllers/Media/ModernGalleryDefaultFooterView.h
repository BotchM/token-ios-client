#import <UIKit/UIKit.h>

#import "ModernGalleryItem.h"

@protocol ModernGalleryDefaultFooterView <NSObject>

@optional
- (void)setTransitionOutProgress:(CGFloat)transitionOutProgress;
- (void)setContentHidden:(bool)contentHidden;

@required

- (void)setItem:(id<ModernGalleryItem>)item;

@end
