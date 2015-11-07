//
//  DemoInputView.h
//  Day-01-UIDevice
//
//  Created by 刘凡 on 15/11/8.
//  Copyright © 2015年 joyios. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol DemoInputViewDelegate;

@interface DemoInputView : UIView
@property (nonatomic, weak) id<DemoInputViewDelegate> delegate;
@end

@protocol DemoInputViewDelegate <NSObject>
@optional
- (void)demoInputViewDidInputText:(DemoInputView *)inputView text:(NSString *)text;
@end
