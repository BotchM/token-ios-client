#import <Foundation/Foundation.h>

@protocol ModernGalleryItem;

@protocol ModernGalleryDefaultFooterAccessoryView <NSObject>

@required

- (void)setItem:(id<ModernGalleryItem>)item;

@end
