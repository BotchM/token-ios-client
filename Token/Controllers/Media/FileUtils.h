#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

NSString *MimeTypeForFileExtension(NSString *fileExtension);
NSString *MimeTypeForFileUTI(NSString *fileUTI);
NSString *TGTemporaryFileName(NSString *fileExtension);
    
#ifdef __cplusplus
}
#endif
