//
//  UISplitViewController.h
//  UIKit
//
//  Copyright (c) 2009-2013, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol UISplitViewControllerDelegate;

NS_CLASS_AVAILABLE_IOS(3_2) @interface UISplitViewController : UIViewController

@property (nonatomic, copy) NSArray *viewControllers;  
@property (nonatomic, assign) id <UISplitViewControllerDelegate> delegate;

// If 'YES', hidden view can be presented and dismissed via a swipe gesture. Defaults to 'YES'.
// Set prior to setting delegate. The swipe gesture is only possible if the delegate implements -splitViewController:willHideViewController:withBarButtonItem:forPopoverController:.
@property (nonatomic) BOOL presentsWithGesture NS_AVAILABLE_IOS(5_1);

@end

@protocol UISplitViewControllerDelegate

@optional

// Called when a button should be added to a toolbar for a hidden view controller.
// Implementing this method allows the hidden view controller to be presented via a swipe gesture if 'presentsWithGesture' is 'YES' (the default).
- (void)splitViewController:(UISplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController:(UIPopoverController *)pc;

// Called when the view is shown again in the split view, invalidating the button and popover controller.
- (void)splitViewController:(UISplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem;

// Called when the view controller is shown in a popover so the delegate can take action like hiding other popovers.
- (void)splitViewController:(UISplitViewController *)svc popoverController:(UIPopoverController *)pc willPresentViewController:(UIViewController *)aViewController;

// Returns YES if a view controller should be hidden by the split view controller in a given orientation.
// (This method is only called on the leftmost view controller and only discriminates portrait from landscape.)
- (BOOL)splitViewController:(UISplitViewController *)svc shouldHideViewController:(UIViewController *)vc inOrientation:(UIInterfaceOrientation)orientation NS_AVAILABLE_IOS(5_0);

- (NSUInteger)splitViewControllerSupportedInterfaceOrientations:(UISplitViewController *)splitViewController NS_AVAILABLE_IOS(7_0);
- (UIInterfaceOrientation)splitViewControllerPreferredInterfaceOrientationForPresentation:(UISplitViewController *)splitViewController NS_AVAILABLE_IOS(7_0);


@end

@interface UIViewController (UISplitViewController)

@property (nonatomic, readonly, retain) UISplitViewController *splitViewController; // If the view controller has a split view controller as its ancestor, return it. Returns nil otherwise.

@end
