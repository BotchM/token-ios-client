#import <Foundation/Foundation.h>

@interface MediaAttachment : NSObject

@property (nonatomic) int type;
@property (nonatomic) bool isMeta;

- (void)serialize:(NSMutableData *)data;

@end

@protocol MediaAttachmentParser <NSObject>

@required

- (MediaAttachment *)parseMediaAttachment:(NSInputStream *)is;

@end
