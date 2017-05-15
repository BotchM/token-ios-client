#import <UIKit/UIKit.h>

@interface CameraTimeCodeView : UIView

@property (nonatomic, copy) NSTimeInterval(^requestedRecordingDuration)(void);

- (void)startRecording;
- (void)stopRecording;
- (void)reset;

- (void)setHidden:(bool)hidden animated:(bool)animated;

@end
