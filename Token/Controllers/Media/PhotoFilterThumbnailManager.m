#import "PhotoFilterThumbnailManager.h"

#import "MemoryImageCache.h"
#import "ATQueue.h"
#import <pthread.h>

#import "PhotoEditor.h"
#import "PhotoFilter.h"
#import "PhotoFilterDefinition.h"
#import "PhotoProcessPass.h"
#import "PhotoEditorPicture.h"

const NSUInteger TGFilterThumbnailCacheSoftMemoryLimit = 2 * 1024 * 1024;
const NSUInteger TGFilterThumbnailCacheHardMemoryLimit = 2 * 1024 * 1024;

@interface PhotoFilterThumbnailManager ()
{
    MemoryImageCache *_filterThumbnailCache;
    ATQueue *_cachingQueue;
    
    UIImage *_thumbnailImage;
    PhotoEditorPicture *_thumbnailPicture;
    
    ATQueue *_filteringQueue;
    dispatch_queue_t _prepQueue;
    
    pthread_rwlock_t _callbackLock;
    NSMutableDictionary *_callbacksForId;
    
    NSInteger _version;
}

@end

@implementation PhotoFilterThumbnailManager

- (instancetype)init
{
    self = [super init];
    if (self != nil)
    {
        [self invalidateThumbnailImages];

        _prepQueue = dispatch_queue_create("ph.pictogra.Pictograph.FilterThumbnailQueue", DISPATCH_QUEUE_CONCURRENT);
        
        _cachingQueue = [[ATQueue alloc] init];
        _callbacksForId = [[NSMutableDictionary alloc] init];
        
        _filteringQueue = [[ATQueue alloc] init];
        pthread_rwlock_init(&_callbackLock, NULL);
    }
    return self;
}

- (void)setThumbnailImage:(UIImage *)image
{
    [self invalidateThumbnailImages];
    _thumbnailImage = image;

    //_thumbnailPicture = [[PhotoEditorPicture alloc] initWithImage:_thumbnailImage];
}

- (void)requestThumbnailImageForFilter:(PhotoFilter *)filter completion:(void (^)(UIImage *image, bool cached, bool finished))completion
{
    if (filter.definition.type == PhotoFilterTypePassThrough)
    {
        if (completion != nil)
        {
            if (_thumbnailImage != nil)
                completion(_thumbnailImage, true, true);
            else
                completion(nil, true, false);
        }
        
        return;
    }
    
    UIImage *cachedImage = [_filterThumbnailCache imageForKey:filter.identifier attributes:nil];
    if (cachedImage != nil)
    {
        if (completion != nil)
            completion(cachedImage, true, true);
        return;
    }
    
    if (_thumbnailImage == nil)
    {
        completion(nil, true, true);
        return;
    }
    
    if (completion != nil)
        completion(_thumbnailImage, true, false);
    
    NSInteger version = _version;
    
    __weak PhotoFilterThumbnailManager *weakSelf = self;
    [self _addCallback:completion forId:filter.identifier createCallback:^
    {
        __strong PhotoFilterThumbnailManager *strongSelf = weakSelf;
        if (strongSelf == nil)
            return;
         
        if (version != strongSelf->_version)
            return;
         
        [strongSelf renderFilterThumbnailWithPicture:strongSelf->_thumbnailPicture filter:filter completion:^(UIImage *result)
        {
            [strongSelf _processCompletionForId:filter.identifier withResult:result];
        }];
    }];
}

- (void)startCachingThumbnailImagesForFilters:(NSArray *)filters
{
    if (_thumbnailImage == nil)
        return;
    
    NSMutableArray *filtersToStartCaching = [[NSMutableArray alloc] init];
    
    for (PhotoFilter *filter in filters)
    {
        if (filter.definition.type != PhotoFilterTypePassThrough && [_filterThumbnailCache imageForKey:filter.identifier attributes:nil] == nil)
            [filtersToStartCaching addObject:filter];
    }
    
    NSInteger version = _version;
    
    [_cachingQueue dispatch:^
    {
        if (version != _version)
            return;
        
        for (PhotoFilter *filter in filtersToStartCaching)
        {
            __weak PhotoFilterThumbnailManager *weakSelf = self;
            [self _addCallback:nil forId:filter.identifier createCallback:^
            {
                __strong PhotoFilterThumbnailManager *strongSelf = weakSelf;
                if (strongSelf == nil)
                    return;
                
                if (version != strongSelf->_version)
                    return;
               
                [strongSelf renderFilterThumbnailWithPicture:strongSelf->_thumbnailPicture filter:filter completion:^(UIImage *result)
                {
                    [strongSelf _processCompletionForId:filter.identifier withResult:result];
                }];
            }];
        }
    }];
}

- (void)stopCachingThumbnailImagesForFilters:(NSArray *)__unused filters
{
    
}

- (void)stopCachingThumbnailImagesForAllFilters
{
    
}

- (void)_processCompletionForId:(NSString *)filterId withResult:(UIImage *)result
{
    [_filterThumbnailCache setImage:result forKey:filterId attributes:nil];
    
    NSArray *callbacks = [self _callbacksForId:filterId];
    [self _removeCallbacksForId:filterId];
    
    for (id callback in callbacks)
    {
        void(^callbackBlock)(UIImage *image, bool cached, bool finished) = callback;
        if (callbackBlock != nil)
            callbackBlock(result, false, true);
    }
}

- (void)renderFilterThumbnailWithPicture:(PhotoEditorPicture *)picture filter:(PhotoFilter *)filter completion:(void (^)(UIImage *result))completion
{
    PhotoEditor *photoEditor = self.photoEditor;
    if (photoEditor == nil)
        return;
    
    NSInteger version = _version;
    dispatch_async(_prepQueue, ^
    {
        GPUImageOutput<GPUImageInput> *gpuFilter = filter.optimizedPass.filter;
        [_filteringQueue dispatch:^
        {
            if (version != _version)
                return;
            
            [picture addTarget:gpuFilter];
            [gpuFilter useNextFrameForImageCapture];
            [picture processSynchronous:true completion:^
            {
                UIImage *image = [gpuFilter imageFromCurrentFramebufferWithOrientation:UIImageOrientationUp];
                [picture removeAllTargets];
                
                if (completion != nil)
                    completion(image);
            }];
        }];
    });
}

- (void)invalidateThumbnailImages
{
    _version = lrand48();

    _filterThumbnailCache = [[MemoryImageCache alloc] initWithSoftMemoryLimit:TGFilterThumbnailCacheSoftMemoryLimit
                                                                hardMemoryLimit:TGFilterThumbnailCacheHardMemoryLimit];
}

- (void)haltCaching
{
    _version = lrand48();
}

- (void)_addCallback:(void (^)(UIImage *, bool, bool))callback forId:(NSString *)filterId createCallback:(void (^)(void))createCallback
{
    if (filterId == nil)
    {
        callback(nil, true, false);
        return;
    }
    
    pthread_rwlock_rdlock(&_callbackLock);
    
    bool isInitial = false;
    if (_callbacksForId[filterId] == nil)
    {
        isInitial = true;
        _callbacksForId[filterId] = [[NSMutableArray alloc] init];
    }
    
    if (callback != nil)
    {
        NSMutableArray *callbacksForId = _callbacksForId[filterId];
        [callbacksForId addObject:callback];
        _callbacksForId[filterId] = callbacksForId;
    }
    
    if (isInitial && createCallback != nil)
        createCallback();
    
    pthread_rwlock_unlock(&_callbackLock);
}

- (NSArray *)_callbacksForId:(NSString *)filterId
{
    if (filterId == nil)
        return nil;
    
    __block NSArray *callbacksForId;
    
    pthread_rwlock_rdlock(&_callbackLock);
    callbacksForId = _callbacksForId[filterId];
    pthread_rwlock_unlock(&_callbackLock);
    
    return [callbacksForId copy];
}

- (void)_removeCallbacksForId:(NSString *)filterId
{
    if (filterId == nil)
        return;
    
    pthread_rwlock_rdlock(&_callbackLock);
    [_callbacksForId removeObjectForKey:filterId];
    pthread_rwlock_unlock(&_callbackLock);
}

@end
