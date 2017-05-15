#import <UIKit/UIKit.h>

@class AudioSliderArea;

@protocol AudioSliderAreaDelegate <NSObject>

@optional

- (void)audioSliderDidBeginDragging:(AudioSliderArea *)sliderArea withTouch:(UITouch *)touch;
- (void)audioSliderDidFinishDragging:(AudioSliderArea *)sliderArea;
- (void)audioSliderDidCancelDragging:(AudioSliderArea *)sliderArea;
- (void)audioSliderWillMove:(AudioSliderArea *)sliderArea withTouch:(UITouch *)touch;

@end

@interface AudioSliderArea : UISlider

@property (nonatomic, weak) id<AudioSliderAreaDelegate> delegate;

@end
