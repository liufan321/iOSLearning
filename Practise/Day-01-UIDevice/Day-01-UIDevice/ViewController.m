//
//  ViewController.m
//  Day-01-UIDevice
//
//  Created by 刘凡 on 15/11/8.
//  Copyright © 2015年 joyios. All rights reserved.
//

#import "ViewController.h"
#import "DemoInputView.h"

@interface ViewController () <DemoInputViewDelegate>

@property (weak, nonatomic) IBOutlet UILabel *batteryLabel;
@property (weak, nonatomic) IBOutlet UITextField *textField;

@property (strong, nonatomic) IBOutlet DemoInputView *demoInputView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self deviceProperties];
    [self deviceBattery];
    [self deviceIdiom];
    
    // 设置输入视图
    self.textField.inputView = self.demoInputView;
    self.demoInputView.delegate = self;
    
    // 监听设备方向变化通知
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceOrientationRotated)
                                                 name:UIDeviceOrientationDidChangeNotification
                                               object:nil];
    // 监听设备电量变化通知
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceBatteryStateChanged)
                                                 name:UIDeviceBatteryStateDidChangeNotification
                                               object:nil];
    // 监听接近状态通知
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceProximityChanged)
                                                 name:UIDeviceProximityStateDidChangeNotification
                                               object:nil];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

/// 接近状态变化
- (void)deviceProximityChanged {
    UIDevice *device = [UIDevice currentDevice];
    
    NSString *proximityMessage = device.proximityState ? @"接近了" : @"远离了";
    
    NSLog(@"%@", proximityMessage);
}

/// 设备电量变化通知
- (void)deviceBatteryStateChanged {
    UIDevice *device = [UIDevice currentDevice];
    NSString *stateMessage;
    
    switch (device.batteryState) {
        case UIDeviceBatteryStateFull:
            stateMessage = [NSString stringWithFormat:@"充电，电量：%.02f", device.batteryLevel];
            break;
        case UIDeviceBatteryStateCharging:
            stateMessage = [NSString stringWithFormat:@"充电，电量：%.02f", device.batteryLevel];
            break;
        case UIDeviceBatteryStateUnplugged:
            stateMessage = [NSString stringWithFormat:@"使用电池，未充电：%.02f", device.batteryLevel];
            break;
        default:
            stateMessage = [NSString stringWithFormat:@"电池状态，未知：%.02f", device.batteryLevel];
            break;
    }
    
    _batteryLabel.text = stateMessage;
}

/// 设备方向变化通知
- (void)deviceOrientationRotated {
    UIDevice *device = [UIDevice currentDevice];
    
    switch (device.orientation) {
        case UIDeviceOrientationPortrait:
            NSLog(@"垂直方向，Home 按钮在下方");
            break;
        case UIDeviceOrientationPortraitUpsideDown:
            NSLog(@"垂直方向，Home 按钮在上方");
            break;
        case UIDeviceOrientationLandscapeLeft:
            NSLog(@"水平方向，Home 按钮在右侧");
            break;
        case UIDeviceOrientationLandscapeRight:
            NSLog(@"水平方向，Home 按钮在左侧");
            break;
        case UIDeviceOrientationFaceUp:
            NSLog(@"设备平放，屏幕冲上");
            break;
        case UIDeviceOrientationFaceDown:
            NSLog(@"设备平放，屏幕冲下");
            break;
        default:
            NSLog(@"未知方向");
            break;
    }
}

/// 设备属性
- (void)deviceProperties {
    UIDevice *device = [UIDevice currentDevice];
    
    NSLog(@"name: %@", device.name);
    NSLog(@"model: %@", device.model);
    NSLog(@"localizedModel: %@", device.localizedModel);
    NSLog(@"systemName: %@", device.systemName);
    NSLog(@"systemVersion: %@", device.systemVersion);
    
    NSLog(@"是否发布设备方向通知 %d", device.isGeneratingDeviceOrientationNotifications);
    NSLog(@"%tu", device.orientation);
    
    NSLog(@"%@", device.identifierForVendor);
    NSLog(@"是否支持多任务 %d", device.isMultitaskingSupported);
    
    device.proximityMonitoringEnabled = YES;
    NSLog(@"是否支持接近监听 %d", device.isProximityMonitoringEnabled);
}

/// 设备类型
- (void)deviceIdiom {
    UIDevice *device = [UIDevice currentDevice];
    
    switch (device.userInterfaceIdiom) {
        case UIUserInterfaceIdiomPad:
            NSLog(@"设备类型：iPad");
            break;
        case UIUserInterfaceIdiomPhone:
            NSLog(@"设备类型：iPhone");
            break;
        case UIUserInterfaceIdiomTV:
            NSLog(@"设备类型：TV");
            break;
        default:
            break;
    }
}

/// 设备电量
- (void)deviceBattery {
    UIDevice *device = [UIDevice currentDevice];
    
    NSLog(@"是否允许监听电池电量 %d", device.isBatteryMonitoringEnabled);
    device.batteryMonitoringEnabled = YES;
    NSLog(@"是否允许监听电池电量 %d", device.isBatteryMonitoringEnabled);
    
    [self deviceBatteryStateChanged];
}

#pragma mark - DemoInputViewDelegate 协议方法
- (void)demoInputViewDidInputText:(DemoInputView *)inputView text:(NSString *)text {
    [self.textField replaceRange:self.textField.selectedTextRange withText:text];
}

@end
