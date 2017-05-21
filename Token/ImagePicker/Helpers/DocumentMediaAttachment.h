#import "MediaAttachment.h"

#import "ImageInfo.h"

#import "DocumentAttributeFilename.h"
#import "DocumentAttributeAnimated.h"
#import "DocumentAttributeImageSize.h"
#import "DocumentAttributeAudio.h"
#import "DocumentAttributeVideo.h"

#define DocumentMediaAttachmentType ((int)0xE6C64318)

@interface DocumentMediaAttachment : MediaAttachment <MediaAttachmentParser, NSCoding, NSCopying>

@property (nonatomic) int64_t localDocumentId;

@property (nonatomic) int64_t documentId;
@property (nonatomic) int64_t accessHash;
@property (nonatomic) int datacenterId;
@property (nonatomic) int32_t userId;
@property (nonatomic) int date;
@property (nonatomic, strong) NSString *mimeType;
@property (nonatomic) int size;
@property (nonatomic) int32_t version;
@property (nonatomic, strong) ImageInfo *thumbnailInfo;

@property (nonatomic, strong) NSString *documentUri;

@property (nonatomic, strong) NSArray *attributes;
@property (nonatomic, strong) NSString *caption;

@property (nonatomic, readonly) NSArray *textCheckingResults;

- (NSString *)safeFileName;
+ (NSString *)safeFileNameForFileName:(NSString *)fileName;
- (NSString *)fileName;

//- (bool)isAnimated;
//- (bool)isSticker;
//- (bool)isStickerWithPack;
//- (id<TGStickerPackReference>)stickerPackReference;
- (bool)isVoice;
- (CGSize)pictureSize;

@end
