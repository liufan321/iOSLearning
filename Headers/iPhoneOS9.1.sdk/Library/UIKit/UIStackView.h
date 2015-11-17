//
//  UIStackView.h
//  UIKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

/// StackView - 堆视图，以堆叠的方式，从左至右横向排列子视图，或者从上至下纵向排列子视图
/* Distribution—the layout along the stacking axis.
 分布 - 设置沿堆叠方向子视图的布局方式
 
 All UIStackViewDistribution enum values fit first and last arranged subviews tightly to the container,
 and except for UIStackViewDistributionFillEqually, fit all items to intrinsicContentSize when possible.
 */
typedef NS_ENUM(NSInteger, UIStackViewDistribution) {
    
    /* When items do not fit (overflow) or fill (underflow) the space available
     adjustments occur according to compressionResistance or hugging
     priorities of items, or when that is ambiguous, according to arrangement
     order.
     */
    UIStackViewDistributionFill = 0,
    
    /* Items are all the same size.
     When space allows, this will be the size of the item with the largest
     intrinsicContentSize (along the axis of the stack).
     Overflow or underflow adjustments are distributed equally among the items.
     */
    UIStackViewDistributionFillEqually,
    
    /* Overflow or underflow adjustments are distributed among the items proportional
     to their intrinsicContentSizes.
     */
    UIStackViewDistributionFillProportionally,
    
    /* Additional underflow spacing is divided equally in the spaces between the items.
     Overflow squeezing is controlled by compressionResistance priorities followed by
     arrangement order.
     */
    UIStackViewDistributionEqualSpacing,
    
    /* Equal center-to-center spacing of the items is maintained as much
     as possible while still maintaining a minimum edge-to-edge spacing within the
     allowed area.
        Additional underflow spacing is divided equally in the spacing. Overflow 
     squeezing is distributed first according to compressionResistance priorities 
     of items, then according to subview order while maintaining the configured 
     (edge-to-edge) spacing as a minimum.
     */
    UIStackViewDistributionEqualCentering,
} NS_ENUM_AVAILABLE_IOS(9_0);

/* Alignment—the layout transverse to the stacking axis.
 对齐 - 设置和堆叠方向垂直的子视图的布局方式
 */
typedef NS_ENUM(NSInteger, UIStackViewAlignment) {
    /* Align the leading and trailing edges of vertically stacked items
     or the top and bottom edges of horizontally stacked items tightly to the container.
     */
    UIStackViewAlignmentFill,
    
    /* Align the leading edges of vertically stacked items
     or the top edges of horizontally stacked items tightly to the relevant edge
     of the container
     */
    UIStackViewAlignmentLeading,
    UIStackViewAlignmentTop = UIStackViewAlignmentLeading,
    UIStackViewAlignmentFirstBaseline, // Valid for horizontal axis only
    
    /* Center the items in a vertical stack horizontally
     or the items in a horizontal stack vertically
     */
    UIStackViewAlignmentCenter,
    
    /* Align the trailing edges of vertically stacked items
     or the bottom edges of horizontally stacked items tightly to the relevant
     edge of the container
     */
    UIStackViewAlignmentTrailing,
    UIStackViewAlignmentBottom = UIStackViewAlignmentTrailing,
    UIStackViewAlignmentLastBaseline, // Valid for horizontal axis only
} NS_ENUM_AVAILABLE_IOS(9_0);

/* UIStackView is a non-rendering subclass of UIView, intended for managing layout of its subviews.
 You may not override +[UIStackView layerClass], and -drawLayer:inContext: will not be sent to
 UIStackView.
 
 UIStackView 是一个不会被渲染的 UIView 的子类，用于管理其子视图的布局
 如果重写 +[UIStackView layerClass] 或者 -drawLayer:inContext: 方法，不会被发送给 UIStackView

 UIStackView arranges its subviews in its arrangedSubviews list in the order of 
 that list along a vertical or horizontal axis, with exact arrangement determined
 by the distribution, alignment, and spacing properties.
 
 UIStackView 沿横向或纵向，顺序布局 `arrangedSubviews` 列表中的子视图
 布局效果取决于 `distribution(分布)`，`alignment(对齐)` 和 `spacing(间距)` 属性
 
 The layout will update automatically when arrangedSubviews list changes
 due to adding, removing, or inserting arrangedSubviews, and also when
 views in the arrangedSubviews list change their hidden property.
 
 当 `arrangedSubviews` 列表因为`追加`，`删除`或`插入`发生变化后，会自动更新布局
 当 `arrangedSubviews` 中子视图的 `hidden` 属性发生变化后，同样会自动更新布局
 
 A horizontal UIStackView will return its tallest view for -viewForFirst/LastBaselineLayout,
 or if that is another stack view, then the relevant viewForFirst/LastBaselineLayout from that
 stack view.
 
 A vertical UIStackView will return its first view for -viewForFirstBaselineLayout and its
 last view for -viewForLastBaselineLayout, or if that is another stack view, then the relevant  
 viewForFirst/LastBaselineLayout from that stack view.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_IOS(9_0)
@interface UIStackView : UIView

/* UIStackView enforces that all views in the arrangedSubviews list
 must be subviews of the UIStackView.
 
 UIStackView 要求所有 `arrangedSubviews` 列表中的视图必须是 UIStackView 的子视图
 
    Thus, when a view is added to the arrangedSubviews, UIStackView
 adds it as a subview if it isn't already. And when a view in a
 UIStackView's arrangedSubviews list receives -removeFromSuperview
 it is also removed from the arrangedSubviews.
 
 因此：
 - 当一个视图被添加至 `arrangedSubviews` 时，如果该视图还不是 UIStackView 的子视图，UIStackView 会将其添加为子视图
 - 当 UIStackView `arrangedSubviews` 中的一个视图收到 -removeFromSuperview 消息时，该视图会被同时从 `arrangedSubviews` 中移除
 */
- (instancetype)initWithArrangedSubviews:(NSArray<__kindof UIView *> *)views; // Adds views as subviews of the receiver.
                                                                              // 所有视图会被当作子视图添加
@property(nonatomic,readonly,copy) NSArray<__kindof UIView *> *arrangedSubviews;

/* Add a view to the end of the arrangedSubviews list.
 向 `arrangedSubviews` 列表的末尾添加一个视图
 
 Maintains the rule that the arrangedSubviews list is a subset of the
 subviews list by adding the view as a subview of the receiver if
 necessary.
 
 规则：`arrangedSubviews` 是 `subviews` 的子集，如果需要，视图会被添加为子视图
 
    Does not affect the subview ordering if view is already a subview 
 of the receiver.
 
 如果已经是子视图，不要改变子视图的顺序
 */
- (void)addArrangedSubview:(UIView *)view;

/* Removes a subview from the list of arranged subviews without removing it as
 a subview of the receiver.
 
 从 `arrangedSubviews` 中删除一个子视图，但是不会将其从 `subviews` 中删除
 
    To remove the view as a subview, send it -removeFromSuperview as usual;
 the relevant UIStackView will remove it from its arrangedSubviews list
 automatically.
 
 要删除子视图，通常发送 `-removeFromSuperview` 消息，对应的 UIStackView 会自动将其从
 `arrangedSubviews` 列表中删除
 */
- (void)removeArrangedSubview:(UIView *)view;
/*
 Adds the view as a subview of the container if it isn't already.

 如果还不是子视图，会将视图添加为子视图
 
    Updates the stack index (but not the subview index) of the
 arranged subview if it's already in the arrangedSubviews list.

 更新堆叠索引(但是不会更新 `子视图` 索引）
 */
- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)stackIndex;

/* A stack with a horizontal axis is a row of arrangedSubviews,
and a stack with a vertical axis is a column of arrangedSubviews.
 
 - `horizontal` 按照横向排列 `arrangedSubviews`
 - `vertical` 按照纵向排列 `arrangedSubviews`
 */
@property(nonatomic) UILayoutConstraintAxis axis;

/* The layout of the arrangedSubviews along the axis
 
 arrangedSubviews 沿堆叠方向(axis) 的布局方式
 */
@property(nonatomic) UIStackViewDistribution distribution;

/* The layout of the arrangedSubviews transverse to the axis;
 e.g., leading/trailing edges in a vertical stack
 
 arrangedSubviews 垂直与堆叠方向(axis) 的布局方式
 例如：纵向排列时，子视图 左/右对齐
 */
@property(nonatomic) UIStackViewAlignment alignment;

/* Spacing between adjacent edges of arrangedSubviews.
 Used as a strict spacing for the Fill distributions, and
 as a minimum spacing for the EqualCentering and EqualSpacing
 distributions. Use negative values to allow overlap.
 
 arrangedSubviews 中相邻子视图之间的间距
 
 - `Fill` 分布时，是准确的间距
 - `EqualCentering` 和 `EqualSpacing` 分布时，是最小间距
 - 使用负值，允许视图重叠
 */
@property(nonatomic) CGFloat spacing;

/* Baseline-to-baseline spacing in vertical stacks.
 - 纵向排列时 Baseline-to-baseline 排列，适用于基于文本的视图
 
    The baselineRelativeArrangement property supports specifications of vertical 
 space from the last baseline of one text-based view to the first baseline of a
 text-based view below, or from the  top (or bottom) of a container to the first
 (or last) baseline of a contained text-based view.
    This property is ignored in horizontal stacks. Use the alignment property
 to specify baseline alignment in horizontal stacks.
    Defaults to NO.
 
 - 横向排列时，忽略此属性
 - 可以使用 `alignment` 属性置顶横向排列的 baseline 对齐方式
 - 默认值是 NO
 */
@property(nonatomic,getter=isBaselineRelativeArrangement) BOOL baselineRelativeArrangement;

/* Uses margin layout attributes for edge constraints where applicable.
    Defaults to NO.
 
 - 如果可用，对 edge 约束使用 margin 布局属性
 - 默认值是 NO
 */
@property(nonatomic,getter=isLayoutMarginsRelativeArrangement) BOOL layoutMarginsRelativeArrangement;    
@end
NS_ASSUME_NONNULL_END
