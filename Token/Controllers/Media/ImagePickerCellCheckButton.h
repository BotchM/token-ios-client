#import <UIKit/UIKit.h>

@interface ImagePickerCellCheckButton : UIButton

@property (nonatomic, strong) UIImageView *checkView;

- (void)setChecked:(bool)checked animated:(bool)animated;
- (bool)checked;

@end

