//
//  ShowMediator.cpp
//  meijia
//
//  Created by apple12 on 15/9/8.
//
//

#include "ShowMediator.h"
#include "GameScene.h"
#include "GameMain.h"

#define XIEDI_ZODER         -1
#define WENSHEN_ZODER       1
#define JIAOLIAN_ZODER      2
#define XIEMIAN_ZODER       3
#define MEIJIA_ZODER        4

void ShowMediator::onRun()
{
    initData();
}

void ShowMediator::initData()
{
    Node* _nodeUI = GameMain::gameMainInstance->makeUpNode;
    Node* _nodeUI1 = GameMain::gameMainInstance->makeUpNode1;
    _nodeUI->getChildByName("mask")->setVisible(false);
    _nodeUI->getChildByName("chushizhija")->setVisible(false);
    _nodeUI->getChildByName("xiujianhouzhijia")->setVisible(true);
    for(int i = 0; i < _nodeUI->getChildByName("xiujianhouzhijia")->getChildrenCount(); i++)
    {
        _nodeUI->getChildByName("xiujianhouzhijia")->getChildren().at(i)->setVisible(true);
    }
    _nodeUI1->getChildByName("mask")->setVisible(false);
    _nodeUI1->getChildByName("chushizhija")->setVisible(false);
    _nodeUI1->getChildByName("xiujianhouzhijia")->setVisible(true);
    for(int i = 0; i < _nodeUI1->getChildByName("xiujianhouzhijia")->getChildrenCount(); i++)
    {
        _nodeUI1->getChildByName("xiujianhouzhijia")->getChildren().at(i)->setVisible(true);
    }

    char zhuangshistr[40];
    string str;
//    if(GameData::getInstance()->getLeftZhijia() != -1)
//    {
//        DropMediator::_curListType = listType_meijia;
//        sprintf(zhuangshistr, "nailart%d_lxy.png", GameData::getInstance()->getLeftZhijia());
//        str = "meijia";
//        setPeishi(_nodeUI, zhuangshistr, str, MEIJIA_ZODER);
//    }
//    if(GameData::getInstance()->getLeftJiaolian() != -1)
//    {
//        DropMediator::_curListType = listType_jiaolian;
//        sprintf(zhuangshistr, "handcarenary%d_lxy.png", GameData::getInstance()->getLeftJiaolian());
//        str = "handcarenary";
//        setPeishi(_nodeUI, zhuangshistr, str, JIAOLIAN_ZODER);
//    }
//    if(GameData::getInstance()->getLeftWenshen() != -1)
//    {
//        DropMediator::_curListType = listType_wenshen;
//        sprintf(zhuangshistr, "handtattoo%d_lxy.png", GameData::getInstance()->getLeftWenshen());
//        str = "wenshen";
//        setPeishi(_nodeUI, zhuangshistr, str, WENSHEN_ZODER);
//    }
//    if(GameData::getInstance()->getLeftXie() != -1)
//    {
//        DropMediator::_curListType = listType_xiezi;
//        sprintf(zhuangshistr, "shose%d_1_makeup.png", GameData::getInstance()->getLeftXie());
//        str = "shose_di";
//        Sprite* toushNode = Sprite::create(zhuangshistr);
//        _nodeUI->addChild(toushNode, -1);
//        toushNode->setPosition(_nodeUI->getChildByName(str)->getPosition());
//        
//        sprintf(zhuangshistr, "shose%d_2_makeup.png", GameData::getInstance()->getLeftXie());
//        str = "shose_mian";
//        setPeishi(_nodeUI, zhuangshistr, str, XIEMIAN_ZODER);
//    }
//    if(GameData::getInstance()->getRightZhijia() != -1)
//    {
//        DropMediator::_curListType = listType_meijia;
//        sprintf(zhuangshistr, "nailart%d_lxy.png", GameData::getInstance()->getRightZhijia());
//        str = "meijia";
//        setPeishi(_nodeUI1, zhuangshistr, str, MEIJIA_ZODER);
//    }
//    if(GameData::getInstance()->getRightJiaolian() != -1)
//    {
//        DropMediator::_curListType = listType_jiaolian;
//        sprintf(zhuangshistr, "handcarenary%d_lxy.png", GameData::getInstance()->getRightJiaolian());
//        str = "handcarenary";
//        setPeishi(_nodeUI1, zhuangshistr, str, JIAOLIAN_ZODER);
//    }
//    if(GameData::getInstance()->getRightWenshen() != -1)
//    {
//        DropMediator::_curListType = listType_wenshen;
//        sprintf(zhuangshistr, "handtattoo%d_lxy.png", GameData::getInstance()->getRightWenshen());
//        str = "wenshen";
//        setPeishi(_nodeUI1, zhuangshistr, str, WENSHEN_ZODER);
//    }
//    if(GameData::getInstance()->getRightXie() != -1)
//    {
//        DropMediator::_curListType = listType_xiezi;
//        sprintf(zhuangshistr, "shose%d_1_makeup.png", GameData::getInstance()->getRightXie());
//        str = "shose_di";
//        Sprite* toushNode = Sprite::create(zhuangshistr);
//        _nodeUI1->addChild(toushNode, -1);
//        toushNode->setPosition(_nodeUI1->getChildByName(str)->getPosition());
//        
//        sprintf(zhuangshistr, "shose%d_2_makeup.png", GameData::getInstance()->getRightXie());
//        str = "shose_mian";
//        setPeishi(_nodeUI1, zhuangshistr, str, XIEMIAN_ZODER);
//    }
}

void ShowMediator::setPeishi(Node* parent, const string& toushistr, const string& str, int pzorder)
{
    Sprite* toushNode = Sprite::create(toushistr);
    parent->addChild(toushNode, pzorder);
    toushNode->setPosition(parent->getChildByName("makeup")->getChildByName(str)->getPosition());
//    if(DropMediator::_curListType == listType_meijia)
//    {
//        parent->getChildByName("xiujianhouzhijia")->setVisible(false);
//    }
}

void ShowMediator::onAddZhijia(vector<RenderTexture*> *tempVector, Node* parent)
{
    log("asdddd");
    float scales[] = {0.226, 0.146, 0.146, 0.136, 0.11};
    float rotations[] = {-8, -8, -4, 1, 8};
    for(int i = 0; i < tempVector->size(); i++)
    {
        vector<RenderTexture*> *v = tempVector;
        if(v->at(i))
        {
            Node* node = parent->getChildByName("xiujianhouzhijia")->getChildren().at(i);
            parent->getChildByName("xiujianhouzhijia")->setVisible(true);
            Node* child = node->getChildren().at(0);
            Node* positionChild = node->getChildren().at(1);
            auto pNode = v->at(i);
            positionChild->addChild(pNode);
            pNode->setAnchorPoint(Vec2(0.5f, 0.0f));
            //            pNode->setPosition(Vec2(child->getPositionX() - 0.5f, child->getPositionY() - 0.5f));
            pNode->setScale(scales[i] / parent->getScaleX(), scales[i] / parent->getScaleX());
            //            pNode->setPositionX(child->getPositionX() - 0.5f);
            log("scaleXXX: %f, scaleYYY: %f", child->getPositionX(), child->getPositionY());
            //            pNode->setRotation(rotations[i]);
            
            pNode->setPositionY(child->getContentSize().height/2 +  Director::getInstance()->getWinSize().height / 2 * pNode->getScaleY() - 513.0f * GameOther::getWindowSmallScale() * pNode->getScaleY());
            child->removeFromParent();
        }
        
    }
    
}

void ShowMediator::onEnter()
{
    onRun();
    ButtonMediator::onEnter();
}

void ShowMediator::onExit()
{
    GameOther::clearEffect();
    ButtonMediator::onExit();
}

bool ShowMediator::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    return false;
}
void ShowMediator::onTouchMoved(Touch* touch, Event* event)
{
    
}
void ShowMediator::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}
void ShowMediator::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}