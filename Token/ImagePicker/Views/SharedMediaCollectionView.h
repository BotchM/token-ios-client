#import <UIKit/UIKit.h>

@class SharedMediaSectionHeaderView;
@class SharedMediaSectionHeader;

@protocol SharedMediaCollectionViewDelegate <UICollectionViewDelegateFlowLayout>

- (void)collectionView:(UICollectionView *)collectionView setupSectionHeaderView:(SharedMediaSectionHeaderView *)sectionHeaderView forSectionHeader:(SharedMediaSectionHeader *)sectionHeader;

@end

@interface SharedMediaCollectionView : UICollectionView

@end
