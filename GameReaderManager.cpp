//
//  GameReaderManager.cpp
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#include "GameReaderManager.h"
#include "GameOther.h"
Node* GameReaderManager::getNodeReaderFile(const char* fileName, const char* position, int scale)
{
    Node* __node = CSLoader::getInstance()->createNode(fileName);
    if(scale == 0)
        __node->setScale(GameOther::getWindowSmallScale());
    if(scale == 1)
        __node->setScale(GameOther::getWindowBigScale());
    if(scale == 2)
        __node->setScale(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
    if(scale == 3)
        __node->setScale(Director::getInstance()->getWinSize().height / WINDOW_HEIGHT);
    if(scale == 4)
    {
        __node->setScaleX(Director::getInstance()->getWinSize().width / WINDOW_WIDTH);
        __node->setScaleY(Director::getInstance()->getWinSize().height / WINDOW_HEIGHT);
    }
    if(strcmp(position, CENTER) == 0)
    {
        __node->setAnchorPoint(Vec2(0.5f, 0.5f));
        __node->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2,
                                 Director::getInstance()->getWinSize().height / 2));
    }
    else if(strcmp(position, BOTTOM) == 0)
    {
        __node->setAnchorPoint(Vec2(0.5f, 0.5f));
        __node->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, WINDOW_HEIGHT / 2 * __node->getScaleY()));
    }
    else if(strcmp(position, BOTTOM_LEFT) == 0)
    {
        __node->setPosition(Vec2::ZERO);
    }
    else if(strcmp(position, BOTTOM_RIGHT) == 0)
    {
        __node->setPosition(Vec2(Director::getInstance()->getWinSize().width - WINDOW_WIDTH * __node->getScaleX(), 0));
    }
    else if(strcmp(position, RIGHT_CENTER) == 0)
    {
        __node->setPosition(Vec2(Director::getInstance()->getWinSize().width - WINDOW_WIDTH * __node->getScaleX(), (Director::getInstance()->getWinSize().height - WINDOW_HEIGHT * __node->getScaleY()) / 2));
    }
    else if(strcmp(position, LEFT_CENTER) == 0)
    {
        __node->setPosition(Vec2(0, (Director::getInstance()->getWinSize().height - WINDOW_HEIGHT * __node->getScaleY()) / 2));
    }
    return __node;
}

Node* GameReaderManager::getNodeFromParent(Node* parentNode, const char* nodeName)
{
    return parentNode->getChildByName(nodeName);
}

Sprite* GameReaderManager::getSpriteFromParent(Node* parentNode, const char* nodeName)
{
    return dynamic_cast<Sprite *>(parentNode->getChildByName(nodeName));
}