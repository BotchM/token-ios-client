#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ViewController;

@interface TGMediaAvatarMenuMixin : NSObject

@property (nonatomic, copy) void (^didFinishWithImage)(UIImage *image);
@property (nonatomic, copy) void (^didFinishWithDelete)(void);
@property (nonatomic, copy) void (^didDismiss)(void);

- (instancetype)initWithParentController:(ViewController *)parentController hasDeleteButton:(bool)hasDeleteButton;
- (instancetype)initWithParentController:(ViewController *)parentController hasDeleteButton:(bool)hasDeleteButton personalPhoto:(bool)personalPhoto;
- (void)present;

@end
