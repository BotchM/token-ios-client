#import "ViewController.h"

#import "ActionStage.h"

#import <AssetsLibrary/AssetsLibrary.h>

#ifdef __cplusplus
extern "C" {
#endif

void dispatchOnAssetsProcessingQueue(dispatch_block_t block);
void sharedAssetsLibraryRetain();
void sharedAssetsLibraryRelease();
    
#ifdef __cplusplus
}
#endif

@protocol TGImagePickerControllerDelegate;

@interface TGImagePickerController : NSObject

+ (id)sharedAssetsLibrary;
+ (id)preloadLibrary;
+ (void)loadAssetWithUrl:(NSURL *)url completion:(void (^)(ALAsset *asset))completion;
+ (void)storeImageAsset:(NSData *)data;

@end

@protocol TGImagePickerControllerDelegate <NSObject>

- (void)TGImagePickerController:(TGImagePickerController *)imagePicker didFinishPickingWithAssets:(NSArray *)assets
NS_SWIFT_NAME(imagePickerControllerDidFinishPickingWithAssets(imagePicker:assets:));

@end
