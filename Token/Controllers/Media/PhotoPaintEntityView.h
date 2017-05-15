#import <UIKit/UIKit.h>

@class PhotoPaintEntity;
@class PhotoPaintEntitySelectionView;
@class PaintUndoManager;

@interface PhotoPaintEntityView : UIView
{
    NSInteger _entityUUID;
    
    CGFloat _angle;
    CGFloat _scale;
}

@property (nonatomic, readonly) NSInteger entityUUID;

@property (nonatomic, readonly) PhotoPaintEntity *entity;
@property (nonatomic, assign) bool inhibitGestures;

@property (nonatomic, readonly) CGFloat angle;
@property (nonatomic, readonly) CGFloat scale;

@property (nonatomic, copy) bool (^shouldTouchEntity)(PhotoPaintEntityView *);
@property (nonatomic, copy) void (^entityBeganDragging)(PhotoPaintEntityView *);
@property (nonatomic, copy) void (^entityChanged)(PhotoPaintEntityView *);

@property (nonatomic, readonly) bool isTracking;

- (void)pan:(CGPoint)point absolute:(bool)absolute;
- (void)rotate:(CGFloat)angle absolute:(bool)absolute;
- (void)scale:(CGFloat)scale absolute:(bool)absolute;

- (void)handlePan:(UIPanGestureRecognizer *)gestureRecognizer;

- (bool)precisePointInside:(CGPoint)point;

@property (nonatomic, weak) PhotoPaintEntitySelectionView *selectionView;
- (PhotoPaintEntitySelectionView *)createSelectionView;
- (CGRect)selectionBounds;

@end


@interface PhotoPaintEntitySelectionView : UIView

@property (nonatomic, weak) PhotoPaintEntityView *entityView;

@property (nonatomic, copy) void (^entityRotated)(CGFloat angle);
@property (nonatomic, copy) void (^entityResized)(CGFloat scale);

@property (nonatomic, readonly) bool isTracking;

- (void)update;

- (void)fadeIn;
- (void)fadeOut;

@end
