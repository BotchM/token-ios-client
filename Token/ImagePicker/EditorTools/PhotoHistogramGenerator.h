#import "PhotoEditorRawDataOutput.h"

@class PhotoHistogram;

@interface PhotoHistogramGenerator : PhotoEditorRawDataOutput

@property (nonatomic, copy) void (^histogramReady)(PhotoHistogram *histogram);

@end
