//
//  PrintScreen.cpp
//  dentist
//
//  Created by apple13 on 14/11/25.
//
//

#include "PrintScreen.h"
#include "GameReaderManager.h"
#include "GameOther.h"
#include "GameMain.h"
#include "PrintScreenManager.h"
//#include "GameUiLayer.h"
#include "ADManager.h"
void PrintScreen::onEnter()
{
	ADManager::hideBanner();
    this->onRun();
    this->setSwallowTouches(true);
    GameMediator::onEnter();
}

void PrintScreen::onExit()
{
	ADManager::showBanner();
	ADManager::showCBInterstial();
    GameMediator::onExit();
}

void PrintScreen::onRun()
{
    Sprite* __bg = Sprite::create("print_bg.png");
    __bg->setAnchorPoint(Vec2(0.5f, 0.5f));
    __bg->setScale(Director::getInstance()->getWinSize().width / __bg->getContentSize().width, Director::getInstance()->getWinSize().height / __bg->getContentSize().height);
    this->addChild(__bg);
    __bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    
    Sprite* __white = Sprite::create("print_white.png");
    __white->setAnchorPoint(Vec2(0.5f, 0.5f));
    __white->setScale(Director::getInstance()->getWinSize().width- (60 * __bg->getScaleX()), Director::getInstance()->getWinSize().height - (60 * __bg->getScaleY()));
    this->addChild(__white);
    __white->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    
    Node* __print = PrintScreenManager::getInstance()->printScreen();
    this->addChild(__print);
    __print->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + (25 * __bg->getScaleY())));
    __print->setScale(0.85f);
    
    _close = Sprite::create("print_close.png");
    _close->setPosition(Vec2(Director::getInstance()->getWinSize().width - (30 * __bg->getScaleX()), Director::getInstance()->getWinSize().height - (30 * __bg->getScaleY())));
    this->addChild(_close);
    
    _email = Sprite::create("print_email.png");
    _email->setAnchorPoint(Vec2(0, 0));
    _email->setPosition(Vec2(60 * __bg->getScaleX(), 45 * __bg->getScaleY()));
    this->addChild(_email);
    
    _fb = Sprite::create("print_facebook.png");
    _fb->setAnchorPoint(Vec2(0.5f, 0));
    _fb->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 45 * __bg->getScaleY()));
    this->addChild(_fb);
    
    _photo = Sprite::create("print_photos.png");
    _photo->setAnchorPoint(Vec2(1, 0));
    _photo->setPosition(Vec2(Director::getInstance()->getWinSize().width - 60 * __bg->getScaleX(), 45 * __bg->getScaleY()));
    this->addChild(_photo);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _fb->setVisible(false);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _fb->setVisible(true);
#endif
}


bool PrintScreen::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(GameOther::getIsClickNode(_close, touch->getLocation()))
    {
//        GameUiLayer::getInstance()->removeSUI(this);
        this->runAction(RemoveSelf::create());
//        this->removeFromParent();
        return true;
    }
    if(GameOther::getIsClickNode(_fb, touch->getLocation()))
    {
        PrintScreenManager::getInstance()->sharePrintScreen();
        return true;
    }
    if(GameOther::getIsClickNode(_photo, touch->getLocation()))
    {
        PrintScreenManager::getInstance()->savePrintScreen();
        return true;
    }
    if(GameOther::getIsClickNode(_email, touch->getLocation()))
    {
        PrintScreenManager::getInstance()->sendEmailPrintScreen();
        return true;
    }
    return false;
}

void PrintScreen::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}

void PrintScreen::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}

void PrintScreen::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}
