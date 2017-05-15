#import <Foundation/Foundation.h>

@interface WeakReference : NSObject

@property (nonatomic, weak) id object;

- (instancetype)initWithObject:(id)object;

@end
