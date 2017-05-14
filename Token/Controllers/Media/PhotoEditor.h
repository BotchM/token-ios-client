#import <Foundation/Foundation.h>
#import <SSignalKit/SSignalKit.h>

#import "VideoEditAdjustments.h"

@class PhotoEditorPreviewView;
@class PaintingData;

@interface PhotoEditor : NSObject

@property (nonatomic, assign) CGSize originalSize;
@property (nonatomic, assign) CGRect cropRect;
@property (nonatomic, readonly) CGSize rotatedCropSize;
@property (nonatomic, assign) CGFloat cropRotation;
@property (nonatomic, assign) UIImageOrientation cropOrientation;
@property (nonatomic, assign) CGFloat cropLockedAspectRatio;
@property (nonatomic, assign) bool cropMirrored;
@property (nonatomic, strong) PaintingData *paintingData;
@property (nonatomic, assign) NSTimeInterval trimStartValue;
@property (nonatomic, assign) NSTimeInterval trimEndValue;
@property (nonatomic, assign) bool sendAsGif;
@property (nonatomic, assign) MediaVideoConversionPreset preset;

@property (nonatomic, weak) PhotoEditorPreviewView *previewOutput;
@property (nonatomic, readonly) NSArray *tools;

@property (nonatomic, readonly) bool processing;
@property (nonatomic, readonly) bool readyForProcessing;

- (instancetype)initWithOriginalSize:(CGSize)originalSize adjustments:(id<MediaEditAdjustments>)adjustments forVideo:(bool)forVideo;

- (void)cleanup;

- (void)setImage:(UIImage *)image forCropRect:(CGRect)cropRect cropRotation:(CGFloat)cropRotation cropOrientation:(UIImageOrientation)cropOrientation cropMirrored:(bool)cropMirrored fullSize:(bool)fullSize;

- (void)processAnimated:(bool)animated completion:(void (^)(void))completion;

- (void)createResultImageWithCompletion:(void (^)(UIImage *image))completion;
- (UIImage *)currentResultImage;

- (bool)hasDefaultCropping;

- (SSignal *)histogramSignal;

- (id<MediaEditAdjustments>)exportAdjustments;
- (id<MediaEditAdjustments>)exportAdjustmentsWithPaintingData:(PaintingData *)paintingData;

@end