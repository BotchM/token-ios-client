#import "OverlayController.h"

@class CameraShotMetadata;
@class PhotoEditorValues;
@class SuggestionContext;

@interface CameraPhotoPreviewController : OverlayController

@property (nonatomic, assign) bool allowCaptions;

@property (nonatomic, copy) CGRect(^beginTransitionIn)(void);
@property (nonatomic, copy) CGRect(^beginTransitionOut)(CGRect referenceFrame);

@property (nonatomic, copy) void(^finishedTransitionIn)(void);

@property (nonatomic, copy) void (^photoEditorShown)(void);
@property (nonatomic, copy) void (^photoEditorHidden)(void);

@property (nonatomic, copy) void(^retakePressed)(void);
@property (nonatomic, copy) void(^sendPressed)(UIImage *resultImage, NSString *caption, NSArray *stickers);

@property (nonatomic, strong) SuggestionContext *suggestionContext;
@property (nonatomic, assign) bool shouldStoreAssets;

- (instancetype)initWithImage:(UIImage *)image metadata:(CameraShotMetadata *)metadata;
- (instancetype)initWithImage:(UIImage *)image metadata:(CameraShotMetadata *)metadata backButtonTitle:(NSString *)backButtonTitle;

@end
