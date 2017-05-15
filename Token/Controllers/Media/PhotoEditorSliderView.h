#import <UIKit/UIKit.h>

@interface PhotoEditorSliderView : UIControl

@property (nonatomic, copy) void(^interactionBegan)(void);
@property (nonatomic, copy) void(^interactionEnded)(void);

@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;

@property (nonatomic, assign) CGFloat minimumValue;
@property (nonatomic, assign) CGFloat maximumValue;

@property (nonatomic, assign) CGFloat startValue;
@property (nonatomic, assign) CGFloat value;

@property (nonatomic, readonly) bool isTracking;

@property (nonatomic, assign) CGFloat knobPadding;
@property (nonatomic, assign) CGFloat lineSize;
@property (nonatomic, strong) UIColor *backColor;
@property (nonatomic, strong) UIColor *trackColor;

@property (nonatomic, strong) UIImage *knobImage;

@property (nonatomic, assign) NSInteger positionsCount;

- (void)setValue:(CGFloat)value animated:(BOOL)animated;

@end

extern const CGFloat PhotoEditorSliderViewMargin;
