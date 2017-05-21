#import "pop/POP.h"

@interface PhotoEditorAnimation : NSObject

+ (POPSpringAnimation *)prepareTransitionAnimationForPropertyNamed:(NSString *)propertyName;
+ (void)performBlock:(void (^)(bool allFinished))block whenCompletedAllAnimations:(NSArray *)animations;

@end
