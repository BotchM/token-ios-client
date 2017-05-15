#import "LegacyCameraController.h"

#import "Hacks.h"

#import <AVFoundation/AVFoundation.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <CommonCrypto/CommonDigest.h>

#import "ImageUtils.h"
#import "ProgressWindow.h"

#import "LegacyMediaPickerTipView.h"

#import "TGImagePickerController.h"
#import "Common.h"
#import "AppDelegate.h"

@interface LegacyCameraController () <UINavigationControllerDelegate, UIImagePickerControllerDelegate>
{
    ProgressWindow *_progressWindow;
    bool _didShowTip;
}

@end

@implementation LegacyCameraController

- (void)setAvatarMode:(bool)avatarMode
{
    _avatarMode = avatarMode;
    self.allowsEditing = YES;// _avatarMode;
}

- (void)loadView
{
    [super loadView];
    
    self.delegate = self;
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleDefault;
}

- (BOOL)prefersStatusBarHidden
{
    return false;
}

- (BOOL)shouldAutorotate
{
    return false;
}

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
}

- (void)viewWillAppear:(BOOL)animated
{
    self.allowsEditing = YES;
    if (!_didShowTip && _isInDocumentMode)
    {
        if (![[[NSUserDefaults standardUserDefaults] objectForKey:@"didShowDocumentPickerTip"] boolValue])
        {
            [[NSUserDefaults standardUserDefaults] setObject:@true forKey:@"didShowDocumentPickerTip"];
            
            _didShowTip = true;
            LegacyMediaPickerTipView *tipView = [[LegacyMediaPickerTipView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.view.bounds.size.width, self.view.bounds.size.height)];
            tipView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
            [self.view addSubview:tipView];
        }
    }
    
    if (iosMajorVersion() >= 7 && !_isInDocumentMode)
    {
        if (animated)
        {
            [UIView animateWithDuration:0.3 animations:^
            {
                [Hacks setApplicationStatusBarAlpha:0.0f];
            }];
        }
        else
            [Hacks setApplicationStatusBarAlpha:0.0f];
    }
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    if (iosMajorVersion() >= 7 && !_isInDocumentMode)
    {
        if (animated)
        {
            [UIView animateWithDuration:0.3 animations:^
            {
                [Hacks setApplicationStatusBarAlpha:1.0f];
            }];
        }
        else
            [Hacks setApplicationStatusBarAlpha:1.0f];
    }
    
    [super viewWillDisappear:animated];
}

- (void)dealloc
{
    if (_progressWindow != nil)
    {
        [_progressWindow dismiss:true];
        _progressWindow = nil;
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)__unused picker
{
    id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
    [delegate legacyCameraControllerCompletedWithNoResult];
}

- (void)TGImagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSString *mediaType = [info objectForKey:UIImagePickerControllerMediaType];
    NSURL *referenceUrl = [info objectForKey:UIImagePickerControllerReferenceURL];
    
    if ([mediaType isEqualToString:(__bridge NSString *)kUTTypeImage])
    {
        //if (picker.sourceType == UIImagePickerControllerSourceTypeCamera)
        //    defaultFlashMode = picker.cameraFlashMode;
        
     
        if (_avatarMode)
        {
            CGRect cropRect = [[info objectForKey:UIImagePickerControllerCropRect] CGRectValue];
            if (ABS(cropRect.size.width - cropRect.size.height) > FLT_EPSILON)
            {
                if (cropRect.size.width < cropRect.size.height)
                {
                    cropRect.origin.x -= (cropRect.size.height - cropRect.size.width) / 2;
                    cropRect.size.width = cropRect.size.height;
                }
                else
                {
                    cropRect.origin.y -= (cropRect.size.width - cropRect.size.height) / 2;
                    cropRect.size.height = cropRect.size.width;
                }
            }
            
            id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
            UIImage *image = TGFixOrientationAndCrop([info objectForKey:UIImagePickerControllerOriginalImage], cropRect, CGSizeMake(600, 600));
            if (image != nil)
                [(id<TGImagePickerControllerDelegate>)delegate TGImagePickerController:nil didFinishPickingWithAssets:@[image]];
            
            return;
        }
        
        id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
        //if ([delegate conformsToProtocol:@protocol(TGImagePickerControllerDelegate)])
        //{
            if (!_isInDocumentMode)
            {
                NSURL *referenceUrl = info[UIImagePickerControllerReferenceURL];
                if (referenceUrl != nil)
                {
                    self.view.userInteractionEnabled = false;
                    
                    id libraryToken = [TGImagePickerController preloadLibrary];
                    [TGImagePickerController loadAssetWithUrl:referenceUrl completion:^(ALAsset *asset)
                    {
                        if (asset != nil)
                        {
                            int64_t randomId = 0;
                            arc4random_buf(&randomId, sizeof(randomId));
                            NSString *tempFileName = [NSTemporaryDirectory() stringByAppendingPathComponent:[[NSString alloc] initWithFormat:@"%" PRIx64 ".bin", randomId]];
                            NSOutputStream *os = [[NSOutputStream alloc] initToFileAtPath:tempFileName append:false];
                            [os open];
                            
                            ALAssetRepresentation *representation = asset.defaultRepresentation;
                            long long size = representation.size;
                            
                            uint8_t buf[128 * 1024];
                            for (long long offset = 0; offset < size; offset += 128 * 1024)
                            {
                                long long batchSize = MIN(128 * 1024, size - offset);
                                NSUInteger readBytes = [representation getBytes:buf fromOffset:offset length:(NSUInteger)batchSize error:nil];
                                [os write:buf maxLength:readBytes];
                            }
                            
                            [os close];
                            
                            NSString *mimeType = (__bridge_transfer NSString*)UTTypeCopyPreferredTagWithClass((__bridge CFStringRef)[representation UTI], kUTTagClassMIMEType);
                            
                            DispatchOnMainThread(^
                            {
                                [delegate legacyCameraControllerCompletedWithDocument:[NSURL fileURLWithPath:tempFileName] fileName:[representation filename] mimeType:mimeType];
                            });
                        }
                        else
                        {
                            DispatchOnMainThread(^
                            {
                                self.view.userInteractionEnabled = true;
                            });
                        }
                        
                        [libraryToken class];
                    }];
                }
           // }
            else
            {
                UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
                
                if (picker.sourceType == UIImagePickerControllerSourceTypeCamera && _storeCapturedAssets)
                {
                    @autoreleasepool
                    {
                        UIImageWriteToSavedPhotosAlbum(image, nil, nil, NULL);
                    }
                }
                
                [(id<TGImagePickerControllerDelegate>)delegate TGImagePickerController:nil didFinishPickingWithAssets:@[image]];
            }
        }
    }
    else if ([mediaType isEqualToString:(__bridge NSString *)kUTTypeMovie])
    {
        id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
        if ([delegate conformsToProtocol:@protocol(TGImagePickerControllerDelegate)])
        {
            if (_isInDocumentMode)
            {
                NSURL *referenceUrl = info[UIImagePickerControllerReferenceURL];
                if (referenceUrl != nil)
                {
                    self.view.userInteractionEnabled = false;
                    
                    id libraryToken = [TGImagePickerController preloadLibrary];
                    [TGImagePickerController loadAssetWithUrl:referenceUrl completion:^(ALAsset *asset)
                     {
                         if (asset != nil)
                         {
                             int64_t randomId = 0;
                             arc4random_buf(&randomId, sizeof(randomId));
                             NSString *tempFileName = [NSTemporaryDirectory() stringByAppendingPathComponent:[[NSString alloc] initWithFormat:@"%" PRIx64 ".bin", randomId]];
                             NSOutputStream *os = [[NSOutputStream alloc] initToFileAtPath:tempFileName append:false];
                             [os open];
                             
                             ALAssetRepresentation *representation = asset.defaultRepresentation;
                             long long size = representation.size;
                             
                             uint8_t buf[128 * 1024];
                             for (long long offset = 0; offset < size; offset += 128 * 1024)
                             {
                                 long long batchSize = MIN(128 * 1024, size - offset);
                                 NSUInteger readBytes = [representation getBytes:buf fromOffset:offset length:(NSUInteger)batchSize error:nil];
                                 [os write:buf maxLength:readBytes];
                             }
                             
                             [os close];
                             
                             NSString *mimeType = (__bridge_transfer NSString*)UTTypeCopyPreferredTagWithClass((__bridge CFStringRef)[representation UTI], kUTTagClassMIMEType);
                             
                             DispatchOnMainThread(^
                                                    {
                                                        [delegate legacyCameraControllerCompletedWithDocument:[NSURL fileURLWithPath:tempFileName] fileName:[representation filename] mimeType:mimeType];
                                                    });
                         }
                         else
                         {
                             DispatchOnMainThread(^
                                                    {
                                                        self.view.userInteractionEnabled = true;
                                                    });
                         }
                         
                         [libraryToken class];
                     }];
                }
            }
            else
            {
                _progressWindow = [[ProgressWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
                [_progressWindow show:true];
                
                NSURL *mediaUrl = [info objectForKey:UIImagePickerControllerMediaURL];
                
                NSString *assetHash = nil;
                if (_storeCapturedAssets && [referenceUrl absoluteString].length != 0)
                {
                    assetHash = [[NSString alloc] initWithFormat:@"%@", [referenceUrl absoluteString]];
                    TGLog(@"Video hash: %@", assetHash);
                }
                
                bool deleteFile = true;
                
                if (picker.sourceType == UIImagePickerControllerSourceTypeCamera && _storeCapturedAssets)
                {
                    UISaveVideoAtPathToSavedPhotosAlbum(mediaUrl.path, [self class], @selector(video:didFinishSavingWithError:contextInfo:), NULL);
                    deleteFile = false;
                }
                
                NSString *videosPath = [[AppDelegate documentsPath] stringByAppendingPathComponent:@"video"];
                NSFileManager *fileManager = [NSFileManager defaultManager];
                NSError *error = nil;
                [fileManager createDirectoryAtPath:videosPath withIntermediateDirectories:true attributes:nil error:&error];
                
                NSString *tmpPath = NSTemporaryDirectory();
                
                int64_t fileId = 0;
                arc4random_buf(&fileId, sizeof(fileId));
                NSString *videoMp4FilePath = [tmpPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%" PRId64 ".mp4", fileId]];
                
                [ActionStageInstance() dispatchOnStageQueue:^
                {
//                    NSDictionary *existingData = [ImageDownloadActor serverMediaDataForAssetUrl:assetHash];
//                    if (existingData != nil)
//                    {
//                        DispatchOnMainThread(^
//                                               {
//                                                   [_progressWindow dismiss:true];
//                                                   _progressWindow = nil;
//                                                   
//                                                   id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
//                                                   [delegate legacyCameraControllerCompletedWithExistingMedia:existingData[@"videoAttachment"]];
   //                                            });
//                    }
//                    else
//                    {
                        AVAsset *avAsset = [[AVURLAsset alloc] initWithURL:mediaUrl options:nil];
                        
                        AVAssetExportSession *exportSession = [[AVAssetExportSession alloc] initWithAsset:avAsset presetName:AVAssetExportPresetPassthrough];
                        
                        exportSession.outputURL = [NSURL fileURLWithPath:videoMp4FilePath];
                        exportSession.outputFileType = AVFileTypeMPEG4;
                        
                        [exportSession exportAsynchronouslyWithCompletionHandler:^
                        {
                            bool endProcessing = false;
                            bool success = false;
                            
                            switch ([exportSession status])
                            {
                                case AVAssetExportSessionStatusFailed:
                                    NSLog(@"Export failed: %@", [[exportSession error] localizedDescription]);
                                    endProcessing = true;
                                    break;
                                case AVAssetExportSessionStatusCancelled:
                                    endProcessing = true;
                                    NSLog(@"Export canceled");
                                    break;
                                case AVAssetExportSessionStatusCompleted:
                                {
                                    TGLog(@"Export mp4 completed");
                                    endProcessing = true;
                                    success = true;
                                    
                                    break;
                                }
                                default:
                                    break;
                            }
                            
                            if (endProcessing)
                            {
                                if (deleteFile)
                                    [fileManager removeItemAtURL:mediaUrl error:nil];
                                
                                if (success)
                                {
                                    AVAsset *mp4Asset = [AVAsset assetWithURL:[NSURL fileURLWithPath:videoMp4FilePath]];
                                    
                                    AVAssetImageGenerator *imageGenerator = [[AVAssetImageGenerator alloc] initWithAsset:mp4Asset];
                                    imageGenerator.maximumSize = CGSizeMake(800, 800);
                                    imageGenerator.appliesPreferredTrackTransform = true;
                                    NSError *imageError = nil;
                                    CGImageRef imageRef = [imageGenerator copyCGImageAtTime:CMTimeMake(0, mp4Asset.duration.timescale) actualTime:NULL error:&imageError];
                                    UIImage *previewImage = [[UIImage alloc] initWithCGImage:imageRef];
                                    if (imageRef != NULL)
                                        CGImageRelease(imageRef);
                                    
                                    if (error == nil && [[mp4Asset tracksWithMediaType:AVMediaTypeVideo] count] > 0)
                                    {
                                        AVAssetTrack *track = [[mp4Asset tracksWithMediaType:AVMediaTypeVideo] objectAtIndex:0];
                                        
                                        CGSize trackNaturalSize = track.naturalSize;
                                        CGSize naturalSize = CGRectApplyAffineTransform(CGRectMake(0, 0, trackNaturalSize.width, trackNaturalSize.height), track.preferredTransform).size;
                                        
                                        NSTimeInterval duration = CMTimeGetSeconds(mp4Asset.duration);
                                        
                                        NSDictionary *finalFileAttributes = [[NSFileManager defaultManager] attributesOfItemAtPath:videoMp4FilePath error:nil];
                                        int32_t fileSize = (int32_t)[[finalFileAttributes objectForKey:NSFileSize] intValue];
                                        
                                        DispatchOnMainThread(^
                                                               {
                                                                   [_progressWindow dismiss:true];
                                                                   _progressWindow = nil;
                                                                   
                                                                   id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
                                                                   [delegate legacyCameraControllerCapturedVideoWithTempFilePath:videoMp4FilePath fileSize:fileSize previewImage:previewImage duration:duration dimensions:naturalSize assetUrl:assetHash];
                                                               });
                                    }
                                }
                                else
                                {
                                    DispatchOnMainThread(^
                                                           {
                                                               [_progressWindow dismiss:true];
                                                               _progressWindow = nil;
                                                               
                                                               id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
                                                               [delegate legacyCameraControllerCompletedWithNoResult];
                                                           });
                                }
                            }
                        }];
                    //}
                }];
            }
        }
    }
}

- (NSString *)_dictionaryString:(NSDictionary *)dict
{
    NSMutableString *string = [[NSMutableString alloc] init];
    
    [dict enumerateKeysAndObjectsUsingBlock:^(id key, id value, __unused BOOL *stop)
     {
         if ([key isKindOfClass:[NSString class]])
             [string appendString:key];
         else if ([key isKindOfClass:[NSNumber class]])
             [string appendString:[key description]];
         [string appendString:@":"];
         
         if ([value isKindOfClass:[NSString class]])
             [string appendString:value];
         else if ([value isKindOfClass:[NSNumber class]])
             [string appendString:[value description]];
         else if ([value isKindOfClass:[NSDictionary class]])
         {
             [string appendString:@"{"];
             [string appendString:[self _dictionaryString:value]];
             [string appendString:@"}"];
         }
         
         [string appendString:@";"];
     }];
    
    return string;
}

+ (void)video:(NSString *)videoPath didFinishSavingWithError:(NSError *)error contextInfo:(void *)__unused contextInfo
{
    [[NSFileManager defaultManager] removeItemAtPath:videoPath error:nil];
    if (error != nil)
        TGLog(@"Video saving error: %@", error);
}

- (void)actionStageActionRequested:(NSString *)action options:(id)options
{
    if ([action isEqualToString:@"imageCropResult"])
    {
        UIImage *image = options;
        
        if ([options isKindOfClass:[UIImage class]])
        {
            id<LegacyCameraControllerDelegate> delegate = _completionDelegate;
            if ([delegate conformsToProtocol:@protocol(TGImagePickerControllerDelegate)])
                [(id<TGImagePickerControllerDelegate>)delegate TGImagePickerController:nil didFinishPickingWithAssets:@[image]];
        }
    }
}

@end
