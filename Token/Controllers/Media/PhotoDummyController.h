#import "PhotoEditorTabController.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;
@class PhotoQualityController;

@interface PhotoDummyController : PhotoEditorTabController

@property (nonatomic, weak) PhotoQualityController *controller;

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView;

@end
