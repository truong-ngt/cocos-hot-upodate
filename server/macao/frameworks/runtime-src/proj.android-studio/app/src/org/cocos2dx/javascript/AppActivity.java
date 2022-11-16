/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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
package org.cocos2dx.javascript;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxJavascriptJavaBridge;

import android.bluetooth.BluetoothAdapter;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;

import android.content.Intent;
import android.content.res.Configuration;
import android.provider.Settings;
import android.util.Base64;
import android.util.Log;
import android.view.WindowManager;


import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class AppActivity extends com.sdkbox.plugin.SDKBoxActivity {

    public static AppActivity activity;
    public static final String GAME_TAG = "GAME_TAG";
    private static ClipboardManager clipboardManager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        activity = AppActivity.this;
        clipboardManager = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // DO OTHER INITIALIZATION BELOW
        SDKWrapper.getInstance().init(this);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        printHashkey();
    }

    @Override
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        SDKWrapper.getInstance().setGLSurfaceView(glSurfaceView, this);

        return glSurfaceView;
    }

    @Override
    protected void onResume() {
        super.onResume();
        SDKWrapper.getInstance().onResume();

    }

    @Override
    protected void onPause() {
        super.onPause();
        SDKWrapper.getInstance().onPause();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        SDKWrapper.getInstance().onDestroy();

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        SDKWrapper.getInstance().onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        SDKWrapper.getInstance().onNewIntent(intent);
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        SDKWrapper.getInstance().onRestart();
    }

    @Override
    protected void onStop() {
        super.onStop();
        SDKWrapper.getInstance().onStop();
    }

    @Override
    public void onBackPressed() {
        SDKWrapper.getInstance().onBackPressed();
        super.onBackPressed();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        SDKWrapper.getInstance().onConfigurationChanged(newConfig);
        super.onConfigurationChanged(newConfig);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        SDKWrapper.getInstance().onRestoreInstanceState(savedInstanceState);
        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        SDKWrapper.getInstance().onSaveInstanceState(outState);
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onStart() {
        SDKWrapper.getInstance().onStart();
        super.onStart();
    }

    public static void openApp(String appPackage) {
        if (checkExistApk(appPackage)) {
            openAPK(appPackage);
            activity.finish();
        } else {
            openMarket(appPackage);
        }
    }

    public static void openMarket(String appPackage) {
        Log.d(GAME_TAG, "openMarket");
        String packageName = appPackage;
        if(appPackage == null || appPackage.length() == 0)
            packageName = getPackegeName();

        try {
            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + packageName));
            activity.startActivity(intent);
        } catch (Exception e) {
            StringBuilder url = new StringBuilder("https://play.google.com/store/apps/details?id=");
            url.append(packageName);
            openURL(url.toString());
        }
    }

    public static boolean checkExistApk(String packApp) {
        PackageManager pm = activity.getPackageManager();
        boolean app_installed = false;
        try {
            pm.getPackageInfo(packApp, PackageManager.GET_ACTIVITIES);
            app_installed = true;
        } catch (PackageManager.NameNotFoundException e) {
            app_installed = false;
        }

        return app_installed;
    }

    public static void openAPK(String packApp) {
        Intent intent = activity.getPackageManager().getLaunchIntentForPackage(packApp);
        activity.startActivity(intent);
    }

    public static void sendSMS(String phone, String sms) {
        Log.d(GAME_TAG, "sendSMS");
        Intent smsIntent = new Intent(Intent.ACTION_VIEW);
        // Invokes only SMS/MMS clients
        smsIntent.setType("vnd.android-dir/mms-sms");
        // Specify the Phone Number
        smsIntent.putExtra("address", phone);
        // Specify the Message
        smsIntent.putExtra("sms_body", sms);

        // Shoot!
        activity.startActivity(smsIntent);
    }

    public static void openURL(String url) {
        try {
            if (!url.startsWith("http://") && !url.startsWith("https://"))
                url = "http://" + url;

            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
            activity.startActivity(intent);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void openIAP(String accountName, int accountId) {
//		Log.d(GAME_TAG, "openIAP");
//		try {
//			atxi.paymentIAP(activity, accountName, accountId, callback);
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
    }

    //call intent
    public static void callIntent(String _sPhone){
        try {
            Intent callIntent = new Intent(Intent.ACTION_DIAL);
            callIntent.setData(Uri.parse("tel:"+  Uri.encode(_sPhone) ));

            AppActivity.activity.startActivity(callIntent);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String getPackegeName() {
        String packageName = activity.getApplicationContext().getPackageName();
        return packageName;
    }

//    public static void getDeviceID() {
//        TelephonyManager telephonyManager = (TelephonyManager) AppActivity.activity.getSystemService(Context.TELEPHONY_SERVICE);
//        String deviceId = telephonyManager.getDeviceId();
//        Log.d(GAME_TAG, "getDeviceID = " + deviceId);
//        Cocos2dxJavascriptJavaBridge.evalString("Global.nativeBridge.onGetDeviceId('" + deviceId + "')");
//    }

    public static String getMachineInfo()
    {
        String info = "Android" + "|" + Build.VERSION.SDK_INT + "|" + Build.MODEL;
        return info;
    }

    private void copyToClipboard(String text)
    {
        try {
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB) {
                ClipData clip = ClipData.newPlainText("copyText", text);
                clipboardManager.setPrimaryClip(clip);
            } else {
                clipboardManager.setText(text);
            }
        } catch (Exception e) {
            Log.e(GAME_TAG, e.toString());
        }
    }

    private String readClipboard()
    {
        try {
            ClipData abc = clipboardManager.getPrimaryClip();
            ClipData.Item item = abc.getItemAt(0);
            String text = item.getText().toString();
            return text;
        }
        catch (Exception e){
            Log.e(GAME_TAG, e.toString());
        }
        return null;
    }

    public void printHashkey(){
        try {
            String packageName = getApplicationContext().getPackageName();
            Log.d(GAME_TAG, "packageName: " + packageName);
            PackageInfo info = getPackageManager().getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                Log.d("KeyHash:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
            }
        } catch (PackageManager.NameNotFoundException e) {

        } catch (NoSuchAlgorithmException e) {

        }
    }

    public static void copyText(String str){
        try{
            activity.copyToClipboard(str);
			Log.d(GAME_TAG, "copyText: " + str);
        }catch (Exception ex){
            Log.e(GAME_TAG, ex.toString());
        }
    }

    public static String pasteText(){
        try{
            String str = activity.readClipboard();
            return str;
        }catch (Exception ex){
            Log.e(GAME_TAG, ex.toString());
            return "";
        }
    }
	
	public static String getDeviceName(){
        try{
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.append(Build.MANUFACTURER.toUpperCase());
            stringBuilder.append(" ");
            stringBuilder.append(Build.MODEL).append(" ");
            stringBuilder.append(Build.VERSION.RELEASE).append(" ");
            stringBuilder.append(BluetoothAdapter.getDefaultAdapter().getName());
            String str = stringBuilder.toString();
            Log.d(GAME_TAG, "device: " + str);
            return str;
        }catch (Exception ex){
            Log.e(GAME_TAG, ex.toString());
            return "";
        }
    }
	
	public static void setBrightness(int val){
        if(val >= 0 && val <= 255) {
            Settings.System.putInt(
                    activity.getContentResolver(),
                    Settings.System.SCREEN_BRIGHTNESS,
                    val);
        }
    }
}
