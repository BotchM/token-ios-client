#import "PhotoEditorTabController.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;

@interface PhotoToolsController : PhotoEditorTabController

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView;

- (void)updateValues;

- (void)prepareForCombinedAppearance;
- (void)finishedCombinedAppearance;

@end
