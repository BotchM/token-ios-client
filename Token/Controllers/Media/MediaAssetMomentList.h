#import "MediaAssetMoment.h"

@interface MediaAssetMomentList : NSObject

@property (nonatomic, readonly) NSUInteger count;

- (instancetype)initWithPHFetchResult:(PHFetchResult *)fetchResult;

- (NSArray *)latestAssets;


- (id)objectAtIndexedSubscript:(NSUInteger)idx;

@end
