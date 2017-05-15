#import "ModernGalleryItem.h"

@class VideoMediaAttachment;

@interface ModernGalleryVideoItem : NSObject <ModernGalleryItem>

@property (nonatomic, strong, readonly) id media;
@property (nonatomic, strong, readonly) NSString *previewUri;
@property (nonatomic, strong, readonly) id videoDownloadArguments;

- (instancetype)initWithMedia:(id)media previewUri:(NSString *)previewUri;

@end
