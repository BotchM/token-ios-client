#import <UIKit/UIKit.h>

@class PhotoFilter;
@class PhotoTool;

@protocol PhotoEditorCollectionViewFiltersDataSource;
@protocol PhotoEditorCollectionViewToolsDataSource;

@interface PhotoEditorCollectionView : UICollectionView <UICollectionViewDelegate, UICollectionViewDataSource>

@property (nonatomic, copy) void(^interactionEnded)(void);

@property (nonatomic, weak) id <PhotoEditorCollectionViewFiltersDataSource> filtersDataSource;
@property (nonatomic, weak) id <PhotoEditorCollectionViewToolsDataSource> toolsDataSource;
@property (nonatomic, strong) UIImage *filterThumbnailImage;

- (instancetype)initWithOrientation:(UIInterfaceOrientation)orientation cellWidth:(CGFloat)cellWidth;

- (void)setMinimumLineSpacing:(CGFloat)minimumLineSpacing;
- (void)setMinimumInteritemSpacing:(CGFloat)minimumInteritemSpacing;

@end

@protocol PhotoEditorCollectionViewFiltersDataSource <NSObject>

- (NSInteger)numberOfFiltersInCollectionView:(PhotoEditorCollectionView *)collectionView;
- (PhotoFilter *)collectionView:(PhotoEditorCollectionView *)collectionView filterAtIndex:(NSInteger)index;
- (void)collectionView:(PhotoEditorCollectionView *)collectionView didSelectFilterWithIndex:(NSInteger)index;
- (void)collectionView:(PhotoEditorCollectionView *)collectionView requestThumbnailImageForFilterAtIndex:(NSInteger)index completion:(void (^)(UIImage *thumbnailImage, bool cached, bool finished))completion;

@end

@protocol PhotoEditorCollectionViewToolsDataSource <NSObject>

- (NSInteger)numberOfToolsInCollectionView:(PhotoEditorCollectionView *)collectionView;
- (PhotoTool *)collectionView:(PhotoEditorCollectionView *)collectionView toolAtIndex:(NSInteger)index;
- (void)collectionView:(PhotoEditorCollectionView *)collectionView didSelectToolWithIndex:(NSInteger)index;

@end

