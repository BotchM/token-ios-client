#import "PhotoPaintSparseView.h"

@class PhotoPaintEntityView;

@interface PhotoEntitiesContainerView : PhotoPaintSparseView

@property (nonatomic, readonly) NSUInteger entitiesCount;
@property (nonatomic, copy) void (^entitySelected)(PhotoPaintEntityView *);
@property (nonatomic, copy) void (^entityRemoved)(PhotoPaintEntityView *);

- (PhotoPaintEntityView *)viewForUUID:(NSInteger)uuid;
- (void)removeViewWithUUID:(NSInteger)uuid;
- (void)removeAll;

- (void)handlePinch:(UIPinchGestureRecognizer *)gestureRecognizer;
- (void)handleRotate:(UIRotationGestureRecognizer *)gestureRecognizer;

- (UIImage *)imageInRect:(CGRect)rect background:(UIImage *)background;

- (bool)isTrackingAnyEntityView;

@end
