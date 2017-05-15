#import "ViewController.h"
#import "OverlayController.h"

#import "PhotoEditorItem.h"

@class PhotoEditor;
@class PhotoEditorPreviewView;

@interface PhotoEditorItemController : ViewController

@property (nonatomic, copy) void(^editorItemUpdated)(void);
@property (nonatomic, copy) void(^beginTransitionIn)(void);
@property (nonatomic, copy) void(^beginTransitionOut)(void);
@property (nonatomic, copy) void(^finishedCombinedTransition)(void);

@property (nonatomic, assign) CGFloat toolbarLandscapeSize;
@property (nonatomic, assign) bool initialAppearance;
@property (nonatomic, assign) bool skipProcessingOnCompletion;

- (instancetype)initWithEditorItem:(id<PhotoEditorItem>)editorItem photoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView;

- (void)attachPreviewView:(PhotoEditorPreviewView *)previewView;

- (void)prepareForCombinedAppearance;
- (void)finishedCombinedAppearance;

@end
