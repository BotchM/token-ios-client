#import <UIKit/UIKit.h>

@class PhotoFilter;

@interface PhotoFilterCell : UICollectionViewCell

@property (nonatomic, readonly) NSString *filterIdentifier;

- (void)setPhotoFilter:(PhotoFilter *)photoFilter;
- (void)setFilterSelected:(BOOL)selected;

- (void)setImage:(UIImage *)image;
- (void)setImage:(UIImage *)image animated:(bool)animated;

+ (CGFloat)filterCellWidth;

@end

extern NSString * const PhotoFilterCellKind;
