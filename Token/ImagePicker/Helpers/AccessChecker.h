#import <Foundation/Foundation.h>

typedef enum {
    PhotoAccessIntentRead,
    PhotoAccessIntentSave,
    PhotoAccessIntentCustomWallpaper
} PhotoAccessIntent;

typedef enum {
    MicrophoneAccessIntentVoice,
    MicrophoneAccessIntentVideo,
    MicrophoneAccessIntentCall,
} MicrophoneAccessIntent;

typedef enum {
    LocationAccessIntentSend,
    LocationAccessIntentTracking,
} LocationAccessIntent;

@interface AccessChecker : NSObject

+ (bool)checkAddressBookAuthorizationStatusWithAlertDismissComlpetion:(void (^)(void))alertDismissCompletion;

+ (bool)checkPhotoAuthorizationStatusForIntent:(PhotoAccessIntent)intent alertDismissCompletion:(void (^)(void))alertDismissCompletion
NS_SWIFT_NAME(checkPhotoAuthorizationStatus(intent:alertDismissCompletion:));

+ (bool)checkMicrophoneAuthorizationStatusForIntent:(MicrophoneAccessIntent)intent alertDismissCompletion:(void (^)(void))alertDismissCompletion;

+ (bool)checkCameraAuthorizationStatusWithAlertDismissComlpetion:(void (^)(void))alertDismissCompletion;

+ (bool)checkLocationAuthorizationStatusForIntent:(LocationAccessIntent)intent alertDismissComlpetion:(void (^)(void))alertDismissCompletion;

@end
