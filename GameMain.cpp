//
//  GameMain.cpp
//  Marry
//
//  Created by apple12 on 15/6/2.
//
//

#include "GameMain.h"
#include "GameReaderManager.h"
#include "GameScene.h"
#include "GameOther.h"

GameMain* GameMain::gameMainInstance = NULL;

bool GameMain::init()
{
    if(!Layer::init())
    {
        return false;
    }
    _type = GameScene::_houseIndex;
    if(_type == maskType)
    {
        makeUpNode = GameReaderManager::getNodeReaderFile("mask.csb", CENTER, 0);
        this->addChild(makeUpNode);
    }else if(_type == makeupType)
    {

        makeUpNode = GameReaderManager::getNodeReaderFile("makeup.csb", CENTER, 0);
        this->addChild(makeUpNode);
    }else if(_type == dressupType)
    {
        makeUpNode = GameReaderManager::getNodeReaderFile("dressup.csb", CENTER, 1);
        this->addChild(makeUpNode);
    }else if(_type == makecardType)
    {
        makeUpNode = GameReaderManager::getNodeReaderFile("kapian.csb", CENTER, 0);
        this->addChild(makeUpNode);
        makeUpNode1 = GameReaderManager::getNodeReaderFile("kapian_ui.csb", CENTER, 0);
        this->addChild(makeUpNode1);
        
    }else if(_type == makesnowmanType)
    {
        makeUpNode = GameReaderManager::getNodeReaderFile("snowman.csb", CENTER, 0);
        this->addChild(makeUpNode);
        makeUpNode1 = GameReaderManager::getNodeReaderFile("snowman_ui.csb", CENTER, 0);
        this->addChild(makeUpNode1);
        
    }
    
    
    gameMainInstance = this;
    return true;
}

bool GameMain::onTouchBegan(Touch* touch, Event* event)
{
    return false;
}

void GameMain::Renwuzhengyan()
{
    Node* body = makeUpNode;
    body->getChildByName("biyan_mask")->setVisible(false);
}
void GameMain::RenwuBiyan()
{
    Node* body = makeUpNode;
    body->getChildByName("biyan_mask")->setVisible(true);
}