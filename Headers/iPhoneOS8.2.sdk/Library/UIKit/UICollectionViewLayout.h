//
//  UICollectionViewLayout.h
//  UIKit
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/CATransform3D.h>
#import <UIKit/UIDynamicBehavior.h>

// The UICollectionViewLayout class is provided as an abstract class for subclassing to define custom collection layouts.
// Defining a custom layout is an advanced operation intended for applications with complex needs.
/**
 UICollectionViewLayout 类提供了一个抽象类，以便于自定义 collection 布局的子类
 自定义布局是一个高级操作，旨在设计复杂交互需求的应用程序
 */

typedef NS_ENUM(NSUInteger, UICollectionElementCategory) {
    UICollectionElementCategoryCell,                    // Cell
    UICollectionElementCategorySupplementaryView,       // 追加视图(类似于Header或者Footer)
    UICollectionElementCategoryDecorationView           // 装饰视图(可以用作背景视图)
};

@class UICollectionViewLayoutAttributes;
@class UICollectionView;
@class UINib;

/**
 *  UICollectionViewLayoutAttributes 对象管理 Collection View 中指定 Cell 的布局相关属性
 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayoutAttributes : NSObject <NSCopying, UIDynamicItem>

/**
 *  边框
 */
@property (nonatomic) CGRect frame;
/**
 *  中心点
 */
@property (nonatomic) CGPoint center;
/**
 *  尺寸
 */
@property (nonatomic) CGSize size;
/**
 *  3D转换矩阵
 */
@property (nonatomic) CATransform3D transform3D;
/**
 *  边界
 */
@property (nonatomic) CGRect bounds NS_AVAILABLE_IOS(7_0);
/**
 *  仿射矩阵
 */
@property (nonatomic) CGAffineTransform transform NS_AVAILABLE_IOS(7_0);
/**
 *  透明度
 */
@property (nonatomic) CGFloat alpha;
/**
 *  纵向层次
 */
@property (nonatomic) NSInteger zIndex; // default is 0
/**
 *  隐藏
 *
 *  出于优化目的，UICollectionView 不会为 hidden 属性是 YES 的 item 创建视图
 */
@property (nonatomic, getter=isHidden) BOOL hidden; // As an optimization, UICollectionView might not create a view for items whose hidden attribute is YES
/**
 *  索引
 */
@property (nonatomic, retain) NSIndexPath *indexPath;

/**
 *  元素分类(Cell / SupplementaryView / DecorationView)
 */
@property (nonatomic, readonly) UICollectionElementCategory representedElementCategory;
/**
 *  representedElementCategory 等于 UICollectionElementCategoryCell 时 返回 nil
 */
@property (nonatomic, readonly) NSString *representedElementKind; // nil when representedElementCategory is UICollectionElementCategoryCell

+ (instancetype)layoutAttributesForCellWithIndexPath:(NSIndexPath *)indexPath;
+ (instancetype)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind withIndexPath:(NSIndexPath *)indexPath;
+ (instancetype)layoutAttributesForDecorationViewOfKind:(NSString *)decorationViewKind withIndexPath:(NSIndexPath*)indexPath;

@end

typedef NS_ENUM(NSInteger, UICollectionUpdateAction) {
    UICollectionUpdateActionInsert,
    UICollectionUpdateActionDelete,
    UICollectionUpdateActionReload,
    UICollectionUpdateActionMove,
    UICollectionUpdateActionNone
};

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewUpdateItem : NSObject

@property (nonatomic, readonly) NSIndexPath *indexPathBeforeUpdate; // nil for UICollectionUpdateActionInsert
@property (nonatomic, readonly) NSIndexPath *indexPathAfterUpdate; // nil for UICollectionUpdateActionDelete
@property (nonatomic, readonly) UICollectionUpdateAction updateAction;

@end

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewLayoutInvalidationContext : NSObject

@property (nonatomic, readonly) BOOL invalidateEverything; // set to YES when invalidation occurs because the collection view is sent -reloadData
@property (nonatomic, readonly) BOOL invalidateDataSourceCounts; // if YES, the layout should requery section and item counts from the collection view - set to YES when the collection view is sent -reloadData and when items are inserted or deleted

- (void)invalidateItemsAtIndexPaths:(NSArray *)indexPaths NS_AVAILABLE_IOS(8_0);
- (void)invalidateSupplementaryElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray *)indexPaths NS_AVAILABLE_IOS(8_0);
- (void)invalidateDecorationElementsOfKind:(NSString *)elementKind atIndexPaths:(NSArray *)indexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly) NSArray *invalidatedItemIndexPaths NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly) NSDictionary *invalidatedSupplementaryIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths
@property (nonatomic, readonly) NSDictionary *invalidatedDecorationIndexPaths NS_AVAILABLE_IOS(8_0); // keys are element kind strings - values are NSArrays of NSIndexPaths

@property (nonatomic) CGPoint contentOffsetAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the collection view's current contentOffset - default is CGPointZero
@property (nonatomic) CGSize contentSizeAdjustment NS_AVAILABLE_IOS(8_0); // delta to be applied to the current content size - default is CGSizeZero

@end

/**
 UICollectionViewLayout 一次刷新循环中方法的调用顺序
 
 1. prepareLayout
    - 在自定义子类中，必须 super 父类的实现
    - 在自定义子类中，可以在此方法中设置一些布局相关的初始参数
 2. collectionViewContentSize
    - 确定 collectionView 的 contentSize
    - layoutAttributesForElementsInRect 方法调用结束后会自动调用此方法，确认 contentSize 是否发生变化
 3. layoutAttributesForElementsInRect
    - 返回指定 rect 范围内所有 cell 的布局属性数组
    - 滚动过程中，会调用此方法，计算出现在屏幕中的 cell 的布局属性
    - 如果滚动距离远，之前计算的布局数组不够，会多次调用此方法
 4. targetContentOffsetForProposedContentOffset
    - 滚动 collectionView 手指离开屏幕时调用此方法，返回停止滚动后的偏移位置
    - 如果滚动距离短，不会调用 layoutAttributesForElementsInRect 方法
    - 如果滚动距离长，之前 layoutAttributesForElementsInRect 计算的 cell 布局属性不够，
      会再次调用 layoutAttributesForElementsInRect 方法，计算将要显示 cell 的 布局属性
    - 如果滚动距离很长，会多次调用 layoutAttributesForElementsInRect 方法
    - 如果在滚动过程中，只要 contentOffset 发生变化，就重新计算 cell 的布局属性，可以重写 
      shouldInvalidateLayoutForBoundsChange 方法，并且返回 YES
 
 如果需要更新 layout，可以给 layout 发送 -invalidateLayout 消息，这样，在下一次 collectionView 的刷新循环中，
 会从 prepareLayout 开始，顺序调用 -collectionViewContentSize 和 -layoutAttributesForElementsInRect 等方法生成更新后的布局
 */
NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewLayout : NSObject <NSCoding>

// Methods in this class are meant to be overridden and will be called by its collection view to gather layout information.
// To get the truth on the current state of the collection view, call methods on UICollectionView rather than these.

@property (nonatomic, readonly) UICollectionView *collectionView;

// Call -invalidateLayout to indicate that the collection view needs to requery the layout information.
// Subclasses must always call super if they override.
/**
 *  调用  -invalidateLayout 方法表示 collection view 需要重新查询布局信息
 *  如果重写此方法，子类必须 super 父类的实现
 *
 *  备注：此方法和 UIView 的 setNeedsLayout 方法十分类似
 */
- (void)invalidateLayout;
- (void)invalidateLayoutWithContext:(UICollectionViewLayoutInvalidationContext *)context NS_AVAILABLE_IOS(7_0);

- (void)registerClass:(Class)viewClass forDecorationViewOfKind:(NSString *)elementKind;
- (void)registerNib:(UINib *)nib forDecorationViewOfKind:(NSString *)elementKind;

@end

@interface UICollectionViewLayout (UISubclassingHooks)

+ (Class)layoutAttributesClass; // override this method to provide a custom class to be used when instantiating instances of UICollectionViewLayoutAttributes
+ (Class)invalidationContextClass NS_AVAILABLE_IOS(7_0); // override this method to provide a custom class to be used for invalidation contexts

// The collection view calls -prepareLayout once at its first layout as the first message to the layout instance.
// The collection view calls -prepareLayout again after layout is invalidated and before requerying the layout information.
// Subclasses should always call super if they override.
- (void)prepareLayout;

// UICollectionView calls these four methods to determine the layout information.
// Implement -layoutAttributesForElementsInRect: to return layout attributes for for supplementary or decoration views, or to perform layout in an as-needed-on-screen fashion.
// Additionally, all layout subclasses should implement -layoutAttributesForItemAtIndexPath: to return layout attributes instances on demand for specific index paths.
// If the layout supports any supplementary or decoration view types, it should also implement the respective atIndexPath: methods for those types.
/**
 UICollectionView 调用以下四个方法决定布局信息
 
 1. 实现 -layoutAttributesForElementsInRect: 返回追加(supplementary)或装饰(decoration)视图的布局属性，或者按照屏幕显示需要的方式进行布局
 2. 所有布局子类应该实现 -layoutAttributesForItemAtIndexPath: 返回指定 indexPath 对应的布局属性实例
 3. 如果布局支持追加(supplementary)或者装饰(decoration)视图类型，还应该分别实现对应类型的 atIndexPath: 方法
 */
/**
 *  返回指定 rect 范围内所有 cell 的布局属性数组
 */
- (NSArray *)layoutAttributesForElementsInRect:(CGRect)rect; // return an array layout attributes instances for all the views in the given rect
- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
- (UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryViewOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;
- (UICollectionViewLayoutAttributes *)layoutAttributesForDecorationViewOfKind:(NSString*)elementKind atIndexPath:(NSIndexPath *)indexPath;

/**
 *  当边界发生改变时，是否应该刷新布局
 *  默认返回 NO，如果返回YES，则在边界变化（滚到到其他位置）时，重新计算需要的布局信息
 */
- (BOOL)shouldInvalidateLayoutForBoundsChange:(CGRect)newBounds; // return YES to cause the collection view to requery the layout for geometry information
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForBoundsChange:(CGRect)newBounds NS_AVAILABLE_IOS(7_0);

- (BOOL)shouldInvalidateLayoutForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);
- (UICollectionViewLayoutInvalidationContext *)invalidationContextForPreferredLayoutAttributes:(UICollectionViewLayoutAttributes *)preferredAttributes withOriginalAttributes:(UICollectionViewLayoutAttributes *)originalAttributes NS_AVAILABLE_IOS(8_0);

/**
 *  返回停止滚动后的偏移位置
 */
- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset withScrollingVelocity:(CGPoint)velocity; // return a point at which to rest after scrolling - for layouts that want snap-to-point scrolling behavior
/**
 *  返回过渡或更新布局之后的偏移位置
 */
- (CGPoint)targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(7_0); // a layout can return the content offset to be applied during transition or update animations

/**
 *  collectionView 的 contentSize
 *
 *  自定义子类必须实现此方法，返回 collectionView 内容的宽和高
 *  注意，返回的宽高不是当前可见范围的宽高，而是所有内容的宽和高
 *  collectionView 使用此信息配置其 contentSize 以便滚动
 *
 *  备注：经过测试，如果不实现此方法，系统会根据数据源方法自动计算 contentSize，而且每次滚动之前都会调用此方法
 */
- (CGSize)collectionViewContentSize; // Subclasses must override this method and use it to return the width and height of the collection view’s content. These values represent the width and height of all the content, not just the content that is currently visible. The collection view uses this information to configure its own content size to facilitate scrolling.

@end

@interface UICollectionViewLayout (UIUpdateSupportHooks)

// This method is called when there is an update with deletes/inserts to the collection view.
// It will be called prior to calling the initial/final layout attribute methods below to give the layout an opportunity to do batch computations for the insertion and deletion layout attributes.
// The updateItems parameter is an array of UICollectionViewUpdateItem instances for each element that is moving to a new index path.
- (void)prepareForCollectionViewUpdates:(NSArray *)updateItems;
- (void)finalizeCollectionViewUpdates; // called inside an animation block after the update

- (void)prepareForAnimatedBoundsChange:(CGRect)oldBounds; // UICollectionView calls this when its bounds have changed inside an animation block before displaying cells in its new bounds
- (void)finalizeAnimatedBoundsChange; // also called inside the animation block

// UICollectionView calls this when prior the layout transition animation on the incoming and outgoing layout
- (void)prepareForTransitionToLayout:(UICollectionViewLayout *)newLayout NS_AVAILABLE_IOS(7_0);
- (void)prepareForTransitionFromLayout:(UICollectionViewLayout *)oldLayout NS_AVAILABLE_IOS(7_0);
- (void)finalizeLayoutTransition NS_AVAILABLE_IOS(7_0);  // called inside an animation block after the transition


// This set of methods is called when the collection view undergoes an animated transition such as a batch update block or an animated bounds change.
// For each element on screen before the invalidation, finalLayoutAttributesForDisappearingXXX will be called and an animation setup from what is on screen to those final attributes.
// For each element on screen after the invalidation, initialLayoutAttributesForAppearingXXX will be called an an animation setup from those initial attributes to what ends up on screen.
- (UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;
- (UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingItemAtIndexPath:(NSIndexPath *)itemIndexPath;
- (UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;
- (UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingSupplementaryElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)elementIndexPath;
- (UICollectionViewLayoutAttributes *)initialLayoutAttributesForAppearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;
- (UICollectionViewLayoutAttributes *)finalLayoutAttributesForDisappearingDecorationElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)decorationIndexPath;

// These methods are called by collection view during an update block.
// Return an array of index paths to indicate views that the layout is deleting or inserting in response to the update.
- (NSArray *)indexPathsToDeleteForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray *)indexPathsToDeleteForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray *)indexPathsToInsertForSupplementaryViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);
- (NSArray *)indexPathsToInsertForDecorationViewOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(7_0);

@end
