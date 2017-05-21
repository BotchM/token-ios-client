#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
    
CGSize ScaleToSize(CGSize size, CGSize maxSize);
CGSize ScaleToFillSize(CGSize size, CGSize maxSize);
    
CGFloat TGDegreesToRadians(CGFloat degrees);
CGFloat TGRadiansToDegrees(CGFloat radians);
    
UIImage *PhotoEditorCrop(UIImage *image, UIImage *paintingImage, UIImageOrientation orientation, CGFloat rotation, CGRect rect, bool mirrored, CGSize maxSize, CGSize originalSize, bool shouldResize);
UIImage *PhotoEditorVideoCrop(UIImage *image, UIImage *paintingImage, UIImageOrientation orientation, CGFloat rotation, CGRect rect, bool mirrored, CGSize maxSize, CGSize originalSize, bool shouldResize, bool useImageSize);
UIImage *PhotoEditorFitImage(UIImage *image, CGSize maxSize);
CGSize TGRotatedContentSize(CGSize contentSize, CGFloat rotation);
    
UIImageOrientation TGNextCWOrientationForOrientation(UIImageOrientation orientation);
UIImageOrientation TGNextCCWOrientationForOrientation(UIImageOrientation orientation);
CGFloat TGRotationForOrientation(UIImageOrientation orientation);
CGFloat TGCounterRotationForOrientation(UIImageOrientation orientation);
CGFloat TGRotationForInterfaceOrientation(UIInterfaceOrientation orientation);
CGAffineTransform TGTransformForVideoOrientation(AVCaptureVideoOrientation orientation, bool mirrored);
    
bool TGOrientationIsSideward(UIImageOrientation orientation, bool *mirrored);
UIImageOrientation TGMirrorSidewardOrientation(UIImageOrientation orientation);
    
UIImageOrientation VideoOrientationForAsset(AVAsset *asset, bool *mirrored);
CGAffineTransform VideoTransformForOrientation(UIImageOrientation orientation, CGSize size, CGRect cropRect, bool mirror);
CGAffineTransform VideoCropTransformForOrientation(UIImageOrientation orientation, CGSize size, bool rotateSize);
CGAffineTransform VideoTransformForCrop(UIImageOrientation orientation, CGSize size, bool mirrored);
    
CGSize TGTransformDimensionsWithTransform(CGSize dimensions, CGAffineTransform transform);
    
CGFloat TGRubberBandDistance(CGFloat offset, CGFloat dimension);
    
bool _CGPointEqualToPointWithEpsilon(CGPoint point1, CGPoint point2, CGFloat epsilon);
bool _CGRectEqualToRectWithEpsilon(CGRect rect1, CGRect rect2, CGFloat epsilon);
    
CGSize PhotoThumbnailSizeForCurrentScreen();
CGSize PhotoEditorScreenImageMaxSize();
    
extern const CGSize PhotoEditorResultImageMaxSize;
    
#ifdef __cplusplus
}
#endif
