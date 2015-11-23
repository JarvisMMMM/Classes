//
//  MakeSnowMan.cpp
//  Christmas
//
//  Created by apple12 on 15/11/20.
//
//

#include "MakeSnowMan.h"
#include "GameScene.h"
#include "MenuLayer.h"
//#include "ADManager.h"
#include "GameListIconMediator.h"
#include "GameEffectLayer.h"

#define     QUYU_NAME                       "quyu_snowman"

#define             VERTICAL_LIST_TAG           100

#define         GIRL_W          156

void MakeSnowMan::onEnter()
{
    this->onRun();
    ButtonMediator::onEnter();
}
void MakeSnowMan::onExit()
{
    instance = NULL;
    ButtonMediator::onExit();
}
void MakeSnowMan::onRun()
{
    exp = 0;
    expValue = 0;
    _bodyIndex = 0;
    isJiazi = false;
    isTouch = true;
    _isCanMove = true;
    isChanzi = true;
    _listNode = GameReaderManager::getNodeReaderFile("snowman_jiazi.csb", LEFT_CENTER, 2);
    this->addChild(_listNode);
    _listNode->setPosition(Vec2(_listNode->getPositionX() - _listNode->getContentSize().width/2, _listNode->getPositionY()));
    touming = _listNode->getChildByName(QUYU_NAME);
    _csbNode = GameMain::gameMainInstance->makeUpNode1;
    _xueqiu = this->getReaderUINode()->getChildByName("xueqiu_in");
    _chanzi = this->getReaderUINode()->getChildByName("chanzi1_snowman");
    xueqiuOutVec = _xueqiu->getPosition();
    instance = this;
}

bool MakeSnowMan::onTouchBegan(Touch *touch, Event *unused_event)
{
    if((this->getClickTargetNode() || this->getDropTargetNode()))
        return false;
    _beginVec2 = touch->getLocation();
    _moveVec2 = touch->getLocation();
    
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    if(itemsBeganTouch(touch))
    {
        return true;
    }
    if(GameOther::getIsClickNode(touming, touch->getLocation()))
    {
        return true;
    }else
    {
        log("87");
        if(GameOther::getIsClickNode(_listNode->getChildByName("guanbi_snowman"), touch->getLocation()))
        {
            jiaziMoveOut(touch);
            return true;
        }
        if(judgeListMove())
            return true;
        if(buttonTouch(touch))
            return true;
        if(jiaziMoveOut(touch))
            return true;
        log("92");
    }
    DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
    return false;
}

void MakeSnowMan::onTouchMoved(Touch *touch, Event *unused_event)
{
    this->onVirtualDropMove(touch);
}

void MakeSnowMan::onTouchEnded(Touch *touch, Event *unused_event)
{
    onVirtualDropEnd(touch);
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeSnowMan::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}


bool MakeSnowMan::itemsBeganTouch(Touch* touch)
{
    if(GameOther::getIsClickNode(_xueqiu, touch->getLocation()))
    {
        auto hand = this->getChildByName("PromptHand");
        if(hand)
        {
            hand->removeFromParent();
        }
        
        setClickTargetNode(_xueqiu);
        addDropIconSprite((Sprite*)_xueqiu, touch->getLocation());
        return true;
    }else if(GameOther::getIsClickNode(_chanzi, touch->getLocation()))
    {
        setClickTargetNode(_chanzi);
        addDropIconSprite((Sprite*)_chanzi, touch->getLocation());
        setChanziGuideShow(_xuerenNode->getChildByName("weiba2_snowman"));
        return true;
    }
}

void MakeSnowMan::touchEnd(Touch *touch)
{
    _isMove = true;
    
    if(!this->getClickTargetNode())
        return;
    
    string str = this->getClickTargetNode()->getName();
    touchEndFunc(str, -1);
    Node* __node = this->decodeYingZi(this->getClickTargetNode(), false);
    if(__node)
        __node->runAction(Sequence::create(DelayTime::create(0.3f), CCCallFuncN::create(CC_CALLBACK_1(MakeSnowMan::onEndYingzi, this)), NULL));
    this->setClickTargetNode(NULL);
}

void MakeSnowMan::touchEndFunc(const string& str, int index)
{
    Node* childNode = this->getClickTargetNode();
    
}

bool MakeSnowMan::buttonTouch(Touch* touch)
{
    for(int i = _csbNode->getChildrenCount() - 1; i >= 1; i--)
    {
        if(GameOther::getIsClickNode(_csbNode->getChildren().at(i), touch->getLocation()))
        {
            initListContent(i - 1, false);
            return true;
        }
    }
}

Node* MakeSnowMan::decodeClickToJump(Node* clickNode)
{
    Node* __targetNode = NULL;
    return __targetNode;
}

Node* MakeSnowMan::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || yingZiNode->getName() == "biankuang1")
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void MakeSnowMan::onEndYingzi(Node* pNode)
{
    pNode->setVisible(true);
}

void MakeSnowMan::onClickToJump(Node* jumpNode)
{
    this->decodeYingZi(this->getClickTargetNode(), false);
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    if(jumpNode->getName() != "honeyBottle_cold")
    {
        jumpNode->runAction(Sequence::create(JumpTo::create(0.6f, jumpNode->getPosition(), 10, 1),
                                             CCCallFunc::create(CC_CALLBACK_0(MakeSnowMan::onClickToJumpCallBack, this)),
                                             NULL));
    }else
    {
        MakeSnowMan::onClickToJumpCallBack();
    }
}



void MakeSnowMan::onClickToJumpCallBack()
{
    this->decodeYingZi(this->getClickTargetNode(), true);
    this->setClickTargetNode(NULL);
}

void MakeSnowMan::loadResources()
{
    //dress 10 had 10 shoses 10
    char name[40];
    for(int i = 1; i < 11; i++)
    {
        sprintf(name, "_dress%d_dressup.png", i);
        Director::getInstance()->getTextureCache()->addImage(name);
        sprintf(name, "_headwear%d_dressup.png", i);
        Director::getInstance()->getTextureCache()->addImage(name);
        sprintf(name, "_shose%d_dressup.png", i);
        Director::getInstance()->getTextureCache()->addImage(name);
    }
    for(int i = 1; i < 7; i++)
    {
        sprintf(name, "_shoutao%d_dressup.png", i);
        Director::getInstance()->getTextureCache()->addImage(name);
        sprintf(name, "_weijin%d_dressup.png", i);
        Director::getInstance()->getTextureCache()->addImage(name);
    }
    
}

void MakeSnowMan::initListContent(int indexListType, bool isScale)
{
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    
    bool isDrop = true;
    bool isVertical = true;
    std::vector<ListIconMediator*> _iconList;
    char spriteName[40];
    int count = 0;
    string bodyStr[] = {"_xueren_snowman.png", "_cat_snowman.png", "_rubbit_snowman.png", "_panda_snowman.png"};
    if(indexListType == snowBodyType)
    {
        count = 4;
    }else if(indexListType == snowHeadType)
    {
        count = 4;
    }else if(indexListType == snowFaceType)
    {
        count = 12;
    }else if(indexListType == snowHatType)
    {
        count = 6;
    }else if(indexListType == snowWeijinType)
    {
        count = 6;
    }
    for(int i = 0 ; i < count; i++)
    {
        if(indexListType == snowBodyType)
        {
            sprintf(spriteName, bodyStr[i].c_str());
        }else if(indexListType == snowHeadType)
        {
            sprintf(spriteName, bodyStr[i].c_str());
        }else if(indexListType == snowFaceType)
        {
            if(i < 4)
            {
                sprintf(spriteName, "_yan%d_face_snowman.png", i + 1);
            }else if(i < 8)
            {
                sprintf(spriteName, "_bizi%d_face_snowman.png", i + 1 - 4);
            }else if(i < 12)
            {
                sprintf(spriteName, "_zui%d_face_snowman.png", i + 1 - 8);
            }
        }else if(indexListType == snowHatType)
        {
            sprintf(spriteName, "_maozi%d_snowman.png", i + 1);
        }else if(indexListType == snowWeijinType)
        {
            sprintf(spriteName, "_weijin%d_snowman.png", i + 1);
        }
        Sprite* sprite = Sprite::create(spriteName);
        sprite->setName(spriteName);
        GameListIconMediator* listIcon = GameListIconMediator::initSprite(i, sprite, "", "", "");
        listIcon->setisvertical(isVertical);
        _iconList.push_back(listIcon);
        listIcon->setparentNode(this);
    }
    
    ListMediator* _list = ListMediator::create();
    Size size;
    size =  touming->getContentSize();
    _list->setListView(&_iconList, isVertical, size, isDrop);
    _list->_tableView->setScrollTouch(false);
    int scrollCount = 4;
    if(count >= scrollCount)
    {
        isRunSlider = true;
        float deltatime = 0.02f;
        if(isScale)
        {
            deltatime = 0.9f;
        }
//        _list->runSlideEnd(Vec2(0, size.height));
        this->runAction(Sequence::create(DelayTime::create(deltatime), CallFunc::create([=](){
            if(isRunSlider)
            {
                isRunSlider = false;
                ListMediator* _list = NULL;
                _list = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
                if(_list)
                    _list->runEndSlideStart();
                
                
            }
        }), DelayTime::create(0.5), CallFunc::create([=](){
            isListTouch = true;
            ListMediator* _list1 = NULL;
            _list1 = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
            if(_list1 && _list1->_tableView)
            {
                _list1->_tableView->setScrollTouch(true);
            }
        }), NULL));
    }
    
    Node* quyu = NULL;
    quyu = touming->getChildByTag(VERTICAL_LIST_TAG);
    if(quyu)
    {
        quyu->removeFromParent();
        quyu = NULL;
    }
    
    
    touming->addChild(_list, 0, VERTICAL_LIST_TAG);
    if(isScale)
    {
        touming->setScale(0);
        touming->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
    }
    _iconList.clear();
    DropMediator::_curListType = indexListType;
    jiaziMoveIn();
}

void MakeSnowMan::onListClick(Sprite* sprite, int index)
{
    if(DropMediator::_curListType == snowBodyType)
    {
        initXuerenBody(_bodyIndex);
        _xueqiu->setVisible(true);
        _xueqiu->runAction(Sequence::create(MoveTo::create(0.2, Vec2(WINDOW_WIDTH/2, _xueqiu->getPositionY())),
                                            CallFunc::create([=](){
            expValue = 0;
            shakeHands();
        }), NULL));
        _bodyIndex = index;
        _xuerenNode = this->getReaderUINode()->getChildByName("snowman")->getChildren().at(2 + _bodyIndex);
    }else if(DropMediator::_curListType == snowHeadType)
    {
        initXuerenHead(_bodyIndex);
        _xueqiu->setVisible(true);
        _xueqiu->runAction(Sequence::create(MoveTo::create(0.2, Vec2(WINDOW_WIDTH/2, _xueqiu->getPositionY())),
                                            CallFunc::create([=](){
            expValue = 0;
            shakeHands();
        }), NULL));
        _bodyIndex = index;
        _xuerenNode = this->getReaderUINode()->getChildByName("snowman")->getChildren().at(2 + _bodyIndex);
    }else if(DropMediator::_curListType == snowFaceType)
    {
        char parStr[40];
        char imageStr[40];
        if(index < 4)
        {
            sprintf(parStr, "yan%d_face_snowman", index + 1);
            sprintf(imageStr, "yan%d_face_snowman.png", index + 1);
        }else if(index < 8)
        {
            index = index - 4;
            sprintf(parStr, "bizi_face_snowman");
            sprintf(imageStr, "bizi%d_face_snowman.png", index + 1);
        }else if(index < 12)
        {
            index = index - 8;
            sprintf(parStr, "zui_face_snowman");
            sprintf(imageStr, "zui%d_face_snowman.png", index + 1);
        }
        dressFlyUp(sprite, parStr, imageStr, index + 1);
        //        GameData::getInstance()->setWeijinIndex(index);
    }else if(DropMediator::_curListType == snowHatType)
    {
        dressFlyUp(sprite, "maozi_snowman", "maozi%d_snowman.png", index + 1);
        //        GameData::getInstance()->setGloveIndex(index);
    }else if(DropMediator::_curListType == snowWeijinType)
    {
        dressFlyUp(sprite, "weijin_snowman", "weijin%d_snowman.png", index + 1);
        //        GameData::getInstance()->setShoseIndex(index);
    }
}

void MakeSnowMan::dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//    Sprite* partSprite = (Sprite*)_zhengheNode->getChildByName(partName);
//    char meitongstr[40];
//    sprintf(meitongstr, pngName, idx);
//    partSprite->setTexture(meitongstr);
    //    if(sprite)
    //        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeSnowMan::dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite = (Sprite*)this->getReaderUINode()->getChildByName("snowman")->getChildByName(partName);
    if(!partSprite)
    {
        partSprite = (Sprite*)this->getReaderUINode()->getChildByName("snowman")->getChildByName("yan_face_snowman")->getChildByName(partName);
    }
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);
    bool isEye = false;
    string partStr = partName;
    if(partStr.find("yan") != string::npos)
    {
        isEye = true;
    }
    Vec2 vec = sprite->getPosition();
    Sprite* flySp = Sprite::create(meitongstr);
    this->addChild(flySp);
    flySp->setPosition(sprite->getParent()->convertToWorldSpace(sprite->getPosition()));
    flySp->setScale(0);
    flySp->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())),
                                                    ScaleTo::create(0.5, 1*GameOther::getWindowSmallScale()), NULL), RemoveSelf::create(), CallFunc::create([=](){
        if(isEye)
        {
            for(auto node :
                this->getReaderUINode()->getChildByName("snowman")->getChildByName("yan_face_snowman")->getChildren())
            {
                node->setVisible(false);
            }
            if(idx == 2)
            {
                Sprite* partSprite1 = (Sprite*)this->getReaderUINode()->getChildByName("snowman")->getChildByName("yan_face_snowman")->getChildByName("yan5_face_snowman");
                partSprite1->setVisible(true);
                partSprite1->setTexture("yan5_face_snowman.png");
            }
        }
        
        partSprite->setVisible(true);
        partSprite->setTexture(meitongstr);
    }), NULL));
    
    
    
    if(sprite)
        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeSnowMan::onVirtualDropBegin(Touch* pTouch)
{
}

void MakeSnowMan::onVirtualDropMove(Touch* pTouch)
{
    Vec2 __vec = pTouch->getLocation();
    if(_dropIcon)
    {
        if(!_isCanMove)
        {
            return;
        }
        if(_dropIcon->getName() == "xueqiu_in")
        {
            _dropIcon->setScale((_dropIcon->getScale() + 0.02)*GameOther::getWindowSmallScale());
        }
        _dropIcon->setPosition(__vec);
        exp++;
        if(exp % 5)
        {
            expValue++;
        }
        if(DropMediator::_curListType == snowBodyType)
        {
            if(expValue == 40)
            {
                auto body = _xuerenNode->getChildByName("body_xueren_snowman");
                _isCanMove = false;
                this->runAction(Sequence::create(CallFunc::create([=](){
                    _dropIcon->runAction(MoveTo::create(0.2, body->getParent()->convertToWorldSpace(body->getPosition())));
                }), DelayTime::create(0.2), CallFunc::create([=](){
                    body->setVisible(true);
                    _xueqiu->setPosition(xueqiuOutVec);
                    onEndCallBack();
                    _isCanMove = true;
                    if(_bodyIndex == 1 || _bodyIndex == 2)
                        _chanzi->runAction(Sequence::create(MoveTo::create(0.2, Vec2(WINDOW_WIDTH/2, _chanzi->getPositionY())),
                                                            NULL));
                }), NULL));
                
            }
        }else if(DropMediator::_curListType == snowHeadType)
        {
            if(expValue == 40)
            {
                _isCanMove = false;
                auto head = _xuerenNode->getChildByName("tou_xueren_snowman");
                this->runAction(Sequence::create(CallFunc::create([=](){
                    _dropIcon->runAction(MoveTo::create(0.2, head->getParent()->convertToWorldSpace(head->getPosition())));
                }), DelayTime::create(0.2), CallFunc::create([=](){
                    head->setVisible(true);
                    //                getClickTargetNode()->setVisible(false);
                    getClickTargetNode()->setPosition(xueqiuOutVec);
                    onEndCallBack();
                    
                    _isCanMove = true;
                }), NULL));
                
            }
        }
        
        decodeGameEffect(pTouch);
    }
}

void MakeSnowMan::onVirtualDropEnd(Touch* pTouch)
{
    if(getClickTargetNode() && _dropIcon)
    {
        getClickTargetNode()->setVisible(true);
        getClickTargetNode()->setScale(_dropIcon->getScale()/GameOther::getWindowSmallScale());
        getClickTargetNode()->setPosition(_dropIcon->getPosition());
    }
    exp = 0;
    onEndCallBack();
}

void MakeSnowMan::onEnd()
{
    if(_chanzi)
    {
       _chanzi->setVisible(false);
    }
    onEndCallBack();
}

void MakeSnowMan::onEndCallBack()
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
}


void MakeSnowMan::decodeGameEffect(Touch* touch)
{
    auto node = getClickTargetNode();
    if(!node)
    {
        return;
    }
    if(node->getName() == "chanzi1_snowman")
    {
        auto weiba = _xuerenNode->getChildByName("weiba2_snowman");
        auto weiba1 = _xuerenNode->getChildByName("weiba1_snowman");
        if(GameOther::getIsClickRectNode(weiba, touch->getLocation(), node->getContentSize().width, true) && isChanzi)
        {
            isChanzi = false;
            auto chanzi = this->getReaderUINode()->getChildByName("chanzi2_snowman");
            this->runAction(Sequence::create(CallFunc::create([=](){
                _chanzi->setPosition(_chanzi->getParent()->convertToNodeSpace(_dropIcon->getPosition()));
                onEndCallBack();
                _chanzi->setVisible(true);
                _chanzi->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, chanzi->getParent()->convertToWorldSpace(chanzi->getPosition())), RotateTo::create(0.5, chanzi->getRotation()), NULL), CallFunc::create([=](){
                    _chanzi->setVisible(false);
                }), NULL));
            }), DelayTime::create(0.5), CallFunc::create([=](){
                chanzi->setVisible(true);
                float roa = chanzi->getRotation();
                chanzi->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateTo::create(0.2, roa), DelayTime::create(0.4), NULL), 3), Hide::create(), NULL));
                Animation* ani = createAnimation(chanzi);
                auto aniNode = this->getReaderUINode()->getChildByName("xuexiedonghua");
                aniNode->runAction(Repeat::create(Animate::create(ani), 3));
                weiba1->setVisible(true);
                weiba1->setOpacity(0);
                weiba1->runAction(FadeIn::create(0.6));
                
                isChanzi = true;
            }), NULL));
        }
    }
}

bool MakeSnowMan::judgeListMove()
{
    ListMediator* templist = NULL;
    log("517");
    templist = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
    if(templist)
    {
        int count1 = templist->_tableView->getContainer()->getActionManager()->getNumberOfRunningActionsInTarget(templist->_tableView->getContainer());
        if(count1 > 0)
        {
            log("524");
            return true;
        }
    }
    log("528");
    return false;
}

void MakeSnowMan::jiaziMoveIn()
{
    if(_listNode->getActionByTag(99))
    {
    }
    if(isJiazi)
    {
        
    }else
    {
        _listNode->setVisible(true);
        isJiazi = true;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(_listNode->getContentSize().width/2, 0)), NULL);
        actionInterval->setTag(99);
        _listNode->runAction(actionInterval);
    }
    
}

bool MakeSnowMan::jiaziMoveOut(Touch* touch)
{
    if(isJiazi && _listNode->isVisible())
    {
        if(_listNode->getActionByTag(99))
            return true;
        isJiazi = false;
        isListTouch = false;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(-_listNode->getContentSize().width/2, 0)), CallFunc::create([=](){
            Node* quyu = touming->getChildByTag(VERTICAL_LIST_TAG);
            quyu->removeFromParent();
            _listNode->setVisible(false);
            isTouch = true;
            
        }), NULL);
        actionInterval->setTag(99);
        _listNode->runAction(actionInterval);
        return true;
    }
    return false;
}

void MakeSnowMan::addDropIconSprite(Sprite* sprite, const Vec2& vec)
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
    getClickTargetNode()->setVisible(false);
    string str = sprite->getName();
    _dropIcon = (GameOther::cloneSprite(sprite));
    //    this->addChild(_dropIcon, 1);
    //    _dropIcon->setAnchorPoint(Vec2(0.5, 1));
    GameEffectLayer::getInstance()->addChild(_dropIcon);
    _dropIcon->setPosition(vec);
    _dropIcon->setScale(sprite->getScale() * GameOther::getWindowSmallScale());
}

void MakeSnowMan::shakeHands()
{
    Sprite* hands = Sprite::create("PromptHand.png");
    this->addChild(hands);
    hands->setName("PromptHand");
    hands->setPosition(Vec2((_xueqiu->getPositionX() + _xueqiu->getContentSize().width - hands->getContentSize().width/2)*GameOther::getWindowSmallScale(), _xueqiu->getPositionY()*GameOther::getWindowSmallScale()));
    hands->setScale(GameOther::getWindowSmallScale());
    hands->runAction(Sequence::create(Repeat::create(Sequence::create(MoveBy::create(1, Vec2(-(_xueqiu->getContentSize().width + hands->getContentSize().width/2) * GameOther::getWindowSmallScale(), 0)), CallFunc::create([=](){
        hands->setFlippedX(true);
    }), MoveBy::create(1, Vec2((_xueqiu->getContentSize().width + hands->getContentSize().width/2) * GameOther::getWindowSmallScale(), 0)), CallFunc::create([=](){
        hands->setFlippedX(false);
    }), NULL), 2), RemoveSelf::create(), NULL));
}

void MakeSnowMan::setChanziGuideShow(Node* node)
{
    node->runAction(Blink::create(2, 5));
    node->setVisible(true);
}
void MakeSnowMan::setChanziGuideHide(Node* node)
{
    node->stopAllActions();
    node->setVisible(false);
}

Animation* MakeSnowMan::createAnimation(Node* node)
{
    Animation* animation = Animation::create();
    int count;
    if(node->getName() == "chanzi2_snowman")
    {
        count = 3;
        char str[40];
        for(int i = 0 ; i < count; i++)
        {
            sprintf(str, "xuehua%d_chanzi_snowman.png", i+1);
            animation->addSpriteFrameWithFile(str);
        }
    }
    animation->setDelayPerUnit(0.3);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(true);
    return animation;
}

void MakeSnowMan::initXuerenBody(int index)
{
    auto xuerenNode = this->getReaderUINode()->getChildByName("snowman")->getChildren().at(2 + index);
    for(auto node : xuerenNode->getChildren())
    {
        node->setVisible(false);
    }
//    auto body = xuerenNode->getChildByName("body_xueren_snowman");
//    body->setVisible(false);
    initXuerenHead(index);
}
void MakeSnowMan::initXuerenHead(int index)
{
    auto xuerenNode = this->getReaderUINode()->getChildByName("snowman")->getChildren().at(2 + index);
    auto head = xuerenNode->getChildByName("tou_xueren_snowman");
    head->setVisible(false);
}