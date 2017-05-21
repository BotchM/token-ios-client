#import <UIKit/UIKit.h>

@interface SharedMediaSectionHeaderView : UIView

@property (nonatomic) NSInteger index;

- (void)setDateString:(NSString *)dateString summaryString:(NSString *)summaryString;

@end
