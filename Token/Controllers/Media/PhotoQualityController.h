#import "PhotoEditorTabController.h"

#import "VideoEditAdjustments.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;
@class PhotoEditorController;

@interface PhotoQualityController : ViewController

@property (nonatomic, weak) id item;

@property (nonatomic, weak) PhotoEditorController *mainController;

@property (nonatomic, copy) void(^beginTransitionOut)(void);
@property (nonatomic, copy) void(^finishedCombinedTransition)(void);

@property (nonatomic, assign) CGFloat toolbarLandscapeSize;

@property (nonatomic, readonly) MediaVideoConversionPreset preset;


- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor;

- (void)attachPreviewView:(PhotoEditorPreviewView *)previewView;

- (void)_animatePreviewViewTransitionOutToFrame:(CGRect)targetFrame saving:(bool)saving parentView:(UIView *)parentView completion:(void (^)(void))completion;

- (void)prepareForCombinedAppearance;
- (void)finishedCombinedAppearance;

@end
