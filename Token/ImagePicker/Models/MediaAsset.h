#import <Foundation/Foundation.h>

#import <Photos/Photos.h>
#import <AssetsLibrary/AssetsLibrary.h>

#import "MediaSelectionContext.h"
#import "MediaEditingContext.h"

typedef enum
{
    MediaAssetAnyType,
    MediaAssetPhotoType,
    MediaAssetVideoType,
    MediaAssetGifType
} MediaAssetType;

typedef enum
{
    MediaAssetSubtypeNone = 0,
    MediaAssetSubtypePhotoPanorama = (1UL << 0),
    MediaAssetSubtypePhotoHDR = (1UL << 1),
    MediaAssetSubtypePhotoScreenshot = (1UL << 2),
    MediaAssetSubtypeVideoStreamed = (1UL << 16),
    MediaAssetSubtypeVideoHighFrameRate = (1UL << 17),
    MediaAssetSubtypeVideoTimelapse = (1UL << 18)
} MediaAssetSubtype;

@interface MediaAsset : NSObject <MediaSelectableItem>

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, readonly) CGSize dimensions;
@property (nonatomic, readonly) NSDate *date;
@property (nonatomic, readonly) bool isVideo;
@property (nonatomic, readonly) NSTimeInterval videoDuration;
@property (nonatomic, readonly) SSignal *actualVideoDuration;
@property (nonatomic, readonly) bool representsBurst;
@property (nonatomic, readonly) NSString *uniformTypeIdentifier;
@property (nonatomic, readonly) NSString *fileName;

@property (nonatomic, readonly) MediaAssetType type;
@property (nonatomic, readonly) MediaAssetSubtype subtypes;

- (instancetype)initWithPHAsset:(PHAsset *)asset;
- (instancetype)initWithALAsset:(ALAsset *)asset;

@property (nonatomic, readonly) PHAsset *backingAsset;
@property (nonatomic, readonly) ALAsset *backingLegacyAsset;

+ (PHAssetMediaType)assetMediaTypeForAssetType:(MediaAssetType)assetType;

@end
