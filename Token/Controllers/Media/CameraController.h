#import "OverlayController.h"
#import "OverlayControllerWindow.h"

@class Camera;
@class CameraPreviewView;
@class SuggestionContext;
@class VideoEditAdjustments;

typedef enum {
    CameraControllerGenericIntent,
    CameraControllerAvatarIntent,
} CameraControllerIntent;

@interface CameraControllerWindow : OverlayControllerWindow

@end

@interface CameraController : OverlayController

@property (nonatomic, assign) bool liveUploadEnabled;
@property (nonatomic, assign) bool shouldStoreCapturedAssets;

@property (nonatomic, assign) bool allowCaptions;
@property (nonatomic, assign) bool inhibitDocumentCaptions;

@property (nonatomic, copy) void(^finishedWithPhoto)(UIImage *resultImage, NSString *caption, NSArray *stickers);
@property (nonatomic, copy) void(^finishedWithVideo)(NSURL *videoURL, UIImage *previewImage, NSTimeInterval duration, CGSize dimensions, VideoEditAdjustments *adjustments, NSString *caption, NSArray *stickers);

@property (nonatomic, copy) void(^beginTransitionOut)(void);
@property (nonatomic, copy) void(^finishedTransitionOut)(void);

@property (nonatomic, strong) SuggestionContext *suggestionContext;

- (instancetype)initWithIntent:(CameraControllerIntent)intent
NS_SWIFT_NAME(init(intent:));

- (instancetype)initWithCamera:(Camera *)camera previewView:(CameraPreviewView *)previewView intent:(CameraControllerIntent)intent
NS_SWIFT_NAME(init(camera:previewView:intent:));

+ (UIInterfaceOrientation)_interfaceOrientationForDeviceOrientation:(UIDeviceOrientation)orientation;

@end
