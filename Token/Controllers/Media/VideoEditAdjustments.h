#import <AVFoundation/AVFoundation.h>
#import "MediaEditingContext.h"
#import <UIKit/UIKit.h>

typedef enum
{
    MediaVideoConversionPresetCompressedDefault,
    MediaVideoConversionPresetCompressedVeryLow,
    MediaVideoConversionPresetCompressedLow,
    MediaVideoConversionPresetCompressedMedium,
    MediaVideoConversionPresetCompressedHigh,
    MediaVideoConversionPresetCompressedVeryHigh,
    MediaVideoConversionPresetAnimation
} MediaVideoConversionPreset;

@interface VideoEditAdjustments : NSObject <MediaEditAdjustments>

@property (nonatomic, readonly) NSTimeInterval trimStartValue;
@property (nonatomic, readonly) NSTimeInterval trimEndValue;
@property (nonatomic, readonly) MediaVideoConversionPreset preset;
@property (nonatomic, readonly) bool sendAsGif;

- (CMTimeRange)trimTimeRange;

- (bool)trimApplied;

- (bool)isCropAndRotationEqualWith:(id<MediaEditAdjustments>)adjustments;

- (NSDictionary *)dictionary;

- (instancetype)editAdjustmentsWithPreset:(MediaVideoConversionPreset)preset maxDuration:(NSTimeInterval)maxDuration;
+ (instancetype)editAdjustmentsWithOriginalSize:(CGSize)originalSize preset:(MediaVideoConversionPreset)preset;

+ (instancetype)editAdjustmentsWithDictionary:(NSDictionary *)dictionary;

+ (instancetype)editAdjustmentsWithOriginalSize:(CGSize)originalSize
                                       cropRect:(CGRect)cropRect
                                cropOrientation:(UIImageOrientation)cropOrientation
                          cropLockedAspectRatio:(CGFloat)cropLockedAspectRatio
                                   cropMirrored:(bool)cropMirrored
                                 trimStartValue:(NSTimeInterval)trimStartValue
                                   trimEndValue:(NSTimeInterval)trimEndValue
                                   paintingData:(PaintingData *)paintingData
                                      sendAsGif:(bool)sendAsGif
                                         preset:(MediaVideoConversionPreset)preset;

@end

typedef VideoEditAdjustments MediaVideoEditAdjustments;

extern const NSTimeInterval VideoEditMinimumTrimmableDuration;
extern const NSTimeInterval VideoEditMaximumGifDuration;
