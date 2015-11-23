//
//  GameMediator.cpp
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#include "GameMediator.h"
#include "GameBgLayer.h"
#include "ADManager.h"
//#include "GameUiLayer.h"


GameMediator* GameMediator::instance;

void GameMediator::onEnter()
{
    auto __event = EventListenerTouchOneByOne::create();
    __event->onTouchBegan = CC_CALLBACK_2(GameMediator::onTouchBegan, this);
    __event->onTouchMoved = CC_CALLBACK_2(GameMediator::onTouchMoved, this);
    __event->onTouchEnded = CC_CALLBACK_2(GameMediator::onTouchEnded, this);
    __event->onTouchCancelled = CC_CALLBACK_2(GameMediator::onTouchCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(__event, this);
    __event->setSwallowTouches(this->getSwallowTouches());
    
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameMediator::onKeyReleased, this);
    listenerkeyPad->onKeyPressed = CC_CALLBACK_2(GameMediator::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    Layer::onEnter();
}

void GameMediator::onExit()
{
    Layer::onExit();
}

void GameMediator::decodeNodeVisibleTrue(Node* pNode)
{
    pNode->setVisible(true);
}
void GameMediator::decodeNodeVisibleFalse(Node* pNode)
{
    pNode->setVisible(false);
}

bool GameMediator::onTouchBegan(Touch *touch, Event *unused_event)
{
    return false;
}

void GameMediator::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}

void GameMediator::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}

void GameMediator::onTouchCancelled(Touch *touch, Event *unused_event)
{
    log("62");
}

void GameMediator::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        ADManager::showAlert();
}

void GameMediator::setReaderUINode(Node* pNode)
{
    _readerUINode = pNode;
//    this->addChild(_readerUINode);
}

Node* GameMediator::getReaderUINode()
{
    return _readerUINode;
}

void GameMediator::setReaderUIBgNode(Node* pNode)
{
    _readerUIBgNode = pNode;
//    GameBgLayer::getInstance()->addChild(_readerUIBgNode);
}

Node* GameMediator::getReaderUIBgNode()
{
    return _readerUIBgNode;
}

void GameMediator::addHead(Node* parentNode, const Vec2& pVec2)
{
    if(_head)
        return;
    
    _head = Sprite::create("head.png");
    _head->setAnchorPoint(Vec2(0, 0.5f));
    parentNode->addChild(_head);
    _head->setPosition(pVec2);
}

void GameMediator::addOneMoveHead(Node* parentNode, const Vec2& startVec2, const Vec2& endVec2)
{
    this->addHead(parentNode, startVec2);
    _headPosition = startVec2;
    _head->runAction(RepeatForever::create(Sequence::create(MoveTo::create(1.6f, endVec2),
                                                            FadeTo::create(0.5f, 0),
                                                            CallFuncN::create(CC_CALLBACK_1(GameMediator::changeOneMoveHead, this)),
                                                            NULL)));
}

void GameMediator::addMoveHead(Node* parentNode, const Vec2& startVec2, const Vec2& endVec2)
{
    this->addHead(parentNode, startVec2);
    _head->runAction(RepeatForever::create(Sequence::create(MoveTo::create(1.6f, endVec2),
                                                            MoveTo::create(1.6f, startVec2),
                                                            NULL)));
}

void GameMediator::changeOneMoveHead(Node* pNode)
{
    pNode->setOpacity(255);
    pNode->setPosition(_headPosition);
}

void GameMediator::removeHead()
{
    if(!_head)
        return;
    _head->removeFromParent();
    this->setHead(NULL);
}

void GameMediator::onAction()
{
    this->getReaderUINode()->stopAllActions();
    float __scale = this->getReaderUINode()->getScale();
    this->getReaderUINode()->setScale(0);
    this->getReaderUINode()->runAction(ScaleTo::create(0.5f, __scale));
}

void GameMediator::onEnd()
{
    if(_isEnd)
        return;
    _isEnd = true;
    this->getReaderUINode()->stopAllActions();
    this->getReaderUINode()->runAction(Sequence::create(ScaleTo::create(0.5f, 0),
                                                        CCCallFunc::create(CC_CALLBACK_0(Node::removeFromParent, this)),
                                                        NULL));
}

void GameMediator::onStartAction(int pInt)
{
    if(pInt == 1)
    {
        float __scale = this->getReaderUINode()->getScale();
        this->getReaderUINode()->setScale(0);
        this->getReaderUINode()->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8f, __scale)),
                                                            CCCallFunc::create(CC_CALLBACK_0(GameMediator::onStartActionCallBack, this)),
                                                            NULL));
    }
    else
    {
        this->setPositionY(Director::getInstance()->getWinSize().height / 2);
        this->runAction(Sequence::create(EaseBackOut::create(MoveTo::create(0.8f, Vec2(this->getPositionX(), 0))),
                                         CCCallFunc::create(CC_CALLBACK_0(GameMediator::onStartActionCallBack, this)),
                                         NULL));
    }
}

void GameMediator::onStartActionCallBack()
{
//    this->onVirtualStartAction();
}

void GameMediator::onEndAction(int pInt)
{
    if(_isEnd)
        return;
    _isEnd = true;
    if(pInt == 1)
    {
        this->getReaderUINode()->runAction(Sequence::create(EaseBackIn::create(ScaleTo::create(0.8f, 0)),
                                                            CCCallFunc::create(CC_CALLBACK_0(GameMediator::onEndActionCallBack, this)),
                                                            NULL));
    }
    else
    {
        Vec2 __vec2 = this->getReaderUINode()->getPosition();
        this->runAction(Sequence::create(EaseBackIn::create(MoveTo::create(0.8f, Vec2(this->getPositionX(), Director::getInstance()->getWinSize().height / 2))),
                                         CCCallFunc::create(CC_CALLBACK_0(GameMediator::onEndActionCallBack, this)),
                                         NULL));
    }
}

void GameMediator::onEndActionCallBack()
{
//    GameUiLayer::getInstance()->removeSUI(this);
    this->onVirtualEndAction();
    
}