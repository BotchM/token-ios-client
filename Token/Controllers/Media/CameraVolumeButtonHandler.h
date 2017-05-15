#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CameraVolumeButtonHandler : NSObject

@property (nonatomic, assign) bool enabled;
@property (nonatomic, assign) bool ignoring;

- (instancetype)initWithUpButtonPressedBlock:(void (^)(void))upButtonPressedBlock upButtonReleasedBlock:(void (^)(void))upButtonReleasedBlock downButtonPressedBlock:(void (^)(void))downButtonPressedBlock downButtonReleasedBlock:(void (^)(void))downButtonReleasedBlock;

- (void)enableIn:(NSTimeInterval)timeInterval;
- (void)disableFor:(NSTimeInterval)timeInterval;
- (void)ignoreEventsFor:(NSTimeInterval)timeInterval andDisable:(bool)disable;

@end
