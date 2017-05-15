#import "MediaPickerGalleryItem.h"
#import "ModernGallerySelectableItem.h"
#import "ModernGalleryEditableItem.h"
#import <AVFoundation/AVFoundation.h>

@protocol MediaEditAdjustments;

@interface MediaPickerGalleryVideoItem : MediaPickerGalleryItem <ModernGallerySelectableItem, ModernGalleryEditableItem>

@property (nonatomic, readonly) AVURLAsset *avAsset;
@property (nonatomic, readonly) CGSize dimensions;

- (instancetype)initWithFileURL:(NSURL *)fileURL dimensions:(CGSize)dimensions duration:(NSTimeInterval)duration;

- (SSignal *)durationSignal;

@end
