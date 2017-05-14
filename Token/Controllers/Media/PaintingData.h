#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class PaintUndoManager;
@class MediaEditingContext;
@protocol MediaEditableItem;

@interface PaintingData : NSObject

@property (nonatomic, readonly) NSString *imagePath;
@property (nonatomic, readonly) NSString *dataPath;
@property (nonatomic, readonly) NSArray *entities;
@property (nonatomic, readonly) PaintUndoManager *undoManager;
@property (nonatomic, readonly) NSArray *stickers;

@property (nonatomic, readonly) NSData *data;
@property (nonatomic, readonly) UIImage *image;

+ (instancetype)dataWithPaintingData:(NSData *)data image:(UIImage *)image entities:(NSArray *)entities undoManager:(PaintUndoManager *)undoManager;

+ (instancetype)dataWithPaintingImagePath:(NSString *)imagePath;

+ (void)storePaintingData:(PaintingData *)data inContext:(MediaEditingContext *)context forItem:(id<MediaEditableItem>)item forVideo:(bool)video;
+ (void)facilitatePaintingData:(PaintingData *)data;

@end
