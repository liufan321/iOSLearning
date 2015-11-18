//
//  UIPopoverSupport.h
//  UIKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

/// Popover 箭头方向
typedef NS_OPTIONS(NSUInteger, UIPopoverArrowDirection) {
    // 上
    UIPopoverArrowDirectionUp = 1UL << 0,
    // 下
    UIPopoverArrowDirectionDown = 1UL << 1,
    // 左
    UIPopoverArrowDirectionLeft = 1UL << 2,
    // 右
    UIPopoverArrowDirectionRight = 1UL << 3,
    // 任意
    UIPopoverArrowDirectionAny = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown | UIPopoverArrowDirectionLeft | UIPopoverArrowDirectionRight,
    // 未知
    UIPopoverArrowDirectionUnknown = NSUIntegerMax
};

@interface UIViewController (UIPopoverController)

/* modalInPopover is set on the view controller when you wish to force the popover hosting the view controller into modal behavior. When this is active, the popover will ignore events outside of its bounds until this is set to NO.
 
 - modalInPopover 用于将 popover 弹出的视图控制器强制设置为 modal 的行为
 - 当该属性设置为 YES 时，popover 将忽略外部的点击事件
 
 大白话解释：
 - 默认数值是 NO，在 popover 外侧点击会关闭视图控制器
 - 如果设置成 YES，忽略 popover 外侧的点击，需要自己调用 dismiss 方法关闭视图控制器
 */
@property (nonatomic,readwrite,getter=isModalInPopover) BOOL modalInPopover NS_AVAILABLE_IOS(3_2);

/* contentSizeForViewInPopover allows you to set the size of the content from within the view controller. This property is read/write, and you should generally not override it.
 
 - 允许设置视图控制器内部视图的大小
 - 此属性是可读/可写的，通常不需要重写此属性
 
 * 注意：此属性在 iOS 7.0 已经废弃，请使用 UIViewController.preferredContentSize 设置
 */
@property (nonatomic,readwrite) CGSize contentSizeForViewInPopover NS_DEPRECATED_IOS(3_2, 7_0, "Use UIViewController.preferredContentSize instead.") __TVOS_PROHIBITED;

@end

