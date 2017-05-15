#import <Foundation/Foundation.h>

@class PHFetchResult;
@class ALAsset;

@class MediaAsset;

@interface MediaAssetFetchResult : NSObject

@property (nonatomic, readonly) NSUInteger count;

- (instancetype)initForALAssetsReversed:(bool)reversed;
- (instancetype)initWithPHFetchResult:(PHFetchResult *)fetchResult reversed:(bool)reversed;

- (MediaAsset *)assetAtIndex:(NSUInteger)index;
- (NSUInteger)indexOfAsset:(MediaAsset *)asset;

- (NSSet *)itemsIdentifiers;

- (void)_appendALAsset:(ALAsset *)asset;

@end
