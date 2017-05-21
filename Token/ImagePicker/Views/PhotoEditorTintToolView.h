#import "PhotoEditorToolView.h"
#import "PhotoEditorItem.h"

@interface PhotoEditorTintToolView : UIView <PhotoEditorToolView>

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem;

@end
