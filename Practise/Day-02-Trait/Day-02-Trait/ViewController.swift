//
//  ViewController.swift
//  Day-02-Trait
//
//  Created by 刘凡 on 15/12/6.
//  Copyright © 2015年 itheima. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var idiomLabel: UILabel!
    @IBOutlet weak var scaleLabel: UILabel!
    @IBOutlet weak var sizeClassLabel: UILabel!
    @IBOutlet weak var forceTouchLabel: UILabel!
    
    private func showTraitCollectionInfo() {
        
        /*
        traitCollection 由 UITraitEnvironment <NSObject> 协议中暴露
        
        UIViewController 和 UIView 都遵守了 UITraitEnvironment 协议
        
        注意：
        - 应该直接使用 traitCollection 属性
        - 不要重写此属性
        - 不要提供自定义实现
        */
        var result: String
        switch traitCollection.userInterfaceIdiom {
        case .Phone: result = "Phone"
        case .Pad: result = "Pad"
        case .TV: result = "TV"
        case .Unspecified: result = "未知"
        }
        idiomLabel.text = result
        
        scaleLabel.text = traitCollection.displayScale.description
        
        if traitCollection.horizontalSizeClass == .Regular && traitCollection.verticalSizeClass == .Regular {
            sizeClassLabel.text = "iPad"
        } else if traitCollection.horizontalSizeClass == .Compact && traitCollection.verticalSizeClass == .Compact {
            sizeClassLabel.text = "iPhone 横屏"
        } else if traitCollection.horizontalSizeClass == .Compact && traitCollection.verticalSizeClass == .Regular {
            sizeClassLabel.text = "iPhone 竖屏"
        } else if traitCollection.horizontalSizeClass == .Regular && traitCollection.verticalSizeClass == .Compact {
            sizeClassLabel.text = "iPhone 6+ 横屏"
        } else {
            sizeClassLabel.text = "未知"
        }
        
        switch traitCollection.forceTouchCapability {
        case .Available: result = "支持压感"
        case .Unavailable: result = "不支持压感"
        case .Unknown: result = "未知"
        }
        forceTouchLabel.text = result
    }
}

// MARK: - UITraitEnvironment protocol
extension ViewController {
    override func traitCollectionDidChange(previousTraitCollection: UITraitCollection?) {
        showTraitCollectionInfo()
    }
}

