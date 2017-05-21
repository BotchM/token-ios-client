#import <UIKit/UIKit.h>

@class MediaAssetGroup;
@class MediaAssetMomentList;

@interface MediaGroupCell : UITableViewCell

@property (nonatomic, readonly) MediaAssetGroup *assetGroup;

- (void)configureForAssetGroup:(MediaAssetGroup *)assetGroup;
- (void)configureForMomentList:(MediaAssetMomentList *)momentList;

@end

extern NSString *const MediaGroupCellKind;
extern const CGFloat MediaGroupCellHeight;
