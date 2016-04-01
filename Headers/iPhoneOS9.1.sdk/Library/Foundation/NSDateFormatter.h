/*	NSDateFormatter.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray<ObjectType>, NSMutableDictionary, NSString;

NS_ASSUME_NONNULL_BEGIN

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

/**
 Instances of NSDateFormatter create string representations of NSDate objects, and convert textual representations of dates and times into NSDate objects. For user-visible representations of dates and times, NSDateFormatter provides a variety of localized presets and configuration options. For fixed format representations of dates and times, such as RFC 3339, you can specify a custom format string.
 * NSDateFormatter 的实例用于创建 NSDate 对象的字符串表示，并且可以将日期和时间的文本表示转换成 NSDate 对象
 * 对于常用的日期和时间表示，NSDateFormatter 提供了多种本地化预设和配置选项
 * 对于日期和时间固定格式的表示，例如 RFC 3339，可以指定一个自定义的格式字符串
 
 Overview
 * 概述
 
 To represent an interval between two NSDate objects, use NSDateIntervalFormatter instead.
 * 要表示两个 NSDate 对象之间的间隔，请使用 `NSDateIntervalFormatter`
 
 To represent a quantity of time specified by an NSDateComponents object, use NSDateComponentsFormatter instead.
 * 要表示由一个 NSDateComponents 对象指定的时间量，请使用 `NSDateComponentsFormatter`
 
 Working With User-Visible Representations of Dates and Times
 * 使用日期和时间的常见表示
 
 When displaying a date to a user, you set the dateStyle and timeStyle properties of the date formatter according to your particular needs. For example, if you want to show the month, day, and year without showing the time, you would set the dateStyle property to NSDateFormatterLongStyle and the timeStyle property to NSDateFormatterNoStyle. Conversely, if you want to show only the time, you would set the dateStyle property to NSDateFormatterNoStyle and the timeStyle property to NSDateFormatterShortStyle. Based on the values of the dateStyle and timeStyle properties, NSDateFormatter provides a representation of a specified date that is appropriate for a given locale.
 * 在显示一个日期时，可以根据具体的需求，设置 `日期格式化器` 的 `dateStyle` 和 `timeStyle` 属性
 * 例如：如果只希望显示 年、月、日，而不希望显示时间
    * 可以将 `dateStyle` 属性设置为 `NSDateFormatterLongStyle`
    * 将 `timeStyle` 属性设置为 `NSDateFormatterNoStyle`
 * 相反，如果希望仅显示时间
    * 可以将 `dateStyle` 属性设置为 `NSDateFormatterNoStyle`
    * 将 `timeStyle` 属性设置为 `NSDateFormatterShortStyle`
 * 基于 `dateStyle` 和 `timeStyle` 属性值，NSDateFormatter 提供了适合于给定语言环境的指定日期的表示
 
 * 示例代码如下：
 
 ```
 // 实例化日期格式器
 NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
 
 dateFormatter.dateStyle = NSDateFormatterMediumStyle;
 dateFormatter.timeStyle = NSDateFormatterNoStyle;
 
 NSDate *date = [NSDate dateWithTimeIntervalSinceReferenceDate:118800];
 
 // US English Locale (en_US)
 dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];
 NSLog(@"%@", [dateFormatter stringFromDate:date]); // Jan 2, 2001
 
 // French Locale (fr_FR)
 dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"fr_FR"];
 NSLog(@"%@", [dateFormatter stringFromDate:date]); // 2 janv. 2001
 
 // Japanese Locale (ja_JP)
 dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"ja_JP"];
 NSLog(@"%@", [dateFormatter stringFromDate:date]); // 2001/01/02
 
 // 简体中文 (zh_CN)
 dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"];
 NSLog(@"%@", [dateFormatter stringFromDate:date]); // 2001年1月2日
 ```
 
 If for some reason you need to define a format that was not specified by the user at the system level, you can set individual attributes such as the locale, time zone, calendar, format string, and various textual strings like the month names.
 * 如果由于某种原因，需要定义不是由用户在系统级别指定的格式
 * 可以单独设置需要的属性，如：语言环境，时区，日历，格式字符串，以及诸如月份名的各种文本串
 
 Note that although setting a format string (dateFormat) in principle specifies an exact format, in practice it may nevertheless also be overridden by a user’s preferences—see Data Formatting Guide for more details.
 *** 请注意，虽然设置格式字符串（日期格式）可以指定一个准确的格式，但是在实践中，也可能被用户的偏好设置覆盖，请参阅 《Data Formatting Guide（数据格式指南）》了解更多详情
 
 Working With Fixed Format Date Representations
 * 使用日期表示的固定格式
 
 When working with fixed format dates, such as RFC 3339, you set the dateFormat property to specify a format string. For most fixed formats, you should also set the locale property to a POSIX locale ("en_US_POSIX"), and set the timeZone property to UTC.
 * 当使用日期的固定格式时，例如 RFC 3339
 * 可以设置 `dateFormat` 指定一个格式字符串
 * 对于大多数固定格式，还应该将 `locale` 属性设置为 "en_US_POSIX"，同时将 `timeZone` 设置为 `UTC`
 
 * 示例代码如下：
 
 ```
 RFC3339DateFormatter = [[NSDateFormatter alloc] init];
 RFC3339DateFormatter.locale = [NSLocale localeWithLocaleIdentifier:@"en_US_POSIX"];
 RFC3339DateFormatter.dateFormat = @"yyyy-MM-dd'T'HH:mm:ssZZZZZ";
 RFC3339DateFormatter.timeZone = [NSTimeZone timeZoneForSecondsFromGMT:0];
 
 // 39 minutes and 57 seconds after the 16th hour of December 19th, 1996 with an offset of -08:00 from UTC (Pacific Standard Time)
 NSString *string = @"1996-12-19T16:39:57-08:00";
 NSDate *date = [RFC3339DateFormatter dateFromString:string];
 ```

 For more information, see Technical Q&A QA1480 “NSDateFormatter and Internet Dates”.
 Formatter Behaviors
 OS X v10.4 introduced the modern behavior for NSDateFormatter. See Data Formatting Guide for a full description of the old and new behaviors.
 Note:iOS Note
 iOS supports only the modern behavior.
 On OS X v10.5 and later, NSDateFormatter defaults to the modern behavior. If necessary, you can set the default class behavior using setDefaultFormatterBehavior:, or you can set the behavior for an instance using formatterBehavior.
 
 Thread Safety
 * 线程按钮
 
 On iOS 7 and later NSDateFormatter is thread safe.
 * iOS 7 和之后版本 NSDateFormatter 是线程安全的
 
 On OS X 10.9 and later NSDateFormatter is thread safe so long as you are using the modern behavior in a 64-bit app.
 
 On earlier versions of the operating system, or when using the legacy formatter behavior or running in 32-bit on OS X, NSDateFormatter is not thread safe, and you therefore must not mutate a date formatter simultaneously from multiple threads.
 * 在早期版本的操作系统，或使用传统格式化行为，或在 32位的 OS X 上运行时
 * NSDateFormatter 不是线程安全的
 * 所以必须不能在同一时间，在多个线程同时转换日期格式
 */
@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    __strong CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

@property NSFormattingContext formattingContext NS_AVAILABLE(10_10, 8_0); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

- (BOOL)getObjectValue:(out id __nullable * __nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSDateFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

/// Returns a string representation of a given date formatted using the receiver’s current settings.
/// 返回给定日期的一个字符串表示，字符串格式按照当前对象的设置
- (NSString *)stringFromDate:(NSDate *)date;
/// Returns a date representation of a given string interpreted using the receiver’s current settings.
/// 返回给定字符串的日期表示，字符串格式按照当前对象的设置
- (nullable NSDate *)dateFromString:(NSString *)string;

/**
 日期和时间样式
 
 ```
 dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"];
 ```
 
 NSDateFormatterNoStyle         无   nil / nil
 NSDateFormatterShortStyle      短   01/1/2 / 下午5:00
 NSDateFormatterMediumStyle     中   2001年1月2日 / 下午5:00:00
 NSDateFormatterLongStyle       长   2001年1月2日 / GMT+8 下午5:00:00
 NSDateFormatterFullStyle       完整 2001年1月2日 星期二 / 中国标准时间 下午5:00:00
 */
typedef NS_ENUM(NSUInteger, NSDateFormatterStyle) {    // date and time format styles
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};

typedef NS_ENUM(NSUInteger, NSDateFormatterBehavior) {
    NSDateFormatterBehaviorDefault = 0,
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
    NSDateFormatterBehavior10_0 = 1000,
#endif
    NSDateFormatterBehavior10_4 = 1040,
};


+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle NS_AVAILABLE(10_6, 4_0);

+ (nullable NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(nullable NSLocale *)locale NS_AVAILABLE(10_6, 4_0);
	// no options defined, pass 0 for now

// Attributes of an NSDateFormatter

+ (NSDateFormatterBehavior)defaultFormatterBehavior;
+ (void)setDefaultFormatterBehavior:(NSDateFormatterBehavior)behavior;

/*
 A convenient way to generate an appropriate localized date format, and set it, in a single operation.

 Equivalent to, though not necessarily implemented as:
 formatter.dateFormat = [NSDateFormatter dateFormatFromTemplate:dateFormatTemplate options:0 locale:formatter.locale];

 Note that the template string is used only to specify which date format components should be included. Ordering and other text will not be preserved.
 The parameter is also not stored, or updated when the locale or other options change, just as with the ‘dateFormat’ property.
 */
- (void) setLocalizedDateFormatFromTemplate:(NSString *)dateFormatTemplate NS_AVAILABLE(10_10, 8_0);


@property (null_resettable, copy) NSString *dateFormat;
/// 日期样式
@property NSDateFormatterStyle dateStyle;
/// 时间样式
@property NSDateFormatterStyle timeStyle;
@property (null_resettable, copy) NSLocale *locale;
/// NSCalendarDate is no longer supported; you should not use this method.
/// 不再支持 NSCalendarDate 方法
@property BOOL generatesCalendarDates;
@property NSDateFormatterBehavior formatterBehavior;

/// 时区
@property (null_resettable, copy) NSTimeZone *timeZone;
/// 日历
@property (null_resettable, copy) NSCalendar *calendar;
/// 启发式
/// 默认为 NO，设置为 YES 可能出错
@property (getter=isLenient) BOOL lenient;
/// 两位数年数表示的最早日期，默认值是 1950-01-01 00:00:00 +0000
@property (nullable, copy) NSDate *twoDigitStartDate;
/// 默认日期，默认数值为 nil
@property (nullable, copy) NSDate *defaultDate;
/**
 以下符号会根据 locale 的属性变化而变化
 
 zh_CN  简体中文
 en_US  美国英语
 zh_TW  繁体中文
 */
// 公元前, 公元
// BC, AD
// 西元前, 西元
@property (null_resettable, copy) NSArray<NSString *> *eraSymbols;

// 一月, 二月, 三月, 四月, 五月, 六月, 七月, 八月, 九月, 十月, 十一月, 十二月
// January, February, March, April, May, June,
// July, August, September, October, November, December
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
@property (null_resettable, copy) NSArray<NSString *> *monthSymbols;
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
// Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
@property (null_resettable, copy) NSArray<NSString *> *shortMonthSymbols;

// 星期日, 星期一, 星期二, 星期三, 星期四, 星期五, 星期六
// Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
// 星期日, 星期一, 星期二, 星期三, 星期四, 星期五, 星期六
@property (null_resettable, copy) NSArray<NSString *> *weekdaySymbols;
// 周日, 周一, 周二, 周三, 周四, 周五, 周六
// Sun, Mon, Tue, Wed, Thu, Fri, Sat
// 週日, 週一, 週二, 週三, 週四, 週五, 週六
@property (null_resettable, copy) NSArray<NSString *> *shortWeekdaySymbols;

// 上午
// AM
// 上午
@property (null_resettable, copy) NSString *AMSymbol;
// 下午
// PM
// 下午
@property (null_resettable, copy) NSString *PMSymbol;

// 公元前, 公元
// Before Christ, Anno Domini
// 西元前, 西元
@property (null_resettable, copy) NSArray<NSString *> *longEraSymbols NS_AVAILABLE(10_5, 2_0);

// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
// J, F, M, A, M, J, J, A, S, O, N, D
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
@property (null_resettable, copy) NSArray<NSString *> *veryShortMonthSymbols NS_AVAILABLE(10_5, 2_0);
// 一月, 二月, 三月, 四月, 五月, 六月, 七月, 八月, 九月, 十月, 十一月, 十二月
// January, February, March, April, May, June,
// July, August, September, October, November, December
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
@property (null_resettable, copy) NSArray<NSString *> *standaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
// Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
// 1月, 2月, 3月, 4月, 5月, 6月, 7月, 8月, 9月, 10月, 11月, 12月
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
// J, F, M, A, M, J, J, A, S, O, N, D
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols NS_AVAILABLE(10_5, 2_0);

// 日, 一, 二, 三, 四, 五, 六
// S, M, T, W, T, F, S
// 日, 一, 二, 三, 四, 五, 六
@property (null_resettable, copy) NSArray<NSString *> *veryShortWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
// 星期日, 星期一, 星期二, 星期三, 星期四, 星期五, 星期六
// Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
// 星期日, 星期一, 星期二, 星期三, 星期四, 星期五, 星期六
@property (null_resettable, copy) NSArray<NSString *> *standaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
// 周日, 周一, 周二, 周三, 周四, 周五, 周六
// Sun, Mon, Tue, Wed, Thu, Fri, Sat
// 週日, 週一, 週二, 週三, 週四, 週五, 週六
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);
// 日, 一, 二, 三, 四, 五, 六
// S, M, T, W, T, F, S
// 日, 一, 二, 三, 四, 五, 六
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols NS_AVAILABLE(10_5, 2_0);

// 第一季度, 第二季度, 第三季度, 第四季度
// 1st quarter, 2nd quarter, 3rd quarter, 4th quarter
// 第1季, 第2季, 第3季, 第4季
@property (null_resettable, copy) NSArray<NSString *> *quarterSymbols NS_AVAILABLE(10_5, 2_0);
// 1季度, 2季度, 3季度, 4季度
// Q1, Q2, Q3, Q4
// 1季, 2季, 3季, 4季
@property (null_resettable, copy) NSArray<NSString *> *shortQuarterSymbols NS_AVAILABLE(10_5, 2_0);
// 第一季度, 第二季度, 第三季度, 第四季度
// 1st quarter, 2nd quarter, 3rd quarter, 4th quarter
// 第1季, 第2季, 第3季, 第4季
@property (null_resettable, copy) NSArray<NSString *> *standaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);
// 1季度, 2季度, 3季度, 4季度
// Q1, Q2, Q3, Q4
// 1季, 2季, 3季, 4季
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols NS_AVAILABLE(10_5, 2_0);

// 公历(格里历)起始日期 1582-10-15 00:00:00 +0000
@property (nullable, copy) NSDate *gregorianStartDate NS_AVAILABLE(10_5, 2_0);

// 是否使用与 Locale 相关的日期格式
// 中文能够显示：前天／昨天／今天／明天／后天
// 英文能够显示：Yesterday / Today / Tomorrow
@property BOOL doesRelativeDateFormatting NS_AVAILABLE(10_6, 4_0);

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSDateFormatter (NSDateFormatterCompatibility)

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "Use -setDateFormat: as of OS X 10.9 to set the date format of a 10.0-style date formatter; but expect 10.0-style date formatting to be deprecated in the future as well");
- (BOOL)allowsNaturalLanguage NS_CALENDAR_DEPRECATED_MAC(10_4, 10_9, "There is no replacement");

@end
#endif

NS_ASSUME_NONNULL_END
