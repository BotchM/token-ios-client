#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ModernView;

@interface ModernViewStorage : NSObject

- (UIView<ModernView> *)dequeueViewWithIdentifier:(NSString *)identifier viewStateIdentifier:(NSString *)viewStateIdentifier;
- (void)enqueueView:(UIView<ModernView> *)view;

- (void)allowResurrectionForOperations:(dispatch_block_t)block;

- (void)clear;

@end
