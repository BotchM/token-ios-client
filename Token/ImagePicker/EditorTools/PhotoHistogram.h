#import <Foundation/Foundation.h>
#import "CurvesTool.h"

@interface PhotoHistogramBins : NSObject

- (id)objectAtIndexedSubscript:(NSUInteger)idx;
- (NSUInteger)count;

@end

@interface PhotoHistogram : NSObject

- (instancetype)initWithLuminanceCArray:(NSUInteger *)luminanceArray redCArray:(NSUInteger *)redArray greenCArray:(NSUInteger *)greenArray blueCArray:(NSUInteger *)blueArray;

- (PhotoHistogramBins *)histogramBinsForType:(PGCurvesType)type;

@end
