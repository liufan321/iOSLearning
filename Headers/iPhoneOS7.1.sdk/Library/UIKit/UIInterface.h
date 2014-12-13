//
//  UIInterface.h
//  UIKit
//
//  Copyright (c) 2005-2013, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIFont.h>

// for UINavigationBar and UIToolBar

typedef NS_ENUM(NSInteger, UIBarStyle) {
    UIBarStyleDefault          = 0,
    UIBarStyleBlack            = 1,
    
    UIBarStyleBlackOpaque      = 1, // Deprecated. Use UIBarStyleBlack
    UIBarStyleBlackTranslucent = 2, // Deprecated. Use UIBarStyleBlack and set the translucent property to YES
};

// System colors

@interface UIColor (UIColorSystemColors)
+ (UIColor *)lightTextColor;                // for a dark background
+ (UIColor *)darkTextColor;                 // for a light background

// Group style table view backgrounds can no longer be represented by a simple color.
// If you want to have a background in your own view that looks like the table view background,
// then you should create an empty table view and place it behind your content.
+ (UIColor *)groupTableViewBackgroundColor; // This method will be deprecated during the 6.0 seed program

+ (UIColor *)viewFlipsideBackgroundColor NS_DEPRECATED_IOS(2_0, 7_0);
+ (UIColor *)scrollViewTexturedBackgroundColor NS_DEPRECATED_IOS(3_2, 7_0);
+ (UIColor *)underPageBackgroundColor NS_DEPRECATED_IOS(5_0, 7_0);
@end

// System fonts

@interface UIFont (UIFontSystemFonts)
+ (CGFloat)labelFontSize;
+ (CGFloat)buttonFontSize;
+ (CGFloat)smallSystemFontSize;
+ (CGFloat)systemFontSize;
@end
