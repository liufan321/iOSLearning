//
//  UITraitCollection.h
//  UIKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UITouch.h>

/*! A trait collection encapsulates the system traits of an interface's environment. */
/*
 Trait(特征) 集合封装了界面环境的系统特征
 */
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) @interface UITraitCollection : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (BOOL)containsTraitsInCollection:(nullable UITraitCollection *)trait;

/*! Returns a trait collection by merging the traits in `traitCollections`. The last trait along any given
 axis (e.g. interface usage) will supercede any others. */
+ (UITraitCollection *)traitCollectionWithTraitsFromCollections:(NSArray<UITraitCollection *> *)traitCollections;


+ (UITraitCollection *)traitCollectionWithUserInterfaceIdiom:(UIUserInterfaceIdiom)idiom;
/// 设备类型枚举，枚举类型在 UIDevice.h 中定义
@property (nonatomic, readonly) UIUserInterfaceIdiom userInterfaceIdiom; // unspecified: UIUserInterfaceIdiomUnspecified

+ (UITraitCollection *)traitCollectionWithDisplayScale:(CGFloat)scale;
/// 屏幕分辨率 1.0 / 2.0 / 3.0，未指定是 0.0
@property (nonatomic, readonly) CGFloat displayScale; // unspecified: 0.0

+ (UITraitCollection *)traitCollectionWithHorizontalSizeClass:(UIUserInterfaceSizeClass)horizontalSizeClass;
/// 水平方向的 SizeClass
@property (nonatomic, readonly) UIUserInterfaceSizeClass horizontalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithVerticalSizeClass:(UIUserInterfaceSizeClass)verticalSizeClass;
/// 垂直方向的 SizeClass
@property (nonatomic, readonly) UIUserInterfaceSizeClass verticalSizeClass; // unspecified: UIUserInterfaceSizeClassUnspecified

+ (UITraitCollection *)traitCollectionWithForceTouchCapability:(UIForceTouchCapability)capability NS_AVAILABLE_IOS(9_0);
/// 是否支持压感(Force Touch)
@property (nonatomic, readonly) UIForceTouchCapability forceTouchCapability NS_AVAILABLE_IOS(9_0); // unspecified: UIForceTouchCapabilityUnknown

@end

/*! Trait environments expose a trait collection that describes their environment. */
/*! 
 `特征环境`协议暴露了一个`特征集合`用于描述环境
 
 UIViewController 和 UIView 都遵守了 UITraitEnvironment 协议
 
 注意：
 - 应该直接使用 traitCollection 属性
 - 不要重写此属性
 - 不要提供自定义实现
 */
@protocol UITraitEnvironment <NSObject>
@property (nonatomic, readonly) UITraitCollection *traitCollection NS_AVAILABLE_IOS(8_0);

/*! To be overridden as needed to provide custom behavior when the environment's traits change. */
/*! 重写此方法，可以在环境特征发生改变时，提供自定义行为 */
- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection NS_AVAILABLE_IOS(8_0);
@end

NS_ASSUME_NONNULL_END
