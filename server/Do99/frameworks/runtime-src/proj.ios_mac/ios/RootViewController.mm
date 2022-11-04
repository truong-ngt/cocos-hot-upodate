/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"

#import "SSKeychain.h"
#import "SSKeychainQuery.h"
#import "ObjCToJavaScriptBridge.h"
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import <AdSupport/AdSupport.h>

static RootViewController *_instance;
@implementation RootViewController
UIToolbar* toolbar;
UIDatePicker* picker;


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        _instance = self;
//        CGRect screenRect = [[UIScreen mainScreen] bounds];
//        CGFloat screenWidth = screenRect.size.width;
//        CGFloat screenHeight = screenRect.size.height;
//        _viewForDatePicker = [[UIView alloc]initWithFrame:CGRectMake(0, 0, screenWidth, screenHeight)];
//        _viewForDatePicker.hidden = YES;
//        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(dismissKeyboard)];
//
//        [_viewForDatePicker addGestureRecognizer:tap];
//
//        _datepicker = [[UIDatePicker alloc]initWithFrame:CGRectMake(0, screenHeight - 100, screenWidth, 100)];
//        _datepicker.backgroundColor = [UIColor whiteColor];
//        _datepicker.datePickerMode = UIDatePickerModeDate;
//        _datepicker.hidden = NO;
//        _datepicker.date = [NSDate date];
//        [_datepicker addTarget:self action:@selector(onDatePickerValueChanged:) forControlEvents:UIControlEventValueChanged];
//        [_viewForDatePicker addSubview:_datepicker];
//        [_instance.view addSubview:_viewForDatePicker];
    }
    return self;
}

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    // Initialize the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    // Set EAGLView as view of RootViewController
    self.view = eaglView;
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}


// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
#ifdef __IPHONE_6_0
- (NSUInteger) supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskAllButUpsideDown;
}
#endif

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (__bridge CCEAGLView *)glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden {
    return YES;
}

// Controls the application's preferred home indicator auto-hiding when this view controller is shown.
// (better use preferredScreenEdgesDeferringSystemGestures for controlling the home indicator)
- (BOOL)prefersHomeIndicatorAutoHidden {
    return NO;
}

// HOME Indicator need to be tapped twice 
-(UIRectEdge)preferredScreenEdgesDeferringSystemGestures
{
    return UIRectEdgeBottom; 
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

/*
 --------------------------------------------------------
 GET DEVICE ID
 --------------------------------------------------------
 */

+ (NSString *)getDeviceID
{
    NSString *appName=@"Do99";
    
    NSString *strApplicationUUID = [SSKeychain passwordForService:appName account:@"Do99"];
    if (strApplicationUUID == nil)
    {
        strApplicationUUID  = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
        [SSKeychain setPassword:strApplicationUUID forService:appName account:@"Do99"];
    }
    return strApplicationUUID;
}

/*
 --------------------------------------------------------
 Date piker
 --------------------------------------------------------
 */

+ (BOOL)showDatePicker
{
    [_instance showDatePicker];
    return TRUE;
}

- (void)showDatePicker
{
    picker = [[UIDatePicker alloc] init];
        picker.backgroundColor = [UIColor whiteColor];
        [picker setValue:[UIColor blackColor] forKey:@"textColor"];

        picker.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        picker.datePickerMode = UIDatePickerModeDate;

        [picker addTarget:self action:@selector(dueDateChanged:) forControlEvents:UIControlEventValueChanged];
        picker.frame = CGRectMake(0.0, [UIScreen mainScreen].bounds.size.height - 350, [UIScreen mainScreen].bounds.size.width, 350);
        [self.view addSubview:picker];

        toolbar = [[UIToolbar alloc]initWithFrame:CGRectMake(0, [UIScreen mainScreen].bounds.size.height - 350, [UIScreen mainScreen].bounds.size.width, 150)];
        toolbar.barStyle = UIBarStyleBlackTranslucent;
        toolbar.items = @[[[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil], [[UIBarButtonItem alloc]initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(onDoneButtonClick)]];
        [toolbar sizeToFit];
        [self.view addSubview:toolbar];
}

-(void) dueDateChanged:(UIDatePicker *)datePicker {
    
        NSCalendar *calendar = [NSCalendar autoupdatingCurrentCalendar];
        NSDate *currDate = datePicker.date;
    NSDateComponents *dComp = [calendar components:( NSCalendarUnitYear | NSCalendarUnitMonth |  NSCalendarUnitDay ) fromDate:currDate];
    NSString * year = [NSString stringWithFormat:@"%ld",(long)[dComp year]];
    NSString * month = [NSString stringWithFormat:@"%ld",(long)[dComp month]];
    NSString * day = [NSString stringWithFormat:@"%ld",(long)[dComp day]];
        NSString *message = [NSString stringWithFormat:@"{\"Year\":\"%@\", \"Month\":\"%@\", \"Day\":\"%@\"}",year, month, day];
        NSString *ggMsg = [NSString stringWithFormat:@"GateNativeBridge.onDatePicker('%@')",message];
        const char* msg2Js = [ggMsg cStringUsingEncoding:NSUTF8StringEncoding];
    
        evalString(msg2Js);
}

-(void)onDoneButtonClick {
    [toolbar removeFromSuperview];
    [picker removeFromSuperview];
}

/*
 --------------------------------------------------------
 OPEN URL
 --------------------------------------------------------
 */
+ (BOOL)openURL: (NSString*) url
{
    return [_instance openURL: url];
}

- (bool)openURL:(NSString*)url
{
    NSURL *URL = [NSURL URLWithString:url];
    
    if (URL) {
        if ([SFSafariViewController class] != nil) {
            SFSafariViewController *sfvc = [[SFSafariViewController alloc] initWithURL:URL];
            sfvc.delegate = self;
            [self presentViewController:sfvc animated:YES completion:nil];
        } else {
            if (![[UIApplication sharedApplication] openURL:URL]) {
                return FALSE;
            }
        }
    } else {
        return FALSE;
    }
    
    return TRUE;
}

/*
 --------------------------------------------------------
 OPEN FACEBOOK PAGE
 --------------------------------------------------------
 */
+ (bool)openFacebookLink1:(NSString*)linkOpenInApp Link2: (NSString*)url{
    [_instance openFacebookLink1:linkOpenInApp Link2:url];
    return TRUE;
}

- (bool)openFacebookLink1:(NSString*)linkOpenInApp Link2: (NSString*)url
{
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"fb://"]]) {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:linkOpenInApp]];
    }
    else {
        return [self openURL:url];
    }
    
    return TRUE;
}

/*
 --------------------------------------------------------
 Copy To ClipBoard
 --------------------------------------------------------
 */
+ (BOOL)copyToClipboard: (NSString*) content
{
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    pasteboard.string = content;
    return TRUE;
}

/*
 --------------------------------------------------------
 AppsFlyer
 --------------------------------------------------------
 */

//+ (void) initAppsFlyer :(NSString*)devKey appId: (NSString*)appId {
//    /** APPSFLYER INIT **/
//    [AppsFlyerLib shared].appsFlyerDevKey =devKey;
//    [AppsFlyerLib shared].appleAppID = appId;
//    [AppsFlyerLib shared].delegate = _instance;
//}
//
//+ (void) trackEventAppsFlyer :(NSString*)eventName appId: (NSString*)eventData {
//    /** APPSFLYER INIT **/
//    NSDictionary *dict = @{eventName:eventData};
//    [[AppsFlyerLib shared] logEvent:eventName withValues:dict];
//}

@end
