#import <Foundation/Foundation.h>

@class SSignal;

@interface SuggestionContext : NSObject

@property (nonatomic, copy) SSignal *(^userListSignal)(NSString *mention);
@property (nonatomic, copy) SSignal *(^hashtagListSignal)(NSString *hashtag);

@end
