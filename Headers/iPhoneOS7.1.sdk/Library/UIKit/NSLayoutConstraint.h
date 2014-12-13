//
//  NSLayoutConstraint.h
//  UIKit
//	
//  Copyright (c) 2009-2013, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <UIKit/UIGeometry.h>

@class NSArray, NSDictionary;


typedef NS_ENUM(NSInteger, NSLayoutRelation) {
    NSLayoutRelationLessThanOrEqual = -1,
    NSLayoutRelationEqual = 0,
    NSLayoutRelationGreaterThanOrEqual = 1,
};

typedef NS_ENUM(NSInteger, NSLayoutAttribute) {
    NSLayoutAttributeLeft = 1,
    NSLayoutAttributeRight,
    NSLayoutAttributeTop,
    NSLayoutAttributeBottom,
    NSLayoutAttributeLeading,
    NSLayoutAttributeTrailing,
    NSLayoutAttributeWidth,
    NSLayoutAttributeHeight,
    NSLayoutAttributeCenterX,
    NSLayoutAttributeCenterY,
    NSLayoutAttributeBaseline,
    
    NSLayoutAttributeNotAnAttribute = 0
};

typedef NS_OPTIONS(NSUInteger, NSLayoutFormatOptions) {
    NSLayoutFormatAlignAllLeft = (1 << NSLayoutAttributeLeft),
    NSLayoutFormatAlignAllRight = (1 << NSLayoutAttributeRight),
    NSLayoutFormatAlignAllTop = (1 << NSLayoutAttributeTop),
    NSLayoutFormatAlignAllBottom = (1 << NSLayoutAttributeBottom),
    NSLayoutFormatAlignAllLeading = (1 << NSLayoutAttributeLeading),
    NSLayoutFormatAlignAllTrailing = (1 << NSLayoutAttributeTrailing),
    NSLayoutFormatAlignAllCenterX = (1 << NSLayoutAttributeCenterX),
    NSLayoutFormatAlignAllCenterY = (1 << NSLayoutAttributeCenterY),
    NSLayoutFormatAlignAllBaseline = (1 << NSLayoutAttributeBaseline),
    
    NSLayoutFormatAlignmentMask = 0xFFFF,
    
    /* choose only one of these three
     */
    NSLayoutFormatDirectionLeadingToTrailing = 0 << 16, // default
    NSLayoutFormatDirectionLeftToRight = 1 << 16,
    NSLayoutFormatDirectionRightToLeft = 2 << 16,  
    
    NSLayoutFormatDirectionMask = 0x3 << 16,  
};

enum {
    UILayoutPriorityRequired = 1000, // a required constraint.  Do not exceed this.
    UILayoutPriorityDefaultHigh = 750, // this is the priority level with which a button resists compressing its content.
    UILayoutPriorityDefaultLow = 250, // this is the priority level at which a button hugs its contents horizontally.  
    UILayoutPriorityFittingSizeLevel = 50, // When you send -[UIView systemLayoutSizeFittingSize:], the size fitting most closely to the target size (the argument) is computed.  UILayoutPriorityFittingSizeLevel is the priority level with which the view wants to conform to the target size in that computation.  It's quite low.  It is generally not appropriate to make a constraint at exactly this priority.  You want to be higher or lower.
};
typedef float UILayoutPriority;

NS_CLASS_AVAILABLE_IOS(6_0)
@interface NSLayoutConstraint : NSObject
{
    @private
    id _container;
    id _firstItem;
    id _secondItem;
    CGFloat _constant;
    CGFloat _loweredConstant;
    id _markerAndPositiveExtraVar;
    id _negativeExtraVar;
    float _coefficient;
    UILayoutPriority _priority;
    uint64_t _layoutConstraintFlags;
    id _flange;
}

/* Create an array of constraints using an ASCII art-like visual format string.
 */
+ (NSArray *)constraintsWithVisualFormat:(NSString *)format options:(NSLayoutFormatOptions)opts metrics:(NSDictionary *)metrics views:(NSDictionary *)views;

/* This macro is a helper for making view dictionaries for +constraintsWithVisualFormat:options:metrics:views:.  
 NSDictionaryOfVariableBindings(v1, v2, v3) is equivalent to [NSDictionary dictionaryWithObjectsAndKeys:v1, @"v1", v2, @"v2", v3, @"v3", nil];
 */
#define NSDictionaryOfVariableBindings(...) _NSDictionaryOfVariableBindings(@"" # __VA_ARGS__, __VA_ARGS__, nil)
UIKIT_EXTERN NSDictionary *_NSDictionaryOfVariableBindings(NSString *commaSeparatedKeysString, id firstValue, ...) NS_AVAILABLE_IOS(6_0); // not for direct use


/* Create constraints explicitly.  Constraints are of the form "view1.attr1 = view2.attr2 * multiplier + constant" 
 If your equation does not have a second view and attribute, use nil and NSLayoutAttributeNotAnAttribute.
 */
+(id)constraintWithItem:(id)view1 attribute:(NSLayoutAttribute)attr1 relatedBy:(NSLayoutRelation)relation toItem:(id)view2 attribute:(NSLayoutAttribute)attr2 multiplier:(CGFloat)multiplier constant:(CGFloat)c;

/* If a constraint's priority level is less than UILayoutPriorityRequired, then it is optional.  Higher priority constraints are met before lower priority constraints.
 Constraint satisfaction is not all or nothing.  If a constraint 'a == b' is optional, that means we will attempt to minimize 'abs(a-b)'.
 This property may only be modified as part of initial set up.  An exception will be thrown if it is set after a constraint has been added to a view.
 */
@property UILayoutPriority priority;

/* When a view is archived, it archives some but not all constraints in its -constraints array.  The value of shouldBeArchived informs UIView if a particular constraint should be archived by UIView.
 If a constraint is created at runtime in response to the state of the object, it isn't appropriate to archive the constraint - rather you archive the state that gives rise to the constraint.  Since the majority of constraints that should be archived are created in Interface Builder (which is smart enough to set this prop to YES), the default value for this property is NO.
 */
@property BOOL shouldBeArchived;

/* accessors
 firstItem.firstAttribute {==,<=,>=} secondItem.secondAttribute * multiplier + constant
 */
@property (readonly, assign) id firstItem;
@property (readonly) NSLayoutAttribute firstAttribute;
@property (readonly) NSLayoutRelation relation;
@property (readonly, assign) id secondItem;
@property (readonly) NSLayoutAttribute secondAttribute;
@property (readonly) CGFloat multiplier;

/* Unlike the other properties, the constant may be modified after constraint creation.  Setting the constant on an existing constraint performs much better than removing the constraint and adding a new one that's just like the old but for having a new constant.
 */
@property CGFloat constant;

@end

/*
 UILayoutSupport protocol is implemented by layout guide objects
 returned by UIViewController properties topLayoutGuide and bottomLayoutGuide.
 These guide objects may be used as layout items in the NSLayoutConstraint
 factory methods.
 */
@protocol UILayoutSupport <NSObject>
@property(nonatomic,readonly) CGFloat length;  // As a courtesy when not using auto layout, this value is safe to refer to in -viewDidLayoutSubviews, or in -layoutSubviews after calling super
@end

