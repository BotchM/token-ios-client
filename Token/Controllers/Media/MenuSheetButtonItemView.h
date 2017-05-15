#import "MenuSheetItemView.h"

typedef enum
{
    MenuSheetButtonTypeDefault,
    MenuSheetButtonTypeCancel,
    MenuSheetButtonTypeDestructive,
    MenuSheetButtonTypeSend
} MenuSheetButtonType;

@interface MenuSheetButtonItemView : MenuSheetItemView

@property (nonatomic, strong) NSString *title;
@property (nonatomic, assign) MenuSheetButtonType buttonType;
@property (nonatomic, copy) void(^longPressAction)(void);
@property (nonatomic, copy) void (^action)(void);

- (instancetype)initWithTitle:(NSString *)title type:(MenuSheetButtonType)type action:(void (^)(void))action
NS_SWIFT_NAME(init(title:type:action:));

@end

extern const CGFloat MenuSheetButtonItemViewHeight;
