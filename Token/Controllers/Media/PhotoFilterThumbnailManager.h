#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class PhotoEditor;
@class PhotoFilter;

@interface PhotoFilterThumbnailManager : NSObject

@property (nonatomic, weak) PhotoEditor *photoEditor;

- (void)setThumbnailImage:(UIImage *)image;
- (void)requestThumbnailImageForFilter:(PhotoFilter *)filter completion:(void (^)(UIImage *thumbnailImage, bool cached, bool finished))completion;
- (void)startCachingThumbnailImagesForFilters:(NSArray *)filters;
- (void)stopCachingThumbnailImagesForFilters:(NSArray *)filters;
- (void)stopCachingThumbnailImagesForAllFilters;
- (void)invalidateThumbnailImages;

- (void)haltCaching;

@end
