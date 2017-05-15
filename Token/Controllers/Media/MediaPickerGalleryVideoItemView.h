#import "ModernGalleryItemView.h"
#import "ModernGalleryEditableItemView.h"
#import "ModernGalleryImageItemImageView.h"
#import "AVFoundation/AVFoundation.h"

@interface MediaPickerGalleryVideoItemView : ModernGalleryItemView <ModernGalleryEditableItemView>

@property (nonatomic, strong) ModernGalleryImageItemImageView *imageView;
@property (nonatomic, strong) AVPlayer *player;

@property (nonatomic, readonly) bool isPlaying;

@property (nonatomic, readonly) bool hasTrimming;
@property (nonatomic, readonly) CMTimeRange trimRange;

- (void)play;
- (void)stop;

- (void)playIfAvailable;

- (void)setPlayButtonHidden:(bool)hidden animated:(bool)animated;
- (void)toggleSendAsGif;

- (void)setScrubbingPanelApperanceLocked:(bool)locked;
- (void)setScrubbingPanelHidden:(bool)hidden animated:(bool)animated;
- (void)presentScrubbingPanelAfterReload:(bool)afterReload;

- (void)prepareForEditing;

- (UIImage *)screenImage;
- (UIImage *)transitionImage;
- (CGRect)editorTransitionViewRect;

@end
