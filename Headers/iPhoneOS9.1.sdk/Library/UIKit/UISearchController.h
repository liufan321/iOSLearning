//
//  UISearchController.h
//  UIKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIPresentationController.h>
#import <UIKit/UIViewControllerTransitioning.h>

NS_ASSUME_NONNULL_BEGIN

@class UISearchController;

@protocol UISearchControllerDelegate <NSObject>
@optional
// These methods are called when automatic presentation or dismissal occurs. They will not be called if you present or dismiss the search controller yourself.
- (void)willPresentSearchController:(UISearchController *)searchController;
- (void)didPresentSearchController:(UISearchController *)searchController;
- (void)willDismissSearchController:(UISearchController *)searchController;
- (void)didDismissSearchController:(UISearchController *)searchController;

// Called after the search controller's search bar has agreed to begin editing or when 'active' is set to YES. If you choose not to present the controller yourself or do not implement this method, a default presentation is performed on your behalf.
- (void)presentSearchController:(UISearchController *)searchController;
@end

@protocol UISearchResultsUpdating <NSObject>
@required
// Called when the search bar's text or scope has changed or when the search bar becomes first responder.
// 当 search bar 成为第一响应者，或者 search bar 的文本或范围发生变化时被调用
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController;
@end

NS_CLASS_AVAILABLE_IOS(8_0) @interface UISearchController : UIViewController <UIViewControllerTransitioningDelegate, UIViewControllerAnimatedTransitioning>

#ifndef SDK_HIDE_TIDE
// Pass nil if you wish to display search results in the same view that you are searching. This is not supported on tvOS; please provide a results controller on tvOS.
#else
// Pass nil if you wish to display search results in the same view that you are searching.
#endif //SDK_HIDE_TIDE
- (instancetype)initWithSearchResultsController:(nullable UIViewController *)searchResultsController;

// The object responsible for updating the content of the searchResultsController.
// 负责更新 searchResultsController 内容的对象
@property (nullable, nonatomic, weak) id <UISearchResultsUpdating> searchResultsUpdater;

// Setting this property to YES is a convenience method that performs a default presentation of the search controller appropriate for how the controller is configured. Implement -presentSearchController: if the default presentation is not adequate.
@property (nonatomic, assign, getter = isActive) BOOL active;

@property (nullable, nonatomic, weak) id <UISearchControllerDelegate> delegate;
// 默认是 YES，标示在搜索过程中是否将底层内容变暗，与 obscuresBackgroundDuringPresentation 的行为相同
@property (nonatomic, assign) BOOL dimsBackgroundDuringPresentation __TVOS_PROHIBITED; // default is YES, and has the same behavior as obscuresBackgroundDuringPresentation.
@property (nonatomic, assign) BOOL obscuresBackgroundDuringPresentation NS_AVAILABLE_IOS(9_1); // default is YES
// 默认是 YES，标示在搜索过程中是否隐藏导航栏
@property (nonatomic, assign) BOOL hidesNavigationBarDuringPresentation;     // default is YES

/**
 显示搜索结果的控制器(只读)
 
 * 当用户在搜索栏中输入文本时，搜索控制器会立即显示此控制器（无动画）
 * 开发人员需要负责将搜索结果传递给此控制器，以显示搜索结果的内容，可以通过 searchResultsUpdater 属性实现此目的
 
 * 如果此属性为 nil，搜索控制器不会在单独展现一个控制器显示来搜索结果
 * 取而代之的是，应该在原控制器（包含搜索栏和可搜索内容）中显示搜索结果
 */
@property (nullable, nonatomic, strong, readonly) UIViewController *searchResultsController;

// You are free to become the search bar's delegate to monitor for text changes and button presses.
// 如果需要，可以设置成 search bar 的代理，监听文本变化和按钮点击事件
@property (nonatomic, strong, readonly) UISearchBar *searchBar;
@end

NS_ASSUME_NONNULL_END
