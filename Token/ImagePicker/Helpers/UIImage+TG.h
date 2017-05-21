#import <UIKit/UIKit.h>

@class ImageLuminanceMap;
@class StaticBackdropImageData;

@interface UIImage (TG)

- (NSDictionary *)attachmentsDictionary;
- (void)setAttachmentsFromDictionary:(NSDictionary *)attachmentsDictionary;

- (StaticBackdropImageData *)staticBackdropImageData;
- (void)setStaticBackdropImageData:(StaticBackdropImageData *)staticBackdropImageData;

- (UIEdgeInsets)extendedEdgeInsets;
- (void)setExtendedEdgeInsets:(UIEdgeInsets)edgeInsets;

- (bool)degraded;
- (void)setDegraded:(bool)degraded;

- (bool)edited;
- (void)setEdited:(bool)edited;

- (bool)fromCloud;
- (void)setFromCloud:(bool)fromCloud;

@end
