#import "ImageView.h"

@interface ModernGalleryImageItemImageView : ImageView

@property (nonatomic) bool isPartial;

@property (nonatomic, copy) void (^progressChanged)(CGFloat);
@property (nonatomic, copy) void (^availabilityStateChanged)(bool);

- (bool)isAvailableNow;

@end
