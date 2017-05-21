#import <Foundation/Foundation.h>

#import "ModernGalleryInterfaceView.h"
#import "ModernGalleryDefaultHeaderView.h"
#import "ModernGalleryDefaultFooterView.h"
#import "ModernGalleryDefaultFooterAccessoryView.h"

@class ModernGalleryController;
@protocol ModernGalleryItem;

@interface ModernGalleryModel : NSObject

@property (nonatomic, strong) NSArray *items;

@property (nonatomic, strong, readonly) id<ModernGalleryItem> focusItem;

@property (nonatomic, copy) void (^itemsUpdated)(id<ModernGalleryItem>);
@property (nonatomic, copy) void (^focusOnItem)(id<ModernGalleryItem>);
@property (nonatomic, copy) UIView *(^actionSheetView)();
@property (nonatomic, copy) UIViewController *(^viewControllerForModalPresentation)();
@property (nonatomic, copy) void (^dismiss)(bool, bool);
@property (nonatomic, copy) void (^dismissWhenReady)();
@property (nonatomic, copy) NSArray *(^visibleItems)();

- (void)_transitionCompleted;
- (void)_replaceItems:(NSArray *)items focusingOnItem:(id<ModernGalleryItem>)item;
- (void)_focusOnItem:(id<ModernGalleryItem>)item;

- (bool)_shouldAutorotate;

- (UIView<ModernGalleryInterfaceView> *)createInterfaceView;
- (UIView<ModernGalleryDefaultHeaderView> *)createDefaultHeaderView;
- (UIView<ModernGalleryDefaultFooterView> *)createDefaultFooterView;
- (UIView<ModernGalleryDefaultFooterAccessoryView> *)createDefaultLeftAccessoryView;
- (UIView<ModernGalleryDefaultFooterAccessoryView> *)createDefaultRightAccessoryView;

@end
