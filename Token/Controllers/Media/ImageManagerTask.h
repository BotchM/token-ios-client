#import "ImageDataSource.h"

@interface ImageManagerTask : NSObject
{
    @public bool _isCancelled;
}

@property (nonatomic, strong) ImageDataSource *dataSource;
@property (nonatomic, strong) id childTaskId;

@end
