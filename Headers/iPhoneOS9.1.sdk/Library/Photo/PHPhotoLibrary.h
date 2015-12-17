//
//  PHPhotoLibrary.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PHChange;

/// 相册授权状态
typedef NS_ENUM(NSInteger, PHAuthorizationStatus) {
    /// 用户还没有授权应用程序访问相册
    PHAuthorizationStatusNotDetermined = 0, // User has not yet made a choice with regards to this application
    /// 应用程序无法访问相册，用户不能修改应用程序的状态，可能是开启了`家长控制`功能
    PHAuthorizationStatusRestricted,        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //   such as parental controls being in place.
    /// 用户拒绝应用程序访问相册
    PHAuthorizationStatusDenied,            // User has explicitly denied this application access to photos data.
    /// 用户授权应用程序访问相册
    PHAuthorizationStatusAuthorized         // User has authorized this application to access photos data.
} NS_AVAILABLE_IOS(8_0);


/// 照片库访问权限变化观察者协议(`拒绝`访问不会调用监听方法)
NS_CLASS_AVAILABLE_IOS(8_0) @protocol PHPhotoLibraryChangeObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
// 此回调会在任意的串行队列被调度，需要注意不要直接更新 UI
- (void)photoLibraryDidChange:(PHChange *)changeInstance;

@end

/*!
 @class        PHPhotoLibrary
 @abstract     A PHPhotoLibrary provides access to the metadata and image data for the photos, videos and related content in the user's photo library, including content from the Camera Roll, iCloud Shared, Photo Stream, imported, and synced from iTunes.
 @discussion   ...
 */
NS_CLASS_AVAILABLE_IOS(8_0) @interface PHPhotoLibrary : NSObject

+ (PHPhotoLibrary *)sharedPhotoLibrary;

/// 返回相册访问授权状态
+ (PHAuthorizationStatus)authorizationStatus;
/// 请求授权访问相册，如果用户已经拒绝，此方法不会弹出提示框询问用户
+ (void)requestAuthorization:(void(^)(PHAuthorizationStatus status))handler;

#pragma mark - Applying Changes

// handlers are invoked on an arbitrary serial queue
// Nesting change requests will throw an exception
- (void)performChanges:(dispatch_block_t)changeBlock completionHandler:(nullable void(^)(BOOL success, NSError *__nullable error))completionHandler;
- (BOOL)performChangesAndWait:(dispatch_block_t)changeBlock error:(NSError *__autoreleasing *)error;


#pragma mark - Change Handling

/// 注册授权变化观察者
- (void)registerChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;
/// 注销授权变化观察者
- (void)unregisterChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;

@end

NS_ASSUME_NONNULL_END