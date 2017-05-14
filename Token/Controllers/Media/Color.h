#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
    
UIColor *TGAccentColor();
UIColor *TGDestructiveAccentColor();
UIColor *TGSelectionColor();
UIColor *TGSeparatorColor();

UIColor *ColorWithHex(int hex);
UIColor *ColorWithHexAndAlpha(int hex, CGFloat alpha);

#ifdef __cplusplus
}
#endif
