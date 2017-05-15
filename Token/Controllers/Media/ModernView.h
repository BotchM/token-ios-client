#import <UIKit/UIKit.h>

@protocol ModernView <NSObject>

- (CGRect)frame;
- (void)setFrame:(CGRect)frame;

- (CGFloat)alpha;
- (void)setAlpha:(CGFloat)alpha;

- (BOOL)hidden;
- (void)setHidden:(BOOL)hidden;

- (void)setViewIdentifier:(NSString *)viewIdentifier;
- (NSString *)viewIdentifier;
- (void)setViewStateIdentifier:(NSString *)viewStateIdentifier;
- (NSString *)viewStateIdentifier;

- (void)willBecomeRecycled;

@end

@interface UIView (ModernView) <ModernView>

@end
