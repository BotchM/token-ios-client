#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CameraShotMetadata : NSObject

@property (nonatomic, assign) CGFloat deviceAngle;
@property (nonatomic, assign) bool frontal;

+ (CGFloat)relativeDeviceAngleFromAngle:(CGFloat)angle orientation:(UIInterfaceOrientation)orientation;

@end
