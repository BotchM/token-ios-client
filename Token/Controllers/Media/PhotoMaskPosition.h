#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

typedef enum
{
    PhotoMaskAnchorNone,
    PhotoMaskAnchorForehead,
    PhotoMaskAnchorEyes,
    PhotoMaskAnchorMouth,
    PhotoMaskAnchorChin
} PhotoMaskAnchor;

@interface PhotoMaskPosition : NSObject

@property (nonatomic, readonly) CGPoint center;
@property (nonatomic, readonly) CGFloat scale;
@property (nonatomic, readonly) CGFloat angle;

+ (instancetype)maskPositionWithCenter:(CGPoint)center scale:(CGFloat)scale angle:(CGFloat)angle;

@end
