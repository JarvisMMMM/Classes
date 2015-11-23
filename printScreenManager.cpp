//
//  PrintScreenManager.cpp
//  testgame
//
//  Created by apple13 on 14-10-10.
//
//

#include "PrintScreenManager.h"
#include "GameBGLayer.h"
#include "GameData.h"
#include "GameOther.h"
#include "GameScene.h"
//#include "GameCoreLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

static PrintScreenManager* instance = 0;
PrintScreenManager* PrintScreenManager::getInstance()
{
    if(!instance)
        instance = new PrintScreenManager();
    return instance;
}

Node* PrintScreenManager::printScreen()
{
    _is_save = false;
    if(!_pRender)
    {
        _pRender = RenderTexture::create(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height, Texture2D::PixelFormat::RGBA8888);
        _pRender->retain();
    }
//    Sprite* __bg = Sprite::create("panZi_zhiLiao.png");
//    __bg->setScale(GameOther::getWindowSmallScale());
//    __bg->setAnchorPoint(Vec2(0.5f, 0));
//    __bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 0));
    
//    Sprite* __title = Sprite::create("title.png");
//    __title->setScale(GameOther::getWindowSmallScale());
//    __title->setAnchorPoint(Vec2(0.5f, 0.5f));
//    __title->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, __bg->getContentSize().height * __bg->getScaleY() / 2));
    
    _pRender->begin();
//    GameBGLayer::gameBGLayer->visit();
    GameScene::gameScene->menuLayerInstance->setVisible(false);
    GameScene::gameScene->visit();
//    GameCoreLayer::getInstance()->visit();
//    __bg->visit();
//    __title->visit();
    _pRender->end();

    GameScene::gameScene->menuLayerInstance->setVisible(true);
    return _pRender;
}

void PrintScreenManager::savePrintScreen()
{
    _flag = SAVE;
    this->beginSavePrintScreen();
}

void PrintScreenManager::sharePrintScreen()
{
    _flag = SHARE;
    this->beginSavePrintScreen();
}

void PrintScreenManager::sendEmailPrintScreen()
{
    _flag = SEND;
    this->beginSavePrintScreen();
}

void PrintScreenManager::beginSavePrintScreen()
{
    if(!_is_save)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        JniMethodInfo t;
        
        std::string ret("");
        if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "getSDPictures", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            
            t.env->DeleteLocalRef(t.classID);
            ret = JniHelper::jstring2string(str);
            _pRender->printSaveToFile(ret, Image::Format::PNG, true);
            t.env->DeleteLocalRef(str);
        }
#endif
    }
    
    Director::getInstance()->getRunningScene()->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(PrintScreenManager::savePrintScreening, this)), NULL));
    _is_save = true;
}

void PrintScreenManager::savePrintScreening()
{
    if(_flag == SAVE)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo jni_method_info;
        if (JniHelper::getStaticMethodInfo(jni_method_info, "org/cocos2dx/lib/Cocos2dxHelper", "savePrintScreen", "()V")) {
            jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
        }
#endif
    }
    if(_flag == SHARE)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo jni_method_info;
        if (JniHelper::getStaticMethodInfo(jni_method_info, "org/cocos2dx/lib/Cocos2dxHelper", "sharePrintScreen", "()V")) {
            jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
        }
#endif
    }
    if(_flag == SEND)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo jni_method_info;
        if (JniHelper::getStaticMethodInfo(jni_method_info, "org/cocos2dx/lib/Cocos2dxHelper", "sendEmailPrintScreen", "()V")) {
            jni_method_info.env->CallStaticVoidMethod(jni_method_info.classID, jni_method_info.methodID);
        }
#endif
    }
}
