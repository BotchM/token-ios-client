#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

#ifdef __cplusplus
extern "C" {
#endif

UIFont *TGSystemFontOfSize(CGFloat size);
UIFont *TGBoldSystemFontOfSize(CGFloat size);
UIFont *TGLightSystemFontOfSize(CGFloat size);
UIFont *TGUltralightSystemFontOfSize(CGFloat size);
UIFont *TGMediumSystemFontOfSize(CGFloat size);
UIFont *TGItalicSystemFontOfSize(CGFloat size);

CTFontRef TGCoreTextSystemFontOfSize(CGFloat size);
CTFontRef TGCoreTextMediumFontOfSize(CGFloat size);
CTFontRef TGCoreTextBoldFontOfSize(CGFloat size);
CTFontRef TGCoreTextLightFontOfSize(CGFloat size);
CTFontRef TGCoreTextFixedFontOfSize(CGFloat size);
CTFontRef TGCoreTextItalicFontOfSize(CGFloat size);
    
#ifdef __cplusplus
}
#endif

@interface Font : NSObject

+ (UIFont *)systemFontOfSize:(CGFloat)size;
+ (UIFont *)boldSystemFontOfSize:(CGFloat)size;

@end
