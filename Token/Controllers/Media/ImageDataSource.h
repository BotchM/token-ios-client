#import "DataResource.h"

@interface ImageDataSource : NSObject

+ (void)registerDataSource:(ImageDataSource *)dataSource;
+ (void)enumerateDataSources:(bool (^)(ImageDataSource *dataSource))handler;

+ (void)enqueueImageProcessingBlock:(void (^)())imageProcessingBlock;

- (bool)canHandleUri:(NSString *)uri;
- (bool)canHandleAttributeUri:(NSString *)uri;
- (DataResource *)loadDataSyncWithUri:(NSString *)uri canWait:(bool)canWait acceptPartialData:(bool)acceptPartialData asyncTaskId:(__autoreleasing id *)asyncTaskId progress:(void (^)(float))progress partialCompletion:(void (^)(DataResource *))partialCompletion completion:(void (^)(DataResource *))completion;
- (id)loadDataAsyncWithUri:(NSString *)uri progress:(void (^)(float progress))progress partialCompletion:(void (^)(DataResource *resource))partialCompletion completion:(void (^)(DataResource *resource))completion;
- (id)loadAttributeSyncForUri:(NSString *)uri attribute:(NSString *)attribute;
- (void)cancelTaskById:(id)taskId;

@end
