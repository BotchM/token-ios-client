#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import "ModernViewStorage.h"

@protocol ModernView;

@interface ModernViewModel : NSObject
{
    @private
    struct {
        int hasNoView : 1;
        int skipDrawInContext : 1;
        int disableSubmodelAutomaticBinding : 1;
        int viewUserInteractionDisabled : 1;
    } _modelFlags;
}

@property (nonatomic, strong) id modelId;

@property (nonatomic, strong) NSString *viewStateIdentifier;

@property (nonatomic) CGRect frame;
@property (nonatomic) CGPoint parentOffset;
@property (nonatomic) float alpha;
@property (nonatomic) bool hidden;

@property (nonatomic, strong, readonly) NSArray *submodels;

@property (nonatomic, copy) void (^unbindAction)();

- (bool)hasNoView;
- (void)setHasNoView:(bool)hasNoView;

- (bool)skipDrawInContext;
- (void)setSkipDrawInContext:(bool)skipDrawInContext;

- (bool)disableSubmodelAutomaticBinding;
- (void)setDisableSubmodelAutomaticBinding:(bool)disableSubmodelAutomaticBinding;

- (bool)viewUserInteractionDisabled;
- (void)setViewUserInteractionDisabled:(bool)viewUserInteractionDisabled;

- (Class)viewClass;
- (UIView<ModernView> *)_dequeueView:(ModernViewStorage *)viewStorage;

- (UIView<ModernView> *)boundView;
- (void)bindViewToContainer:(UIView *)container viewStorage:(ModernViewStorage *)viewStorage;
- (void)unbindView:(ModernViewStorage *)viewStorage;
- (void)moveViewToContainer:(UIView *)container;

- (void)_offsetBoundViews:(CGSize)offset;

- (void)drawInContext:(CGContextRef)context;
- (void)drawSubmodelsInContext:(CGContextRef)context;

- (void)sizeToFit;
- (CGRect)bounds;

- (bool)containsSubmodel:(ModernViewModel *)model;
- (void)addSubmodel:(ModernViewModel *)model;
- (void)insertSubmodel:(ModernViewModel *)model belowSubmodel:(ModernViewModel *)belowSubmodel;
- (void)insertSubmodel:(ModernViewModel *)model aboveSubmodel:(ModernViewModel *)aboveSubmodel;
- (void)removeSubmodel:(ModernViewModel *)model viewStorage:(ModernViewStorage *)viewStorage;
- (void)layoutForContainerSize:(CGSize)containerSize;

- (void)collectBoundModelViewFramesRecursively:(NSMutableDictionary *)dict;
- (void)collectBoundModelViewFramesRecursively:(NSMutableDictionary *)dict ifPresentInDict:(NSMutableDictionary *)anotherDict;
- (void)restoreBoundModelViewFramesRecursively:(NSMutableDictionary *)dict;

@end
