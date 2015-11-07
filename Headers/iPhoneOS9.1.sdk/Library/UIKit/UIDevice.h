//
//  UIDevice.h
//  UIKit
//
//  Copyright (c) 2007-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 设备方向
 */
typedef NS_ENUM(NSInteger, UIDeviceOrientation) {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
                                            // 垂直方向，Home 按钮在下方
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
                                            // 垂直方向，Home 按钮在上方
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
                                            // 水平方向，Home 按钮在右侧
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
                                            // 水平方向，Home 按钮在左侧
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
                                            // 设备平放，屏幕冲上
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
                                            // 设备平放，屏幕冲下
} __TVOS_PROHIBITED;

/*!
 设备电池状态
 */
typedef NS_ENUM(NSInteger, UIDeviceBatteryState) {
    UIDeviceBatteryStateUnknown,
    UIDeviceBatteryStateUnplugged,   // on battery, discharging
                                     // 使用电池，未充电
    UIDeviceBatteryStateCharging,    // plugged in, less than 100%
                                     // 充电，电量少于 100%
    UIDeviceBatteryStateFull,        // plugged in, at 100%
                                     // 充电，电量 100%
} __TVOS_PROHIBITED;              // available in iPhone 3.0

/*!
 设备类型
 */
typedef NS_ENUM(NSInteger, UIUserInterfaceIdiom) {
    UIUserInterfaceIdiomUnspecified = -1,
    UIUserInterfaceIdiomPhone NS_ENUM_AVAILABLE_IOS(3_2), // iPhone and iPod touch style UI
    UIUserInterfaceIdiomPad NS_ENUM_AVAILABLE_IOS(3_2), // iPad style UI
#ifndef SDK_HIDE_TIDE
    UIUserInterfaceIdiomTV NS_ENUM_AVAILABLE_IOS(9_0), // Apple TV style UI
#endif
};

/// 判断设备是否处于垂直方向
static inline BOOL UIDeviceOrientationIsPortrait(UIDeviceOrientation orientation)  __TVOS_PROHIBITED {
    return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown);
}

/// 判断设备是否处于水平方向
static inline BOOL UIDeviceOrientationIsLandscape(UIDeviceOrientation orientation)  __TVOS_PROHIBITED {
    return ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

/*!
 UIDevice 类提供了一个单例实例，表示当前设备。
 
 通过此实例，可以获取设备的信息，诸如：指定的名称，设备型号，操作系统名称和版本。
 */
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIDevice : NSObject 

/// 返回表示当前设备的单例对象
+ (UIDevice *)currentDevice;

@property(nonatomic,readonly,strong) NSString    *name;              // e.g. "My iPhone"
                                                                     // 名称
@property(nonatomic,readonly,strong) NSString    *model;             // e.g. @"iPhone", @"iPod touch"
                                                                     // 型号
@property(nonatomic,readonly,strong) NSString    *localizedModel;    // localized version of model
                                                                     // 本地化型号
@property(nonatomic,readonly,strong) NSString    *systemName;        // e.g. @"iOS"
                                                                     // 系统名称
@property(nonatomic,readonly,strong) NSString    *systemVersion;     // e.g. @"4.0"
                                                                     // 系统版本
/// 返回当前设备方向，如果没有注册设备方向通知，该属性返回 UIDeviceOrientationUnknown
@property(nonatomic,readonly) UIDeviceOrientation orientation __TVOS_PROHIBITED;       // return current device orientation.  this will return UIDeviceOrientationUnknown unless device orientation notifications are being generated.

/// 用于唯一标示设备的 UUID
@property(nullable, nonatomic,readonly,strong) NSUUID      *identifierForVendor NS_AVAILABLE_IOS(6_0);      // a UUID that may be used to uniquely identify the device, same across apps from a single vendor.

/// 标示是否发布方向旋转通知
@property(nonatomic,readonly,getter=isGeneratingDeviceOrientationNotifications) BOOL generatesDeviceOrientationNotifications __TVOS_PROHIBITED;
- (void)beginGeneratingDeviceOrientationNotifications __TVOS_PROHIBITED;      // nestable
- (void)endGeneratingDeviceOrientationNotifications __TVOS_PROHIBITED;

/// 是否允许监听电池电量，默认值是 NO，需要在真机设置才有效
@property(nonatomic,getter=isBatteryMonitoringEnabled) BOOL batteryMonitoringEnabled NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // default is NO
/// 设备电池状态，如果禁用监听，返回 UIDeviceBatteryStateUnknown
@property(nonatomic,readonly) UIDeviceBatteryState          batteryState NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // UIDeviceBatteryStateUnknown if monitoring disabled
/// 设备电池电量，如果启用监听，返回 0 .. 1.0，否则返回 -1
@property(nonatomic,readonly) float                         batteryLevel NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;  // 0 .. 1.0. -1.0 if UIDeviceBatteryStateUnknown

/// 是否允许接近监听，默认值是 NO
@property(nonatomic,getter=isProximityMonitoringEnabled) BOOL proximityMonitoringEnabled NS_AVAILABLE_IOS(3_0); // default is NO
/// 接近状态，如果不允许接近监听，始终返回 NO
@property(nonatomic,readonly)                            BOOL proximityState NS_AVAILABLE_IOS(3_0);  // always returns NO if no proximity detector

/// 是否支持多任务
@property(nonatomic,readonly,getter=isMultitaskingSupported) BOOL multitaskingSupported NS_AVAILABLE_IOS(4_0);

/// 设备类型
@property(nonatomic,readonly) UIUserInterfaceIdiom userInterfaceIdiom NS_AVAILABLE_IOS(3_2);

/// 播放系统单击按键音效
- (void)playInputClick NS_AVAILABLE_IOS(4_2);  // Plays a click only if an enabling input view is on-screen and user has enabled input clicks.

@end

@protocol UIInputViewAudioFeedback <NSObject>
@optional

/// 允许播放输入按键提示音
/*!
 步骤
 1. 自定义输入视图，并且遵守 UIInputViewAudioFeedback 协议
 2. 实现 enableInputClicksWhenVisible 方法，返回 YES
 3. 监听按钮点击事件，调用 [[UIDevice currentDevice] playInputClick];
 */
@property (nonatomic, readonly) BOOL enableInputClicksWhenVisible; // If YES, an input view will enable playInputClick.

@end

/* The UI_USER_INTERFACE_IDIOM() function is provided for use when deploying to a version of the iOS less than 3.2. If the earliest version of iPhone/iOS that you will be deploying for is 3.2 or greater, you may use -[UIDevice userInterfaceIdiom] directly.
 
 UI_USER_INTERFACE_IDIOM() 函数是为 iOS 3.2 以前版本提供的。如果应用程序的版本大于 3.2，应该直接使用 -[UIDevice userInterfaceIdiom]
 */
static inline UIUserInterfaceIdiom UI_USER_INTERFACE_IDIOM() {
    return ([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)] ?
            [[UIDevice currentDevice] userInterfaceIdiom] :
            UIUserInterfaceIdiomPhone);
}

UIKIT_EXTERN NSString *const UIDeviceOrientationDidChangeNotification __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIDeviceBatteryStateDidChangeNotification   NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIDeviceBatteryLevelDidChangeNotification   NS_AVAILABLE_IOS(3_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIDeviceProximityStateDidChangeNotification NS_AVAILABLE_IOS(3_0);

NS_ASSUME_NONNULL_END
