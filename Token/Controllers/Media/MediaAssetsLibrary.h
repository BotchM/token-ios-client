#import <SSignalKit/SSignalKit.h>
#import "MediaAsset.h"
#import "MediaAssetGroup.h"
#import "MediaAssetFetchResult.h"

typedef enum
{
    MediaLibraryAuthorizationStatusNotDetermined,
    MediaLibraryAuthorizationStatusRestricted,
    MediaLibraryAuthorizationStatusDenied,
    MediaLibraryAuthorizationStatusAuthorized
} MediaLibraryAuthorizationStatus;

static MediaLibraryAuthorizationStatus MediaLibraryCachedAuthorizationStatus = MediaLibraryAuthorizationStatusNotDetermined;

@interface MediaAssetsLibrary : NSObject
{
    SQueue *_queue;
}

@property (nonatomic, readonly) MediaAssetType assetType;

- (instancetype)initForAssetType:(MediaAssetType)assetType;
+ (instancetype)libraryForAssetType:(MediaAssetType)assetType;

- (SSignal *)assetWithIdentifier:(NSString *)identifier;

- (SSignal *)assetGroups;
- (SSignal *)cameraRollGroup;

- (SSignal *)assetsOfAssetGroup:(MediaAssetGroup *)assetGroup reversed:(bool)reversed;

- (SSignal *)libraryChanged;
- (SSignal *)updatedAssetsForAssets:(NSArray *)assets;

- (SSignal *)saveAssetWithImage:(UIImage *)image;
- (SSignal *)saveAssetWithImageData:(NSData *)imageData;
- (SSignal *)saveAssetWithImageAtUrl:(NSURL *)url;
- (SSignal *)saveAssetWithVideoAtUrl:(NSURL *)url;
- (SSignal *)_saveAssetWithUrl:(NSURL *)url isVideo:(bool)isVideo;

+ (instancetype)sharedLibrary;

+ (bool)usesPhotoFramework;

+ (SSignal *)authorizationStatusSignal;
+ (void)requestAuthorizationForAssetType:(MediaAssetType)assetType completion:(void (^)(MediaLibraryAuthorizationStatus status, MediaAssetGroup *cameraRollGroup))completion
NS_SWIFT_NAME(requestAuthorization(for:completion:));
+ (MediaLibraryAuthorizationStatus)authorizationStatus;

@end

NSInteger MediaAssetGroupComparator(MediaAssetGroup *group1, MediaAssetGroup *group2, void *context);

extern NSString *const MediaAssetsKey;
extern NSString *const MediaChangesKey;
