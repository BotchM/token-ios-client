#import "CurvesTool.h"

@class PhotoHistogram;

@interface TGHistogramView : UIView

@property (nonatomic, assign) bool isLandscape;

- (void)setHistogram:(PhotoHistogram *)histogram type:(PGCurvesType)type animated:(bool)animated;

@end
