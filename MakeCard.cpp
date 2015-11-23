//
//  MakeCard.cpp
//  Christmas
//
//  Created by apple12 on 15/11/19.
//
//

#include "MakeCard.h"
#include "GameScene.h"
#include "MenuLayer.h"
//#include "ADManager.h"
#include "GameListIconMediator.h"

#define     QUYU_NAME                       "quyu_gongjulan2_kapian"
#define     SIGNQUYU_NAME                   "quyu_gongjulan_qianming"

#define             VERTICAL_LIST_TAG           100
#define             HORIZONTAL_LIST_TAG         1000

#define         GIRL_W          156

void MakeCard::onEnter()
{
    this->onRun();
    ButtonMediator::onEnter();
}
void MakeCard::onExit()
{
    instance = NULL;
    ButtonMediator::onExit();
}
void MakeCard::onRun()
{
    _isDraw = false;
    _curSelectBi = NULL;
    _draw = NULL;
    _color4FVector = {
        ccc4f(230.0f/255.0f, 0.0f/255.0f, 18.0f/255.0f, 1),
        ccc4f(137.0f/255.0f, 104.0f/255.0f, 255.0f/255.0f, 1),
        ccc4f(228.0f/255.0f, 0.0f/255.0f, 127.0f/255.0f, 1),
        ccc4f(255.0f/255.0f, 107.0f/255.0f, 35.0f/255.0f, 1),
        ccc4f(255.0f/255.0f, 154.0f/255.0f, 208.0f/255.0f, 1),
        ccc4f(0.0f/255.0f, 255.0f/255.0f, 0.0f/255.0f, 1),
        ccc4f(0.0f/255.0f, 153.0f/255.0f, 68.0f/255.0f, 1),
        ccc4f(255.0f/255.0f, 200.0f/255.0f, 5.0f/255.0f, 1),
        ccc4f(255.0f/255.0f, 0, 255.0f/255.0f, 1),
        ccc4f(0, 0, 255.0f/255.0f, 1),
        ccc4f(0, 255.0f/255.0f, 255.0f/255.0f, 1),
        ccc4f(255.0f/255.0f, 255.0f/255.0f, 0, 1)};
    
    auto node = GameReaderManager::getNodeReaderFile("kapian_jiazi.csb", CENTER, 0);
    this->addChild(node);
    _zhengheNode = this->getReaderUINode()->getChildByName("zhenghe");
    _cardUINode = GameMain::gameMainInstance->makeUpNode1;
    toumingquyu = GameReaderManager::getNodeFromParent(node, QUYU_NAME);
    signNameToumingquyu = GameReaderManager::getNodeFromParent(node, SIGNQUYU_NAME);
    _signNamePutNode = this->getReaderUINode()->getChildByName("qianming_kapian");
    _signNameNode = node->getChildByName("qianmingbufen");
    _yinzhangParentNode = this->getReaderUINode()->getChildByName("yinzhang");
    loadResources();
    instance = this;
}

bool MakeCard::onTouchBegan(Touch *touch, Event *unused_event)
{
    if((this->getClickTargetNode() || this->getDropTargetNode()))
        return false;
    _beginVec2 = touch->getLocation();
    _moveVec2 = touch->getLocation();
    
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    if(_signNameNode->isVisible())
    {
        if(GameOther::getIsClickNode(_signNameNode->getChildByName("baocun_qianming"), touch->getLocation()))
        {
            _signNameNode->runAction(Sequence::create(CallFunc::create([=](){
                signNameToumingquyu->runAction(Sequence::create(EaseBackIn::create(ScaleTo::create(0.5, 0)), CallFunc::create([=](){
                    Node* quyu = NULL;
                    quyu = signNameToumingquyu->getChildByTag(VERTICAL_LIST_TAG);
                    if(quyu)
                    {
                        quyu->removeFromParent();
                        quyu = NULL;
                    }
                }), NULL));
                decodeSave();
            }),EaseBackIn::create(ScaleTo::create(0.5, 0)), Hide::create(), NULL));
        }else if(GameOther::getIsClickNode(_signNameNode->getChildByName("lajitong_qianming"), touch->getLocation()))
        {
            _draw->removeFromParent();
            _draw = DrawNode::create();
            this->addChild(_draw);
        }
        return true;
    }
    if(GameOther::getIsClickNode(toumingquyu, touch->getLocation()))
    {
        return true;
    }else
    {
        log("87");
        if(judgeListMove())
            return true;
        if(buttonTouch(touch))
            return true;
        log("92");
        if(GameOther::getIsClickNode(_signNamePutNode, touch->getLocation()))
        {
            if(_draw)
                _draw->removeFromParent();
            _draw = DrawNode::create();
            this->addChild(_draw);
            
            _signNameNode->setScale(0);
            initListContent(cardBiType, true);
            _signNameNode->runAction(Sequence::create(Show::create(), EaseBackOut::create(ScaleTo::create(0.5, 1)), NULL));
            
        }
    }
    DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
    return false;
}

void MakeCard::onTouchMoved(Touch *touch, Event *unused_event)
{
    this->onVirtualDropMove(touch);
}

void MakeCard::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeCard::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeCard::touchEnd(Touch *touch)
{
    _isMove = true;
    
    if(!this->getClickTargetNode())
        return;
    
    string str = this->getClickTargetNode()->getName();
    touchEndFunc(str, -1);
    Node* __node = this->decodeYingZi(this->getClickTargetNode(), false);
    if(__node)
        __node->runAction(Sequence::create(DelayTime::create(0.3f), CCCallFuncN::create(CC_CALLBACK_1(MakeCard::onEndYingzi, this)), NULL));
    this->setClickTargetNode(NULL);
}

void MakeCard::touchEndFunc(const string& str, int index)
{
    Node* childNode = this->getClickTargetNode();
    
}

bool MakeCard::buttonTouch(Touch* touch)
{
    auto buttonParent = _cardUINode->getChildByName("gongjulan1_kapian");
    for(int i = 0; i < buttonParent->getChildrenCount(); i++)
    {
        if(GameOther::getIsClickNode(buttonParent->getChildren().at(i), touch->getLocation()))
        {
            initListContent(i, false);
            return true;
        }
    }
}

Node* MakeCard::decodeClickToJump(Node* clickNode)
{
    Node* __targetNode = NULL;
    return __targetNode;
}

Node* MakeCard::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || yingZiNode->getName() == "biankuang1")
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void MakeCard::onEndYingzi(Node* pNode)
{
    pNode->setVisible(true);
}

void MakeCard::onClickToJump(Node* jumpNode)
{
    this->decodeYingZi(this->getClickTargetNode(), false);
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    if(jumpNode->getName() != "honeyBottle_cold")
    {
        jumpNode->runAction(Sequence::create(JumpTo::create(0.6f, jumpNode->getPosition(), 10, 1),
                                             CCCallFunc::create(CC_CALLBACK_0(MakeCard::onClickToJumpCallBack, this)),
                                             NULL));
    }else
    {
        MakeCard::onClickToJumpCallBack();
    }
}



void MakeCard::onClickToJumpCallBack()
{
    this->decodeYingZi(this->getClickTargetNode(), true);
    this->setClickTargetNode(NULL);
}

void MakeCard::loadResources()
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

void MakeCard::initListContent(int indexListType, bool isScale)
{
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    
    bool isDrop = true;
    bool isVertical = false;
    std::vector<ListIconMediator*> _iconList;
    char spriteName[40];
    int count = 12;
    for(int i = 0 ; i < count; i++)
    {
        if(indexListType == cardColorType)
        {
            sprintf(spriteName, "_yanse%d_kapian.png", i + 1);
        }else if(indexListType == cardHuawenType)
        {
            sprintf(spriteName, "_huawen%d_kapian.png", i + 1);
        }else if(indexListType == cardBlessType)
        {
            sprintf(spriteName, "_zhufuhua%d_kapian.png", i + 1);
        }else if(indexListType == cardStampType)
        {
            sprintf(spriteName, "_youpiao%d_kapian.png", i + 1);
        }else if(indexListType == cardSealType)
        {
            sprintf(spriteName, "_yinzhang%d_kapian.png", i + 1);
        }else if(indexListType == cardBiType)
        {
            sprintf(spriteName, "bi%d_qianming.png", i + 1);
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
    Node* touming;
    if(indexListType == cardBiType)
    {
        touming = signNameToumingquyu;
    }else
    {
        touming = toumingquyu;
    }
    size =  touming->getContentSize();
    _list->setListView(&_iconList, isVertical, size, isDrop);
    _list->_tableView->setScrollTouch(false);
    int scrollCount = 6;
    if(count >= scrollCount)
    {
        isRunSlider = true;
        float deltatime = 0.02f;
        if(isScale)
        {
            deltatime = 0.9f;
        }
        _list->runSlideEnd(Vec2(size.width, 0));
        this->runAction(Sequence::create(DelayTime::create(deltatime), CallFunc::create([=](){
            if(isRunSlider)
            {
                isRunSlider = false;
                ListMediator* _list = NULL;
                _list = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
                if(_list)
                    _list->runStartSlideEnd();
                
                
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
    if((DropMediator::_curListType != indexListType) && ((DropMediator::_curListType == cardBiType || indexListType != cardBiType) || (DropMediator::_curListType != cardBiType || indexListType == cardBiType)))
    {
        quyu = signNameToumingquyu->getChildByTag(VERTICAL_LIST_TAG);
        if(quyu)
        {
            quyu->removeFromParent();
            quyu = NULL;
        }
        quyu = toumingquyu->getChildByTag(VERTICAL_LIST_TAG);
        if(quyu)
        {
            quyu->removeFromParent();
            quyu = NULL;
        }
    }else
    {
        quyu = touming->getChildByTag(VERTICAL_LIST_TAG);
        if(quyu)
        {
            quyu->removeFromParent();
            quyu = NULL;
        }
    }
    
    
    touming->addChild(_list, 0, VERTICAL_LIST_TAG);
    if(isScale)
    {
        touming->setScale(0);
        touming->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
    }
    _iconList.clear();
    
    DropMediator::_curListType = indexListType;
    
}

void MakeCard::onListClick(Sprite* sprite, int index)
{
    bool isLaugh = false;
    if(DropMediator::_curListType == cardSealType)
    {
        gaiZhang(sprite, index);
//        isLaugh = true;
//        dressUp(sprite, "dress_dressup", "dress%d_dressup.png", index + 1);
//        GameData::getInstance()->setDressIndex(index);
    }else if(DropMediator::_curListType == cardColorType)
    {
        isLaugh = true;
        dressUp(sprite, "yanse_kapian", "yanse%d_kapian.png", index + 1);
//        GameData::getInstance()->setShoseIndex(index);
    }else if(DropMediator::_curListType == cardHuawenType)
    {
        isLaugh = true;
        dressFlyUp(sprite, "huawen_kapian", "huawen%d_kapian.png", index + 1);
//        GameData::getInstance()->setWeijinIndex(index);
    }else if(DropMediator::_curListType == cardBlessType)
    {
        isLaugh = true;
        dressFlyUp(sprite, "zhufuhua_kapian", "zhufuhua%d_kapian.png", index + 1);
//        GameData::getInstance()->setGloveIndex(index);
    }else if(DropMediator::_curListType == cardStampType)
    {
        isLaugh = true;
        dressFlyUp(sprite, "youpiao_kapian", "youpiao%d_kapian.png", index + 1);
//        GameData::getInstance()->setShoseIndex(index);
    }else if(DropMediator::_curListType == cardBiType)
    {
        int tempY = 0;
        if(_curSelectVec.y != 0)
        {
            tempY = sprite->getPositionY() - _curSelectVec.y;
        }
        huabiIndex = index;
        if(!_curSelectBi)
        {
            _curSelectVec = sprite->getPosition();
            _curSelectBi = sprite;
        }else
        {
            _curSelectBi->setPosition(_curSelectVec);
            _curSelectBi->setScale(1);
            _curSelectBi = sprite;
        }
        Vec2 vec;
        if(tempY != 0)
        {
            vec = sprite->getPosition();
        }
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
        sprite->setPosition(Vec2(_curSelectVec.x, _curSelectVec.y + 10 + tempY));
        sprite->setScale(1.2);
        if(tempY != 0)
        {
            _curSelectVec = vec;
        }
    }
}

void MakeCard::dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite = (Sprite*)_zhengheNode->getChildByName(partName);
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);
    partSprite->setTexture(meitongstr);
//    if(sprite)
//        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeCard::dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite = (Sprite*)_zhengheNode->getChildByName(partName);
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);
    
    Vec2 vec = sprite->getPosition();
    Sprite* flySp = Sprite::create(meitongstr);
    this->addChild(flySp);
    flySp->setPosition(sprite->getParent()->convertToWorldSpace(sprite->getPosition()));
    flySp->setScale(0);
    flySp->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())),
                                                    ScaleTo::create(0.5, 1*GameOther::getWindowSmallScale()), NULL), RemoveSelf::create(), CallFunc::create([=](){
        partSprite->setTexture(meitongstr);
    }), NULL));
    
    
    
    if(sprite)
        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeCard::onVirtualDropBegin(Touch* pTouch)
{
    this->getDropIcon()->runAction(RotateTo::create(0.3f, 30));
}

void MakeCard::onVirtualDropMove(Touch* pTouch)
{
    Vec2 __vec = pTouch->getLocation();
    if(GameOther::getIsClickNode(GameReaderManager::getNodeFromParent(_signNameNode, "di_qianming_kapian"), __vec))
    {
        if(!_isDraw)
        {
            _beginVec2 = _moveVec2 = __vec;
            _isDraw = true;
        }
        else
        {
//            Vec2 v = _signNameNode->convertToNodeSpace(__vec);
            _moveVec2 = __vec;
            _draw->drawSegment(Vec2(_beginVec2.x, _beginVec2.y), Vec2(_moveVec2.x, _moveVec2.y), 6, _color4FVector.at(huabiIndex));
            _beginVec2 = __vec;
        }
    }
    else
        _isDraw = false;
}

void MakeCard::onVirtualDropEnd(Touch* pTouch)
{
}

void MakeCard::decodeSave()
{
    _curSelectBi = NULL;
    auto smallPosition = this->getReaderUINode()->getChildByName("qianming_kapian")->getPosition();
    auto bigPosition = GameReaderManager::getNodeFromParent(_signNameNode, "di_qianming_kapian")->getPosition();
    auto smallSize = this->getReaderUINode()->getChildByName("qianming_kapian")->getContentSize();
    auto bigSize = GameReaderManager::getNodeFromParent(_signNameNode, "di_qianming_kapian")->getContentSize();
    _draw->setScale(smallSize.width/ bigSize.width, smallSize.height/ bigSize.height);
    auto ss = Vec2((bigPosition.x - bigSize.width/2)*_draw->getScaleX(),(bigPosition.y - bigSize.height/2)*_draw->getScaleY());
    log("SS:%f, %f", ss.x, ss.y);
    _draw->setPosition(Vec2((smallPosition.x - ss.x - smallSize.width/2)*GameOther::getWindowSmallScale(), (smallPosition.y - ss.y - smallSize.height/2)*GameOther::getWindowSmallScale()));
//    _draw->setAnchorPoint(Vec2(0.5, 0.5));
    
}


void MakeCard::gaiZhang(Sprite* sprite, int index)
{
    auto yinzhang1_kapian = _yinzhangParentNode->getChildByName("zhang1_kapian");
    auto yinzhang2_kapian = _yinzhangParentNode->getChildByName("zhang2_kapian");
    Vec2 vec = yinzhang1_kapian->getPosition();
    yinzhang1_kapian->setPositionX(WINDOW_WIDTH + yinzhang1_kapian->getContentSize().width/2);
    yinzhang1_kapian->runAction(Sequence::create(Show::create(), MoveTo::create(0.5, vec), Hide::create(), CallFunc::create([=](){
        yinzhang1_kapian->setPosition(vec);
    }), NULL));
    yinzhang2_kapian->runAction(Sequence::create(DelayTime::create(0.5), Show::create(), DelayTime::create(0.5), Hide::create(), CallFunc::create([=](){
        dressUp(sprite, "yinzhang_kapian", "yinzhang%d_kapian.png", index + 1);
    }), NULL));
}

bool MakeCard::judgeListMove()
{
    ListMediator* templist = NULL;
    Node* touming;
    if(DropMediator::_curListType == cardBiType)
    {
        touming = signNameToumingquyu;
    }else
    {
        touming = toumingquyu;
    }
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
