#import <UIKit/UIKit.h>

#import <SSignalKit/SSignalKit.h>

extern NSString *ImageViewOptionKeepCurrentImageAsPlaceholder;
extern NSString *ImageViewOptionEmbeddedImage;
extern NSString *ImageViewOptionSynchronous;

@interface ImageView : UIImageView
{
    UIImageView *_extendedInsetsImageView;
}

@property (nonatomic) bool expectExtendedEdges;
@property (nonatomic) bool legacyAutomaticProgress;

- (void)loadUri:(NSString *)uri withOptions:(NSDictionary *)options;
- (void)reset;

- (void)performTransitionToImage:(UIImage *)image partial:(bool)partial duration:(NSTimeInterval)duration;
- (void)performProgressUpdate:(CGFloat)progress;
- (UIImage *)currentImage;

- (void)setSignal:(SSignal *)signal;

- (void)_commitImage:(UIImage *)image partial:(bool)partial loadTime:(NSTimeInterval)loadTime;
- (void)_updateProgress:(float)value;

@end
