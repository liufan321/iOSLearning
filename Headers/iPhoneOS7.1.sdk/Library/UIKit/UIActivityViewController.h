//
//  UIActivityViewController.h
//  UIKit
//
//  Copyright 2012-2013, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>

typedef void (^UIActivityViewControllerCompletionHandler)(NSString *activityType, BOOL completed);

NS_CLASS_AVAILABLE_IOS(6_0) @interface UIActivityViewController : UIViewController

- (id)initWithActivityItems:(NSArray *)activityItems applicationActivities:(NSArray *)applicationActivities;

@property(nonatomic,copy) UIActivityViewControllerCompletionHandler completionHandler;  // set to nil after call
@property(nonatomic,copy) NSArray *excludedActivityTypes; // default is nil. activity types listed will not be displayed

@end
