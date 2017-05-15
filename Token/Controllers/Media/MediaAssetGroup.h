#import <Photos/Photos.h>
#import <AssetsLibrary/AssetsLibrary.h>

#import "MediaAsset.h"

typedef enum
{
    MediaAssetGroupSubtypeNone = 0,
    MediaAssetGroupSubtypeCameraRoll,
    MediaAssetGroupSubtypeMyPhotoStream,
    MediaAssetGroupSubtypeFavorites,
    MediaAssetGroupSubtypeSelfPortraits,
    MediaAssetGroupSubtypePanoramas,
    MediaAssetGroupSubtypeVideos,
    MediaAssetGroupSubtypeSlomo,
    MediaAssetGroupSubtypeTimelapses,
    MediaAssetGroupSubtypeBursts,
    MediaAssetGroupSubtypeScreenshots,
    MediaAssetGroupSubtypeRegular
} MediaAssetGroupSubtype;

@interface MediaAssetGroup : NSObject

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) NSInteger assetCount;
@property (nonatomic, readonly) MediaAssetGroupSubtype subtype;
@property (nonatomic, readonly) bool isCameraRoll;
@property (nonatomic, readonly) bool isPhotoStream;
@property (nonatomic, readonly) bool isReversed;

@property (nonatomic, readonly) PHFetchResult *backingFetchResult;
@property (nonatomic, readonly) PHAssetCollection *backingAssetCollection;
@property (nonatomic, readonly) ALAssetsGroup *backingAssetsGroup;

- (instancetype)initWithPHFetchResult:(PHFetchResult *)fetchResult;
- (instancetype)initWithPHAssetCollection:(PHAssetCollection *)collection fetchResult:(PHFetchResult *)fetchResult;
- (instancetype)initWithALAssetsGroup:(ALAssetsGroup *)assetsGroup;
- (instancetype)initWithALAssetsGroup:(ALAssetsGroup *)assetsGroup subtype:(MediaAssetGroupSubtype)subtype;

- (NSArray *)latestAssets;

+ (bool)_isSmartAlbumCollectionSubtype:(PHAssetCollectionSubtype)subtype requiredForAssetType:(MediaAssetType)assetType;

@end
