#import <UIKit/UIKit.h>

@class PhotoEditorView;
@class PaintingData;

@interface PhotoEditorPreviewView : UIView

@property (nonatomic, readonly) PhotoEditorView *imageView;
@property (nonatomic, readonly) UIImageView *paintingView;

@property (nonatomic, copy) void(^touchedDown)(void);
@property (nonatomic, copy) void(^touchedUp)(void);
@property (nonatomic, copy) void(^interactionEnded)(void);

@property (nonatomic, readonly) bool isTracking;

- (void)setSnapshotImage:(UIImage *)image;
- (void)setSnapshotView:(UIView *)view;
- (void)setPaintingImageWithData:(PaintingData *)values;
- (void)setPaintingHidden:(bool)hidden;

- (void)setSnapshotImageOnTransition:(UIImage *)image;

- (void)setCropRect:(CGRect)cropRect cropOrientation:(UIImageOrientation)cropOrientation cropRotation:(CGFloat)cropRotation cropMirrored:(bool)cropMirrored originalSize:(CGSize)originalSize;

- (UIView *)originalSnapshotView;

- (void)performTransitionInWithCompletion:(void (^)(void))completion;
- (void)setNeedsTransitionIn;
- (void)performTransitionInIfNeeded;

- (void)prepareTransitionFadeView;
- (void)performTransitionFade;

- (void)prepareForTransitionOut;

- (void)performTransitionToCropAnimated:(bool)animated;

@end
