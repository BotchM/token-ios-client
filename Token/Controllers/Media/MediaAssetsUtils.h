#import "MediaAssetFetchResultChange.h"
#import "MediaAssetImageSignals.h"

@class MediaAsset;
@class MediaSelectionContext;

@interface MediaAssetsPreheatMixin : NSObject

@property (nonatomic, copy) NSInteger (^assetCount)(void);
@property (nonatomic, copy) MediaAsset *(^assetAtIndexPath)(NSIndexPath *);

@property (nonatomic, assign) MediaAssetImageType imageType;
@property (nonatomic, assign) CGSize imageSize;
@property (nonatomic, assign) bool reversed;

- (instancetype)initWithCollectionView:(UICollectionView *)collectionView scrollDirection:(UICollectionViewScrollDirection)scrollDirection;
- (void)update;
- (void)stop;

@end


@interface MediaAssetsCollectionViewIncrementalUpdater : NSObject

+ (void)updateCollectionView:(UICollectionView *)collectionView withChange:(MediaAssetFetchResultChange *)change completion:(void (^)(bool incremental))completion;

@end


@interface MediaAssetsSaveToCameraRoll : NSObject

+ (void)saveImageAtURL:(NSURL *)url;
+ (void)saveImageWithData:(NSData *)imageData;
+ (void)saveVideoAtURL:(NSURL *)url;

@end


@interface MediaAssetsDateUtils : NSObject

+ (NSString *)formattedDateRangeWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate currentDate:(NSDate *)currentDate shortDate:(bool)shortDate;

@end
