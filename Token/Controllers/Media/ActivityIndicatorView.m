#import "ActivityIndicatorView.h"

@implementation ActivityIndicatorView

+ (NSArray *)animationFrames
{
    static NSArray *array = nil;
    if (array == nil)
    {
        NSMutableArray *mutableArray = [[NSMutableArray alloc] init];
        for (int i = 1; i <= 24; i++)
        {
            UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"grayProgress%d.png", i]];
            if (image != nil)
                [mutableArray addObject:image];
        }
        array = [[NSArray alloc] initWithArray:mutableArray];
    }
    return array;
}

+ (NSArray *)largeAnimationFrames
{
    static NSArray *array = nil;
    if (array == nil)
    {
        NSMutableArray *mutableArray = [[NSMutableArray alloc] init];
        for (int i = 0; i <= 24; i++)
        {
            UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"navbar_big_progress_%d.png", i]];
            if (image != nil)
                [mutableArray addObject:image];
        }
        array = [[NSArray alloc] initWithArray:mutableArray];
    }
    return array;
}

+ (NSArray *)smallWhiteAnimationFrames
{
    static NSArray *array = nil;
    if (array == nil)
    {
        NSMutableArray *mutableArray = [[NSMutableArray alloc] init];
        
        for (int i = 1; i <= 24; i++)
        {
            UIImage *image = [UIImage imageNamed:[[NSString alloc] initWithFormat:@"RProgress%d.png", i]];
            if (image != nil)
                [mutableArray addObject:image];
        }
        array = [[NSArray alloc] initWithArray:mutableArray];
    }
    return array;
}

- (id)initWithStyle:(ActivityIndicatorViewStyle)style
{
    NSArray *frames = style == ActivityIndicatorViewStyleSmall ? [ActivityIndicatorView animationFrames] : (style == ActivityIndicatorViewStyleLarge ?[ActivityIndicatorView largeAnimationFrames] : [ActivityIndicatorView smallWhiteAnimationFrames]);
    self = [super initWithImage:[frames objectAtIndex:0]];
    if (self)
    {
        [self setAnimationImages:frames];
    }
    return self;
}

- (id)init
{
    NSArray *frames = [ActivityIndicatorView animationFrames];
    self = [super initWithImage:[frames objectAtIndex:0]];
    if (self)
    {
        [self setAnimationImages:frames];
    }
    return self;
}

- (id)initWithFrame:(CGRect)__unused frame
{
    NSArray *frames = [ActivityIndicatorView animationFrames];
    self = [super initWithImage:[frames objectAtIndex:0]];
    if (self)
    {
        [self setAnimationImages:frames];
    }
    return self;
}

@end
