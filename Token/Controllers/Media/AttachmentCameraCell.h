#import "AttachmentMenuCell.h"
#import "AttachmentCameraView.h"

@interface AttachmentCameraCell : AttachmentMenuCell

@property (nonatomic, readonly) AttachmentCameraView *cameraView;

- (void)attachCameraViewIfNeeded:(AttachmentCameraView *)cameraView;

@end

extern NSString *const AttachmentCameraCellIdentifier;
