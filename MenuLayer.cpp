//
//  MenuLayer.cpp
//  BabyGrow
//
//  Created by apple12 on 15/4/3.
//
//

#include "MenuLayer.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "PrintScreen.h"
#include "DrawImageManager.h"
#include "ADManager.h"
#include "GameScene.h"
#include "MakeUpMediator.h"
#include "DressUpMediator.h"

Sprite* MenuLayer::refreshMenuSprite = NULL;
Sprite* MenuLayer::funcMenuSprite = NULL;
Sprite* MenuLayer::noSoundMenuSprite = NULL;
Sprite* MenuLayer::soundMenuSprite = NULL;
Sprite* MenuLayer::backMenuSprite = NULL;
Sprite* MenuLayer::_backMenuSprite = NULL;
Sprite* MenuLayer::photoMenuSprite = NULL;
Sprite* MenuLayer::starMenuSprite = NULL;
Sprite* MenuLayer::homeMenuSprite = NULL;
Sprite* MenuLayer::XMenuSprite = NULL;
Sprite* MenuLayer::_XMenuSprite = NULL;



MenuLayer::MenuLayer()
{
    winsize = Director::getInstance()->getWinSize();
    refreshMenuSprite = NULL;
    funcMenuSprite = NULL;
    noSoundMenuSprite = NULL;
    soundMenuSprite = NULL;
    photoMenuSprite = NULL;
    starMenuSprite = NULL;
    homeMenuSprite = NULL;
    XMenuSprite = NULL;
    _XMenuSprite = NULL;
    backMenuSprite = NULL;
    _backMenuSprite = NULL;
    isTouch = false;
}
MenuLayer::~MenuLayer()
{
    //    CC_SAFE_FREE(refreshMenuSprite);
    //    CC_SAFE_FREE(funcMenuSprite);
    //    CC_SAFE_FREE(noSoundMenuSprite);
    //    CC_SAFE_FREE(soundMenuSprite);
    //    CC_SAFE_FREE(photoMenuSprite);
    //    CC_SAFE_FREE(starMenuSprite);
    //    CC_SAFE_FREE(homeMenuSprite);
    //    CC_SAFE_FREE(XMenuSprite);
    //    CC_SAFE_FREE(_XMenuSprite);
    //    CC_SAFE_FREE(backMenuSprite);
}

bool MenuLayer::onTouchBegan(Touch* touch, Event* event)
{
    return false;
}

MenuLayer* MenuLayer::create()
{
    
    MenuLayer *ret = new (std::nothrow) MenuLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool MenuLayer::menuButton(Touch* touch, bool isClose, bool hasLeft, bool hasRight)
{
    this->setPositionY(GameScene::menuOffY);
    float dttime = 0.2f;
    float easeElasticTime = 1;
    if(isTouch)
        return false;
    if(isClose)
    {
        if(homeMenuSprite)
        {
            if(GameScene::_houseIndex == dressupType)
                DressUpMediator::dressupMediatorInstance->funcButtonShow();
            XMenuSprite->setVisible(true);
            _XMenuSprite->setVisible(false);
            homeMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
            soundMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
            refreshMenuSprite ->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
            photoMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
            starMenuSprite->runAction(Sequence::create((MoveTo::create(dttime, XMenuSprite->getPosition())), CallFunc::create([=](){
                homeMenuSprite->removeFromParent();
                soundMenuSprite->removeFromParent();
                refreshMenuSprite->removeFromParent();
                photoMenuSprite->removeFromParent();
                starMenuSprite->removeFromParent();
                
                homeMenuSprite = NULL;
                soundMenuSprite = NULL;
                refreshMenuSprite = NULL;
                photoMenuSprite = NULL;
                starMenuSprite = NULL;
                
            }), NULL));
            
            return true;
        }
    }
    
    if(!XMenuSprite)
    {
        if(XMenuSprite)
        {
            if(GameOther::getIsClickNode(XMenuSprite, touch->getLocation()))
            {
                return true;
            }
        }
        
    }else
    {
        if(homeMenuSprite)
        {
            if(GameOther::getIsClickNode(homeMenuSprite, touch->getLocation()))
            {
                GameOther::clearEffect();
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                Scene* scene = StartScene::createScene();
                Director::getInstance()->replaceScene(scene);
                //                GameSoundManager::getInstance()->stopLoopEffect(SLEEP);
                GameSoundManager::getInstance()->stopAllEffect();
                //                if(isSleep)
                //                {
                //                    GameSoundManager::getInstance()->playBgSound(BGSOUND);
                //                }
                return true;
            }else if(GameOther::getIsClickNode(soundMenuSprite, touch->getLocation()))
            {
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                string soundName;
                if(StartScene::isSound)
                {
                    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
                    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);
                    soundName = "anniu6.png";
                }
                else
                {
                    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
                    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
//                                        SimpleAudioEngine::getInstance()->setEffectsVolume();
                    soundName = "anniu5.png";
                }
                StartScene::isSound = !StartScene::isSound;
                Vec2 position = soundMenuSprite->getPosition();
                soundMenuSprite->removeFromParent();
                soundMenuSprite = Sprite::create(soundName);
                this->addChild(soundMenuSprite);
                soundMenuSprite  ->setScale(GameOther::getWindowSmallScale());
                soundMenuSprite->setPosition(position);
                closeMenu();
                return true;
            }else if(GameOther::getIsClickNode(refreshMenuSprite, touch->getLocation()))
            {
                GameData* data = GameData::getInstance();
                data->initData();
                DrawImageManager::_s_instance = NULL;
                GameSoundManager::getInstance()->stopAllEffect();
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                if(GameScene::_houseIndex == showType)
                    GameScene::_houseIndex = dressupType;
                Scene* scene = GameScene::createScene(GameScene::_houseIndex, true);
                Director::getInstance()->replaceScene(scene);
                GameSoundManager::getInstance()->stopAllEffect();
                GameData::refreshInstance();
                if(GameScene::_houseIndex == makeupType)
                    GameScene::refreshAll();
                //                if(isSleep)
                //                {
                //                    GameSoundManager::getInstance()->playBgSound(BGSOUND);
                //                }
                return true;
            }else if(GameOther::getIsClickNode(photoMenuSprite, touch->getLocation()))
            {
                GameSoundManager::getInstance()->playEffect(TAKEPHOTOS);
                auto printScreen = PrintScreen::create();
                GameScene::gameScene->getParent()->addChild(printScreen);
                closeMenu();
                return true;
            }else if(GameOther::getIsClickNode(starMenuSprite, touch->getLocation()))
            {
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                    ADManager::onEvaluation();
                #endif
                closeMenu();
                return true;
            }else if(GameOther::getIsClickNode(backMenuSprite, touch->getLocation()))
            {
                backMenuFunc(backMenuSprite);
                closeMenu();
                return true;
            }else if(GameOther::getIsClickNode(_backMenuSprite, touch->getLocation()))
            {
                _backMenuFunc(_backMenuSprite);
                closeMenu();
                return true;
            }
        }
    }
    
    if(!XMenuSprite)
    {
        XMenuSprite = Sprite::create("anniu3.png");
        this->addChild(XMenuSprite);
		float bannnerADOffY = 0.0f;
		#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    		bannnerADOffY = 100;
        #endif
        XMenuSprite->setPosition(Vec2(XMenuSprite->getContentSize().width/2*GameOther::getWindowSmallScale() + 10, winsize.height - (XMenuSprite->getContentSize().height/2*GameOther::getWindowSmallScale()) - (10 + bannnerADOffY)* Director::getInstance()->getWinSize().height / WINDOW_HEIGHT));
        XMenuSprite->setScale(GameOther::getWindowSmallScale());
        
        _XMenuSprite = Sprite::create("anniu4.png");
        this->addChild(_XMenuSprite);
        _XMenuSprite->setPosition(Vec2(_XMenuSprite->getContentSize().width/2*GameOther::getWindowSmallScale() + 10, XMenuSprite->getPositionY()));
        _XMenuSprite->setScale(GameOther::getWindowSmallScale());
        _XMenuSprite->setVisible(false);
        
        if(hasRight)
        {
            string str;
            str = "anniu2.png";
            
            backMenuSprite = Sprite::create(str);
            this->addChild(backMenuSprite);
            backMenuSprite->setScale(GameOther::getWindowSmallScale());
            backMenuSprite->setPosition(Vec2(winsize.width - backMenuSprite->getContentSize().width/2*backMenuSprite->getScale() - 10 , XMenuSprite->getPositionY()));
            backMenuSprite->runAction(RepeatForever::create(Sequence::create(Repeat::create(Sequence::create(EaseBackOut::create(ScaleTo::create(0.2, 1.1*GameOther::getWindowSmallScale())), EaseBackOut::create(ScaleTo::create(0.2, 1*GameOther::getWindowSmallScale())), NULL), 2), DelayTime::create(5), NULL)));
        }
        
        if(hasLeft)
        {
            string str = "anniu1.png";
            _backMenuSprite = Sprite::create(str);
            this->addChild(_backMenuSprite);
             _backMenuSprite->setScale(GameOther::getWindowSmallScale() );
            float x;
            if(hasRight)
            {
                x = winsize.width - _backMenuSprite->getContentSize().width/2*_backMenuSprite->getScale() - _backMenuSprite->getContentSize().width*_backMenuSprite->getScale() - 10;
            }else
            {
                x = winsize.width - _backMenuSprite->getContentSize().width/2*_backMenuSprite->getScale() - 10;
            }
            _backMenuSprite->setPosition(Vec2(x, XMenuSprite->getPositionY()));
           _backMenuSprite->runAction(RepeatForever::create(Sequence::create(Repeat::create(Sequence::create(EaseBackOut::create(ScaleTo::create(0.2, 1.1*GameOther::getWindowSmallScale())), EaseBackOut::create(ScaleTo::create(0.2, 1*GameOther::getWindowSmallScale())), NULL), 2), DelayTime::create(5), NULL)));
        }
        return true;
        
    }else
    {
        if(GameOther::getIsClickNode(XMenuSprite, touch->getLocation()) || GameOther::getIsClickNode(_XMenuSprite, touch->getLocation()))
        {
            if(homeMenuSprite)
            {
                if(GameScene::_houseIndex == dressupType)
                    DressUpMediator::dressupMediatorInstance->funcButtonShow();
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                XMenuSprite->setVisible(true);
                _XMenuSprite->setVisible(false);
                homeMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
                soundMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
                refreshMenuSprite ->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
                photoMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
                starMenuSprite->runAction(Sequence::create((MoveTo::create(dttime, XMenuSprite->getPosition())), CallFunc::create([=](){
                    homeMenuSprite->removeFromParent();
                    soundMenuSprite->removeFromParent();
                    refreshMenuSprite->removeFromParent();
                    photoMenuSprite->removeFromParent();
                    starMenuSprite->removeFromParent();
                    
                    homeMenuSprite = NULL;
                    soundMenuSprite = NULL;
                    refreshMenuSprite = NULL;
                    photoMenuSprite = NULL;
                    starMenuSprite = NULL;
                    
                }), NULL));
                
                return true;
            }else
            {
                float fixY = 0;
                if(GameScene::_houseIndex == dressupType)
                    DressUpMediator::dressupMediatorInstance->funcButtonHide();
                GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
                XMenuSprite->setVisible(false);
                _XMenuSprite->setVisible(true);
                XMenuSprite->runAction(Sequence::create(ScaleBy::create(dttime, 0.1), ScaleTo::create(dttime, -0.1), ScaleTo::create(dttime, GameOther::getWindowSmallScale()), NULL));
                homeMenuSprite = Sprite::create("anniu10.png");
                this->addChild(homeMenuSprite);
                homeMenuSprite->setPosition(Vec2(XMenuSprite->getPositionX(), XMenuSprite->getPositionY()));
                homeMenuSprite->runAction(EaseElasticOut::create(MoveBy::create(easeElasticTime, Vec2(XMenuSprite->getContentSize().width*GameOther::getWindowSmallScale() + 10, 0)), 0.2));
                homeMenuSprite->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
                string soundName;
                if(StartScene::isSound)
                    soundName = "anniu5.png";
                else
                    soundName = "anniu6.png";
                soundMenuSprite = Sprite::create(soundName);
                this->addChild(soundMenuSprite);
                soundMenuSprite->setPosition(Vec2(XMenuSprite->getPositionX(), XMenuSprite->getPositionY()));
                soundMenuSprite->runAction(EaseElasticOut::create(MoveBy::create(easeElasticTime, Vec2(0, -(XMenuSprite->getContentSize().height*GameOther::getWindowSmallScale() + 10 + fixY*GameOther::getWindwoHeightScale()))), 0.2));
                soundMenuSprite->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
                
                refreshMenuSprite = Sprite::create("anniu7.png");
                this->addChild(refreshMenuSprite);
                refreshMenuSprite->setPosition(Vec2(XMenuSprite->getPositionX(), XMenuSprite->getPositionY()));
                refreshMenuSprite->runAction(EaseElasticOut::create(MoveBy::create(easeElasticTime, Vec2(0, -2*(XMenuSprite->getContentSize().height*GameOther::getWindowSmallScale() + 10 + fixY*GameOther::getWindwoHeightScale()))), 0.2));
                refreshMenuSprite->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
                
                photoMenuSprite = Sprite::create("anniu8.png");
                this->addChild(photoMenuSprite);
                photoMenuSprite->setPosition(Vec2(XMenuSprite->getPositionX(), XMenuSprite->getPositionY()));
                photoMenuSprite->runAction(EaseElasticOut::create(MoveBy::create(easeElasticTime, Vec2(0, -3*(XMenuSprite->getContentSize().height*GameOther::getWindowSmallScale() + 10 + fixY*GameOther::getWindwoHeightScale()))), 0.2));
                photoMenuSprite->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
                
                
                starMenuSprite = Sprite::create("anniu9.png");
                this->addChild(starMenuSprite);
                starMenuSprite->setPosition(Vec2(XMenuSprite->getPositionX(), XMenuSprite->getPositionY()));
                starMenuSprite->runAction(EaseElasticOut::create(MoveBy::create(easeElasticTime, Vec2(0, -4*(XMenuSprite->getContentSize().height*GameOther::getWindowSmallScale() + 10 + fixY*GameOther::getWindwoHeightScale()))), 0.2));
                starMenuSprite->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                starMenuSprite->setVisible(false);
#endif
                return true;
            }
            
            return true;
        }else if(GameOther::getIsClickNode(backMenuSprite, touch->getLocation()))
        {
            backMenuFunc(backMenuSprite);
            return true;
        }else if(GameOther::getIsClickNode(_backMenuSprite, touch->getLocation()))
        {
            _backMenuFunc(_backMenuSprite);
            return true;
        }
    }
    return false;
}

void MenuLayer::backMenuFunc(Node* node)
{
    node->runAction(ScaleTo::create(0.2, 0.9*GameOther::getWindowSmallScale()));
    GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
    if(GameScene::_houseIndex == maskType)
    {
        GameScene::setLoading(GameScene::gameScene, makeupType);
    }else if(GameScene::_houseIndex == makeupType)
    {
        MakeUpMediator::makeupMediatorInstance->decodePrintScreenFace();
        GameScene::setLoading(GameScene::gameScene, dressupType);
    }else if(GameScene::_houseIndex == dressupType)
    {
        GameSoundManager::getInstance()->playBgSound(SHOW_BG);
        GameScene::gameScene->showRoom();
    }
}

void MenuLayer::_backMenuFunc(Node* node)// towards left
{
    node->runAction(ScaleTo::create(0.2, 0.9*GameOther::getWindowSmallScale()));
    GameSoundManager::getInstance()->playEffect(BUTTONUPSOUND);
    if(GameScene::_houseIndex == showType)
    {
        GameSoundManager::getInstance()->playBgSound(MAKEUP_BG);
        GameScene::gameScene->dressupRoom();
    }
    if(GameScene::_houseIndex == dressupType)
    {
        
        GameScene::setLoading(GameScene::gameScene, makeupType);
    }else if(GameScene::_houseIndex == makeupType)
    {
        ADManager::hideBanner();
        GameScene::setLoading(GameScene::gameScene, maskType);
        
    }
}

void MenuLayer::callback()
{
    auto director = Director::getInstance();
    auto scene = GameScene::createScene(dressupType);
    director->replaceScene(scene);
}

void MenuLayer::closeMenu()
{
    if(homeMenuSprite)
    {
        float dttime = 0.2f;
        XMenuSprite->setVisible(true);
        _XMenuSprite->setVisible(false);
        homeMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
        soundMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
        refreshMenuSprite ->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
        photoMenuSprite->runAction((MoveTo::create(dttime, XMenuSprite->getPosition())));
        starMenuSprite->runAction(Sequence::create((MoveTo::create(dttime, XMenuSprite->getPosition())), CallFunc::create([=](){
            if(homeMenuSprite)
            {
                homeMenuSprite->removeFromParent();
                soundMenuSprite->removeFromParent();
                refreshMenuSprite->removeFromParent();
                photoMenuSprite->removeFromParent();
                starMenuSprite->removeFromParent();
            }
            
            homeMenuSprite = NULL;
            soundMenuSprite = NULL;
            refreshMenuSprite = NULL;
            photoMenuSprite = NULL;
            starMenuSprite = NULL;
            
        }), NULL));
    }
}
