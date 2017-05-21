#import <Foundation/Foundation.h>
#import <UIKit+AFNetworking.h>
#import <CoreGraphics/CoreGraphics.h>

@interface ModernGalleryComplexTransitionDescription : NSObject

@property (nonatomic, strong) UIImage *overlayImage;
@property (nonatomic, assign) CGFloat cornerRadius;
@property (nonatomic, assign) UIEdgeInsets insets;

@end

@protocol ModernGalleryTransitionView <NSObject>

@required

- (UIImage *)transitionImage;

@optional

- (CGRect)transitionContentRect;

- (bool)hasComplexTransition;
- (ModernGalleryComplexTransitionDescription *)complexTransitionDescription;

@end
