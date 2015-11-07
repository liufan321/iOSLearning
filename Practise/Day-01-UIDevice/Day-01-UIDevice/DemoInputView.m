//
//  DemoInputView.m
//  Day-01-UIDevice
//
//  Created by 刘凡 on 15/11/8.
//  Copyright © 2015年 joyios. All rights reserved.
//

#import "DemoInputView.h"

@interface DemoInputView() <UIInputViewAudioFeedback>

@end

@implementation DemoInputView

- (BOOL)enableInputClicksWhenVisible {
    return YES;
}

- (IBAction)clickButton:(UIButton *)sender {
    [[UIDevice currentDevice] playInputClick];
    
    if ([self.delegate respondsToSelector:@selector(demoInputViewDidInputText:text:)]) {
        [self.delegate demoInputViewDidInputText:self text:sender.currentTitle];
    }
}

@end
