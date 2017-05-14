#ifndef Telegraph_Common_h
#define Telegraph_Common_h

#import "ASCommon.h"

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#define TGUseSocial true

#define TG_ENABLE_AUDIO_NOTES true

#define TGAssert(expr) assert(expr)

#define UIColorRGB(rgb) ([[UIColor alloc] initWithRed:(((rgb >> 16) & 0xff) / 255.0f) green:(((rgb >> 8) & 0xff) / 255.0f) blue:(((rgb) & 0xff) / 255.0f) alpha:1.0f])
#define UIColorRGBA(rgb,a) ([[UIColor alloc] initWithRed:(((rgb >> 16) & 0xff) / 255.0f) green:(((rgb >> 8) & 0xff) / 255.0f) blue:(((rgb) & 0xff) / 255.0f) alpha:a])

#define TGRestrictedToMainThread {if(![[NSThread currentThread] isMainThread]) TGLog(@"***** Warning: main thread-bound operation is running in background! *****");}


extern int TGLocalizedStaticVersion;
#define TGLocalizedStatic(s) ({ static int _localizedStringVersion = 0; static NSString *_localizedString = nil; if (_localizedString == nil || _localizedStringVersion != TGLocalizedStaticVersion) { _localizedString = TGLocalized(s); _localizedStringVersion = TGLocalizedStaticVersion; } _localizedString; })

#define TG_TIMESTAMP_DEFINE(s) CFAbsoluteTime tg_timestamp_##s = CFAbsoluteTimeGetCurrent(); int tg_timestamp_line_##s = __LINE__;
#define TG_TIMESTAMP_MEASURE(s) { CFAbsoluteTime tg_timestamp_current_time = CFAbsoluteTimeGetCurrent(); TGLog(@"%s %d-%d: %f ms", #s, tg_timestamp_line_##s, __LINE__, (tg_timestamp_current_time - tg_timestamp_##s) * 1000.0); tg_timestamp_##s = tg_timestamp_current_time; tg_timestamp_line_##s = __LINE__; }

#ifdef __cplusplus
extern "C" {
#endif
int cpuCoreCount();
bool hasModernCpu();
int deviceMemorySize();
    
void TGSetLocalizationFromFile(NSString *filePath);
bool TGIsCustomLocalizationActive();
void TGResetLocalization();
NSString *TGLocalized(NSString *s);

bool TGObjectCompare(id obj1, id obj2);
bool StringCompare(NSString *s1, NSString *s2);
    
NSTimeInterval TGCurrentSystemTime();

NSString *StringMD5(NSString *string);
UIUserInterfaceSizeClass CurrentSizeClass();
    
int iosMajorVersion();
int iosMinorVersion();
    
void printMemoryUsage(NSString *tag);
    
void TGDumpViews(UIView *view, NSString *indent);
    
NSString *TGEncodeText(NSString *string, int key);
void DispatchOnMainThread(dispatch_block_t block);
void DispatchAfter(double delay, dispatch_queue_t queue, dispatch_block_t block);
    
#ifdef __cplusplus
}
#endif

@interface NSNumber (IntegerTypes)

- (int32_t)int32Value;
- (int64_t)int64Value;

@end

#ifdef __LP64__
#   define CGFloor floor
#else
#   define CGFloor floorf
#endif

#ifdef __LP64__
#   define CGRound round
#   define CGCeil ceil
#   define CGPow pow
#   define CGSin sin
#   define CGCos cos
#   define CGSqrt sqrt
#else
#   define CGRound roundf
#   define CGCeil ceilf
#   define CGPow powf
#   define CGSin sinf
#   define CGCos cosf
#   define CGSqrt sqrtf
#endif

#define CGEven(x) ((((int)x) & 1) ? (x + 1) : x)
#define CGOdd(x) ((((int)x) & 1) ? x : (x + 1))

//#import "TGAppearance.h"
#import "TColor.h"

#endif
