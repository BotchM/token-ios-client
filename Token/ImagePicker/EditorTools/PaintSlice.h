#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class Painting;

@interface PaintSlice : NSObject

@property (nonatomic, readonly) CGRect bounds;
@property (nonatomic, readonly) NSData *data;

- (instancetype)initWithData:(NSData *)data bounds:(CGRect)bounds;

- (instancetype)swappedSliceForPainting:(Painting *)painting;

@end
