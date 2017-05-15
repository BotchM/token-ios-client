#import <UIKit/UIKit.h>

@interface MediaAssetsMomentsSectionHeaderView : UIView

@property (nonatomic) NSInteger index;

- (void)setTitle:(NSString *)title location:(NSString *)location date:(NSString *)date;

@end
