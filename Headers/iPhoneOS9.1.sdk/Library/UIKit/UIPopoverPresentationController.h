//
//  UIPopoverPresentationController.h
//  UIKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <UIKit/UIPresentationController.h>
#import <UIKit/UIPopoverSupport.h>
#import <UIKit/UIPopoverBackgroundView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPopoverPresentationController;

__TVOS_PROHIBITED
@protocol UIPopoverPresentationControllerDelegate <UIAdaptivePresentationControllerDelegate>
@optional

// 准备 popover 展现
- (void)prepareForPopoverPresentation:(UIPopoverPresentationController *)popoverPresentationController;

// Called on the delegate when the popover controller will dismiss the popover. Return NO to prevent the
// dismissal of the view.
// 将要 dismiss popover 前调用，返回 NO 阻止视图的 dismiss
- (BOOL)popoverPresentationControllerShouldDismissPopover:(UIPopoverPresentationController *)popoverPresentationController;

// Called on the delegate when the user has taken action to dismiss the popover. This is not called when the popover is dimissed programatically.
// 通过操作 dismiss popover 时，调用此代理方法，通过程序 dismiss 不会调用此代理方法
- (void)popoverPresentationControllerDidDismissPopover:(UIPopoverPresentationController *)popoverPresentationController;

// -popoverPresentationController:willRepositionPopoverToRect:inView: is called on your delegate when the
// popover may require a different view or rectangle.
// 当 popover 请求一个不同的视图或矩形区域时调用此代理方法
- (void)popoverPresentationController:(UIPopoverPresentationController *)popoverPresentationController willRepositionPopoverToRect:(inout CGRect *)rect inView:(inout UIView  * __nonnull * __nonnull)view;

@end

NS_CLASS_AVAILABLE_IOS(8_0) __TVOS_PROHIBITED @interface UIPopoverPresentationController : UIPresentationController

@property (nullable, nonatomic, weak) id <UIPopoverPresentationControllerDelegate> delegate;

// 设置允许的箭头方向，如果该方向不可用，系统会尝试其他方向
// 具体的箭头方向，可以在 popover 展现之后，通过 arrowDirection 只读属性获得
@property (nonatomic, assign) UIPopoverArrowDirection permittedArrowDirections;

// 显示 popover 的定位参照视图，必须要指定
// 注意，如果参照的是导航栏的按钮，需要通过 `barButtonItem` 属性指定
@property (nullable, nonatomic, strong) UIView *sourceView;
// sourceView 的 bounds
@property (nonatomic, assign) CGRect sourceRect;

// By default, a popover is not allowed to overlap its source view rect.
// 默认情况下，popover 不允许与 source view 的矩形区域重叠

// When this is set to YES, popovers with more content than available space are allowed to overlap the source view rect in order to accommodate the content.
// 如果设置成 YES，允许 popover 可以与 source view 的矩形区域重叠
// 从而可以获得更大的可用空间，达到显示更多内容的目的
@property (nonatomic, assign) BOOL canOverlapSourceViewRect NS_AVAILABLE_IOS(9_0);

// 显示 popover 的定位参照 UIBarButtonItem
@property (nullable, nonatomic, strong) UIBarButtonItem *barButtonItem;

// Returns the direction the arrow is pointing on a presented popover. Before presentation, this returns UIPopoverArrowDirectionUnknown.
// - 只读属性，返回方向箭头指向展现的 popover 的方向
// - 例如：popover 在 sourceView 的上方，则返回的方向是 UIPopoverArrowDirectionDown
// - 在展现完成之前，此属性返回 UIPopoverArrowDirectionUnknown
@property (nonatomic, readonly) UIPopoverArrowDirection arrowDirection;

// By default, a popover disallows interaction with any view outside of the popover while the popover is presented.
// This property allows the specification of an array of UIView instances which the user is allowed to interact with
// while the popover is up.
// - 默认情况下，当 popover 的视图控制器展现时，不允许与 popover 之外的视图进行交互
// - 此属性允许指定一个 UIView 的数组，数组中包含的视图，在 popover 展现时，同样能够进行用户交互
@property (nullable, nonatomic, copy) NSArray<UIView *> *passthroughViews;

// Set popover background color. Set to nil to use default background color. Default is nil.
// - 设置 popover 的背景颜色，就是 popover 的`小箭头的颜色`
// - 设置为 nil 使用默认的背景颜色
// - 默认值是 nil
@property (nullable, nonatomic, copy) UIColor *backgroundColor;

// Clients may wish to change the available area for popover display. The default implementation of this method always
// returns insets which define 10 points from the edges of the display, and presentation of popovers always accounts
// for the status bar. The rectangle being inset is always expressed in terms of the current device orientation; (0, 0)
// is always in the upper-left of the device. This may require insets to change on device rotation.
// - 应用程序可能会希望修改 popover 显示的可用面积
// - 此方法默认返回的边距，是距离显示边缘有 10 个点的距离
// - popover 的展现不会遮挡状态栏
// - 边界的矩形计算是符合设备方向的，(0, 0) 始终是设备的左上角
// - 这意味着在不同设备方向，可以设置不同的边距
@property (nonatomic, readwrite) UIEdgeInsets popoverLayoutMargins;

// Clients may customize the popover background chrome by providing a class which subclasses `UIPopoverBackgroundView`
// and which implements the required instance and class methods on that class.
//
// 要自定义 popover 的背景，可以：
// - 提供一个 `UIPopoverBackgroundView` 的子类
// - 在子类中实现需要的实例和类方法
@property (nullable, nonatomic, readwrite, strong) Class <UIPopoverBackgroundViewMethods> popoverBackgroundViewClass;

@end

NS_ASSUME_NONNULL_END
