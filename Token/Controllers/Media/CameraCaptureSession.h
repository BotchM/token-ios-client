#import <AVFoundation/AVFoundation.h>

#import "Camera.h"

@class CameraMovieWriter;

@interface CameraCaptureSession : AVCaptureSession

@property (nonatomic, readonly) AVCaptureDevice *videoDevice;
@property (nonatomic, readonly) AVCaptureStillImageOutput *imageOutput;
@property (nonatomic, readonly) AVCaptureVideoDataOutput *videoOutput;
@property (nonatomic, readonly) AVCaptureAudioDataOutput *audioOutput;
@property (nonatomic, readonly) CameraMovieWriter *movieWriter;

@property (nonatomic, assign) bool alwaysSetFlash;
@property (nonatomic, assign) PGCameraMode currentMode;
@property (nonatomic, assign) PGCameraFlashMode currentFlashMode;

@property (nonatomic, assign) PGCameraPosition currentCameraPosition;
@property (nonatomic, readonly) PGCameraPosition preferredCameraPosition;

@property (nonatomic, readonly) bool isZoomAvailable;
@property (nonatomic, assign) CGFloat zoomLevel;

@property (nonatomic, readonly) CGPoint focusPoint;

@property (nonatomic, copy) void(^outputSampleBuffer)(CMSampleBufferRef sampleBuffer, AVCaptureConnection *connection);

@property (nonatomic, copy) void(^changingPosition)(void);
@property (nonatomic, copy) bool(^requestPreviewIsMirrored)(void);

- (instancetype)initWithMode:(PGCameraMode)mode position:(PGCameraPosition)position;

- (void)performInitialConfigurationWithCompletion:(void (^)(void))completion;

- (void)setFocusPoint:(CGPoint)point focusMode:(AVCaptureFocusMode)focusMode exposureMode:(AVCaptureExposureMode)exposureMode monitorSubjectAreaChange:(bool)monitorSubjectAreaChange;
- (void)setExposureTargetBias:(CGFloat)bias;

- (bool)isResetNeeded;
- (void)reset;
- (void)resetFlashMode;

- (void)startVideoRecordingWithOrientation:(AVCaptureVideoOrientation)orientation mirrored:(bool)mirrored completion:(void (^)(NSURL *outputURL, CGAffineTransform transform, CGSize dimensions, NSTimeInterval duration, bool success))completion;
- (void)stopVideoRecording;

- (void)captureNextFrameCompletion:(void (^)(UIImage * image))completion;

+ (AVCaptureDevice *)_deviceWithCameraPosition:(PGCameraPosition)position;

+ (bool)_isZoomAvailableForDevice:(AVCaptureDevice *)device;

@end