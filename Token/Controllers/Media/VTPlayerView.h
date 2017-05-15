#import <UIKit/UIKit.h>

#import <CoreVideo/CoreVideo.h>

@interface VTPlayerView : UIView

- (void)displayPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end
