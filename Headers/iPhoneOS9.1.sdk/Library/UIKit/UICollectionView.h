//
//  UICollectionView.h
//  UIKit
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIScrollView.h>
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UICollectionViewScrollPosition) {
    UICollectionViewScrollPositionNone                 = 0,
    
    // The vertical positions are mutually exclusive to each other, but are bitwise or-able with the horizontal scroll positions.
    // Combining positions from the same grouping (horizontal or vertical) will result in an NSInvalidArgumentException.
    UICollectionViewScrollPositionTop                  = 1 << 0,
    UICollectionViewScrollPositionCenteredVertically   = 1 << 1,
    UICollectionViewScrollPositionBottom               = 1 << 2,
    
    // Likewise, the horizontal positions are mutually exclusive to each other.
    UICollectionViewScrollPositionLeft                 = 1 << 3,
    UICollectionViewScrollPositionCenteredHorizontally = 1 << 4,
    UICollectionViewScrollPositionRight                = 1 << 5
};

@class UICollectionView;
@class UICollectionViewCell;
@class UICollectionViewLayout;
@class UICollectionViewTransitionLayout;
@class UICollectionViewLayoutAttributes;
@class UITouch;
@class UINib;
@class UICollectionReusableView;

// layout transition block signature
typedef void (^UICollectionViewLayoutInteractiveTransitionCompletion)(BOOL completed, BOOL finished);
#ifndef SDK_HIDE_TIDE
NS_CLASS_AVAILABLE_IOS(9_0) @interface UICollectionViewFocusUpdateContext : UIFocusUpdateContext

@property (nonatomic, strong, readonly, nullable) NSIndexPath *previouslyFocusedIndexPath;
@property (nonatomic, strong, readonly, nullable) NSIndexPath *nextFocusedIndexPath;

@end
#endif

@protocol UICollectionViewDataSource <NSObject>
@required

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section;

// The cell that is returned must be retrieved from a call to -dequeueReusableCellWithReuseIdentifier:forIndexPath:
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@optional

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView;

// The view that is returned must be retrieved from a call to -dequeueReusableSupplementaryViewOfKind:withReuseIdentifier:forIndexPath:
- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

- (BOOL)collectionView:(UICollectionView *)collectionView canMoveItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (void)collectionView:(UICollectionView *)collectionView moveItemAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath*)destinationIndexPath NS_AVAILABLE_IOS(9_0);

@end

@protocol UICollectionViewDelegate <UIScrollViewDelegate>
@optional

// Methods for notification of selection/deselection and highlight/unhighlight events.
// The sequence of calls leading to selection from a user touch is:
//
// (when the touch begins)
// 1. -collectionView:shouldHighlightItemAtIndexPath:
// 2. -collectionView:didHighlightItemAtIndexPath:
//
// (when the touch lifts)
// 3. -collectionView:shouldSelectItemAtIndexPath: or -collectionView:shouldDeselectItemAtIndexPath:
// 4. -collectionView:didSelectItemAtIndexPath: or -collectionView:didDeselectItemAtIndexPath:
// 5. -collectionView:didUnhighlightItemAtIndexPath:
- (BOOL)collectionView:(UICollectionView *)collectionView shouldHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView shouldDeselectItemAtIndexPath:(NSIndexPath *)indexPath; // called when the user taps on an already-selected item in multi-select mode
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didDeselectItemAtIndexPath:(NSIndexPath *)indexPath;

- (void)collectionView:(UICollectionView *)collectionView willDisplayCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
- (void)collectionView:(UICollectionView *)collectionView willDisplaySupplementaryView:(UICollectionReusableView *)view forElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(8_0);
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingCell:(UICollectionViewCell *)cell forItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)collectionView:(UICollectionView *)collectionView didEndDisplayingSupplementaryView:(UICollectionReusableView *)view forElementOfKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath;

// These methods provide support for copy/paste actions on cells.
// All three should be implemented if any are.
- (BOOL)collectionView:(UICollectionView *)collectionView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL)collectionView:(UICollectionView *)collectionView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;
- (void)collectionView:(UICollectionView *)collectionView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(nullable id)sender;

// support for custom transition layout
- (nonnull UICollectionViewTransitionLayout *)collectionView:(UICollectionView *)collectionView transitionLayoutForOldLayout:(UICollectionViewLayout *)fromLayout newLayout:(UICollectionViewLayout *)toLayout;
#ifndef SDK_HIDE_TIDE
// Focus
- (BOOL)collectionView:(UICollectionView *)collectionView canFocusItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (BOOL)collectionView:(UICollectionView *)collectionView shouldUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context NS_AVAILABLE_IOS(9_0);
- (void)collectionView:(UICollectionView *)collectionView didUpdateFocusInContext:(UICollectionViewFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator NS_AVAILABLE_IOS(9_0);
- (nullable NSIndexPath *)indexPathForPreferredFocusedViewInCollectionView:(UICollectionView *)collectionView NS_AVAILABLE_IOS(9_0);
#endif

- (NSIndexPath *)collectionView:(UICollectionView *)collectionView targetIndexPathForMoveFromItemAtIndexPath:(NSIndexPath *)originalIndexPath toProposedIndexPath:(NSIndexPath *)proposedIndexPath NS_AVAILABLE_IOS(9_0);

- (CGPoint)collectionView:(UICollectionView *)collectionView targetContentOffsetForProposedContentOffset:(CGPoint)proposedContentOffset NS_AVAILABLE_IOS(9_0); // customize the content offset to be applied during transition or update animations

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionView : UIScrollView

/// 构造函数
///
/// @param frame  frame
/// @param layout 用于组织排列 item 的布局对象，collection view 会对指定对象强引用，必须不能为 nil。
///
/// @return 指定 frame 和 layout 的 collectionView，如果对象创建失败，返回 nil
- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong) UICollectionViewLayout *collectionViewLayout;
@property (nonatomic, weak, nullable) id <UICollectionViewDelegate> delegate;
@property (nonatomic, weak, nullable) id <UICollectionViewDataSource> dataSource;
@property (nonatomic, strong, nullable) UIView *backgroundView; // will be automatically resized to track the size of the collection view and placed behind all cells and supplementary views.

// For each reuse identifier that the collection view will use, register either a class or a nib from which to instantiate a cell.
// If a nib is registered, it must contain exactly 1 top level object which is a UICollectionViewCell.
// If a class is registered, it will be instantiated via alloc/initWithFrame:
- (void)registerClass:(nullable Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(nullable UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;

- (void)registerClass:(nullable Class)viewClass forSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(nullable UINib *)nib forSupplementaryViewOfKind:(NSString *)kind withReuseIdentifier:(NSString *)identifier;

- (__kindof UICollectionViewCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;
- (__kindof UICollectionReusableView *)dequeueReusableSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

// These properties control whether items can be selected, and if so, whether multiple items can be simultaneously selected.
@property (nonatomic) BOOL allowsSelection; // default is YES
@property (nonatomic) BOOL allowsMultipleSelection; // default is NO

- (nullable NSArray<NSIndexPath *> *)indexPathsForSelectedItems; // returns nil or an array of selected index paths
- (void)selectItemAtIndexPath:(nullable NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UICollectionViewScrollPosition)scrollPosition;
- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

- (void)reloadData; // discard the dataSource and delegate data and requery as necessary

- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated; // transition from one layout to another
- (void)setCollectionViewLayout:(UICollectionViewLayout *)layout animated:(BOOL)animated completion:(void (^ __nullable)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

- (UICollectionViewTransitionLayout *)startInteractiveTransitionToCollectionViewLayout:(UICollectionViewLayout *)layout completion:(nullable UICollectionViewLayoutInteractiveTransitionCompletion)completion NS_AVAILABLE_IOS(7_0);
- (void)finishInteractiveTransition NS_AVAILABLE_IOS(7_0);
- (void)cancelInteractiveTransition NS_AVAILABLE_IOS(7_0);

// Information about the current state of the collection view.

- (NSInteger)numberOfSections;
- (NSInteger)numberOfItemsInSection:(NSInteger)section;

- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
- (nullable UICollectionViewLayoutAttributes *)layoutAttributesForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

- (nullable NSIndexPath *)indexPathForItemAtPoint:(CGPoint)point;
- (nullable NSIndexPath *)indexPathForCell:(UICollectionViewCell *)cell;

- (nullable UICollectionViewCell *)cellForItemAtIndexPath:(NSIndexPath *)indexPath;
- (NSArray<__kindof UICollectionViewCell *> *)visibleCells;
- (NSArray<NSIndexPath *> *)indexPathsForVisibleItems;

- (UICollectionReusableView *)supplementaryViewForElementKind:(NSString *)elementKind atIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0);
- (NSArray<UICollectionReusableView *> *)visibleSupplementaryViewsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);
- (NSArray<NSIndexPath *> *)indexPathsForVisibleSupplementaryElementsOfKind:(NSString *)elementKind NS_AVAILABLE_IOS(9_0);

// Interacting with the collection view.
#pragma mark - 与 collection view 交互

/**
 Scrolls the collection view contents until the specified item is visible.
 将 collection view 内容滚动至`指定 item`可见的位置
 */
- (void)scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UICollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;

// These methods allow dynamic modification of the current set of items in the collection view
// 以下方法允许动态修改 collection view 中的当前 items 集合
/**
 Inserts new sections at the specified indexes.
 在指定的 indexes 插入新的 sections
 
 Use this method to insert one or more sections into the collection view. This method adds the sections, and it is up to your data source to report the number of items in each section when asked for the information. The collection view then uses that information to get updated layout attributes for the newly inserted sections and items. If the insertions cause a change in the collection view’s visible content, those changes are animated into place.
 * 使用此方法向 collection view 插入一个或多个 section
 * 此方法添加 sections，并且询问数据源每个 section 中包含的 item 数量
 * 然后使用这些信息为新插入的 section 和 items 获取更新后的布局属性
 * 如果插入的内容导致 collection view 可见内容的变化，这些变化会以动画方式调整
 
 You can also call this method from a block passed to the performBatchUpdates:completion: method when you want to animate multiple separate changes into place at the same time. See the description of that method for more information.
 * 如果希望在同一时间，以动画的方式改变多个 section 或者 item
 * 还可以在传递给 `performBatchUpdates:completion:` 方法的 block 中调用此方法
 * 相关内容，请参阅该方法的信息
 */
- (void)insertSections:(NSIndexSet *)sections;

- (void)deleteSections:(NSIndexSet *)sections;
- (void)reloadSections:(NSIndexSet *)sections;
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection;

- (void)insertItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)deleteItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)reloadItemsAtIndexPaths:(NSArray<NSIndexPath *> *)indexPaths;
- (void)moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;

/**
 Animates multiple insert, delete, reload, and move operations as a group.
 以动画组的方式，同时处理多个插入、删除、刷新和移动操作
 
 You can use this method in cases where you want to make multiple changes to the collection view in one single animated operation, as opposed to in several separate animations. You might use this method to insert, delete, reload, or move cells or use it to change the layout parameters associated with one or more cells. Use the blocked passed in the updates parameter to specify all of the operations you want to perform.
 * 如果希望在一个动画操作中实现 collection view 中的多处变化，可以使用此方法
 * 可以使用此方法插入、删除、加载或移动多个 cell，或者同时变化这些 cell 关联的布局参数
 * 在传递给 update 参数的块代码中，指定所有希望执行的操作即可
 
 Deletes are processed before inserts in batch operations. This means the indexes for the deletions are processed relative to the indexes of the collection view’s state before the batch operation, and the indexes for the insertions are processed relative to the indexes of the state after all the deletions in the batch operation.
 * 注意：在批量执行的操作中，删除操作会先于插入操作执行
 */
- (void)performBatchUpdates:(void (^ __nullable)(void))updates completion:(void (^ __nullable)(BOOL finished))completion; // allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable.

// Support for reordering
#pragma mark - 支持重新排序


- (BOOL)beginInteractiveMovementForItemAtIndexPath:(NSIndexPath *)indexPath NS_AVAILABLE_IOS(9_0); // returns NO if reordering was prevented from beginning - otherwise YES
- (void)updateInteractiveMovementTargetPosition:(CGPoint)targetPosition NS_AVAILABLE_IOS(9_0);
- (void)endInteractiveMovement NS_AVAILABLE_IOS(9_0);
- (void)cancelInteractiveMovement NS_AVAILABLE_IOS(9_0);

#ifndef SDK_HIDE_TIDE
// Support for Focus
@property (nonatomic) BOOL remembersLastFocusedIndexPath NS_AVAILABLE_IOS(9_0); // defaults to NO. If YES, when focusing on a collection view the last focused index path is focused automatically. If the collection view has never been focused, then the preferred focused index path is used.
#endif
@end

@interface NSIndexPath (UICollectionViewAdditions)

/// 实例化 IndexPath
///
/// @param item    item
/// @param section section
///
/// @return NSIndexPath
+ (instancetype)indexPathForItem:(NSInteger)item inSection:(NSInteger)section NS_AVAILABLE_IOS(6_0);

@property (nonatomic, readonly) NSInteger item NS_AVAILABLE_IOS(6_0);

@end

NS_ASSUME_NONNULL_END
