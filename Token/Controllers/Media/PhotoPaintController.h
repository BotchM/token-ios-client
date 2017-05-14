#import "PhotoEditorTabController.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;

@interface PhotoPaintController : PhotoEditorTabController

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView;

- (PaintingData *)paintingData;

+ (CGRect)photoContainerFrameForParentViewFrame:(CGRect)parentViewFrame toolbarLandscapeSize:(CGFloat)toolbarLandscapeSize orientation:(UIInterfaceOrientation)orientation panelSize:(CGFloat)panelSize;

@end

extern const CGFloat PhotoPaintTopPanelSize;
extern const CGFloat PhotoPaintBottomPanelSize;
