#import "PhotoEditorToolView.h"
#import "PhotoEditorItem.h"

@interface PhotoEditorBlurToolView : UIView <PhotoEditorToolView>

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem;

@end
