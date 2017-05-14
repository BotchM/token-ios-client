#import <SSignalKit/SSignalKit.h>
#import <UIKit/UIKit.h>

@interface PaintFaceFeature : NSObject
{
    CGPoint _position;
}

@property (nonatomic, readonly) CGPoint position;

@end


@interface PaintFaceEye : PaintFaceFeature

@property (nonatomic, readonly, getter=isClosed) bool closed;

@end


@interface PaintFaceMouth : PaintFaceFeature

@property (nonatomic, readonly, getter=isSmiling) bool smiling;

@end


@interface PaintFace : NSObject

@property (nonatomic, readonly) NSInteger uuid;

@property (nonatomic, readonly) CGRect bounds;
@property (nonatomic, readonly) CGFloat angle;

@property (nonatomic, readonly) PaintFaceEye *leftEye;
@property (nonatomic, readonly) PaintFaceEye *rightEye;
@property (nonatomic, readonly) PaintFaceMouth *mouth;

- (CGPoint)foreheadPoint;
- (CGPoint)eyesCenterPointAndDistance:(CGFloat *)distance;
- (CGFloat)eyesAngle;
- (CGPoint)mouthPoint;
- (CGPoint)chinPoint;

@end


@interface PaintFaceDetector : NSObject

+ (SSignal *)detectFacesInImage:(UIImage *)image originalSize:(CGSize)originalSize;

@end


@interface PaintFaceUtils : NSObject

+ (CGFloat)transposeWidth:(CGFloat)width paintingSize:(CGSize)paintingSize originalSize:(CGSize)originalSize;
+ (CGPoint)transposePoint:(CGPoint)point paintingSize:(CGSize)paintingSize originalSize:(CGSize)originalSize;
+ (CGRect)transposeRect:(CGRect)rect paintingSize:(CGSize)paintingSize originalSize:(CGSize)originalSize;

@end
