#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "MediaPickerCaptionInputPanel.h"

@class SuggestionContext;

@interface PhotoCaptionInputMixin : NSObject

@property (nonatomic, readonly) MediaPickerCaptionInputPanel *inputPanel;
@property (nonatomic, readonly) UIView *dismissView;

@property (nonatomic, assign) UIInterfaceOrientation interfaceOrientation;
@property (nonatomic, readonly) CGFloat keyboardHeight;
@property (nonatomic, assign) CGFloat contentAreaHeight;

@property (nonatomic, strong) SuggestionContext *suggestionContext;

@property (nonatomic, copy) UIView *(^panelParentView)(void);

@property (nonatomic, copy) void (^panelFocused)(void);
@property (nonatomic, copy) void (^finishedWithCaption)(NSString *caption);
@property (nonatomic, copy) void (^keyboardHeightChanged)(CGFloat keyboardHeight, NSTimeInterval duration, NSInteger animationCurve);

- (void)createInputPanelIfNeeded;
- (void)beginEditing;
- (void)enableDismissal;

- (void)destroy;

@property (nonatomic, strong) NSString *caption;
- (void)setCaption:(NSString *)caption animated:(bool)animated;

- (void)setCaptionPanelHidden:(bool)hidden animated:(bool)animated;

- (void)updateLayoutWithFrame:(CGRect)frame edgeInsets:(UIEdgeInsets)edgeInsets;

@end
