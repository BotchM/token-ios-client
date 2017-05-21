#import "MediaAttachment.h"

#import "VideoInfo.h"
#import "ImageInfo.h"

#define VideoMediaAttachmentType ((int)0x338EAA20)

@interface VideoMediaAttachment : MediaAttachment <NSCoding, MediaAttachmentParser>

@property (nonatomic) int64_t videoId;
@property (nonatomic) int64_t accessHash;

@property (nonatomic) int64_t localVideoId;

@property (nonatomic) int duration;
@property (nonatomic) CGSize dimensions;

@property (nonatomic, strong) VideoInfo *videoInfo;
@property (nonatomic, strong) ImageInfo *thumbnailInfo;

@property (nonatomic) NSString *caption;
@property (nonatomic) bool hasStickers;
@property (nonatomic, strong) NSArray *embeddedStickerDocuments;

@property (nonatomic, readonly) NSArray *textCheckingResults;

@property (nonatomic) bool loopVideo;

@end
