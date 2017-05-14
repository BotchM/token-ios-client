#import "PhotoTool.h"

typedef enum
{
    PGCurvesTypeLuminance,
    PGCurvesTypeRed,
    PGCurvesTypeGreen,
    PGCurvesTypeBlue
} PGCurvesType;

@interface CurvesValue : NSObject <NSCopying>

@property (nonatomic, assign) CGFloat blacksLevel;
@property (nonatomic, assign) CGFloat shadowsLevel;
@property (nonatomic, assign) CGFloat midtonesLevel;
@property (nonatomic, assign) CGFloat highlightsLevel;
@property (nonatomic, assign) CGFloat whitesLevel;

- (NSArray *)interpolateCurve;

@end

@interface CurvesToolValue : NSObject <NSCopying, CustomToolValue>

@property (nonatomic, strong) CurvesValue *luminanceCurve;
@property (nonatomic, strong) CurvesValue *redCurve;
@property (nonatomic, strong) CurvesValue *greenCurve;
@property (nonatomic, strong) CurvesValue *blueCurve;

@property (nonatomic, assign) PGCurvesType activeType;

@end

@interface CurvesTool : PhotoTool

@end
