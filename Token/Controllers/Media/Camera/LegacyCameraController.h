#import <UIKit/UIKit.h>

@protocol LegacyCameraControllerDelegate <NSObject>

@optional

- (void)legacyCameraControllerCapturedVideoWithTempFilePath:(NSString *)tempVideoFilePath fileSize:(int32_t)fileSize previewImage:(UIImage *)previewImage duration:(NSTimeInterval)duration dimensions:(CGSize)dimenstions assetUrl:(NSString *)assetUrl
NS_SWIFT_NAME(legacyCameraControllerCapturedVideo(path:fileSize:image:duration:dimensions:assetUrl:));
- (void)legacyCameraControllerCompletedWithExistingMedia:(id)media
NS_SWIFT_NAME(legacyCameraControllerCompleted(media:));

- (void)legacyCameraControllerCompletedWithNoResult;
- (void)legacyCameraControllerCompletedWithDocument:(NSURL *)fileUrl fileName:(NSString *)fileName mimeType:(NSString *)mimeType
NS_SWIFT_NAME(legacyCameraControllerCompletedWithDocument(fileUrl:fileName:mimeType:));

@end

@interface LegacyCameraController : UIImagePickerController

@property (nonatomic, weak) id<LegacyCameraControllerDelegate> completionDelegate;
@property (nonatomic) bool storeCapturedAssets;
@property (nonatomic) bool isInDocumentMode;
@property (nonatomic) bool avatarMode;

@end
