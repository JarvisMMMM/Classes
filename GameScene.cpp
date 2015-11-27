//
//  BabyBatheMilk.cpp
//  BabyGame
//
//  Created by apple12 on 15/1/8.
//
//

#include "GameScene.h"
#include "GameBGLayer.h"
#include "ButtonMediator.h"
#include "ADManager.h"
#include "ShowMediator.h"
#include "GameEffectLayer.h"
#include "DrawImageManager.h"
#include "MakeUpMediator.h"
#include "MaskMediator.h"
#include "DressUpMediator.h"
#include "MakeCard.h"
#include "MakeSnowMan.h"
#include "MakeAndSleep.h"

#define     LAYER_TAG           1001
#define     YINGHUOCHONG_LIZI       1002

int GameScene::_houseIndex;
GameScene* GameScene::gameScene = NULL;
int GameScene::_babyIndex;
int GameScene::_babyState = -1;
float GameScene::menuOffY = 0.0f;

bool GameScene::isrefresh;

bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    GameScene::initRoomContent();
    return true;
}

void GameScene::onEnter()
{
    auto dispatch = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    dispatch->addEventListenerWithSceneGraphPriority(touchListener, this);

    Layer::onEnter();
}

void GameScene::initRoomContent()
{
    GameMain* gameMediator = NULL;
    bool hasLeft = false;
    bool hasRight = false;
    bg = GameBGLayer::create(_houseIndex);
    this->addChild(bg);
    gameMediator = GameMain::create();
    this->addChild(gameMediator);
    if(_houseIndex == maskType)
    {
        MaskMediator* button = MaskMediator::create();
        button->setPageMaxNum(5);
        this->addChild(button);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setPlayerNode(node);
        hasLeft = false;
        hasRight = true;
//        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=](){
//            ADManager::showBanner();
//            ADManager::showCBInterstial();
//        }), NULL));
        
    }else if(_houseIndex == makeupType)
    {
        MakeUpMediator* button = MakeUpMediator::create();
        button->setPageMaxNum(10);
        this->addChild(button);
        button->setTag(100);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setPlayerNode(node);
        hasLeft = true;
        hasRight = true;
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=](){
            ADManager::showBanner();
            
        }), NULL));
//        ADManager::showAmobInterstial();
    }else if(_houseIndex == dressupType)
    {
//        GameOther::starEffect(bg);
        DressUpMediator* button = DressUpMediator::create();
        button->setPageMaxNum(1);
        this->addChild(button);
        button->setTag(100);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setPlayerNode(node);
        if(grilPosition.x == 0 && grilPosition.y == 0)
            grilPosition = node->getPosition();
//        hasLeft = true;
//        hasRight = true;
//        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=](){
//            ADManager::showBanner();
//            ADManager::showCBInterstial();
//        }), NULL));
    }else if(_houseIndex == makecardType)
    {
        MakeCard* button = MakeCard::create();
        button->setPageMaxNum(1);
        this->addChild(button);
        button->setTag(100);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setReaderUINode(node);
//        hasLeft = true;
//        hasRight = true;
    }else if(_houseIndex == makesnowmanType)
    {
        MakeSnowMan* button = MakeSnowMan::create();
        button->setPageMaxNum(1);
        this->addChild(button);
        button->setTag(100);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setReaderUINode(node);
        //        hasLeft = true;
        //        hasRight = true;
    }else if(_houseIndex == makesleepType)
    {
        MakeAndSleep* button = MakeAndSleep::create();
        button->setPageMaxNum(1);
        this->addChild(button);
        button->setTag(100);
        Node* node = ((GameMain*)gameMediator)->gameMainInstance->makeUpNode;
        button->setReaderUINode(node);
        //        hasLeft = true;
        //        hasRight = true;
    }
    
    createMenuLayer(hasLeft, hasRight);
    GameEffectLayer::_s_instance = NULL;
    GameEffectLayer* __effectLayer = GameEffectLayer::getInstance();
    this->addChild(__effectLayer);

    gameScene = this;
    
}

void GameScene::createMenuLayer(bool hasLeft, bool hasRight)
{
    _hasLeft = hasLeft;
    _hasRight = hasRight;
    menuLayerInstance = (MenuLayer*)MenuLayer::create();
    this->addChild(menuLayerInstance);
    menuLayerInstance->menuButton(NULL, false, hasLeft, hasRight);
}
void GameScene::onExit()
{
    Layer::onExit();
}

Scene* GameScene::createScene(int houseIndex, bool isRefresh)
{
    _houseIndex = houseIndex;
    isrefresh = isRefresh;
    GameScene* layer = GameScene::create();
   
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    return false;
}

void GameScene::refresh()
{
}

void GameScene::refreshAll()
{
//    GameData::getInstance()->setLeftXie(-1);
//    GameData::getInstance()->setLeftJiaolian(-1);
//    GameData::getInstance()->setLeftWenshen(-1);
//    GameData::getInstance()->setLeftZhijia(-1);
//    GameData::getInstance()->setRightXie(-1);
//    GameData::getInstance()->setRightJiaolian(-1);
//    GameData::getInstance()->setRightWenshen(-1);
//    GameData::getInstance()->setRightZhijia(-1);
}

void GameScene::setLoading(Node* node, houseType index)
{
    if(node->getChildByName("setloading"))
    {
        return;
    }
    ADManager::hideBanner();
    Sprite* __sp = Sprite::create("loading.png");
    __sp->setName("setloading");
    __sp->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2,
                           Director::getInstance()->getWinSize().height / 2));
    node->addChild(__sp);
    float __x = Director::getInstance()->getWinSize().width / WINDOW_WIDTH;
    float __y = Director::getInstance()->getWinSize().height / WINDOW_HEIGHT;
    __sp->setScale(__x > __y ? __x : __y);
    __sp->runAction(Sequence::create(DelayTime::create(0.2), CallFunc::create([=](){
        auto scene = GameScene::createScene(index);
        Director::getInstance()->replaceScene(scene);
    }), NULL));
}

void GameScene::showRoom()
{
    if(!this->getChildByTag(LAYER_TAG))
    {
        ADManager::hideBanner();
        auto layerColor = LayerColor::create(ccc4(255, 255, 255, 255),
                                             Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                             Director::getInstance()->getOpenGLView()->getFrameSize().height);
        layerColor->setName("noclick");
        layerColor->setTag(LAYER_TAG);
        this->addChild(layerColor);
        layerColor->setOpacity(0);
        layerColor->runAction(Sequence::create(FadeIn::create(0.5), CallFunc::create([&](){
            GameOther::starEffect(bg);
            _houseIndex = showType;
            GameBGLayer::gameBGLayer->setAnimationShow(showType);
            GameBGLayer::gameBGLayer->getChildByTag(1)->getChildByTag(100)->setVisible(true);
            DressUpMediator::dressupMediatorInstance->_csbNode->setVisible(false);
            DressUpMediator::dressupMediatorInstance->jiaziMoveOut();
            menuLayerInstance->backMenuSprite->setVisible(false);
            backmenuPosition = menuLayerInstance->_backMenuSprite->getPosition();
            menuLayerInstance->_backMenuSprite->setPosition(menuLayerInstance->backMenuSprite->getPosition());
            this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=](){
                ADManager::showBanner();
                ADManager::showCBInterstial();
            }), NULL));
        }), FadeOut::create(0.5), CallFunc::create([=]()mutable{
            layerColor->removeFromParent();
            layerColor = NULL;
        }), NULL));
    }
}

void GameScene::dressupRoom()
{
    if(!this->getChildByTag(LAYER_TAG))
    {
        ADManager::hideBanner();
        auto layerColor = LayerColor::create(ccc4(255, 255, 255, 255),
                                             Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                             Director::getInstance()->getOpenGLView()->getFrameSize().height);
        layerColor->setName("noclick");
        layerColor->setTag(LAYER_TAG);
        this->addChild(layerColor);
        layerColor->setOpacity(0);
        layerColor->runAction(Sequence::create(FadeIn::create(0.5), CallFunc::create([&](){
            if(_houseIndex != showType)
                GameSoundManager::getInstance()->playBgSound(MAKEUP_BG);
            GameOther::clearEffect();
            _houseIndex = dressupType;
//            GameBGLayer::gameBGLayer->setAnimationShow(dressupType);
            GameBGLayer::gameBGLayer->getChildByTag(1)->getChildByTag(100)->setVisible(false);
            DressUpMediator::dressupMediatorInstance->_csbNode->setVisible(true);
            DressUpMediator::dressupMediatorInstance->getPlayerNode()->setPosition(grilPosition);
            DressUpMediator::dressupMediatorInstance->funcButtonShow();
            menuLayerInstance->backMenuSprite->setVisible(true);
            menuLayerInstance->_backMenuSprite->setPosition(backmenuPosition);
            this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=](){
                ADManager::showBanner();
            }), NULL));
        }), FadeOut::create(0.5), CallFunc::create([=]()mutable{
            layerColor->removeFromParent();
            layerColor = NULL;
        }), NULL));
    }
    
}

void GameScene::makeupRoom()
{
    ADManager::hideBanner();
    auto layerColor = LayerColor::create(Color4B::WHITE,
                                         Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                         Director::getInstance()->getOpenGLView()->getFrameSize().height);
    layerColor->setName("noclick");
    GameScene::gameScene->getParent()->addChild(layerColor);
    layerColor->setOpacity(0);
    layerColor->runAction(Sequence::create(FadeTo::create(0.5, 255), CallFunc::create([&](){
        auto director = Director::getInstance();
        auto scene = GameScene::createScene(makeupType);
        director->replaceScene(scene);
    }), FadeOut::create(1), NULL));
}