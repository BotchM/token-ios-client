#import "PGCameraMomentSegment.h"

@class Camera;

@interface PGCameraMomentSession : NSObject

@property (nonatomic, copy) void (^beganCapture)(void);
@property (nonatomic, copy) void (^finishedCapture)(void);
@property (nonatomic, copy) bool (^captureIsAvailable)(void);
@property (nonatomic, copy) void (^durationChanged)(NSTimeInterval);

@property (nonatomic, readonly) bool isCapturing;
@property (nonatomic, readonly) UIImage *previewImage;
@property (nonatomic, readonly) bool hasSegments;

@property (nonatomic, readonly) PGCameraMomentSegment *lastSegment;

- (instancetype)initWithCamera:(Camera *)camera;

- (void)captureSegment;
- (void)commitSegment;

- (void)addSegment:(PGCameraMomentSegment *)segment;
- (void)removeSegment:(PGCameraMomentSegment *)segment;
- (void)removeLastSegment;
- (void)removeAllSegments;

@end
