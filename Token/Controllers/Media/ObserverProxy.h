#import <Foundation/Foundation.h>

@interface ObserverProxy : NSObject

@property (nonatomic) NSUInteger numberOfRunLoopPassesToDelayTargetNotifications;

- (instancetype)initWithTarget:(id)target targetSelector:(SEL)targetSelector name:(NSString *)name;
- (instancetype)initWithTarget:(id)target targetSelector:(SEL)targetSelector name:(NSString *)name object:(id)object;

@end
