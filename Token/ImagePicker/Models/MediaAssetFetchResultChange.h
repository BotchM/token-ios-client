#import "MediaAssetFetchResult.h"

@class PHFetchResultChangeDetails;

@interface MediaAssetFetchResultChange : NSObject

@property (nonatomic, readonly) MediaAssetFetchResult *fetchResultBeforeChanges;
@property (nonatomic, readonly) MediaAssetFetchResult *fetchResultAfterChanges;

@property (nonatomic, readonly) bool hasIncrementalChanges;

@property (nonatomic, readonly) NSIndexSet *removedIndexes;
@property (nonatomic, readonly) NSIndexSet *insertedIndexes;
@property (nonatomic, readonly) NSIndexSet *updatedIndexes;

@property (nonatomic, readonly) bool hasMoves;
- (void)enumerateMovesWithBlock:(void(^)(NSUInteger fromIndex, NSUInteger toIndex))handler;

+ (instancetype)changeWithPHFetchResultChangeDetails:(PHFetchResultChangeDetails *)changeDetails reversed:(bool)reversed;

@end
