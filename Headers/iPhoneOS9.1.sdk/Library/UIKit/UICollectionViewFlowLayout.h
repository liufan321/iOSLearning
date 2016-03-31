//
//  UICollectionViewFlowLayout.h
//  UIKit
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <UIKit/UICollectionViewLayout.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSString *const UICollectionElementKindSectionHeader NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN NSString *const UICollectionElementKindSectionFooter NS_AVAILABLE_IOS(6_0);

typedef NS_ENUM(NSInteger, UICollectionViewScrollDirection) {
    UICollectionViewScrollDirectionVertical,
    UICollectionViewScrollDirectionHorizontal
};

NS_CLASS_AVAILABLE_IOS(7_0) @interface UICollectionViewFlowLayoutInvalidationContext : UICollectionViewLayoutInvalidationContext

@property (nonatomic) BOOL invalidateFlowLayoutDelegateMetrics; // if set to NO, flow layout will not requery the collection view delegate for size information etc.
@property (nonatomic) BOOL invalidateFlowLayoutAttributes; // if set to NO, flow layout will keep all layout information, effectively not invalidating - useful for a subclass which invalidates only a piece of itself

@end

@protocol UICollectionViewDelegateFlowLayout <UICollectionViewDelegate>
@optional

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath;
- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section;
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section;
- (CGFloat)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section;
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section;
- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout referenceSizeForFooterInSection:(NSInteger)section;

@end

NS_CLASS_AVAILABLE_IOS(6_0) @interface UICollectionViewFlowLayout : UICollectionViewLayout

/**
 The minimum spacing to use between lines of items in the grid.
 * Collection View 中，每一行 items 之间的最小间距
 
 If the delegate object does not implement the collectionView:layout:minimumLineSpacingForSectionAtIndex: method, the flow layout uses the value in this property to set the spacing between lines in a section.
 * 如果代理对象没有实现 `collectionView:layout:minimumLineSpacingForSectionAtIndex:` 方法
 * Flow Layout(流水布局) 对象使用此属性中的值设置同一个 section(分组) 中的最小行间距
 
 For a vertically scrolling grid, this value represents the minimum spacing between successive rows. For a horizontally scrolling grid, this value represents the minimum spacing between successive columns. This spacing is not applied to the space between the header and the first line or between the last line and the footer.
 * 对于垂直滚动的网格，此数值表示`行`与`行`之间的距离
 * 对于水平滚动的网格，此数值表示`列`与`列`之间的距离
 * 注意：此数值不会被应用到 `第一行` 与 `组头`之间的间距，也不会被应用到 `最后一行` 和 `组尾` 之间的间距
 
 The default value of this property is 10.0.
 * 此属性的默认值是 10.0
 */
@property (nonatomic) CGFloat minimumLineSpacing;
/**
 The minimum spacing to use between items in the same row.
 * 同一行中每个格子之间的最小间距
 */
@property (nonatomic) CGFloat minimumInteritemSpacing;
/**
 The default size to use for cells.
 * 每个格子默认使用的尺寸
 */
@property (nonatomic) CGSize itemSize;
/**
 The estimated size of cells in the collection view.
 * 在 Collection View 中格子的预估尺寸
 
 defaults to CGSizeZero - setting a non-zero size enables cells that self-size via -preferredLayoutAttributesFittingAttributes:
 * 默认值是 CGSizeZero
 * 设置一个非零尺寸，允许 cell 通过 -preferredLayoutAttributesFittingAttributes: 确认自身大小
 */
@property (nonatomic) CGSize estimatedItemSize NS_AVAILABLE_IOS(8_0); // defaults to CGSizeZero - setting a non-zero size enables cells that self-size via -preferredLayoutAttributesFittingAttributes:
/**
 The scroll direction of the grid.
 * Collection View 的滚动方向
 * 默认是 UICollectionViewScrollDirectionVertical(垂直滚动)
 */
@property (nonatomic) UICollectionViewScrollDirection scrollDirection; // default is UICollectionViewScrollDirectionVertical
/**
 The default sizes to use for section headers.
 * 组头的默认尺寸
 */
@property (nonatomic) CGSize headerReferenceSize;
/**
 The default sizes to use for section footers.
 * 组尾的默认尺寸
 
 If the delegate does not implement the collectionView:layout:referenceSizeForFooterInSection: method, the flow layout object uses the default footer sizes set for this property.
 * 如果代理没有实现 `collectionView:layout:referenceSizeForFooterInSection:` 方法
 * Flow Layout(流水布局) 对象使用此属性中的值设置组尾的尺寸
 
 During layout, only the size that corresponds to the appropriate scrolling direction is used. For example, for the vertical scrolling direction, the layout object uses the height value specified by this property. (In that instance, the width of the footer would be set to the width of the collection view.) If the size in the appropriate scrolling dimension is 0, no footer is added.
 * 在布局过程中，仅使用 `size` 属性中与滚动方向相同的值
 * 例如：如果是垂直滚动，布局对象使用此属性的 `height` 值指定组尾的高度，同时使用 collection view 的宽度设置组尾的宽度
 * 如果在滚动方向上的值为 0，则不会添加组尾
 
 The default size values are (0, 0).
 * 默认值是 (0, 0)
 */
@property (nonatomic) CGSize footerReferenceSize;
/**
 The margins used to lay out content in a section
 * 用于布局各分组内容之间的间距
 
 If the delegate object does not implement the collectionView:layout:insetForSectionAtIndex: method, the flow layout uses the value in this property to set the margins for each section.
 * 如果代理没有实现 `collectionView:layout:insetForSectionAtIndex:` 方法
 * Flow Layout(流水布局) 对象使用此属性中的值设置每个分组之间的间距
 
 Section insets reflect the spacing at the outer edges of the section. The margins affect the initial position of the header view, the minimum space on either side of each line of items, and the distance from the last line to the footer view. The margin insets do not affect the size of the header and footer views in the non scrolling direction.
 * 分组间距影响分组的外边缘的距离，(垂直方向滚动时，sectionInset 的 `left` 和 `right` 会影响最左侧和最右侧 items 的边距)
 * 分组间距会影响`第一行`和`组头`之间的间距，(垂直方向滚动时，sectionInset 的 `top` 会影响组头和第一行的间距)
 * 分组间距还会影响`最后一行`和`组尾`之间的间距，(垂直方向滚动时，sectionInset 的 `bottom` 会影响组尾和最后一行的间距)
 * 间距值不会影响`组头`和`组尾`的尺寸
 
 The default edge insets are all set to 0.
 * 默认间距的所有值均为 0
 */
@property (nonatomic) UIEdgeInsets sectionInset;

// Set these properties to YES to get headers that pin to the top of the screen and footers that pin to the bottom while scrolling (similar to UITableView).
/**
 将以下属性设置为 YES，可以在滚动时，让组头悬停在屏幕顶部，组尾悬停在底部，与 UITableView 类似
 */
@property (nonatomic) BOOL sectionHeadersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);
@property (nonatomic) BOOL sectionFootersPinToVisibleBounds NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
