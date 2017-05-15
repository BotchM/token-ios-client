#import <UIKit/UIKit.h>

#import "ModernGalleryItem.h"

@protocol ModernGalleryDefaultHeaderView <NSObject>

@required

- (void)setItem:(id<ModernGalleryItem>)item;

@end
