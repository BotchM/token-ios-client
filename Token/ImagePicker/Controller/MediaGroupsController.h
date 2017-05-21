#import "ViewController.h"
#import "MediaAssetsController.h"

@interface MediaGroupsController : ViewController

@property (nonatomic, strong) SuggestionContext *suggestionContext;
@property (nonatomic, assign) bool localMediaCacheEnabled;
@property (nonatomic, assign) bool liveVideoUploadEnabled;
@property (nonatomic, assign) bool captionsEnabled;

@property (nonatomic, copy) void (^openAssetGroup)(MediaAssetGroup *);

- (instancetype)initWithAssetsLibrary:(MediaAssetsLibrary *)assetsLibrary intent:(MediaAssetsControllerIntent)intent;

@end
