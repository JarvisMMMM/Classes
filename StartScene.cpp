//
//  StartScene.cpp
//  BabyGrow
//
//  Created by apple12 on 15/3/18.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define TITLEFALLTIME        0.2
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
#define TITLEFALLTIME        0.2
#else
#define TITLEFALLTIME        0.05
#endif

#include "StartScene.h"
//#include "SelectScene.h"
#include "GameReaderManager.h"
#include "GameOther.h"
#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
#include "ADManager.h"
#include "GameMediator.h"

bool StartScene::_isNoStart;
bool StartScene::isSound = true;

bool StartScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    isTouched = false;
    GameSoundManager::getInstance()->playBgSound(START_BG);
    auto dispatch = Director::getInstance()->getEventDispatcher();
    auto touchLisenter = EventListenerTouchOneByOne::create();
    touchLisenter->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan, this);
    touchLisenter->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved, this);
    touchLisenter->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded, this);
    dispatch->addEventListenerWithSceneGraphPriority(touchLisenter, this);
    
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
    listenerkeyPad->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    bg = GameReaderManager::getNodeReaderFile("bg_start.csb", CENTER, 1);
    this->addChild(bg);
    
    rootNode = GameReaderManager::getNodeReaderFile("start.csb", CENTER, 0);
    this->addChild(rootNode);
    
    titleNode = GameReaderManager::getNodeReaderFile("title.csb", CENTER, 0);
    this->addChild(titleNode);
    initAnimation(bg);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(QIPAO_MP3);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(MIANMO_MP3);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(TIEDONGXI);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(XUANZUAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PENSHUI_MP3);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PAPERDIAPEREFFECT);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BUTTONUPSOUND);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(TAKEPHOTOS);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(PLAY);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(JIANZI_MP3);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FENPU);
    if(_isNoStart)
    {
    	ADManager::hideBanner();
    }
    return true;
}

void StartScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        ADManager::showAlert();
}

bool StartScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void StartScene::onTouchMoved(Touch* touch, Event* event)
{
}

void StartScene::onTouchEnded(Touch* touch, Event* event)
{
    if(GameOther::getIsClickNode(rootNode->getChildByName("begin2_start"), touch->getLocation()) && !isTouched)
    {
        GameSoundManager::getInstance()->playEffect(PLAY);
            isTouched = true;
        rootNode->getChildByName("begin2_start")->runAction(Sequence::create(RotateBy::create(0.5, 360), CallFunc::create([&](){
            GameOther::clearEffect();
            setLoading(this, maskType);
        }), NULL));
        
        //        auto scene = GameScene::createScene(0);
        //        Director::getInstance()->replaceScene(scene);
    }else
    {
        rootNode->getChildByName("begin2_start")->setOpacity(255);
    }
}

void StartScene::setLoading(Node* node, houseType index)
{
    Sprite* __sp = Sprite::create("loading.png");
    __sp->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2,
                           Director::getInstance()->getWinSize().height / 2));
    node->addChild(__sp);
    float __x = Director::getInstance()->getWinSize().width / WINDOW_WIDTH;
    float __y = Director::getInstance()->getWinSize().height / WINDOW_HEIGHT;
    __sp->setScale(__x > __y ? __x : __y);
    __sp->runAction(Sequence::create(DelayTime::create(0.2), CallFunc::create([=](){
        auto scene = GameScene::createScene(index);
        Director::getInstance()->replaceScene(scene);
        GameSoundManager::getInstance()->playBgSound(MAKEUP_BG);
    }), NULL));
}

Scene* StartScene::createScene(bool isStart)
{
    _isNoStart = isStart;
    StartScene* layer = StartScene::create();
    Scene* scene = Scene::create();
    scene->addChild(layer);
    return scene;
}

void StartScene::initAnimation(Node* bg)
{
    auto bg_nanguandeng_start = bg->getChildByName("bg_nanguandeng_start");
    bg_nanguandeng_start->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL)));
    
    Node* biaoti1 = titleNode->getChildByName("biaoti_start");
    Vec2 vec = biaoti1->getPosition();
    biaoti1->setPositionY(Director::getInstance()->getWinSize().height + biaoti1->getContentSize().height/2);
    
    biaoti1->runAction(Sequence::create(EaseBackOut::create(MoveTo::create(0.5, vec)), CallFunc::create([=](){
        schedule(schedule_selector(StartScene::scheduleUpdate1));
    }), NULL));
    
    auto biaoti2 = biaoti1->getChildren().at(0);
    biaoti2->setScale(0);
    biaoti2->runAction(Sequence::create(DelayTime::create(0.5), EaseBackOut::create(ScaleTo::create(1, 1)), NULL));
    
    
    Node* anniu1 = rootNode->getChildByName("begin1_start");
    Node* anniu2 = rootNode->getChildByName("begin2_start");
   
    auto node = rootNode->getChildByName("girl_start");
    Node* __yanpi = GameReaderManager::getNodeFromParent(node, "biyan_start");
    __yanpi->runAction(RepeatForever::create(Sequence::create(Hide::create(),
                                                              DelayTime::create(2.0f),
                                                              Show::create(),
                                                              DelayTime::create(0.1f),
                                                              NULL)));
    
    auto node2 = rootNode->getChildByName("girl2_start");
    Node* __yanpi2 = GameReaderManager::getNodeFromParent(node2, "girl2_biyan_start");
    __yanpi2->runAction(RepeatForever::create(Sequence::create(Hide::create(),
                                                              DelayTime::create(3.0f),
                                                              Show::create(),
                                                              DelayTime::create(0.1f),
                                                              NULL)));
    
//    node->runAction(RepeatForever::create(Sequence::create(MoveBy::create(5, Vec2(0, -10*rootNode->getScale())), MoveBy::create(5, Vec2(0, 10*rootNode->getScale())), NULL)));
    float anniuScale = anniu1->getScale();
    anniu1->setScale(0);
    anniu2->setScale(0);
    
    anniu1->runAction(Sequence::create(DelayTime::create(2), EaseBackOut::create(ScaleTo::create(0.4f, anniuScale)), NULL));
    anniu2->runAction(Sequence::create(DelayTime::create(2), EaseBackOut::create(ScaleTo::create(0.4f, anniuScale)), CallFunc::create([=](){
        schedule(schedule_selector(StartScene::scheduleUpdate));
    }), NULL));
//    ManAction();
    GirlAction();
    GameOther::starEffect(bg, 0.5);
}

void StartScene::ManAction()
{
    Node* __man = GameReaderManager::getNodeFromParent(rootNode, "girl_start");
   Vec2 vec = __man->getPosition();
    __man->setPositionX(__man->getPositionX() + WINDOW_WIDTH*rootNode->getScaleX());
    __man->runAction(Sequence::create(DelayTime::create(1.0f), EaseBackInOut::create(MoveTo::create(1.0f, Vec2(vec.x, __man->getPositionY()))),
                                      NULL));
}

void StartScene::GirlAction()
{
    Node* __girl = GameReaderManager::getNodeFromParent(rootNode, "girl2_start");
    __girl->setPositionX(-__girl->getPositionX());
    __girl->runAction(EaseBackInOut::create(MoveTo::create(1.0f, Vec2(-__girl->getPositionX(), __girl->getPositionY()))));
}

void StartScene::scheduleUpdate1(float dt)
{
    unschedule(schedule_selector(StartScene::scheduleUpdate1));
    Node* biaoti1 = titleNode->getChildByName("biaoti_start");
    Vec2 vec = biaoti1->getPosition();
    auto repeatAction1 = RepeatForever::create(Sequence::create(MoveTo::create(1.5, Vec2(vec.x, vec.y  - 15)), MoveTo::create(1.5, Vec2(vec.x, vec.y + 15)), NULL));
    biaoti1->runAction(repeatAction1);
}

void StartScene::scheduleUpdate(float dt)
{
    Node* anniu1 = rootNode->getChildByName("begin1_start");
    Node* anniu2 = rootNode->getChildByName("begin2_start");
    unschedule(schedule_selector(StartScene::scheduleUpdate));
    float tempScale1 = anniu1->getScale();
    float tempScale2 = anniu2->getScale();
    auto repeatAction3 = RepeatForever::create(Sequence::create(ScaleTo::create(1, tempScale1 + 0.1f), ScaleTo::create(1, tempScale1), NULL));
    auto repeatAction2 = RepeatForever::create(Sequence::create(ScaleTo::create(1, tempScale2 + 0.1f), ScaleTo::create(1, tempScale2), NULL));
    anniu1->runAction(repeatAction3);
    anniu1->runAction(RepeatForever::create(RotateBy::create(5, 360)));
    anniu2->runAction(repeatAction2);
}