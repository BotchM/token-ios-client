#import <UIKit/UIKit.h>

@class MediaAssetsMomentsSectionHeader;
@class MediaAssetsMomentsSectionHeaderView;

@protocol MediaAssetsMomentsCollectionViewDelegate <UICollectionViewDelegateFlowLayout>

- (void)collectionView:(UICollectionView *)collectionView setupSectionHeaderView:(MediaAssetsMomentsSectionHeaderView *)sectionHeaderView forSectionHeader:(MediaAssetsMomentsSectionHeader *)sectionHeader;

@end

@interface MediaAssetsMomentsCollectionView : UICollectionView

@end
