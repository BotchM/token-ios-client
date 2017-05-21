#import <Foundation/Foundation.h>

@class Painting;
@class PhotoEntitiesContainerView;

@interface PaintUndoManager : NSObject <NSCopying>

@property (nonatomic, weak) Painting *painting;
@property (nonatomic, weak) PhotoEntitiesContainerView *entitiesContainer;

@property (nonatomic, copy) void (^historyChanged)(void);

@property (nonatomic, readonly) bool canUndo;
- (void)registerUndoWithUUID:(NSInteger)uuid block:(void (^)(Painting *, PhotoEntitiesContainerView *, NSInteger))block;
- (void)unregisterUndoWithUUID:(NSInteger)uuid;

- (void)undo;

- (void)reset;

@end
