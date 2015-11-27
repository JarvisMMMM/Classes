//
//  MakeChristmasHome.cpp
//  Christmas
//
//  Created by apple12 on 15/11/25.
//
//

#include "MakeChristmasHome.h"
#include "GameScene.h"
#include "MenuLayer.h"
//#include "ADManager.h"
#include "GameListIconMediator.h"

#define     QUYU_NAME                       "quyu_gongjulan2_kapian"
#define     SIGNQUYU_NAME                   "quyu_gongjulan_qianming"

#define             VERTICAL_LIST_TAG           100
#define             HORIZONTAL_LIST_TAG         1000

#define         GIRL_W          156

void MakeChristmasHome::onEnter()
{
    this->onRun();
    ButtonMediator::onEnter();
}
void MakeChristmasHome::onExit()
{
    instance = NULL;
    ButtonMediator::onExit();
}
void MakeChristmasHome::onRun()
{
    auto node = GameReaderManager::getNodeReaderFile("kapian_jiazi.csb", CENTER, 0);
    this->addChild(node);
    loadResources();
    instance = this;
}

bool MakeChristmasHome::onTouchBegan(Touch *touch, Event *unused_event)
{
    if((this->getClickTargetNode() || this->getDropTargetNode()))
        return false;
    _beginVec2 = touch->getLocation();
    _moveVec2 = touch->getLocation();
    
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
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
    }
    DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
    return false;
}

void MakeChristmasHome::onTouchMoved(Touch *touch, Event *unused_event)
{
    this->onVirtualDropMove(touch);
}

void MakeChristmasHome::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeChristmasHome::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeChristmasHome::touchEnd(Touch *touch)
{
    _isMove = true;
    
    if(!this->getClickTargetNode())
        return;
    
    string str = this->getClickTargetNode()->getName();
    touchEndFunc(str, -1);
    Node* __node = this->decodeYingZi(this->getClickTargetNode(), false);
    if(__node)
        __node->runAction(Sequence::create(DelayTime::create(0.3f), CCCallFuncN::create(CC_CALLBACK_1(ButtonMediator::onEndYingzi, this)), NULL));
    this->setClickTargetNode(NULL);
}

void MakeChristmasHome::touchEndFunc(const string& str, int index)
{
    Node* childNode = this->getClickTargetNode();
    
}

bool MakeChristmasHome::buttonTouch(Touch* touch)
{
//    auto buttonParent = _cardUINode->getChildByName("gongjulan1_kapian");
//    for(int i = 0; i < buttonParent->getChildrenCount(); i++)
//    {
//        if(GameOther::getIsClickNode(buttonParent->getChildren().at(i), touch->getLocation()))
//        {
//            initListContent(i, false);
//            return true;
//        }
//    }
}



Node* MakeChristmasHome::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || yingZiNode->getName() == "biankuang1")
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void MakeChristmasHome::loadResources()
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

void MakeChristmasHome::initListContent(int indexListType, bool isScale)
{
//    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
//    
//    bool isDrop = true;
//    bool isVertical = false;
//    std::vector<ListIconMediator*> _iconList;
//    char spriteName[40];
//    int count = 12;
//    for(int i = 0 ; i < count; i++)
//    {
//        if(indexListType == cardColorType)
//        {
//            sprintf(spriteName, "_yanse%d_kapian.png", i + 1);
//        }else if(indexListType == cardHuawenType)
//        {
//            sprintf(spriteName, "_huawen%d_kapian.png", i + 1);
//        }else if(indexListType == cardBlessType)
//        {
//            sprintf(spriteName, "_zhufuhua%d_kapian.png", i + 1);
//        }else if(indexListType == cardStampType)
//        {
//            sprintf(spriteName, "_youpiao%d_kapian.png", i + 1);
//        }else if(indexListType == cardSealType)
//        {
//            sprintf(spriteName, "_yinzhang%d_kapian.png", i + 1);
//        }else if(indexListType == cardBiType)
//        {
//            sprintf(spriteName, "bi%d_qianming.png", i + 1);
//        }
//        Sprite* sprite = Sprite::create(spriteName);
//        sprite->setName(spriteName);
//        GameListIconMediator* listIcon = GameListIconMediator::initSprite(i, sprite, "", "", "");
//        listIcon->setisvertical(isVertical);
//        _iconList.push_back(listIcon);
//        listIcon->setparentNode(this);
//    }
//    
//    ListMediator* _list = ListMediator::create();
//    Size size;
//    Node* touming;
//    if(indexListType == cardBiType)
//    {
//        touming = signNameToumingquyu;
//    }else
//    {
//        touming = toumingquyu;
//    }
//    size =  touming->getContentSize();
//    _list->setListView(&_iconList, isVertical, size, isDrop);
//    _list->_tableView->setScrollTouch(false);
//    int scrollCount = 6;
//    if(count >= scrollCount)
//    {
//        isRunSlider = true;
//        float deltatime = 0.02f;
//        if(isScale)
//        {
//            deltatime = 0.9f;
//        }
//        _list->runSlideEnd(Vec2(size.width, 0));
//        this->runAction(Sequence::create(DelayTime::create(deltatime), CallFunc::create([=](){
//            if(isRunSlider)
//            {
//                isRunSlider = false;
//                ListMediator* _list = NULL;
//                _list = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
//                if(_list)
//                    _list->runStartSlideEnd();
//                
//                
//            }
//        }), DelayTime::create(0.5), CallFunc::create([=](){
//            isListTouch = true;
//            ListMediator* _list1 = NULL;
//            _list1 = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
//            if(_list1 && _list1->_tableView)
//            {
//                _list1->_tableView->setScrollTouch(true);
//            }
//        }), NULL));
//    }
//    
//    Node* quyu = NULL;
//    if((DropMediator::_curListType != indexListType) && ((DropMediator::_curListType == cardBiType || indexListType != cardBiType) || (DropMediator::_curListType != cardBiType || indexListType == cardBiType)))
//    {
//        quyu = signNameToumingquyu->getChildByTag(VERTICAL_LIST_TAG);
//        if(quyu)
//        {
//            quyu->removeFromParent();
//            quyu = NULL;
//        }
//        quyu = toumingquyu->getChildByTag(VERTICAL_LIST_TAG);
//        if(quyu)
//        {
//            quyu->removeFromParent();
//            quyu = NULL;
//        }
//    }else
//    {
//        quyu = touming->getChildByTag(VERTICAL_LIST_TAG);
//        if(quyu)
//        {
//            quyu->removeFromParent();
//            quyu = NULL;
//        }
//    }
//    
//    
//    touming->addChild(_list, 0, VERTICAL_LIST_TAG);
//    if(isScale)
//    {
//        touming->setScale(0);
//        touming->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
//    }
//    _iconList.clear();
//    
//    DropMediator::_curListType = indexListType;
    
}

void MakeChristmasHome::onListClick(Sprite* sprite, int index)
{
//    bool isLaugh = false;
//    if(DropMediator::_curListType == cardSealType)
//    {
//        gaiZhang(sprite, index);
//        //        isLaugh = true;
//        //        dressUp(sprite, "dress_dressup", "dress%d_dressup.png", index + 1);
//        //        GameData::getInstance()->setDressIndex(index);
//    }else if(DropMediator::_curListType == cardColorType)
//    {
//        isLaugh = true;
//        dressUp(sprite, "yanse_kapian", "yanse%d_kapian.png", index + 1);
//        //        GameData::getInstance()->setShoseIndex(index);
//    }else if(DropMediator::_curListType == cardHuawenType)
//    {
//        isLaugh = true;
//        dressFlyUp(sprite, "huawen_kapian", "huawen%d_kapian.png", index + 1);
//        //        GameData::getInstance()->setWeijinIndex(index);
//    }else if(DropMediator::_curListType == cardBlessType)
//    {
//        isLaugh = true;
//        dressFlyUp(sprite, "zhufuhua_kapian", "zhufuhua%d_kapian.png", index + 1);
//        //        GameData::getInstance()->setGloveIndex(index);
//    }else if(DropMediator::_curListType == cardStampType)
//    {
//        isLaugh = true;
//        dressFlyUp(sprite, "youpiao_kapian", "youpiao%d_kapian.png", index + 1);
//        //        GameData::getInstance()->setShoseIndex(index);
//    }else if(DropMediator::_curListType == cardBiType)
//    {
//        int tempY = 0;
//        if(_curSelectVec.y != 0)
//        {
//            tempY = sprite->getPositionY() - _curSelectVec.y;
//        }
//        huabiIndex = index;
//        if(!_curSelectBi)
//        {
//            _curSelectVec = sprite->getPosition();
//            _curSelectBi = sprite;
//        }else
//        {
//            _curSelectBi->setPosition(_curSelectVec);
//            _curSelectBi->setScale(1);
//            _curSelectBi = sprite;
//        }
//        Vec2 vec;
//        if(tempY != 0)
//        {
//            vec = sprite->getPosition();
//        }
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//        sprite->setPosition(Vec2(_curSelectVec.x, _curSelectVec.y + 10 + tempY));
//        sprite->setScale(1.2);
//        if(tempY != 0)
//        {
//            _curSelectVec = vec;
//        }
//    }
}

void MakeChristmasHome::dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
//    if(isSounds)
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//    Sprite* partSprite = (Sprite*)_zhengheNode->getChildByName(partName);
//    char meitongstr[40];
//    sprintf(meitongstr, pngName, idx);
//    partSprite->setTexture(meitongstr);
//    //    if(sprite)
//    //        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeChristmasHome::dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
//    if(isSounds)
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//    Sprite* partSprite = (Sprite*)_zhengheNode->getChildByName(partName);
//    char meitongstr[40];
//    sprintf(meitongstr, pngName, idx);
//    
//    Vec2 vec = sprite->getPosition();
//    Sprite* flySp = Sprite::create(meitongstr);
//    this->addChild(flySp);
//    flySp->setPosition(sprite->getParent()->convertToWorldSpace(sprite->getPosition()));
//    flySp->setScale(0);
//    flySp->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())),
//                                                    ScaleTo::create(0.5, 1*GameOther::getWindowSmallScale()), NULL), RemoveSelf::create(), CallFunc::create([=](){
//        partSprite->setTexture(meitongstr);
//    }), NULL));
//    
//    
//    
//    if(sprite)
//        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeChristmasHome::onVirtualDropBegin(Touch* pTouch)
{
}

void MakeChristmasHome::onVirtualDropMove(Touch* pTouch)
{
    
}

void MakeChristmasHome::onVirtualDropEnd(Touch* pTouch)
{
}
bool MakeChristmasHome::judgeListMove()
{
//    ListMediator* templist = NULL;
//    Node* touming;
//    if(DropMediator::_curListType == cardBiType)
//    {
//        touming = signNameToumingquyu;
//    }else
//    {
//        touming = toumingquyu;
//    }
//    log("517");
//    templist = (ListMediator*)touming->getChildByTag(VERTICAL_LIST_TAG);
//    if(templist)
//    {
//        int count1 = templist->_tableView->getContainer()->getActionManager()->getNumberOfRunningActionsInTarget(templist->_tableView->getContainer());
//        if(count1 > 0)
//        {
//            log("524");
//            return true;
//        }
//    }
//    log("528");
//    return false;
}