#import "PhotoEditorTabController.h"

@class PhotoEditor;
@class SuggestionContext;
@class PhotoEditorPreviewView;

@interface PhotoCaptionController : PhotoEditorTabController

@property (nonatomic, copy) void (^captionSet)(NSString *caption);

@property (nonatomic, strong) SuggestionContext *suggestionContext;

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView caption:(NSString *)caption;

@end
