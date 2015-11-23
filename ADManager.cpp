//
//  androidJNI.cpp
//  dentistsalon
//
//  Created by apple13 on 14/11/26.
//
//

#include "ADManager.h"
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
//#include "GameButtonLayer.h"

void ADManager::showBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "showAdmobJNI", "()V"))
    {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
#endif
}
void ADManager::hideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "hideAdmobJNI", "()V"))
    {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
#endif
}
void ADManager::showCBInterstial()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "showChartBoostJNI", "()V"))
    {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
#endif
}
void ADManager::showAmobInterstial()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "showAdmobInterstitialAdJNI", "()V"))
    {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
#endif
}

void ADManager::showAlert()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "showMessage", "()V"))
    {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
#endif
}

void ADManager::bannerCallBack()
{
    if(GameScene::gameScene && GameScene::gameScene->menuLayerInstance)
    {
        GameScene::gameScene->menuLayerInstance->setPositionY(-120 * Director::getInstance()->getWinSize().height / 1024);
        
        log("callback if");
    }else
    {
        log("callback else");
    }
    GameScene::menuOffY = -120 * Director::getInstance()->getWinSize().height / 1024;
}

extern "C"
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void Java_org_cocos2dx_lib_ADBannerManager_callback(JNIEnv* env, jobject thiz)
    {
        ADManager::bannerCallBack();
    }
#endif
}
void ADManager::onEvaluation()
{
    
}