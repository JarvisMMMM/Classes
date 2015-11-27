//
//  GameBGLayer.cpp
//  BabyGrow
//
//  Created by apple12 on 15/3/19.
//
//

#include "GameBGLayer.h"
#include"cocostudio/CocoStudio.h"
#include "GameReaderManager.h"
#include "MenuLayer.h"
#include "GameOther.h"

int GameBGLayer::_houseIndex;
GameBGLayer* GameBGLayer::gameBGLayer = NULL;

bool GameBGLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    string str;
    if(_houseIndex == makeupType)
    {
        str = "bg_makeup.csb";
    }else if(_houseIndex == maskType)
    {
        str = "bg_mask.csb";
    }else if(_houseIndex == dressupType || _houseIndex == showType)
    {
        str = "bg_dressup.csb";
    }else if(_houseIndex == makecardType)
    {
        str = "bg_kapian.csb";
    }else if(_houseIndex == makesnowmanType)
    {
        str = "bg_snowman.csb";
    }else if(_houseIndex == makesleepType)
    {
        str = "bg_shuijiao_zhu.csb";
    }else if(_houseIndex == makechristmasType)
    {
        str = "bg_snowman.csb";
    }
   
    Node* bg = GameReaderManager::getNodeReaderFile(str.c_str(), CENTER, 1);
    this->addChild(bg);
    bg->setTag(1);
    
    gameBGLayer = NULL;
    gameBGLayer = this;
    if(_houseIndex == dressupType || _houseIndex == showType)
    {
//        dressupAnimation();
    }
    return true;
}

Node *GameBGLayer::create(int houseIndex)
{
    _houseIndex = houseIndex;
    Node* layer = GameBGLayer::create();
    return layer;
}

void GameBGLayer::onEnter()
{
    auto dispatch = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameBGLayer::onTouchBegan, this);
    dispatch->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Layer::onEnter();
}

void GameBGLayer::onExit()
{
    
    CCLOG("BGLayer 74");
    Layer::onExit();
}

void GameBGLayer::dressupAnimation()
{
    Node* node = this->getChildByTag(1)->getChildByName("show");
    cardinalineMove(node, 8, "guiji", "guiji1", "yu2");
    cardinalineMove(node, 13, "guiji2", "guiji3", "yu1");
    ParticleSystemQuad* p = (ParticleSystemQuad*)node->getChildByName("Particle_5");
    p->stopSystem();
    //show
//-----------------------------------
    //dressup
    Node* node1 = this->getChildByTag(1)->getChildByName("dressup");
    cardinalineMove(node1, 8, "guiji2", "guiji3", "yu3");
    cardinalineMove(node1, 13, "guiji4", "guiji5", "yu4");
    
    
    cardinalineMove1(node1, 5, "guiji", "yu1");
    cardinalineMove1(node1, 8, "guiji1", "yu2");
//    ParticleSystemQuad* p1 = (ParticleSystemQuad*)node1->getChildByName("Particle_3_Copy");
//    p1->stopSystem();
//    ParticleSystemQuad* p2 = (ParticleSystemQuad*)node1->getChildByName("Particle_3");
//    p2->stopSystem();
}


void GameBGLayer::setAnimationShow(houseType type)
{
    Node* node = this->getChildByTag(1)->getChildByTag(100);
    node->getChildByName("nanguadeng1_bg_show_dressup")->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.5), DelayTime::create(0.5), FadeIn::create(1.5), DelayTime::create(0.5), NULL)));
    node->getChildByName("nanguadeng2_bg_show_dressup")->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.5), DelayTime::create(0.5), FadeIn::create(1.5), DelayTime::create(0.5), NULL)));
}


void GameBGLayer::cardinalineMove(Node* node, float dtime, const string& guijistr, const string& guiji1str, const string& name)
{
    Node* guiji = node->getChildByName(guijistr);
    Node* yu2 = node->getChildByName(name);
    auto array = PointArray::create(20);
    array->addControlPoint(Vec2(0   , 0));
    array->addControlPoint(Vec2(guiji->getChildren().at(0)->getPositionX() - yu2->getPositionX(),
                                guiji->getChildren().at(0)->getPositionY() - yu2->getPositionY()));
    array->addControlPoint(Vec2(guiji->getChildren().at(1)->getPositionX() - yu2->getPositionX(),
                                guiji->getChildren().at(1)->getPositionY() - yu2->getPositionY()));
    array->addControlPoint(Vec2(guiji->getChildren().at(2)->getPositionX() - yu2->getPositionX(),
                                guiji->getChildren().at(2)->getPositionY() - yu2->getPositionY()));
    auto action = CardinalSplineBy::create(dtime, array, 0);
    action->setTag(10);
    Vec2 vec = Vec2(guiji->getChildren().at(2)->getPositionX(),
                    guiji->getChildren().at(2)->getPositionY());
    Node* guiji1 = node->getChildByName(guiji1str);
    auto array1 = PointArray::create(20);
    
    array1->addControlPoint(Vec2(0   , 0));
    array1->addControlPoint(Vec2(guiji1->getChildren().at(0)->getPositionX() - vec.x,
                                 guiji1->getChildren().at(0)->getPositionY() - vec.y));
    array1->addControlPoint(Vec2(guiji1->getChildren().at(1)->getPositionX() - vec.x,
                                 guiji1->getChildren().at(1)->getPositionY() - vec.y));
    array1->addControlPoint(Vec2(guiji1->getChildren().at(2)->getPositionX() - vec.x,
                                 guiji1->getChildren().at(2)->getPositionY() - vec.y));
    auto action1 = CardinalSplineBy::create(dtime, array1, 0);
    
    yu2->runAction(RepeatForever::create(Sequence::create(action, CallFunc::create([=](){
        yu2->setScaleX(-yu2->getScaleX());
    }), action1, CallFunc::create([=](){
        yu2->setScaleX(-yu2->getScaleX());
    }),  NULL)));
//    yu2->runAction(RepeatForever::create(Sequence::create(action, ScaleTo::create(0.2, -yu2->getScaleX(), yu2->getScaleY()), action1, ScaleTo::create(0.2, -yu2->getScaleX(), yu2->getScaleY()),  NULL)));
}

void GameBGLayer::cardinalineMove1(Node* parent, float dtime, const string& guijistr, const string& name)
{
    Node* yu1 = parent->getChildByName(name);
    Vec2 hudie1Vec = yu1->getPosition();
    Node* guiji = parent->getChildByName(guijistr);
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(guiji->getChildren().at(0)->getPositionX() - yu1->getPositionX(),
                                guiji->getChildren().at(0)->getPositionY() - yu1->getPositionY()));
    array->addControlPoint(Vec2(guiji->getChildren().at(1)->getPositionX() - yu1->getPositionX(),
                                guiji->getChildren().at(1)->getPositionY() - yu1->getPositionY()));
    array->addControlPoint(Vec2(guiji->getChildren().at(2)->getPositionX() - yu1->getPositionX(),
                                guiji->getChildren().at(2)->getPositionY() - yu1->getPositionY()));
    auto action = CardinalSplineBy::create(dtime, array, 0);
    action->setTag(10);
    yu1->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(3), CallFunc::create([=](){
        yu1->setPosition(hudie1Vec);
    }),  NULL)));
}

bool GameBGLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}