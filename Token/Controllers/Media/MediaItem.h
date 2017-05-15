#import <Foundation/Foundation.h>

#import "ImageInfo.h"
#import "VideoMediaAttachment.h"
#import "TGUser.h"

typedef enum {
    MediaItemTypePhoto = 0,
    MediaItemTypeVideo = 1
} MediaItemType;

@protocol MediaItem <NSObject, NSCopying>

@property (nonatomic) MediaItemType type;

- (id)itemId;
- (int)date;
- (int)authorUid;
- (TGUser *)author;

- (UIImage *)immediateThumbnail;

- (ImageInfo *)imageInfo;
- (VideoMediaAttachment *)videoAttachment;

@optional

- (int)itemMessageId;
- (id)itemMediaId;

@end
