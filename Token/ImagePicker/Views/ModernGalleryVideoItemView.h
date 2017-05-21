#import "ModernGalleryItemView.h"
#import "ModernGalleryZoomableItemView.h"

@class ImageView;
@class AVPlayer;

@interface ModernGalleryVideoItemView : ModernGalleryItemView

@property (nonatomic, strong) ImageView *imageView;
@property (nonatomic, strong) AVPlayer *player;
@property (nonatomic) CGSize videoDimensions;

- (bool)shouldLoopVideo:(NSUInteger)currentLoopCount;

- (void)play;
- (void)loadAndPlay;
- (void)hidePlayButton;
- (void)stop;
- (void)stopForOutTransition;

- (void)_willPlay;

@end
