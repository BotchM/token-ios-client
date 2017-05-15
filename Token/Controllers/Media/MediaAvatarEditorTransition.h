#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class SSignal;
@class PhotoEditorController;

@interface MediaAvatarEditorTransition : NSObject

@property (nonatomic, copy) CGRect (^referenceFrame)(void);

@property (nonatomic, copy) CGSize (^referenceImageSize)(void);
@property (nonatomic, copy) SSignal *(^referenceScreenImageSignal)(void);

@property (nonatomic, assign) CGRect outReferenceFrame;
@property (nonatomic, strong) UIView *repView;

- (instancetype)initWithController:(PhotoEditorController *)controller fromView:(UIView *)fromView;

- (void)presentAnimated:(bool)animated;
- (void)dismissAnimated:(bool)animated completion:(void (^)(void))completion;

@end
