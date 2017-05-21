#import <SSignalKit/SSignalKit.h>

#import "VideoEditAdjustments.h"

@interface MediaVideoFileWatcher : NSObject
{
    NSURL *_fileURL;
}

- (void)setupWithFileURL:(NSURL *)fileURL;
- (id)fileUpdated:(bool)completed;

@end


@interface MediaVideoConverter : NSObject

+ (SSignal *)convertAVAsset:(AVAsset *)avAsset adjustments:(MediaVideoEditAdjustments *)adjustments watcher:(MediaVideoFileWatcher *)watcher;
+ (SSignal *)convertAVAsset:(AVAsset *)avAsset adjustments:(MediaVideoEditAdjustments *)adjustments watcher:(MediaVideoFileWatcher *)watcher inhibitAudio:(bool)inhibitAudio;
+ (SSignal *)hashForAVAsset:(AVAsset *)avAsset adjustments:(MediaVideoEditAdjustments *)adjustments;

+ (NSUInteger)estimatedSizeForPreset:(MediaVideoConversionPreset)preset duration:(NSTimeInterval)duration hasAudio:(bool)hasAudio;
+ (MediaVideoConversionPreset)bestAvailablePresetForDimensions:(CGSize)dimensions;

@end


@interface MediaVideoConversionResult : NSObject

@property (nonatomic, readonly) NSURL *fileURL;
@property (nonatomic, readonly) NSUInteger fileSize;
@property (nonatomic, readonly) NSTimeInterval duration;
@property (nonatomic, readonly) CGSize dimensions;
@property (nonatomic, readonly) UIImage *coverImage;
@property (nonatomic, readonly) id liveUploadData;

- (NSDictionary *)dictionary;

@end
