#import "GPUImageContext.h"
#import <UIKit/UIKit.h>

@interface PhotoEditorView : UIView <GPUImageInput>

@property (nonatomic, assign) bool enabled;

@end
