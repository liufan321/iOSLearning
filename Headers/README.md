# 新增文件

## UIKit

* NSFileProviderExtension.h
* UIAccessibilityCustomAction.h
* UIAlertController.h
* UIDocumentMenuViewController.h
* UIDocumentPickerExtensionViewController.h
* UIDocumentPickerViewController.h
* UIImageAsset.h
* UIInputViewController.h
* UILexicon.h
* UIPopoverPresentationController.h
* UIPopoverSupport.h
* UIPresentationController.h
* UIPrinter.h
* UIPrinterPickerController.h
* UISearchController.h
* UITraitCollection.h
* UIUserNotificationSettings.h
* UIVisualEffectView.h

共计 18 个

## Foundation

* NSDateComponentsFormatter.h
* NSDateIntervalFormatter.h
* NSEnergyFormatter.h
* NSExtensionContext.h
* NSExtensionItem.h
* NSExtensionRequestHandling.h
* NSItemProvider.h
* NSLengthFormatter.h
* NSMassFormatter.h
* NSUserActivity.h

共计 10 个

## dispatch

* block.h

共计 1 个

## CommonCrypto

* CommonCryptoError.h
* CommonRandom.h

共计 2 个

## 8.2 SDK 差异

### Foundation.framework

#### NSThread.h

新增属性

```
@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0);
```