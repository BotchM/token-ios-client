#import "PhotoEditorToolView.h"
#import "PhotoEditorItem.h"

@interface PhotoEditorGenericToolView : UIView <PhotoEditorToolView>

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem;

@end
