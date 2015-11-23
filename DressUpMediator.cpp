//
//  DressUpMediator.cpp
//  japanesesalon
//
//  Created by apple12 on 15/6/23.
//
//

#include "DressUpMediator.h"
#include "DrawImageManager.h"
#include "GameScene.h"
#include "MenuLayer.h"
#include "ADManager.h"
#include "GameListIconMediator.h"

#define     QUYU_NAME                       "jiazi2_dressup"

#define             VERTICAL_LIST_TAG           100
#define             HORIZONTAL_LIST_TAG         1000

#define         GIRL_W          156

DressUpMediator* DressUpMediator::dressupMediatorInstance;

void DressUpMediator::onEnter()
{
    loadResources();
    _girl1 = NULL;
    isTouxiangGirl1 = true;
    isTouxiangGirl2 = true;
    isTouxiangGirl3 = true;
    isTouxiangGirl4 = true;
    _girlIndex = -1;
    isJiazi = false;
    isTouch = true;
    this->onRun();
    ButtonMediator::onEnter();
}
void DressUpMediator::onExit()
{
    dressupMediatorInstance = NULL;
    ButtonMediator::onExit();
}
void DressUpMediator::onRun()
{
    _listNode = GameReaderManager::getNodeReaderFile("dressup_jiazi.csb", RIGHT_CENTER, 2);
    this->addChild(_listNode);
    _headPortrait = GameReaderManager::getNodeReaderFile("dressup_ui.csb", CENTER, 2);
    this->addChild(_headPortrait);
    _leftButtonNode = GameReaderManager::getNodeReaderFile("dressup_ui2.csb", LEFT_CENTER, 2);//left func button
    this->addChild(_leftButtonNode);
    _listNode->setPosition(Vec2(_listNode->getPositionX() + _listNode->getContentSize().width/2, _listNode->getPositionY()));
    auto normalButton = _leftButtonNode->getChildByName("weidianji");
    normalButton->setVisible(false);
    _last_page_num = 0;
    _pageNumBg = NULL;
    
//    getPlayerNode()->runAction(RepeatForever::create(Sequence::create(MoveBy::create(5, Vec2(0, -30*getPlayerNode()->getScale())), MoveBy::create(5, Vec2(0, 30*getPlayerNode()->getScale())), NULL)));
    
    toumingquyu = _listNode->getChildByName(QUYU_NAME);
    dressupMediatorInstance = this;
    initParticleEffect();
    headPortraitMoveIn();
    scheduleUpdate();
//    addFace();
//    addJewel();
}

void DressUpMediator::addFace()
{
    if(!GameData::getInstance()->getMakeUpRender())
        return;
    Node* __printFace = dynamic_cast<Node*>(GameData::getInstance()->getMakeUpRender());
    Node* __face = GameReaderManager::getNodeFromParent(this->getPlayerNode(), DRESSUP_PARENT)->getChildByName("face_kongbai_dressup");
    __face->removeAllChildren();
    __face->addChild(__printFace);
    __printFace->setAnchorPoint(Vec2(0.5f, 0.5f));
    __printFace->setPosition(Vec2(__face->getContentSize().width / 2, __face->getContentSize().height / 2));
    auto node = dynamic_cast<Node*>(GameData::getInstance()->getMakeUpRender()->getSprite());
    __printFace->setScale(__face->getContentSize().width / node->getContentSize().width,
                          __face->getContentSize().height / node->getContentSize().height);
}


void DressUpMediator::addJewel()
{
//    int index = GameData::getInstance()->getHairIndex();
//    dressUp(NULL, "hair", "hair%d_dressup.png", index, false);
    if(GameData::getInstance()->getWeijinIndex() != 0)
    {
        dressUp(NULL, "weijin_dressup", "weijin%d_dressup.png", GameData::getInstance()->getWeijinIndex(), false);
    }
    if(GameData::getInstance()->getGloveIndex() != 0)
    {
        dressUp(NULL, "shoutao_dressup", "shoutao%d_dressup.png", GameData::getInstance()->getGloveIndex(), false);
    }
    if(GameData::getInstance()->getDressIndex() != 0)
    {
        dressUp(NULL, "dress_dressup", "dress%d_dressup.png", GameData::getInstance()->getDressIndex(), false);
    }
    if(GameData::getInstance()->getShoseIndex() != 0)
    {
        string str = "shoes%d_dressup.png";
        dressUp(NULL, "shoes_ressup", str.c_str(), GameData::getInstance()->getShoseIndex(), false);
    }
    if(GameData::getInstance()->getHadIndex() != 0)
    {
        string str = "headwear%d_dressup.png";
        dressUp(NULL, "headwear_dressup", str.c_str(), GameData::getInstance()->getHadIndex(), false);
    }
}

void DressUpMediator::initParticleEffect()
{
    
}

bool DressUpMediator::onTouchBegan(Touch *touch, Event *unused_event)
{
    _beginTouch = touch;
    _beginEvent = unused_event;
    if((this->getClickTargetNode() || this->getDropTargetNode()))
        return false;
    bool backIsChange;
    Node* node = GameScene::gameScene->getChildByTag(100);
    if(node->isVisible())
    {
        backIsChange = true;
    }else
    {
        backIsChange = false;
    }
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    if(GameOther::getIsClickNode(toumingquyu, touch->getLocation()) && isJiazi)
    {
        return true;
    }else
    {
        if(judgeListMove())
            return true;
        if(jiaziMoveOut(touch))
            return true;
    }
    _pBeginVec2 = touch->getLocation();
    _pMoveVec2_b = touch->getLocation();
    _pMoveVec2_n = touch->getLocation();
    Node* biankuang = _leftButtonNode->getChildByName("weidianji");
    headTouch(touch);
    for(int i = biankuang->getChildrenCount() - 1; i >=0 ; i--)
    {
        Node* childNode = biankuang->getChildren().at(i);
        if(childNode->getName() != "noclick" && GameOther::getIsClickNode(childNode, touch->getLocation()))
        {
            if(childNode->getName() == "button1_dressup")
            {
                initListContent(dressupClothesType);
                GameOther::changeGRAYNodeToWhite(childNode);
            }else if(childNode->getName() == "button2_dressup")
            {
                initListContent(dressupHadType);
                GameOther::changeGRAYNodeToWhite(childNode);
            }else if(childNode->getName() == "button3_dressup")
            {
                initListContent(dressupWeijinType);
                GameOther::changeGRAYNodeToWhite(childNode);
            }else if(childNode->getName() == "button4_dressup")
            {
                initListContent(dressupGloveType);
                GameOther::changeGRAYNodeToWhite(childNode);
            }else if(childNode->getName() == "button5_dressup")
            {
                initListContent(dressupShoesType);
                GameOther::changeGRAYNodeToWhite(childNode);
            }
            touchDownButton((Sprite*)childNode);
            break;
        }
    }
    
    DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
    if(GameScene::_houseIndex != dressupType)
    {
//        Node* girl = this->getPlayerNode()->getChildByName("girl_dress");
//        if(GameOther::getIsClickNode(girl, touch->getLocation()))
//        {
            setClickTargetNode(this->getPlayerNode());
            Vec2 vec = touch->getLocation();
            girlVec = Vec2(vec.x - this->getPlayerNode()->getPositionX(), vec.y - this->getPlayerNode()->getPositionY());
            return true;
//        }
    }
    
    return false;
}

void DressUpMediator::onTouchMoved(Touch *touch, Event *unused_event)
{
    _isMove = true;
    if(this->getDropTargetNode())
    {
        this->onDropMove(touch);
        return;
    }
    
    if(!this->getClickTargetNode())
        return;
    if(this->getClickTargetNode()->getName() == "grilNode")
    {
        Vec2 vec = touch->getLocation();
        this->getClickTargetNode()->setPosition(Vec2(vec.x - girlVec.x, vec.y - girlVec.y));
        return;
    }
    if(this->getClickTargetNode()->getName() != "biankuang1" && (this->getClickTargetNode()->getName().find("eye_shadow_box") == string::npos)
       &&(this->getClickTargetNode()->getName().find("blush_box") == string::npos))
    {
        if(abs(touch->getLocation().x - _pBeginVec2.x) < 50 && touch->getLocation().y > _pBeginVec2.y + 50)
        {
            this->setDropTargetNode(this->getClickTargetNode());
            this->decodeYingZi(this->getClickTargetNode(), false);
            this->onDropBegin(touch);
            return;
        }
    }
    _pMoveVec2_n = touch->getLocation();
    
    _pMoveVec2_b = touch->getLocation();
}

void DressUpMediator::onTouchEnded(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
//    this->onEnd(touch);
}

void DressUpMediator::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
//    this->onEnd(touch);
}

void DressUpMediator::onListClick(Sprite* sprite, int index)
{
    bool isLaugh = false;
    if(DropMediator::_curListType == dressupClothesType)
    {
        isLaugh = true;
        dressUp(sprite, "dress_dressup", "dress%d_dressup.png", index + 1);
        GameData::getInstance()->setDressIndex(index);
    }else if(DropMediator::_curListType == dressupHadType)
    {
        isLaugh = true;
        string str;
        str = "headwear%d_dressup.png";
        dressUp(sprite, "headwear_dressup", str.c_str(), index + 1);
        GameData::getInstance()->setShoseIndex(index);
    }else if(DropMediator::_curListType == dressupWeijinType)
    {
        isLaugh = true;
//        Sprite* hair = (Sprite*)this->getPlayerNode()->getChildByName(DRESSUP_PARENT)->getChildByName("dress");
//        hair->setVisible(true);
        dressUp(sprite, "weijin_dressup", "weijin%d_dressup.png", index + 1);
        GameData::getInstance()->setWeijinIndex(index);
    }else if(DropMediator::_curListType == dressupGloveType)
    {
        isLaugh = true;
        dressUp(sprite, "shoutao_dressup", "shoutao%d_dressup.png", index + 1);
        GameData::getInstance()->setGloveIndex(index);
    }else if(DropMediator::_curListType == dressupShoesType)
    {
        isLaugh = true;
        dressUp(sprite, "shose_dressup", "shose%d_dressup.png", index + 1);
        GameData::getInstance()->setShoseIndex(index);
    }
    if(isLaugh)
        setGirlLaugh(_girl, _girlIndex);
}

void DressUpMediator::dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite = (Sprite*)this->getPlayerNode()->getChildByName(DRESSUP_PARENT)->getChildByName(partName);
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);
    partSprite->setTexture(meitongstr);
    if(sprite)
        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
    if(DropMediator::_curListType == dressupClothesType  && isSounds)
    {
        yanhuaParticleEffect(this,this->convertToNodeSpace(partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())));
    }
}


void DressUpMediator::touchEnd(Touch *touch)
{
    _isMove = true;
    
    if(!this->getClickTargetNode())
        return;
    
    string str = this->getClickTargetNode()->getName();
    if(abs(_pBeginVec2.x - touch->getLocation().x) < 20 && abs(_pBeginVec2.y - touch->getLocation().y) < 20)
    {        
        if(str == "grilNode" && GameScene::_houseIndex == showType)
        {
            Node* girl = (this->getPlayerNode());
            girl->setScaleX(-girl->getScaleX());
        }
        touchEndFunc(str, -1);
        GameOther::arrowRemoveFunc();
    }else
    {
        touchEndFunc(str, -1);
    }
    Node* __node = this->decodeYingZi(this->getClickTargetNode(), false);
    if(__node)
        __node->runAction(Sequence::create(DelayTime::create(0.3f), CCCallFuncN::create(CC_CALLBACK_1(DressUpMediator::onEndYingzi, this)), NULL));
    this->setClickTargetNode(NULL);
}

void DressUpMediator::touchEndFunc(const string& str, int index)
{
    Node* childNode = this->getClickTargetNode();
    if(str == ITEMS_MIANMO || str == ITEMS_MIANMO_1 || str == ITEMS_MIANMO_2)
    {
        DrawImageManager::getInstance()->onEndTouch();
        GameMain::gameMainInstance->Renwuzhengyan();
        GameSoundManager::getInstance()->stopLoopEffect(MIANMO_MP3);
    }else if(str == ITEMS_YANXIAN)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find(ITEMS_YANMEI) != string::npos)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find(ITEMS_JIEMAOSHUA) != string::npos)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find(ITEMS_YANYING) != string::npos)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find(ITEMS_BLUSH) != string::npos)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find(ITEMS_CHUNCAI) != string::npos)
    {
        DrawImageManager::getInstance()->onEndTouch();
    }else if(str.find("eye_shadow_box") != string::npos)//点击瓶子 旁边跳动
    {
        string s = childNode->getName();
        int length = s.length();
        string ss;
        if(length == 15)
        {
            ss = s.substr(length - 1, length);
        }else
        {
            ss = s.substr(length - 2, length);
        }
        int number = std::atoi(ss.c_str());
        char shuazi[30];
        sprintf(shuazi, "eye_shadow_brush%d", number);
        onClickToJump(childNode->getParent()->getChildByName(shuazi));
    }else if(str.find("blush_box") != string::npos)
    {
        string strlength = childNode->getName();
        int length = strlength.length();
        string ss;
        if(length == 10)
        {
            ss = strlength.substr(length - 1, length);
        }else
        {
            ss = strlength.substr(length - 2, length);
        }
        int number = std::atoi(ss.c_str());
        
        char str[40];
        sprintf(str, "blush_brush%d", number);
        onClickToJump(childNode->getParent()->getChildByName(str));
    }else
    {
        if(str.find("_") == 0)//影子
        {
            return;
        }
        if(str == ITEMS_MEITONG)
        {
//            initListContent(meitongType);
        }
        
    }
}

void DressUpMediator::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        ADManager::showAlert();
}


Node* DressUpMediator::decodeClickToJump(Node* clickNode)
{
//    const char* __name = clickNode->getParent()->getParent()->getName().c_str();
    Node* __targetNode = NULL;
    return __targetNode;
}

Node* DressUpMediator::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || yingZiNode->getName() == "biankuang1")
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void DressUpMediator::onEndYingzi(Node* pNode)
{
    pNode->setVisible(true);
}

void DressUpMediator::onClickToJump(Node* jumpNode)
{
    this->decodeYingZi(this->getClickTargetNode(), false);
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    if(jumpNode->getName() != "honeyBottle_cold")
    {
        jumpNode->runAction(Sequence::create(JumpTo::create(0.6f, jumpNode->getPosition(), 10, 1),
                                             CCCallFunc::create(CC_CALLBACK_0(DressUpMediator::onClickToJumpCallBack, this)),
                                             NULL));
    }else
    {
        DressUpMediator::onClickToJumpCallBack();
    }
}



void DressUpMediator::onClickToJumpCallBack()
{
    this->decodeYingZi(this->getClickTargetNode(), true);
    this->setClickTargetNode(NULL);
}

bool DressUpMediator::judgeListMove()
{
    ListMediator* templist = NULL;
    templist = (ListMediator*)_listNode->getChildByName(QUYU_NAME)->getChildByTag(VERTICAL_LIST_TAG);
    if(templist)
    {
        int count1 = templist->_tableView->getContainer()->getActionManager()->getNumberOfRunningActionsInTarget(templist->_tableView->getContainer());
        if(count1 > 0)
        {
            return true;
        }
    }
    return false;
}

void DressUpMediator::initListContent(int indexListType)
{
    if(judgeListMove())
        return;
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    
    bool isDrop = true;
    bool isVertical = true;
    std::vector<ListIconMediator*> _iconList;
    char spriteName[40];
    int count = 0;
    if(indexListType == dressupClothesType)
    {
        count = 10;
    }else if(indexListType == dressupHadType)
    {
        count = 10;
    }else if(indexListType == dressupWeijinType)
    {
        count = 6;
    }else if(indexListType == dressupGloveType)
    {
        count = 6;
    }else if(indexListType == dressupShoesType)
    {
        count = 10;
    }else
    {
        count = 10;
    }
    DropMediator::_curListType = indexListType;
    for(int i = 0 ; i < count; i++)
    {
        if(indexListType == dressupClothesType)
        {
            sprintf(spriteName, "_dress%d_dressup.png", i + 1);
        }else if(indexListType == dressupHadType)
        {
            sprintf(spriteName, "_headwear%d_dressup.png", i + 1);
        }else if(indexListType == dressupWeijinType)
        {
            sprintf(spriteName, "_weijin%d_dressup.png", i + 1);
        }else if(indexListType == dressupGloveType)
        {
            sprintf(spriteName, "_shoutao%d_dressup.png", i + 1);
//            if(i == 0)
//            {
//                sprintf(spriteName, "x.png");
//            }else
//            {
//                if(i <= 10)
//                {
//                    sprintf(spriteName, "_earring%d_dressup.png", i);
//                }else
//                {
//                    sprintf(spriteName, "_necklace%d_dressup.png", i - 10);
//                }
//            }
            
        }else if(indexListType == dressupShoesType)
        {
            sprintf(spriteName, "_shose%d_dressup.png", i + 1);
            
//            if(i == 0)
//            {
//                sprintf(spriteName, "x.png");
//            }else
//            {
//                sprintf(spriteName, "_shouchiwupin%d_dressup.png", i);
//            }
            
        }
        Sprite* sprite = Sprite::create(spriteName);
        sprite->setName(spriteName);
        GameListIconMediator* listIcon = GameListIconMediator::initSprite(i, sprite, "", "", "jiazi3_dressup.png");
        listIcon->setisvertical(isVertical);
        _iconList.push_back(listIcon);
        listIcon->setparentNode(this);
    }
    
    ListMediator* _list = ListMediator::create();
    Size size;
    size =  GameReaderManager::getNodeFromParent(_listNode, QUYU_NAME)->getContentSize();
    _list->setListView(&_iconList, isVertical, size, isDrop);
    _list->_tableView->setScrollTouch(false);
    int scrollCount = 6;
    if(count >= scrollCount)
    {
        isRunSlider = true;
//        _list->runSlideEnd(Vec2(0, size.height));
        this->runAction(Sequence::create(DelayTime::create(0.02), CallFunc::create([=](){
            if(isRunSlider)
            {
                isRunSlider = false;
                ListMediator* _list = NULL;
                _list = (ListMediator*)GameReaderManager::getNodeFromParent(_listNode, QUYU_NAME)->getChildByTag(VERTICAL_LIST_TAG);
                if(_list)
                    _list->runEndSlideStart();
                
                
            }
        }), DelayTime::create(0.5), CallFunc::create([=](){
            isListTouch = true;
            ListMediator* _list1 = NULL;
            _list1 = (ListMediator*)GameReaderManager::getNodeFromParent(_listNode, QUYU_NAME)->getChildByTag(VERTICAL_LIST_TAG);
            if(_list1 && _list1->_tableView)
            {
                _list1->_tableView->setScrollTouch(true);
            }
        }), NULL));
    }
    
    
    Node* quyu = NULL;
    quyu = _listNode->getChildByName(QUYU_NAME)->getChildByTag(VERTICAL_LIST_TAG);
    if(quyu)
    {
        quyu->removeFromParent();
        quyu = NULL;
    }
        GameReaderManager::getNodeFromParent(_listNode, QUYU_NAME)->addChild(_list, 0, VERTICAL_LIST_TAG);
    _iconList.clear();
    jiaziMoveIn();
    
}

void DressUpMediator::jiaziMoveIn()
{
    if(_listNode->getActionByTag(99))
    {
        refreshButton();
    }
    if(isJiazi)
    {
        
    }else
    {
        _listNode->setVisible(true);
        isJiazi = true;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(-_listNode->getContentSize().width/2, 0)), NULL);
        actionInterval->setTag(99);
        _listNode->runAction(actionInterval);
        
        auto headTargetPosition = _headPortrait->getChildByName("renwukuang");
        headTargetPosition->runAction(MoveBy::create(0.2, Vec2(300, 0)));
        
    }
    
}

bool DressUpMediator::jiaziMoveOut(Touch* touch)
{
    if(isJiazi && _listNode->isVisible())
    {
        if(touch)
        {
            bool ret = false;
            Node* biankuang = _leftButtonNode->getChildByName("weidianji");
            for(int i = biankuang->getChildrenCount() - 1; i >=0 ; i--)
            {
                Node* childNode = biankuang->getChildren().at(i);
                if(childNode->getName() != "noclick" && GameOther::getIsClickNode(childNode, touch->getLocation()))
                {
                    if(childNode->getName() == "button1_dressup")
                    {
                        initListContent(dressupClothesType);
                        GameOther::changeGRAYNodeToWhite(childNode);
                        ret = true;
                    }else if(childNode->getName() == "button2_dressup")
                    {
                        initListContent(dressupHadType);
                        GameOther::changeGRAYNodeToWhite(childNode);
                        ret = true;
                    }else if(childNode->getName() == "button3_dressup")
                    {
                        initListContent(dressupWeijinType);
                        GameOther::changeGRAYNodeToWhite(childNode);
                        ret = true;
                    }else if(childNode->getName() == "button4_dressup")
                    {
                        initListContent(dressupGloveType);
                        GameOther::changeGRAYNodeToWhite(childNode);
                        ret = true;
                    }else if(childNode->getName() == "button5_dressup")
                    {
                        initListContent(dressupShoesType);
                        GameOther::changeGRAYNodeToWhite(childNode);
                        ret = true;
                    }
                    if(ret)
                        touchDownButton((Sprite*)childNode);
                    return ret;
                }
            }
        }
        
        if(_listNode->getActionByTag(99))
            return true;
        isJiazi = false;
        isListTouch = false;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(_listNode->getContentSize().width/2, 0)), CallFunc::create([=](){
            Node* quyu = _listNode->getChildByName(QUYU_NAME)->getChildByTag(VERTICAL_LIST_TAG);
            quyu->removeFromParent();
            _listNode->setVisible(false);
            isTouch = true;
            
        }), NULL);
        actionInterval->setTag(99);
        _listNode->runAction(actionInterval);
        auto headTargetPosition = _headPortrait->getChildByName("renwukuang");
        headTargetPosition->runAction(MoveTo::create(0.2, Vec2::ZERO));
        refreshButton();
        return true;
    }
    return false;
}

void DressUpMediator::touchDownButton(Sprite* node)
{
    refreshButton();
    string strlength = "button";
    int length = strlength.length();
    string s = node->getName();
    int length1 = s.length();
    string ss = s.substr(length, 1);
    int number = std::atoi(ss.c_str());
    char str[30];
    sprintf(str, "_button%d_dressup.png", number);
    node->setTexture(str);
    Vec2 vec = node->getPosition();
    node->setPositionX(-node->getContentSize().width);
    node->runAction(EaseBackOut::create(MoveTo::create(0.5f, vec)));
}

void DressUpMediator::refreshButton()
{
    vector<string> strVector = {"button1_dressup.png", "button2_dressup.png","button3_dressup.png","button4_dressup.png","button5_dressup.png"};
    vector<string> strNameVector = {"button1_dressup", "button2_dressup","button3_dressup","button4_dressup","button5_dressup"};
    for(int i = 0 ; i < 5; i++)
    {
        ((Sprite*)_leftButtonNode->getChildByName("weidianji")->getChildByName(strNameVector[i]))->setTexture(strVector[i]);
    }
}

void DressUpMediator::funcButtonHide()
{
    auto normalButton = _leftButtonNode->getChildByName("weidianji");
    auto pressButton = _leftButtonNode->getChildByName("dianji");
    for(int i = 0; i < normalButton->getChildrenCount(); i++)
    {
        Node* __node = normalButton->getChildren().at(i);
        Node* press = pressButton->getChildren().at(i);
        if(__node->getName().find("button") != std::string::npos)
        {
            __node->setVisible(false);
        }else if(press->getName().find("_press") != std::string::npos)
        {
            press->setVisible(false);
        }
    }
}

void DressUpMediator::funcButtonShow()
{
    auto normalButton = _leftButtonNode->getChildByName("weidianji");
    normalButton->setVisible(true);
    auto pressButton = _leftButtonNode->getChildByName("dianji");
    for(int i = 0; i < normalButton->getChildrenCount(); i++)
    {
        Node* __node = normalButton->getChildren().at(i);
        Node* press = pressButton->getChildren().at(i);
        Vec2 __vec2 = Vec2(27.00, __node->getPositionY());
        if(__node->getName().find("button") != std::string::npos)
        {
            __node->setVisible(true);
            __node->setPositionX(-__node->getContentSize().width);
            __node->stopAllActions();
            __node->runAction(EaseBackOut::create(MoveTo::create(0.6f * __node->getTag(), __vec2)));
        }
        if(press->getName().find("_press") != std::string::npos)
        {
            press->setVisible(false);
        }
    }
}

void DressUpMediator::headPortraitMoveIn()
{
    auto kuang = _headPortrait->getChildByName("renwukuang");
    _girl1 = kuang->getChildByName("girl1");
    _girl2 = kuang->getChildByName("girl2");
    _girl3 = kuang->getChildByName("girl3");
    _girl4 = kuang->getChildByName("girl4");
    _headKuang1 = _girl1->getChildren().at(0);
    _headKuang2 = _girl2->getChildren().at(0);
    _headKuang3 = _girl3->getChildren().at(0);
    _headKuang4 = _girl4->getChildren().at(0);
    _headVector.pushBack(_headKuang1);
    _headVector.pushBack(_headKuang2);
    _headVector.pushBack(_headKuang3);
    _headVector.pushBack(_headKuang4);
    Vec2 girlVec1 = _girl1->getPosition();
    Vec2 girlVec2 = _girl2->getPosition();
    Vec2 girlVec3 = _girl3->getPosition();
    Vec2 girlVec4 = _girl4->getPosition();
    float girlW = _headKuang1->getContentSize().width;
    _girl1->setPosition(WINDOW_WIDTH + girlW, _girl1->getPositionY());
    _girl2->setPosition(WINDOW_WIDTH + girlW, _girl2->getPositionY());
    _girl3->setPosition(0 - girlW , _girl3->getPositionY());
    _girl4->setPosition(0 - girlW, _girl4->getPositionY());
    
    auto move1 = EaseBackOut::create(MoveTo::create(0.5, girlVec2));
    _girl2->runAction(move1);
    auto move2 = EaseBackOut::create(MoveTo::create(0.5, girlVec1));
    _girl1->runAction(Sequence::create(move1->clone(), DelayTime::create(0.01), move2, NULL));
    
    auto move3 = EaseBackOut::create(MoveTo::create(0.5, girlVec3));
    _girl3->runAction(move3);
    auto move4 = EaseBackOut::create(MoveTo::create(0.5, girlVec4));
    _girl4->runAction(Sequence::create(move3->clone(), DelayTime::create(0.01), move4, NULL));
    
//    setEyeBlink(girl1);
//    setEyeBlink(girl2);
//    setEyeBlink(girl3);
//    setEyeBlink(girl4);
    
}


void DressUpMediator::headTouch(Touch* touch)
{
    if(_girlIndex != -1)
        return;
    for(int i = 0; i < _headVector.size(); i++)
    {
        auto node = _headVector.at(i);
        if(GameOther::getIsClickNode(node, touch->getLocation()))
        {
            node->getParent()->setZOrder(1);
            _girlIndex = i;
            
        }
    }
    auto headTargetPosition = _headPortrait->getChildByName("renwukuang_xiao");
    for(int i = 0; i < _headVector.size(); i++)
    {
        if(i != _girlIndex)
        {
            auto node = _headVector.at(i)->getParent();
            node->runAction(Sequence::create(Spawn::create(
                                                           MoveTo::create(0.2, _headVector.at(_girlIndex)->getParent()->getPosition()),
                                                           ScaleTo::create(0.2, 0.5), NULL),
                                             MoveTo::create(0.5, headTargetPosition->getChildren().at(i)->getPosition()),
                                             NULL));
        }else
        {
            _headVector.at(_girlIndex)->getParent()->runAction(Sequence::create(DelayTime::create(0.2), Spawn::create(MoveTo::create(0.5, headTargetPosition->getChildren().at(_girlIndex)->getPosition()), ScaleTo::create(0.5, 0.5), NULL), NULL));
            auto girlParent = this->getPlayerNode()->getChildByName("girl_kongbai_dressup");
            _girl = girlParent->getChildren().at(3 - _girlIndex);
            _girl->setVisible(true);
            Vec2 girlVec = _girl->getPosition();
            _girl->setPositionX(-GIRL_W);
            _girl->runAction(EaseBackOut::create(MoveTo::create(0.5, girlVec)));
            
            setEyeBlink(_girl);
            setGirlNormal(_girl, _girlIndex);
            funcButtonShow();
        }
    }
}


void DressUpMediator::setGirlLaugh(Node* node, int girlIndex, bool isBigRenwu)
{
    char str[40];
    char str1[40];
    
    int mouthIndex;
    int yanzheIndex;
    if(isBigRenwu)
    {
        sprintf(str, "laughzui_girl%d_dressup.png", girlIndex + 1);
        sprintf(str1, "laughzhe_girl%d_dressup.png", girlIndex + 1);
        yanzheIndex = 4;
        mouthIndex = 3;
    }else
    {
        sprintf(str, "laughzui_girl%d_renwukuang.png", girlIndex + 1);
        sprintf(str1, "laughzhe_girl%d_renwukuang.png", girlIndex + 1);
        yanzheIndex = 2;
        mouthIndex = 1;
    }
    
    auto eyeZhe = ((Sprite*)node->getChildren().at(yanzheIndex));
    eyeZhe->setVisible(true);
    eyeZhe->setTexture(str1);
    auto mouth = (Sprite*)node->getChildren().at(mouthIndex);
    if(mouth->getNumberOfRunningActions() == 0)
    {
        mouth->runAction(Sequence::create(ScaleTo::create(0.2, 0.8), CallFunc::create([=](){
            (mouth)->setTexture(str);
        }), ScaleTo::create(0.2, 1), DelayTime::create(1), CallFunc::create([=](){
            setGirlNormal(node, girlIndex, isBigRenwu);
        }), NULL));
    }
    
    
}
void DressUpMediator::setGirlNormal(Node* node, int girlIndex, bool isBigRenwu)
{
    char str[40];
    int mouthIndex;
    int yanzheIndex;
    if(isBigRenwu)
    {
        sprintf(str, "normalzui_girl%d_dressup.png", girlIndex + 1);
        yanzheIndex = 4;
        mouthIndex = 3;
    }else
    {
        sprintf(str, "normalzui_girl%d_renwukuang.png", girlIndex + 1);
        yanzheIndex = 2;
        mouthIndex = 1;
    }
    auto mouth = (Sprite*)node->getChildren().at(mouthIndex);
    mouth->runAction(Sequence::create(ScaleTo::create(0.2, 0.8), CallFunc::create([=](){
        (mouth)->setTexture(str);
    }), ScaleTo::create(0.2, 1), NULL));
    
    ((Sprite*)node->getChildren().at(yanzheIndex))->setVisible(false);
}

void DressUpMediator::setTouxiangLaugh(Node* node)
{
    char str[40];
    char str1[40];
    sprintf(str, "laughzui_girl%d_renwukuang.png", _girlIndex + 1);
    sprintf(str1, "laughzhe_girl%d_renwukuang.png", _girlIndex + 1);
    ((Sprite*)node->getChildren().at(3))->setTexture(str);
    ((Sprite*)node->getChildren().at(4))->setTexture(str1);
}
void DressUpMediator::setTouxiangNormal(Node* node)
{
    char str[40];
    sprintf(str, "normalzui_girl%d_renwukuang.png", _girlIndex + 1);
    ((Sprite*)node->getChildren().at(3))->setTexture(str);
    ((Sprite*)node->getChildren().at(4))->setVisible(false);
}
void DressUpMediator::setEyeBlink(Node* node)
{
    Node* __yanpi = node->getChildByName("biyandonghua");
    __yanpi->runAction(RepeatForever::create(Sequence::create(CallFunc::create([=](){
        __yanpi->getChildren().at(0)->setVisible(true);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(1)->setVisible(true);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(2)->setVisible(true);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(2)->setVisible(false);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(1)->setVisible(false);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(0)->setVisible(false);
    }),
                                                              DelayTime::create(3.0f),
                                                              NULL)));
}

void DressUpMediator::setEyeBlinkOne(Node* node, int girlIndex, int laugh)
{
    Node* __yanpi = node->getChildByName("biyandonghua");
    __yanpi->runAction(Sequence::create(CallFunc::create([=](){
        __yanpi->getChildren().at(0)->setVisible(true);
    }),
                                                              DelayTime::create(0.1f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(1)->setVisible(true);
    }),
                                                              DelayTime::create(0.1f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(2)->setVisible(true);
    }),
                                                              DelayTime::create(0.1f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(2)->setVisible(false);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(1)->setVisible(false);
    }),
                                                              DelayTime::create(0.05f),
                                                              CallFunc::create([=](){
        __yanpi->getChildren().at(0)->setVisible(false);
    }),
                                                              NULL));
    if(laugh)
    {
        setGirlLaugh(node, girlIndex, false);
    }else
    {
        setGirlNormal(node, girlIndex, false);
    }
}

void DressUpMediator::update(float dt)
{
    if(_girl1)
    {
        if(isTouxiangGirl1)
        {
            isTouxiangGirl1 = false;
            float rand = random(1, 8);
            int laugh = (int)random(0, 1);
            this->runAction(Sequence::create(DelayTime::create(rand), CallFunc::create([=](){
                setEyeBlinkOne(_girl1, 0, laugh);
            }), DelayTime::create(1), CallFunc::create([=]()mutable{
                isTouxiangGirl1 = true;
            }), NULL));
        }
        if(isTouxiangGirl2)
        {
            isTouxiangGirl2 = false;
            float rand = random(1, 8);
            int laugh = (int)random(0, 1);
            this->runAction(Sequence::create(DelayTime::create(rand), CallFunc::create([=](){
                setEyeBlinkOne(_girl2, 1, laugh);
            }), DelayTime::create(1), CallFunc::create([=]()mutable{
                isTouxiangGirl2 = true;
            }), NULL));
        }
        if(isTouxiangGirl3)
        {
            isTouxiangGirl3 = false;
            float rand = random(1, 8);
            int laugh = (int)random(0, 1);
            this->runAction(Sequence::create(DelayTime::create(rand), CallFunc::create([=](){
                setEyeBlinkOne(_girl3, 2, laugh);
            }), DelayTime::create(1), CallFunc::create([=]()mutable{
                isTouxiangGirl3 = true;
            }), NULL));
        }
        if(isTouxiangGirl4)
        {
            isTouxiangGirl4 = false;
            float rand = random(1, 8);
            int laugh = (int)random(0, 1);
            this->runAction(Sequence::create(DelayTime::create(rand), CallFunc::create([=](){
                setEyeBlinkOne(_girl4, 3, laugh);
            }), DelayTime::create(1), CallFunc::create([=]()mutable{
                isTouxiangGirl4 = true;
            }), NULL));
        }
    }
    
}

void DressUpMediator::loadResources()
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
