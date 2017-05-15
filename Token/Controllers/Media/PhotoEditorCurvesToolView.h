#import "PhotoEditorToolView.h"
#import "PhotoEditorItem.h"
#import "CurvesTool.h"

@interface PhotoEditorCurvesToolView : UIView <PhotoEditorToolView>

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem;

+ (UIColor *)colorForCurveType:(PGCurvesType)curveType;

@end
