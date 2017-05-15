#import <UIKit/UIKit.h>
#import "PhotoEditorItem.h"
#import "PhotoEditorToolView.h"

@interface PhotoEditorBlurAreaView : UIView <PhotoEditorToolView>

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem;

@end
