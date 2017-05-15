#import <UIKit/UIKit.h>

@interface ModernGalleryImageItemContainerView : UIView

@property (nonatomic, copy) UIView *(^contentView)(void);

@end
