//
//  ButtonMediator.cpp
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#include "ButtonMediator.h"
#include "GameScene.h"
#include "MakeUpMediator.h"
#include "DressUpMediator.h"

#define         ZHUOMIAN_BG               "biankuang1"

void ButtonMediator::onEnter()
{
    isChangePage = false;
    this->onInitPage();
    DropMediator::onEnter();
}

void ButtonMediator::onExit()
{
    DropMediator::onExit();
}

void ButtonMediator::onInitPage()
{
    if(this->getPageMaxNum() <= 1)
        return;
    auto page = GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page");
    page->setPosition(Vec2(-WINDOW_WIDTH * (this->getPageMaxNum() - 1), page->getPositionY()));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page")->runAction(MoveTo::create(3, Vec2(0, GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page")->getPositionY())));
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page")->runAction(MoveTo::create(1, Vec2(0, GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page")->getPositionY())));
#endif
    
    _last_page_num = 0;
    _pageNumBg = NULL;
    this->decodePageFlag();
}

void ButtonMediator::decodeTouch()
{
    _isMove = false;
    if(this->isScheduled(schedule_selector(ButtonMediator::decodeTouchTimer)))
        this->unschedule(schedule_selector(ButtonMediator::decodeTouchTimer));
    this->schedule(schedule_selector(ButtonMediator::decodeTouchTimer), 0.2f, kRepeatForever, 0);
}

void ButtonMediator::decodeTouchTimer(float dt)
{
    this->unschedule(schedule_selector(ButtonMediator::decodeTouchTimer));
    if(!_isMove)
    {
        this->setDropTargetNode(this->getClickTargetNode());
        this->decodeYingZi(this->getClickTargetNode(), false);
        this->onDropBegin(_beginTouch);
        this->decodePage(_beginTouch->getLocation().x > _pBeginVec2.x);
    }
}


bool ButtonMediator::onTouchBegan(Touch *touch, Event *unused_event)
{
    _beginTouch = touch;
    _beginEvent = unused_event;
    
    if(this->getClickTargetNode() || this->getDropTargetNode())
        return false;
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    if(GameScene::_houseIndex == makeupType)
    {
        ((MakeUpMediator*)this)->decodeJiaziMove(touch);
    }
    _pBeginVec2 = touch->getLocation();
    _pMoveVec2_b = touch->getLocation();
    _pMoveVec2_n = touch->getLocation();
    
    Node* __page = GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page");
    if(!__page)
    {
        for(int i = 0; i < this->getReaderUINode()->getChildrenCount(); i++)
        {
            auto node = this->getReaderUINode()->getChildren().at(i);
            if(GameOther::getIsClickNode(node, touch->getLocation()))
            {
                this->setClickTargetNode(node);
                this->decodeTouch();
            }
        }
    }else
    {
        for(int i = 0; i < __page->getChildrenCount(); i++)
        {
            for(int j = (int)__page->getChildren().at(i)->getChildrenCount() - 1; j >= 0; j--)
            {
                auto node = __page->getChildren().at(i)->getChildren().at(j);
                if(GameOther::getIsClickNode(node, touch->getLocation()) &&
                   strcmp(node->getName().c_str(), "noclick") != 0 &&
                   strcmp(node->getName().c_str(), "yingzi") != 0)
                {
                    if(strcmp(node->getName().c_str(), "pingzi") != 0 &&
                       this->onVirtualAutoDrop())
                    {
                        if(node->getName().find(ITEMS_JIEMAO) != string::npos ||
                           node->getName().find(ITEMS_EYE_SHADOW_BOX) != string::npos ||
                           node->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI) != string::npos||
                           node->getName().find(ITEMS_QUDOUYE_NOCLICK_PINGZI) != string::npos||
                           node->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_1) != string::npos||
                           node->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_2) != string::npos||
                           node->getName().find(ITEMS_FENPU_NOCLICK_PINGZI) != string::npos)//点击瓶子 旁边跳动
                        {
                            this->setClickTargetNode(node);
                        }else
                        {
                            if(node->getName().find(ITEMS_EYE_SHADOW_BOX) != string::npos ||
                               node->getName().find(ITEMS_EARRING) != string::npos ||
                               node->getName().find(ITEMS_NECKLACE) != string::npos)
                            {
                                GameOther::changeGRAYNodeToWhite(__page->getChildren().at(i)->getChildren().at(j));
                            }
                            if(node->getName().find("_") == 0)//影子
                            {
                                return false;
                            }
                            this->setClickTargetNode(node);
                            this->decodeTouch();
                        }
                        
                    }else if(node->getName() == ITEMS_HAIR)
                    {
                        this->setClickTargetNode(node);
                    }else if(node->getName() == ITEMS_MEITONG)
                    {
                        this->setClickTargetNode(node);
                    }
                    else
                        GameOther::changeGRAYNodeToWhite(__page->getChildren().at(i)->getChildren().at(j));
                    return true;
                }
            }
        }
        
        DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
        if(GameOther::getIsClickNode(GameReaderManager::getNodeFromParent(this->getReaderUINode(), ZHUOMIAN_BG), touch->getLocation()))
        {
            this->setClickTargetNode(GameReaderManager::getNodeFromParent(this->getReaderUINode(), ZHUOMIAN_BG));
            return true;
        }
        
        
    }
    
    return false;
}

void ButtonMediator::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(abs(touch->getLocation().x - _pBeginVec2.x) != 0 && abs(touch->getLocation().y - _pBeginVec2.y) != 0)
        _isMove = true;
    
    //有拖拽的对象时，move方法给拖拽使用
    if(this->getDropTargetNode())
    {
        this->onDropMove(touch);
        return;
    }
    
    if(!this->getClickTargetNode())
        return;
    if(this->getClickTargetNode()->getName() != ZHUOMIAN_BG && (this->getClickTargetNode()->getName().find(ITEMS_EYE_SHADOW_BOX) == string::npos)
       && this->getClickTargetNode()->getName().find(ITEMS_JIEMAO) == string::npos
       &&(this->getClickTargetNode()->getName().find(ITEMS_BLUSH_BOX) == string::npos)
       && this->getClickTargetNode()->getName().find(ITEMS_MEITONG) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_YANXIAN_TONG) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_HAIR) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_EARRING) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_NECKLACE) == string::npos &&
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI) == string::npos&&
       this->getClickTargetNode()->getName().find(ITEMS_QUDOUYE_NOCLICK_PINGZI) == string::npos&&
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_1) == string::npos&&
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_2) == string::npos&&
       this->getClickTargetNode()->getName().find(ITEMS_FENPU_NOCLICK_PINGZI) == string::npos)
    {
        if(this->getClickTargetNode()->getName().find(ITEMS_CHUNCAI) != string::npos)
        {
            
            if(GameOther::getStrNumber(this->getClickTargetNode()->getName(), ITEMS_CHUNCAI) >= 7)
            {
                return;
            }
        }
        if(!this->getIsDropHeight() ||
           (abs(touch->getLocation().x - _pBeginVec2.x) < 50 && touch->getLocation().y > _pBeginVec2.y + 50))
        {
            if(strcmp(this->getClickTargetNode()->getName().c_str(), ZHUOMIAN_BG) != 0 &&
               strcmp(this->getClickTargetNode()->getName().c_str(), "pingzi") != 0 &&
               this->onVirtualDrop())
            {
                this->setDropTargetNode(this->getClickTargetNode());
                this->decodeYingZi(this->getClickTargetNode(), false);
                this->onDropBegin(touch);
                this->decodePage(touch->getLocation().x > _pBeginVec2.x);
                return;
            }
        }else if(this->getClickTargetNode()->getName().find("chuangketieon") != string::npos)
        {
            this->setDropTargetNode(this->getClickTargetNode());
            this->decodeYingZi(this->getClickTargetNode(), false);
            this->onDropBegin(touch);
            this->decodePage(touch->getLocation().x > _pBeginVec2.x);
            return;
        }
    }
    
    
    if(this->getPageMaxNum() == 1)
        return;
    _pMoveVec2_n = touch->getLocation();
    Node* __page = GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page");
    __page->setPosition(Vec2(__page->getPositionX() + (_pMoveVec2_n.x - _pMoveVec2_b.x) / this->getReaderUINode()->getScale(), __page->getPositionY()));
    _pMoveVec2_b = touch->getLocation();
}

void ButtonMediator::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
}

void ButtonMediator::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
}

void ButtonMediator::touchEnd(Touch *touch)
{
    if(this->getDropTargetNode())
    {
//        GameData::getInstance()->setMakeDressNum(GameData::getInstance()->getMakeDressNum() + 1);
        this->onDropEnd(touch);
    }
    
    _isMove = true;
    
    if(!this->getClickTargetNode())
        return;
    
    this->decodePage(touch->getLocation().x > _pBeginVec2.x);
    
    if(abs(_pBeginVec2.x - touch->getLocation().x) < 20 && abs(_pBeginVec2.y - touch->getLocation().y) < 20)
    {
        //点击瓶子跳动
        if(strcmp(this->getClickTargetNode()->getName().c_str(), "pingzi") == 0 ||
           this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI) != string::npos||
           this->getClickTargetNode()->getName().find(ITEMS_QUDOUYE_NOCLICK_PINGZI) != string::npos||
           this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_1) != string::npos||
           this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_2) != string::npos||
           this->getClickTargetNode()->getName().find(ITEMS_FENPU_NOCLICK_PINGZI) != string::npos ||
           this->getClickTargetNode()->getName().find(ITEMS_JIEMAO) != string::npos ||
           this->getClickTargetNode()->getName().find(ITEMS_EYE_SHADOW_BOX) != string::npos ||
           this->getClickTargetNode()->getName().find(ITEMS_BLUSH_BOX) != string::npos ||
           this->getClickTargetNode()->getName().find(ITEMS_CHUNCAI) != string::npos)
        {
            if(this->getClickTargetNode()->getName().find(ITEMS_CHUNCAI) != string::npos)
            {
                int num = GameOther::getStrNumber(this->getClickTargetNode()->getName(), ITEMS_CHUNCAI);
                if(num >= 7)
                {
                    this->onClickToJump(this->decodeClickToJump());
                    GameOther::changeGRAYNodeToWhite(this->getClickTargetNode());
                    return;
                }
            }else
            {
                this->onClickToJump(this->decodeClickToJump());
                GameOther::changeGRAYNodeToWhite(this->getClickTargetNode());
                return;
            }
            
        }
        string str = this->getClickTargetNode()->getName();
        if(!this->getDropTargetNode())
            this->onVirtualEnd(touch, str);
        //除了瓶子 别的点击了没有移动执行
        if(strcmp(this->getClickTargetNode()->getName().c_str(), ZHUOMIAN_BG) != 0 && this->getClickTargetNode()->getActionManager()->getNumberOfRunningActionsInTarget(this->getClickTargetNode()) == 0 )
        {
            this->onClickToJump(this->getClickTargetNode());
            return;
        }
        
    }
    if(this->getClickTargetNode()->getName().find(ITEMS_MEITONG) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_YANXIAN_TONG) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_HAIR) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_EARRING) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_NECKLACE) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_EYE_SHADOW_BOX) == string::npos
       && this->getClickTargetNode()->getName().find(ITEMS_JIEMAO) == string::npos)
    {
        //没有跳动的现在制空
        Node* __node = this->decodeYingZi(this->getClickTargetNode(), false);
        if(__node)
            __node->runAction(Sequence::create(DelayTime::create(0.3f), CallFuncN::create(CC_CALLBACK_1(ButtonMediator::onEndYingzi, this)), NULL));
    }
    
    this->setClickTargetNode(NULL);
}

void ButtonMediator::onEndYingzi(Node* pNode)
{
    pNode->setVisible(true);
}

void ButtonMediator::decodePage(bool is_left)
{
    if(this->getPageMaxNum() == 1)
        return;
    Node* __page = GameReaderManager::getNodeFromParent(this->getReaderUINode(), "page");
    
    
    int __current_page_num = _last_page_num;
    if(__page)
    {
        float __h = WINDOW_WIDTH * (this->getPageMaxNum() - 1);
        if(__page->getPositionX() > 0)
            __page->runAction(MoveTo::create(0.2f, Vec2(0, __page->getPositionY())));
        else if(__page->getPositionX() < -__h)
            __page->runAction(MoveTo::create(0.2f, Vec2(-__h, __page->getPositionY())));
        else
        {
            int __yu = -(int)__page->getPositionX() % WINDOW_WIDTH;
            int __zheng = (int)__page->getPositionX() / WINDOW_WIDTH;
            
            
            if(is_left)
            {
                if(__yu < WINDOW_WIDTH / 7 * 6)
                {
                    __current_page_num = __zheng;
                    __page->runAction(MoveTo::create(0.2f, Vec2(__zheng * WINDOW_WIDTH, __page->getPositionY())));
                }
                else
                {
                    __current_page_num = __zheng - 1;
                    __page->runAction(MoveTo::create(0.2f, Vec2((__zheng - 1) * WINDOW_WIDTH, __page->getPositionY())));
                }
            }
            else
            {
                if(__yu > WINDOW_WIDTH / 7)
                {
                    __current_page_num = __zheng - 1;
                    __page->runAction(MoveTo::create(0.2f, Vec2((__zheng - 1) * WINDOW_WIDTH, __page->getPositionY())));
                }
                else
                {
                    __current_page_num = __zheng;
                    __page->runAction(MoveTo::create(0.2f, Vec2(__zheng * WINDOW_WIDTH, __page->getPositionY())));
                }
                
            }
        }
    }
    
    
    if(_last_page_num != __current_page_num)
    {
        _last_page_num = __current_page_num;
        isChangePage = true;
        this->onVirtualPage();
    }else
        isChangePage = false;
    
    _last_page_num = __current_page_num;
    this->decodePageFlag();
}

int ButtonMediator::getCurrentPage()
{
    return abs(_last_page_num);
}

Node* ButtonMediator::decodeClickToJump()
{
    const char* __name = this->getClickTargetNode()->getParent()->getParent()->getName().c_str();
    
    Node* __parentNode = GameReaderManager::getNodeFromParent(this->getReaderUINode(), __name);
    Node* __targetNode = NULL;
    for(int i = 0; i < __parentNode->getChildrenCount(); i++)
    {
        for(int j = 0; j < __parentNode->getChildren().at(i)->getChildrenCount(); j++)
        {
            Node* __node = __parentNode->getChildren().at(i)->getChildren().at(j);
            if(__node->getName().find("_") != string::npos && __node->getPositionX() != this->getClickTargetNode()->getPositionX())
            {
                if(!__targetNode)
                {
                    if(__node != this->getClickTargetNode())
                        __targetNode = __node;
                }
                else
                {
                    __targetNode = this->getClickTargetNode()->getParent()->getChildByTag(this->getClickTargetNode()->getTag() - 1);
                    return __targetNode;
//                    float __x_c = abs((__node->getParent()->getPositionX() + __node->getPositionX()) - (this->getClickTargetNode()->getParent()->getPositionX() + this->getClickTargetNode()->getPositionX()));
//                    float __x_t = abs((__targetNode->getParent()->getPositionX() + __targetNode->getPositionX()) - (this->getClickTargetNode()->getParent()->getPositionX() + this->getClickTargetNode()->getPositionX()));
//                    if(__x_c < __x_t && __node != this->getClickTargetNode())
//                        __targetNode = __node;
                }
            }
        }
    }
    return __targetNode;
}

Node* ButtonMediator::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || strcmp(yingZiNode->getName().c_str(), ZHUOMIAN_BG) == 0)
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void ButtonMediator::onClickToJump(Node* jumpNode)
{
    this->decodeYingZi(jumpNode, false);
    GameSoundManager::getInstance()->playEffect("jump.mp3");
    jumpNode->runAction(Sequence::create(JumpTo::create(0.6f, jumpNode->getPosition(), 10, 1),
                                         CallFunc::create(CC_CALLBACK_0(ButtonMediator::onClickToJumpCallBack, this)),
                                                             NULL));
}

void ButtonMediator::onClickToJumpCallBack()
{
    if(this->getClickTargetNode() &&(
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI) != string::npos ||
       this->getClickTargetNode()->getName().find(ITEMS_QUDOUYE_NOCLICK_PINGZI) != string::npos ||
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_1) != string::npos ||
       this->getClickTargetNode()->getName().find(ITEMS_MIANMO_NOCLICK_PINGZI_2) != string::npos ||
       this->getClickTargetNode()->getName().find(ITEMS_FENPU_NOCLICK_PINGZI) != string::npos ||
                                     this->getClickTargetNode()->getName().find(ITEMS_JIEMAO) != string::npos ||
                                     this->getClickTargetNode()->getName().find(ITEMS_EYE_SHADOW_BOX) != string::npos ||
                                     this->getClickTargetNode()->getName().find(ITEMS_BLUSH_BOX) != string::npos ||
                                     this->getClickTargetNode()->getName().find(ITEMS_CHUNCAI) != string::npos))
    {
        if(this->getClickTargetNode()->getName().find(ITEMS_CHUNCAI) != string::npos)
        {
            int num = GameOther::getStrNumber(this->getClickTargetNode()->getName(), ITEMS_CHUNCAI);
            if(num >= 7)
            {
                
            }else
            {
                this->decodeYingZi(this->getClickTargetNode(), true);
                this->setClickTargetNode(NULL);
                return;
            }
        }
        this->decodeYingZi(this->getClickTargetNode()->getParent()->getChildByTag(this->getClickTargetNode()->getTag() - 1), true);
    }else if(this->getClickTargetNode())
    {
        this->decodeYingZi(this->getClickTargetNode(), true);
    }
    this->setClickTargetNode(NULL);
}

void ButtonMediator::decodePageFlag()
{
    if(this->getPageMaxNum() == 1)
        return;
    if(!_pageNumBg)
    {
        _pageNumBg = Layer::create();
        this->addChild(_pageNumBg);
        float __w = 0;
        float __h = 0;
        
        for(int i = 0; i < this->getPageMaxNum(); i++)
        {
            Sprite* __sp = Sprite::create("dotBlue.png");
            _pageNumBg->addChild(__sp);
            __sp->setAnchorPoint(Vec2(0.5f, 0.5));
            __sp->setScale((__sp->getScale())/2.0f + GameOther::getWindowSmallScale()/2.5f + GameOther::getWindowSmallScale() / 15.0f);
            __sp->setPosition(Vec2(__w, __sp->getContentSize().height*__sp->getScale()/2));
            __w += __sp->getContentSize().width*(__sp->getScale());
        }
        
        _pageNumBg->setContentSize(Size(__w, __h));
        _pageNumBg->setPosition(Vec2((Director::getInstance()->getWinSize().width - _pageNumBg->getContentSize().width) / 2, 0));
    }
    
    for(int i = 0; i < _pageNumBg->getChildrenCount(); i++)
    {
        if(i == -_last_page_num)
            _pageNumBg->getChildren().at(i)->setColor(Color3B::GRAY);
        else
            _pageNumBg->getChildren().at(i)->setColor(Color3B::WHITE);
    }
    
}
