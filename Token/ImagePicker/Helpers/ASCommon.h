#ifndef ActionStage_ASCommon_h
#define ActionStage_ASCommon_h

#import <Foundation/Foundation.h>
#include <inttypes.h>

//#define DISABLE_LOGGING

//#define INTERNAL_RELEASE

//#define EXTERNAL_INTERNAL_RELEASE

#ifdef __cplusplus
extern "C" {
#endif

void TGLogSetEnabled(bool enabled);
bool TGLogEnabled();
void TGLog(NSString *format, ...);
void TGLogv(NSString *format, va_list args);

void TGLogSynchronize();
NSArray *TGGetLogFilePaths(int count);
NSArray *TGGetPackedLogs();
    
#ifdef __cplusplus
}
#endif

#endif
