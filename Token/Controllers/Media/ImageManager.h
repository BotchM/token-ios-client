#import "DataResource.h"

@interface ImageManager : NSObject

+ (ImageManager *)instance;

- (UIImage *)loadImageSyncWithUri:(NSString *)uri canWait:(bool)canWait decode:(bool)decode acceptPartialData:(bool)acceptPartialData asyncTaskId:(__autoreleasing id *)asyncTaskId progress:(void (^)(float))progress partialCompletion:(void (^)(UIImage *))partialCompletion completion:(void (^)(UIImage *))completion;
- (id)beginLoadingImageAsyncWithUri:(NSString *)uri decode:(bool)decode progress:(void (^)(float))progress partialCompletion:(void (^)(UIImage *))partialCompletion completion:(void (^)(UIImage *))completion;

- (DataResource *)loadDataSyncWithUri:(NSString *)uri canWait:(bool)canWait acceptPartialData:(bool)acceptPartialData asyncTaskId:(__autoreleasing id *)asyncTaskId progress:(void (^)(float))progress partialCompletion:(void (^)(DataResource *))partialCompletion completion:(void (^)(DataResource *))completion;
- (id)loadAttributeSyncForUri:(NSString *)uri attribute:(NSString *)attribute;

- (void)cancelTaskWithId:(id)taskId;

@end
