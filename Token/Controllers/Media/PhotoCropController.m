#import "PhotoCropController.h"

#import "UIControl+HitTestEdgeInsets.h"
#import "Font.h"

#import "ImageUtils.h"
#import "ImageBlur.h"
#import "PaintUtils.h"

#import "PhotoEditorAnimation.h"
#import "PhotoEditorUtils.h"
#import "PhotoEditorInterfaceAssets.h"

#import "PhotoEditor.h"

#import "PGPhotoEditorValues.h"
#import "CameraShotMetadata.h"
#import "PaintingData.h"

#import "PhotoEditorPreviewView.h"
#import "PhotoCropView.h"
#import "ModernButtonView.h"

#import "MenuSheetController.h"

#import "Common.h"

const CGFloat PhotoCropButtonsWrapperSize = 61.0f;
const CGSize PhotoCropAreaInsetSize = { 9, 9 };

NSString * const PhotoCropOriginalAspectRatio = @"original";

@interface PhotoCropController ()
{
    bool _forVideo;
    
    UIView *_wrapperView;
    
    CGFloat _autoRotationAngle;
    
    UIView *_buttonsWrapperView;
    ModernButton *_rotateButton;
    ModernButton *_mirrorButton;
    ModernButton *_aspectRatioButton;
    ModernButton *_resetButton;

    PhotoCropView *_cropView;
    
    UIImage *_screenImage;
    
    UIView *_snapshotView;
    UIImage *_snapshotImage;
    
    bool _appeared;
    UIImage *_imagePendingLoad;
    
    CGRect _transitionOutFrame;
    UIView *_transitionOutView;
    
    CGFloat _resetButtonWidth;
    
    dispatch_semaphore_t _waitSemaphore;
}

@property (nonatomic, weak) PhotoEditor *photoEditor;
@property (nonatomic, weak) PhotoEditorPreviewView *previewView;

@end

@implementation PhotoCropController

- (instancetype)initWithPhotoEditor:(PhotoEditor *)photoEditor previewView:(PhotoEditorPreviewView *)previewView metadata:(CameraShotMetadata *)metadata forVideo:(bool)forVideo
{
    self = [super init];
    if (self != nil)
    {
        self.photoEditor = photoEditor;
        self.previewView = previewView;
        _forVideo = forVideo;
        
        if (ABS(metadata.deviceAngle) > FLT_EPSILON)
            _autoRotationAngle = metadata.deviceAngle;
        
        _waitSemaphore = dispatch_semaphore_create(0);
    }
    return self;
}

- (void)loadView
{
    [super loadView];
    
    __weak PhotoCropController *weakSelf = self;
    void(^interactionEnded)(void) = ^
    {
        __strong PhotoCropController *strongSelf = weakSelf;
        if (strongSelf == nil)
            return;
        
        if ([strongSelf shouldAutorotate])
            [ViewController attemptAutorotation];
    };
    
    _wrapperView = [[UIView alloc] initWithFrame:self.view.bounds];
    _wrapperView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview:_wrapperView];
    
    PhotoEditor *photoEditor = self.photoEditor;
    _cropView = [[PhotoCropView alloc] initWithOriginalSize:photoEditor.originalSize hasArbitraryRotation:!_forVideo];
    [_cropView setCropRect:photoEditor.cropRect];
    [_cropView setCropOrientation:photoEditor.cropOrientation];
    [_cropView setRotation:photoEditor.cropRotation];
    [_cropView setMirrored:photoEditor.cropMirrored];
    _cropView.interactionBegan = ^
    {
        __strong PhotoCropController *strongSelf = weakSelf;
        if (strongSelf == nil)
            return;
        
        [strongSelf setAutoButtonHidden:true];
    };
    _cropView.croppingChanged = ^
    {
        __strong PhotoCropController *strongSelf = weakSelf;
        if (strongSelf == nil)
            return;
        
        [strongSelf _updateEditorValues];
        
        PhotoEditor *photoEditor = strongSelf.photoEditor;
        if (!photoEditor.hasDefaultCropping || photoEditor.cropLockedAspectRatio > FLT_EPSILON)
            [strongSelf setAutoButtonHidden:true];
        
        if (strongSelf.valuesChanged != nil)
            strongSelf.valuesChanged();
    };
    if (_snapshotView != nil)
    {
        [_cropView setSnapshotView:_snapshotView];
        _snapshotView = nil;
    }
    else if (_snapshotImage != nil)
    {
        [_cropView setSnapshotImage:_snapshotImage];
        _snapshotImage = nil;
    }
    _cropView.interactionEnded = interactionEnded;
    [_wrapperView addSubview:_cropView];
    
    [_cropView setPaintingImage:_photoEditor.paintingData.image];
    
    _buttonsWrapperView = [[UIView alloc] initWithFrame:CGRectZero];
    [_wrapperView addSubview:_buttonsWrapperView];
    
    _rotateButton = [[ModernButton alloc] initWithFrame:CGRectMake(0, 0, 36, 36)];
    _rotateButton.exclusiveTouch = true;
    _rotateButton.hitTestEdgeInsets = UIEdgeInsetsMake(-10, -10, -10, -10);
    [_rotateButton addTarget:self action:@selector(rotate) forControlEvents:UIControlEventTouchUpInside];
    [_rotateButton setImage:[UIImage imageNamed:@"PhotoEditorRotateIcon"] forState:UIControlStateNormal];
    [_buttonsWrapperView addSubview:_rotateButton];
    
    _mirrorButton = [[ModernButton alloc] initWithFrame:CGRectMake(0, 0, 36, 36)];
    _mirrorButton.exclusiveTouch = true;
    _mirrorButton.imageEdgeInsets = UIEdgeInsetsMake(4.0f, 0.0f, 0.0f, 0.0f);
    _mirrorButton.hitTestEdgeInsets = UIEdgeInsetsMake(-10, -10, -10, -10);
    [_mirrorButton addTarget:self action:@selector(mirror) forControlEvents:UIControlEventTouchUpInside];
    [_mirrorButton setImage:[UIImage imageNamed:@"PhotoEditorMirrorIcon"] forState:UIControlStateNormal];
    [_buttonsWrapperView addSubview:_mirrorButton];
    
    _aspectRatioButton = [[ModernButton alloc] initWithFrame:CGRectMake(0, 0, 36, 36)];
    _aspectRatioButton.exclusiveTouch = true;
    _aspectRatioButton.hitTestEdgeInsets = UIEdgeInsetsMake(-10, -10, -10, -10);
    [_aspectRatioButton addTarget:self action:@selector(aspectRatioButtonPressed) forControlEvents:UIControlEventTouchUpInside];
    [_aspectRatioButton setImage:[UIImage imageNamed:@"PhotoEditorAspectRatioIcon"] forState:UIControlStateNormal];
    [_aspectRatioButton setImage:[UIImage imageNamed:@"PhotoEditorAspectRatioIcon_Applied"] forState:UIControlStateSelected];
    [_aspectRatioButton setImage:[UIImage imageNamed:@"PhotoEditorAspectRatioIcon_Applied"] forState:UIControlStateSelected | UIControlStateHighlighted];
    [_buttonsWrapperView addSubview:_aspectRatioButton];
    
    NSString *resetButtonTitle = TGLocalized(@"CropReset");
    _resetButton = [[ModernButton alloc] init];
    _resetButton.exclusiveTouch = true;
    _resetButton.hitTestEdgeInsets = UIEdgeInsetsMake(-10, -10, -10, -10);
    _resetButton.titleLabel.font = [Font systemFontOfSize:13];
    [_resetButton addTarget:self action:@selector(resetButtonPressed) forControlEvents:UIControlEventTouchUpInside];
    [_resetButton setTitle:resetButtonTitle forState:UIControlStateNormal];
    [_resetButton setTitleColor:[UIColor whiteColor]];
    [_resetButton sizeToFit];
    _resetButton.frame = CGRectMake(0, 0, _resetButton.frame.size.width, 24);
    [_buttonsWrapperView addSubview:_resetButton];
    
    if ([resetButtonTitle respondsToSelector:@selector(sizeWithAttributes:)])
        _resetButtonWidth = CGCeil([resetButtonTitle sizeWithAttributes:@{ NSFontAttributeName:TGSystemFontOfSize(13) }].width);
    else
        _resetButtonWidth = CGCeil([resetButtonTitle sizeWithFont:TGSystemFontOfSize(13)].width);
    
    if (photoEditor.cropLockedAspectRatio > FLT_EPSILON)
    {
        _aspectRatioButton.selected = true;
        [_cropView setLockedAspectRatio:photoEditor.cropLockedAspectRatio performResize:false animated:false];
    }
    else if ([photoEditor hasDefaultCropping] && ABS(_autoRotationAngle) > FLT_EPSILON)
    {
        _resetButton.selected = true;
        [_resetButton setTitle:TGLocalized(@"CropAuto") forState:UIControlStateNormal];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self transitionIn];
}

- (BOOL)shouldAutorotate
{
    return (!_cropView.isTracking && [super shouldAutorotate]);
}

- (bool)isDismissAllowed
{
    return _appeared && !_cropView.isTracking && !_cropView.isAnimating;
}

#pragma mark -

- (void)setAutorotationAngle:(CGFloat)autorotationAngle
{
    if (fabs(autorotationAngle) < TGDegreesToRadians(5.0f))
        return;
    
    _autoRotationAngle = autorotationAngle;
    
    PhotoEditor *photoEditor = self.photoEditor;
    if ([photoEditor hasDefaultCropping] && fabs(_autoRotationAngle) > FLT_EPSILON && photoEditor.cropLockedAspectRatio < FLT_EPSILON)
    {
        _resetButton.selected = true;
        [_resetButton setTitle:TGLocalized(@"CropAuto") forState:UIControlStateNormal];
    }
}

- (void)setImage:(UIImage *)image
{
    if (_dismissing && !_switching)
        return;
    
    if (_waitSemaphore != nil)
        dispatch_semaphore_signal(_waitSemaphore);
    
    if (!_appeared)
    {
        _imagePendingLoad = image;
        return;
    }
    
    [_cropView setImage:image];
}

- (void)setSnapshotImage:(UIImage *)snapshotImage
{
    _snapshotImage = snapshotImage;
}

- (void)setSnapshotView:(UIView *)snapshotView
{
    _snapshotView = snapshotView;
}

- (void)_updateEditorValues
{
    PhotoEditor *photoEditor = self.photoEditor;
    photoEditor.cropRect = _cropView.cropRect;
    photoEditor.cropRotation = _cropView.rotation;
    photoEditor.cropLockedAspectRatio = _cropView.lockedAspectRatio;
    photoEditor.cropOrientation = _cropView.cropOrientation;
    photoEditor.cropMirrored = _cropView.mirrored;
}

#pragma mark - Transition

- (void)transitionIn
{
    _buttonsWrapperView.alpha = 0.0f;
    
    [UIView animateWithDuration:0.3f animations:^
    {
        _buttonsWrapperView.alpha = 1.0f;
    }];
    
    [_cropView animateTransitionIn];
}

- (void)animateTransitionIn
{
    if ([_transitionView isKindOfClass:[PhotoEditorPreviewView class]])
        [(PhotoEditorPreviewView *)_transitionView performTransitionToCropAnimated:true];
    
    [super animateTransitionIn];
}

- (void)_finishedTransitionInWithView:(UIView *)transitionView
{
    _appeared = true;
    
    if (_imagePendingLoad != nil)
        [_cropView setImage:_imagePendingLoad];
    [transitionView removeFromSuperview];
    
    [_cropView transitionInFinishedAnimated:false completion:nil];
}

- (void)transitionOutSwitching:(bool)switching completion:(void (^)(void))completion
{
    _dismissing = true;
    
    if (switching)
    {
        _switching = true;
        
        PhotoEditorPreviewView *previewView = self.previewView;
        [previewView performTransitionToCropAnimated:false];
        [previewView setSnapshotView:[_cropView cropSnapshotView]];
        
        [_cropView performConfirmAnimated:false updateInterface:false];
        
        if (!_forVideo)
        {
            PhotoEditor *photoEditor = self.photoEditor;
            
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^
            {
                if (dispatch_semaphore_wait(_waitSemaphore, dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC))))
                {
                    TGLog(@"Photo crop on switching failed");
                    return;
                }
                
                UIImage *croppedImage = [_cropView croppedImageWithMaxSize:PhotoEditorScreenImageMaxSize()];
                [photoEditor setImage:croppedImage forCropRect:_cropView.cropRect cropRotation:_cropView.rotation cropOrientation:_cropView.cropOrientation cropMirrored:_cropView.mirrored fullSize:false];
                
                [photoEditor processAnimated:false completion:^
                {
                    DispatchOnMainThread(^
                    {
                        [previewView setSnapshotImage:croppedImage];
                        
                        if (!previewView.hidden)
                            [previewView performTransitionInWithCompletion:nil];
                        else
                            [previewView setNeedsTransitionIn];
                    });
                }];
                
                if (self.finishedPhotoProcessing != nil)
                    self.finishedPhotoProcessing();
            });
        }
    }
    
    [UIView animateWithDuration:0.3f animations:^
    {
        _buttonsWrapperView.alpha = 0.0f;
    } completion:^(__unused BOOL finished)
    {
        if (completion != nil)
            completion();
    }];
    
    [_cropView animateTransitionOut];
}

- (CGRect)_targetFrameForTransitionInFromFrame:(CGRect)fromFrame
{
    CGSize referenceSize = [self referenceViewSize];
    
    UIInterfaceOrientation orientation = self.interfaceOrientation;
    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad)
        orientation = UIInterfaceOrientationPortrait;
    
    CGRect containerFrame = [PhotoCropController photoContainerFrameForParentViewFrame:CGRectMake(0, 0, referenceSize.width, referenceSize.height) toolbarLandscapeSize:self.toolbarLandscapeSize orientation:orientation hasArbitraryRotation:_cropView.hasArbitraryRotation];
    containerFrame = CGRectInset(containerFrame, PhotoCropAreaInsetSize.width, PhotoCropAreaInsetSize.height);
    
    CGSize fittedSize = ScaleToSize(fromFrame.size, containerFrame.size);
    CGRect toFrame = CGRectMake(containerFrame.origin.x + (containerFrame.size.width - fittedSize.width) / 2,
                                containerFrame.origin.y + (containerFrame.size.height - fittedSize.height) / 2,
                                fittedSize.width,
                                fittedSize.height);
    
    return toFrame;
}

- (void)transitionOutSaving:(bool)saving completion:(void (^)(void))completion
{
    UIView *snapshotView = nil;
    CGRect sourceFrame = CGRectZero;
    
    if (_transitionOutView != nil)
    {
        snapshotView = _transitionOutView;
        sourceFrame = _transitionOutFrame;
    }
    else
    {
        snapshotView = [_cropView cropSnapshotView];
        sourceFrame = [_cropView cropRectFrameForView:self.view];
    }

    snapshotView.frame = sourceFrame;
    
    if (snapshotView.superview != self.view)
        [self.view addSubview:snapshotView];
    
    [self transitionOutSwitching:false completion:nil];
    
    CGRect referenceFrame = CGRectZero;
    UIView *referenceView = nil;
    UIView *parentView = nil;
    
    if (self.beginTransitionOut != nil)
        referenceView = self.beginTransitionOut(&referenceFrame, &parentView);
    
    UIView *toTransitionView = nil;
    CGRect targetFrame = CGRectZero;
    
    if (parentView == nil)
        parentView = referenceView.superview.superview;
    
    UIView *backgroundSuperview = parentView;
    UIView *transitionBackgroundView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, backgroundSuperview.frame.size.width, backgroundSuperview.frame.size.height)];
    transitionBackgroundView.backgroundColor = [PhotoEditorInterfaceAssets toolbarBackgroundColor];
    [backgroundSuperview addSubview:transitionBackgroundView];
    
    [UIView animateWithDuration:0.3f animations:^
    {
        transitionBackgroundView.alpha = 0.0f;
    } completion:^(__unused BOOL finished)
    {
        [transitionBackgroundView removeFromSuperview];
    }];
    
    if (saving)
    {
        CGSize fittedSize = ScaleToSize(snapshotView.frame.size, self.view.frame.size);
        targetFrame = CGRectMake((self.view.frame.size.width - fittedSize.width) / 2,
                                 (self.view.frame.size.height - fittedSize.height) / 2,
                                 fittedSize.width,
                                 fittedSize.height);
        
        UIImage *transitionImage = nil;
        if ([referenceView isKindOfClass:[UIImageView class]])
            transitionImage = ((UIImageView *)referenceView).image;
        
        if (transitionImage != nil)
            toTransitionView = [[UIImageView alloc] initWithImage:transitionImage];
        else
            toTransitionView = [snapshotView snapshotViewAfterScreenUpdates:false];
        
        toTransitionView.frame = snapshotView.frame;
    }
    else
    {  
        UIImage *transitionImage = nil;
        if ([referenceView isKindOfClass:[UIImageView class]])
            transitionImage = ((UIImageView *)referenceView).image;
        
        if (transitionImage != nil)
            toTransitionView = [[UIImageView alloc] initWithImage:transitionImage];
        else
            toTransitionView = [referenceView snapshotViewAfterScreenUpdates:false];
        
        targetFrame = referenceFrame;
        toTransitionView.frame = snapshotView.frame;
    }
    
    [parentView addSubview:toTransitionView];
    
    POPSpringAnimation *animation = [PhotoEditorAnimation prepareTransitionAnimationForPropertyNamed:kPOPViewFrame];
    animation.fromValue = [NSValue valueWithCGRect:toTransitionView.frame];
    animation.toValue = [NSValue valueWithCGRect:targetFrame];
    
    POPSpringAnimation *snapshotAnimation = [PhotoEditorAnimation prepareTransitionAnimationForPropertyNamed:kPOPViewFrame];
    snapshotAnimation.fromValue = [NSValue valueWithCGRect:snapshotView.frame];
    snapshotAnimation.toValue = [NSValue valueWithCGRect:targetFrame];
    
    POPSpringAnimation *snapshotAlphaAnimation = [PhotoEditorAnimation prepareTransitionAnimationForPropertyNamed:kPOPViewAlpha];
    snapshotAlphaAnimation.fromValue = @([snapshotView alpha]);
    snapshotAlphaAnimation.toValue = @(0.0f);
    
    [PhotoEditorAnimation performBlock:^(__unused bool allFinished)
    {
        [toTransitionView removeFromSuperview];
        [snapshotView removeFromSuperview];
         
        if (completion != nil)
            completion();
    } whenCompletedAllAnimations:@[ animation, snapshotAnimation, snapshotAlphaAnimation ]];
    
    [toTransitionView pop_addAnimation:animation forKey:@"frame"];
    [snapshotView pop_addAnimation:snapshotAnimation forKey:@"frame"];
    [snapshotView pop_addAnimation:snapshotAlphaAnimation forKey:@"alpha"];
}

- (CGRect)transitionOutReferenceFrame
{
    return [_cropView cropRectFrameForView:self.view];
}

- (UIView *)transitionOutReferenceView
{
    return [_cropView cropSnapshotView];
}

- (void)prepareTransitionOutSaving:(bool)saving
{
    if (saving)
    {
        _transitionOutFrame = [_cropView cropRectFrameForView:self.view];
        
        [_cropView performConfirmAnimated:false updateInterface:false];
     
        _transitionOutView = [[UIImageView alloc] initWithImage:[_cropView croppedImageWithMaxSize:CGSizeMake(1280, 1280)]];
        _transitionOutView.frame = _transitionOutFrame;
        
        [self.view addSubview:_transitionOutView];

        _cropView.hidden = true;
        
        [self _updateEditorValues];
    }
}

- (id)currentResultRepresentation
{
    if (_transitionOutView != nil && [_transitionOutView isKindOfClass:[UIImageView class]])
    {
        return ((UIImageView *)_transitionOutView).image;
    }
    else
    {
        return [_cropView croppedImageWithMaxSize:CGSizeMake(750, 750)];
    }
}

#pragma mark - Actions

- (UIImageOrientation)cropOrientation
{
    return _cropView.cropOrientation;
}

- (void)rotate
{
    [_cropView rotate90DegreesCCWAnimated:true];
}

- (void)mirror
{
    [_cropView mirror];
}

- (void)aspectRatioButtonPressed
{
    if (_cropView.isAnimating)
        return;
    
    if (_cropView.isAspectRatioLocked)
    {
        [_cropView unlockAspectRatio];
        _aspectRatioButton.selected = false;
    }
    else
    {
        [_cropView performConfirmAnimated:true];
        
        MenuSheetController *controller = [[MenuSheetController alloc] init];
        controller.dismissesByOutsideTap = true;
        controller.hasSwipeGesture = true;
        __weak MenuSheetController *weakController = controller;
        __weak PhotoCropController *weakSelf = self;
        
        void (^action)(NSString *) = ^(NSString *ratioString)
        {
            __strong PhotoCropController *strongSelf = weakSelf;
            __strong MenuSheetController *strongController = weakController;
            if (strongSelf == nil)
                return;
            
            CGFloat aspectRatio = 0.0f;
            if ([ratioString isEqualToString:PhotoCropOriginalAspectRatio])
            {
                PhotoEditor *photoEditor = strongSelf->_photoEditor;
                aspectRatio = photoEditor.originalSize.height / photoEditor.originalSize.width;
            }
            else
            {
                aspectRatio = [ratioString floatValue];
                if (_cropView.cropOrientation == UIImageOrientationLeft || _cropView.cropOrientation == UIImageOrientationRight)
                    aspectRatio = 1.0f / aspectRatio;
            }
            
            strongSelf->_aspectRatioButton.selected = true;
            
            void (^setAspectRatioBlock)(void) = ^
            {
                [strongSelf setAutoButtonHidden:true];
                [strongSelf->_cropView setLockedAspectRatio:aspectRatio performResize:true animated:true];
            };
            
            if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
                setAspectRatioBlock();
            else
                DispatchAfter(0.1f, dispatch_get_main_queue(), setAspectRatioBlock);
            
            [strongController dismissAnimated:true];
        };
        
        NSMutableArray *items = [[NSMutableArray alloc] init];
        [items addObject:[[MenuSheetButtonItemView alloc] initWithTitle:TGLocalized(@"CropAspectRatioOriginal") type:MenuSheetButtonTypeDefault action:^{ action(PhotoCropOriginalAspectRatio); }]];
        [items addObject:[[MenuSheetButtonItemView alloc] initWithTitle:TGLocalized(@"CropAspectRatioSquare") type:MenuSheetButtonTypeDefault action:^{ action(@"1.0"); }]];
        
        CGSize croppedImageSize = _cropView.cropRect.size;
        if (_cropView.cropOrientation == UIImageOrientationLeft || _cropView.cropOrientation == UIImageOrientationRight)
            croppedImageSize = CGSizeMake(croppedImageSize.height, croppedImageSize.width);
        
        static NSArray *ratiosDefinitions = nil;
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^
        {
            ratiosDefinitions = @
            [
                @[ @3.0f, @2.0f ],
                @[ @5.0f, @3.0f ],
                @[ @4.0f, @3.0f ],
                @[ @5.0f, @4.0f ],
                @[ @7.0f, @5.0f ],
                @[ @16.0f, @9.0f ]
            ];
        });
        
        for (NSArray *ratioDef in ratiosDefinitions)
        {
            CGFloat widthComponent;
            CGFloat heightComponent;
            CGFloat ratio = 0.0f;
            
            if (croppedImageSize.width >= croppedImageSize.height)
            {
                widthComponent = [ratioDef.firstObject floatValue];
                heightComponent = [ratioDef.lastObject floatValue];
            }
            else
            {
                widthComponent = [ratioDef.lastObject floatValue];
                heightComponent = [ratioDef.firstObject floatValue];
            }
            
            ratio = heightComponent / widthComponent;
            
            [items addObject:[[MenuSheetButtonItemView alloc] initWithTitle:[NSString stringWithFormat:@"%d:%d", (int)widthComponent, (int)heightComponent] type:MenuSheetButtonTypeDefault action:^{ action([NSString stringWithFormat:@"%f", ratio]); }]];
        }
        
        [items addObject:[[MenuSheetButtonItemView alloc] initWithTitle:TGLocalized(@"Cancel") type:MenuSheetButtonTypeCancel action:^
        {
            __strong MenuSheetController *strongController = weakController;
            if (strongController != nil)
                [strongController dismissAnimated:true];
        }]];
        
        [controller setItemViews:items];
        controller.sourceRect = ^CGRect
        {
            __strong PhotoCropController *strongSelf = weakSelf;
            if (strongSelf != nil)
                return [strongSelf.view convertRect:strongSelf->_aspectRatioButton.frame fromView:strongSelf->_aspectRatioButton.superview];
            
            return CGRectZero;
        };
        [controller presentInViewController:self.parentViewController sourceView:self.view animated:true];
    }
}

- (void)resetButtonPressed
{
    if (_cropView.isAnimatingRotation)
        return;
    
    bool hasAutorotationAngle = ABS(_autoRotationAngle) > FLT_EPSILON;
    PhotoEditor *photoEditor = self.photoEditor;
    
    if ([photoEditor hasDefaultCropping] && photoEditor.cropLockedAspectRatio < FLT_EPSILON && hasAutorotationAngle && _resetButton.selected)
    {
        [_cropView setRotation:_autoRotationAngle animated:true];
        [self setAutoButtonHidden:true];
    }
    else
    {
        _aspectRatioButton.selected = false;
        
        [_cropView resetAnimated:true];
        
        if (hasAutorotationAngle)
            [self setAutoButtonHidden:false];
    }
    
    if (self.cropReset != nil)
        self.cropReset();
}

- (void)setAutoButtonHidden:(bool)hidden
{
    if (hidden)
    {
        _resetButton.selected = false;
        [_resetButton setTitle:TGLocalized(@"CropReset") forState:UIControlStateNormal];
    }
    else
    {
        _resetButton.selected = true;
        [_resetButton setTitle:TGLocalized(@"CropAuto") forState:UIControlStateNormal];
    }
}

#pragma mark - Layout

+ (CGRect)photoContainerFrameForParentViewFrame:(CGRect)parentViewFrame toolbarLandscapeSize:(CGFloat)toolbarLandscapeSize orientation:(UIInterfaceOrientation)orientation hasArbitraryRotation:(bool)hasArbitraryRotation
{
    CGFloat panelToolbarPortraitSize = PhotoEditorToolbarSize;
    CGFloat panelToolbarLandscapeSize = toolbarLandscapeSize;
    
    if (hasArbitraryRotation)
    {
        panelToolbarPortraitSize += PhotoEditorPanelSize;
        panelToolbarLandscapeSize += PhotoEditorPanelSize;
    }
    else
    {
        panelToolbarPortraitSize += PhotoEditorPanelSize - 55;
        panelToolbarLandscapeSize += PhotoEditorPanelSize - 55;
    }
    
    switch (orientation)
    {
        case UIInterfaceOrientationLandscapeLeft:
            return CGRectMake(panelToolbarLandscapeSize, 0, parentViewFrame.size.width - panelToolbarLandscapeSize, parentViewFrame.size.height);
            
        case UIInterfaceOrientationLandscapeRight:
            return CGRectMake(0, 0, parentViewFrame.size.width - panelToolbarLandscapeSize, parentViewFrame.size.height);
            
        default:
            return CGRectMake(0, 0, parentViewFrame.size.width, parentViewFrame.size.height - panelToolbarPortraitSize);
    }
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    UIView *snapshotView = [_buttonsWrapperView snapshotViewAfterScreenUpdates:false];
    snapshotView.frame = _buttonsWrapperView.frame;
    [_wrapperView insertSubview:snapshotView aboveSubview:_buttonsWrapperView];
    
    _buttonsWrapperView.alpha = 0.0f;
    [UIView animateWithDuration:duration animations:^
    {
        _buttonsWrapperView.alpha = 1.0f;
        snapshotView.alpha = 0.0f;
    } completion:^(__unused BOOL finished)
    {
        [snapshotView removeFromSuperview];
    }];
    
    [self.view setNeedsLayout];
    
    [super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
}

- (void)viewWillLayoutSubviews
{
    [super viewWillLayoutSubviews];
    
    [self updateLayout:[UIApplication sharedApplication].statusBarOrientation];
}

- (void)updateLayout:(UIInterfaceOrientation)orientation
{
    if ([self inFormSheet] || [UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad)
        orientation = UIInterfaceOrientationPortrait;
    
    CGSize referenceSize = [self referenceViewSize];
    
    CGFloat screenSide = MAX(referenceSize.width, referenceSize.height) + 2 * PhotoEditorPanelSize;
    _wrapperView.frame = CGRectMake((referenceSize.width - screenSide) / 2, (referenceSize.height - screenSide) / 2, screenSide, screenSide);
    
    UIEdgeInsets screenEdges = UIEdgeInsetsMake((screenSide - referenceSize.height) / 2, (screenSide - referenceSize.width) / 2, (screenSide + referenceSize.height) / 2, (screenSide + referenceSize.width) / 2);
    
    [UIView performWithoutAnimation:^
    {
        switch (orientation)
        {
            case UIInterfaceOrientationLandscapeLeft:
            {
                _buttonsWrapperView.frame = CGRectMake(screenEdges.left + self.toolbarLandscapeSize,
                                                       screenEdges.top,
                                                       PhotoCropButtonsWrapperSize,
                                                       referenceSize.height);
                
                _rotateButton.frame = CGRectMake(25, 10, _rotateButton.frame.size.width, _rotateButton.frame.size.height);
                _mirrorButton.frame = CGRectMake(25, 60, _mirrorButton.frame.size.width, _mirrorButton.frame.size.height);
                
                _aspectRatioButton.frame = CGRectMake(25,
                                                      _buttonsWrapperView.frame.size.height - _aspectRatioButton.frame.size.height - 10,
                                                      _aspectRatioButton.frame.size.width,
                                                      _aspectRatioButton.frame.size.height);
                
                _resetButton.transform = CGAffineTransformIdentity;
                _resetButton.frame = CGRectMake(0, 0, _resetButtonWidth, 24);
                
                CGFloat xOrigin = 0;
                if (_resetButton.frame.size.width > _buttonsWrapperView.frame.size.width)
                {
                    _resetButton.transform = CGAffineTransformMakeRotation((CGFloat)M_PI_2);
                    xOrigin = 8;
                }
                
                _resetButton.frame = CGRectMake(_buttonsWrapperView.frame.size.width - _resetButton.frame.size.width - xOrigin,
                                                (_buttonsWrapperView.frame.size.height - _resetButton.frame.size.height) / 2,
                                                _resetButton.frame.size.width,
                                                _resetButton.frame.size.height);
            }
                break;
                
            case UIInterfaceOrientationLandscapeRight:
            {
                _buttonsWrapperView.frame = CGRectMake(screenEdges.right - self.toolbarLandscapeSize - PhotoCropButtonsWrapperSize,
                                                       screenEdges.top,
                                                       PhotoCropButtonsWrapperSize,
                                                       referenceSize.height);
                
                _rotateButton.frame = CGRectMake(_buttonsWrapperView.frame.size.width - _rotateButton.frame.size.width - 25, 10, _rotateButton.frame.size.width, _rotateButton.frame.size.height);
                _mirrorButton.frame = CGRectMake(_buttonsWrapperView.frame.size.width - _mirrorButton.frame.size.width - 25, 60, _mirrorButton.frame.size.width, _mirrorButton.frame.size.height);
                
                _aspectRatioButton.frame = CGRectMake(_buttonsWrapperView.frame.size.width - _aspectRatioButton.frame.size.width - 25,
                                                      _buttonsWrapperView.frame.size.height - _aspectRatioButton.frame.size.height - 10,
                                                      _aspectRatioButton.frame.size.width,
                                                      _aspectRatioButton.frame.size.height);
                
                _resetButton.transform = CGAffineTransformIdentity;
                _resetButton.frame = CGRectMake(0, 0, _resetButtonWidth, 24);
                
                CGFloat xOrigin = 0;
                if (_resetButtonWidth > _buttonsWrapperView.frame.size.width)
                {
                    _resetButton.transform = CGAffineTransformMakeRotation((CGFloat)-M_PI_2);
                    xOrigin = 8;
                }
                
                _resetButton.frame = CGRectMake(xOrigin,
                                                (_buttonsWrapperView.frame.size.height - _resetButton.frame.size.height) / 2,
                                                _resetButton.frame.size.width,
                                                _resetButton.frame.size.height);
            }
                break;
                
            default:
            {
                _buttonsWrapperView.frame = CGRectMake(screenEdges.left,
                                                       screenEdges.bottom - PhotoEditorToolbarSize - PhotoCropButtonsWrapperSize,
                                                       referenceSize.width,
                                                       PhotoCropButtonsWrapperSize);
                
                _rotateButton.frame = CGRectMake(10, _buttonsWrapperView.frame.size.height - _rotateButton.frame.size.height - 25, _rotateButton.frame.size.width, _rotateButton.frame.size.height);
                _mirrorButton.frame = CGRectMake(60, _buttonsWrapperView.frame.size.height - _mirrorButton.frame.size.height - 25, _mirrorButton.frame.size.width, _mirrorButton.frame.size.height);
                
                _aspectRatioButton.frame = CGRectMake(_buttonsWrapperView.frame.size.width - _aspectRatioButton.frame.size.width - 10,
                                                      _buttonsWrapperView.frame.size.height - _aspectRatioButton.frame.size.height - 25,
                                                      _aspectRatioButton.frame.size.width,
                                                      _aspectRatioButton.frame.size.height);
                
                _resetButton.transform = CGAffineTransformIdentity;
                _resetButton.frame = CGRectMake((_buttonsWrapperView.frame.size.width - _resetButton.frame.size.width) / 2,
                                                10,
                                                _resetButtonWidth,
                                                24);
            }
                break;
        }
    }];
    
    CGRect containerFrame = [PhotoCropController photoContainerFrameForParentViewFrame:CGRectMake(0, 0, referenceSize.width, referenceSize.height) toolbarLandscapeSize:self.toolbarLandscapeSize orientation:orientation hasArbitraryRotation:_cropView.hasArbitraryRotation];
    containerFrame = CGRectOffset(containerFrame, screenEdges.left, screenEdges.top);
    _cropView.interfaceOrientation = orientation;
    _cropView.frame = CGRectInset(containerFrame, PhotoCropAreaInsetSize.width, PhotoCropAreaInsetSize.height);
    
    [UIView performWithoutAnimation:^
    {
        [_cropView _layoutRotationView];
    }];
}

@end