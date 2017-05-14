#import "PhotoEditorItem.h"

@class PhotoFilterDefinition;
@class PhotoProcessPass;

@interface PhotoFilter : NSObject <PhotoEditorItem, NSCopying>
{
    PhotoProcessPass *_pass;
}

@property (nonatomic, readonly) PhotoFilterDefinition *definition;
@property (nonatomic, retain) PhotoProcessPass *pass;
@property (nonatomic, readonly) PhotoProcessPass *optimizedPass;

- (void)invalidate;

+ (PhotoFilter *)filterWithDefinition:(PhotoFilterDefinition *)definition;

@end
