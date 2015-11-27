//
//  MakeAndSleep.cpp
//  Christmas
//
//  Created by apple12 on 15/11/25.
//
//

#include "MakeAndSleep.h"
#include "GameScene.h"
#include "MenuLayer.h"
//#include "ADManager.h"
#include "GameListIconMediator.h"
#include "GameEffectLayer.h"

#define     QUYU_NAME                       "quyu_gongjulan2_kapian"
#define     SIGNQUYU_NAME                   "quyu_gongjulan_qianming"

#define             VERTICAL_LIST_TAG           100
#define             HORIZONTAL_LIST_TAG         1000

#define             WASCAIJIAN_TAG      1000
#define             WASMOVED_TAG        1001

#define             LAYER_TAG           1001

#define         GIRL_W          156

#define         HEZI                0
#define         WANJU               1
#define         HUDIEJIE            2
#define         DUANDAI             3
#define         WANJU_INDEX         4

void MakeAndSleep::onEnter()
{
    this->onRun();
    ButtonMediator::onEnter();
}
void MakeAndSleep::onExit()
{
    instance = NULL;
    ButtonMediator::onExit();
}
void MakeAndSleep::onRun()
{
    _caijianOK = 0;
    mianhuaCount = 0;
    _tangguoIndex = 0;
    _selectClothIndex = 0;
    completeLoading1 = false;
    completeLoading2 = false;
    completeLoading3 = false;
    completeLoading4 = false;
    isJiazi = false;
    isTouch = true;
    pImage = NULL;
    _shuijiaoZiNode = GameMain::gameMainInstance->makeUpNode1;
    _listNode = GameReaderManager::getNodeReaderFile("snowman_jiazi.csb", LEFT_CENTER, 0);
    _csbNode = GameReaderManager::getNodeReaderFile("shuijiao_zi_tanguo_ui.csb", LEFT_CENTER, 0);
    _colorNode = GameReaderManager::getNodeReaderFile("shuijiao_zi_dress_ui2.csb", RIGHT_CENTER, 0);
    toumingquyu = _listNode->getChildByName("quyu_snowman");
    _csbNode->setPositionX(-_listNode->getContentSize().width/2);
    _listNode->setPositionX(_listNode->getPositionX() - _listNode->getContentSize().width/2);
    _colorNode->setPositionX(_colorNode->getChildren().at(2)->getContentSize().width);
    this->addChild(_csbNode);
    this->addChild(_listNode);
    this->addChild(_colorNode);
    _buouNode = _shuijiaoZiNode->getChildByName("buou");
    _tangguoNode = _shuijiaoZiNode->getChildByName("tangguo");
    _qunziNode = _shuijiaoZiNode->getChildByName("dress");
    _tiaosezhenSprite = (Sprite*)_colorNode->getChildByName("tiaoseban3_zizhizuo");
    loadResources();
    instance = this;
    
//    auto zhenxiantuan = _buouNode->getChildByName("zhenxiantuan");
//    Vec2 vec = zhenxiantuan->getPosition();
//    zhenxiantuan->setVisible(true);
//    zhenxiantuan->setPositionX(vec.x + 300);
//    zhenxiantuan->runAction(MoveTo::create(0.5, vec));
//    initListContent(0);
    loadingBar1 = static_cast<LoadingBar*>(_buouNode->getChildByName("LoadingBar_1"));
    loadingBar1->setVisible(true);
    loadingBar2 = static_cast<LoadingBar*>(_buouNode->getChildByName("LoadingBar_2"));
    loadingBar2->setVisible(true);
    loadingBar3 = static_cast<LoadingBar*>(_buouNode->getChildByName("LoadingBar_3"));
    loadingBar3->setVisible(true);
    loadingBar4 = static_cast<LoadingBar*>(_buouNode->getChildByName("LoadingBar_4"));
    loadingBar4->setVisible(true);
//    enterDressup();
    qipaoLogic(0);
    qipaoLogic(1);
    qipaoLogic(2);
//    enterTanguo();
//    enterBuou();
}

bool MakeAndSleep::onTouchBegan(Touch *touch, Event *unused_event)
{
    if((this->getClickTargetNode() || this->getDropTargetNode()))
        return false;
    _beginVec2 = touch->getLocation();
    _moveVec2 = touch->getLocation();
    
    if(GameScene::gameScene->menuLayerInstance->menuButton(touch, false, GameScene::gameScene->_hasLeft, GameScene::gameScene->_hasRight))
        return true;
    if(GameOther::getIsClickNode(toumingquyu, _beginVec2))
    {
        return true;
    }else
    {
        if(GameOther::getIsClickNode(_listNode->getChildByName("guanbi_snowman"), _beginVec2))
        {
            jiaziMoveOut(_listNode);
            return true;
        }
//        if(GameOther::getIsClickNode(_listNodeTanguo->getChildByName("guanbi_snowman"), _beginVec2))
//        {
//            jiaziMoveOut(_listNodeTanguo);
//            return true;
//        }
        if(judgeListMove())
            return true;
        if(buttonTouch(touch))
            return true;
        if(selectClothTouch(touch))
            return true;
        if(buouPointTouch(touch))
            return true;
        if(saveBuou(touch))
            return true;
        if(saveDress(touch))
            return true;
        if(saveTangguo(touch))
            return true;
        if(selectQunziTouch(touch))
            return true;
        if(qunziPointTouch(touch))
            return true;
        if(qipaoTouch(touch))
            return true;
        zhentouTouch(touch);
        mianhuatouTouch(touch);
        if(GameOther::getIsClickNode(_tiaosezhenSprite, touch->getLocation()))
        {
            deltaY= touch->getLocation().y/GameOther::getWindowSmallScale() - _tiaosezhenSprite->getPositionY();
            if(!pImage)
                pImage = GameOther::createImageFromSprite((Sprite*)_colorNode->getChildByName("tiaoseban2_zizhizuo"));
            
            isColorZhizhen = true;
        }
    }
    DropMediator::setMenuLayerTouch(GameScene::gameScene->menuLayerInstance, touch);
    return true;
}

void MakeAndSleep::onTouchMoved(Touch *touch, Event *unused_event)
{
    this->onVirtualDropMove(touch);
}

void MakeAndSleep::onTouchEnded(Touch *touch, Event *unused_event)
{
    isColorZhizhen = false;
    this->touchEnd(touch);
    Node* parentNode;
    if(_stateIndex == STATE_BUOU)
    {
        parentNode = _buouNode;
    }else if(_stateIndex == STATE_DRESS)
    {
        parentNode = _qunziNode;
    }else
        return;
    hideLoadingBarArrow(parentNode);
    //    this->onEnd(touch);
}

void MakeAndSleep::onTouchCancelled(Touch *touch, Event *unused_event)
{
    this->touchEnd(touch);
    //    this->onEnd(touch);
}

void MakeAndSleep::touchEnd(Touch *touch)
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

void MakeAndSleep::touchEndFunc(const string& str, int index)
{
    Node* childNode = this->getClickTargetNode();
    
}

bool MakeAndSleep::buttonTouch(Touch* touch)
{
    auto buttonParent = _csbNode;
    for(int i = 1; i < buttonParent->getChildrenCount(); i++)
    {
        if(GameOther::getIsClickNode(buttonParent->getChildren().at(i), touch->getLocation()))
        {
            initListContent(i);
            return true;
        }
    }
}

bool MakeAndSleep::selectClothTouch(Touch* touch)
{
    if(!_buouNode->isVisible())
        return false;
    auto buliaoParent = _buouNode->getChildByName("buliaoxuanze");
    auto buliaoCaijianParent = _buouNode->getChildByName("buliaocaijian");
    Vec2 vec = touch->getLocation();
    for(int i = 0;i < buliaoParent->getChildrenCount(); i++)
    {
        if(GameOther::getIsClickNode(buliaoParent->getChildren().at(i), vec))
        {
            buliaoParent->setVisible(false);
            buliaoCaijianParent->getChildren().at(i)->setVisible(true);
            _buouNode->getChildByName("caijianxian_buou")->setVisible(true);
            _buouNode->getChildByName("caijianPoint")->setVisible(true);
            _selectClothIndex = i;
            return true;
        }
    }
    return false;
}

bool MakeAndSleep::selectQunziTouch(Touch* touch)
{
    auto buliaoParent = _qunziNode->getChildByName("xuanze");
    auto buliaoCaijianParent = _qunziNode->getChildByName("caijian");
    Vec2 vec = touch->getLocation();
    for(int i = 0;i < buliaoParent->getChildrenCount(); i++)
    {
        if(GameOther::getIsClickNode(buliaoParent->getChildren().at(i), vec))
        {
            buliaoParent->setVisible(false);
            buliaoCaijianParent->getChildren().at(i)->setVisible(true);
            _qunziNode->getChildByName("caijian")->getChildren().at(i)->getChildByName("caijianxian_qunzi1")->setVisible(true);
            _qunziNode->getChildByName("qunzi1Points")->setVisible(true);
            _selectClothIndex = i;
            return true;
        }
    }
    return false;
}

bool MakeAndSleep::buouPointTouch(Touch* touch)
{
    auto caijianPoint = _buouNode->getChildByName("caijianPoint");
    Vec2 vec = touch->getLocation();
    for(int i = 0; i < caijianPoint->getChildrenCount(); i++)
    {
        auto point = caijianPoint->getChildren().at(i);
        if(point->getTag() != WASCAIJIAN_TAG && point->getTag() != WASMOVED_TAG && GameOther::getIsClickNode(point, vec))
        {
            point->setTag(WASCAIJIAN_TAG);
            ((Sprite*)point)->setTexture("dian2_caijian.png");
            decodePoint(point->getName());
            return true;
        }
    }
    return false;
}

bool MakeAndSleep::qunziPointTouch(Touch* touch)
{
    auto caijianPoint = _qunziNode->getChildByName("qunzi1Points");
    Vec2 vec = touch->getLocation();
    for(int i = 0; i < caijianPoint->getChildrenCount(); i++)
    {
        auto point = caijianPoint->getChildren().at(i);
        if(point->getTag() != WASCAIJIAN_TAG && point->getTag() != WASMOVED_TAG && GameOther::getIsClickNode(point, vec))
        {
            point->setTag(WASCAIJIAN_TAG);
            ((Sprite*)point)->setTexture("dian2_caijian.png");
            decodeQunziPoint(point->getName());
            return true;
        }
    }
    return false;
}

void MakeAndSleep::zhentouTouch(Touch* touch)
{
    Node* parentNode;
    if(_stateIndex == STATE_BUOU)
    {
        parentNode = _buouNode;
    }else if(_stateIndex == STATE_DRESS)
    {
        parentNode = _qunziNode;
    }else
        return;
    auto zhen = parentNode->getChildByName("zhenxiantuan")->getChildByName("zhen_zizhizuo");
    Vec2 vec = touch->getLocation();
    if(GameOther::getIsClickNode(zhen, vec))
    {
        addDropIconSprite((Sprite*)zhen, vec);
        showLoadingBarArrow(parentNode);
    }
}

void MakeAndSleep::mianhuatouTouch(Touch* touch)
{
    auto mianhua = _buouNode->getChildByName("mianhua_buou");
    Vec2 vec = touch->getLocation();
    if(GameOther::getIsClickNode(mianhua, vec))
    {
        addDropIconSprite((Sprite*)mianhua, vec);
    }
}

void MakeAndSleep::decodePoint(const string& str)
{
    bool isPointDone = true;
    auto caijianPoint = _buouNode->getChildByName("caijianPoint");
    for(int i = 0; i < caijianPoint->getChildrenCount(); i++)
    {
        auto point = caijianPoint->getChildren().at(i);
        if(point->getName().find(str) != string::npos)
        {
            if(point->getTag() != WASCAIJIAN_TAG)
            {
                isPointDone = false;
                break;
            }
        }
    }
    if(isPointDone)
    {
        _caijianOK++;
        int index = GameOther::getStrNumber(str, "dian");
        auto node = _buouNode->getChildByName("buliaocaijian")->getChildren().at(_selectClothIndex)->getChildren().at(5 - index);
       if(index == 2)
       {
           node->runAction(MoveBy::create(0.5, Vec2(-100, 0)));
       }else if(index == 3)
       {
           node->runAction(MoveBy::create(0.5, Vec2(0, 100)));
       }else if(index == 4)
       {
           node->runAction(MoveBy::create(0.5, Vec2(-50, -100)));
       }else if(index == 5)
       {
           node->runAction(MoveBy::create(0.5, Vec2(100, 0)));
       }
        if(_caijianOK == 4)
        {
            int count  = _buouNode->getChildByName("buliaocaijian")->getChildren().at(_selectClothIndex)->getChildrenCount();
            for(int i = 0; i < count; i++)
            {
                auto n = _buouNode->getChildByName("buliaocaijian")->getChildren().at(_selectClothIndex)->getChildren().at(i);
                if(i != count - 1)
                {
                    n->runAction(FadeOut::create(2));
                    auto xian = _buouNode->getChildByName("caijianxian_buou");
                    auto pointParent = _buouNode->getChildByName("caijianPoint");
                    xian->runAction(FadeOut::create(2));
                    pointParent->runAction(FadeOut::create(2));
                    auto zhenxiantuan = _buouNode->getChildByName("zhenxiantuan");
                    Vec2 vec = zhenxiantuan->getPosition();
                    zhenxiantuan->setVisible(true);
                    zhenxiantuan->setPositionX(vec.x + 300);
                    zhenxiantuan->runAction(MoveTo::create(0.5, vec));
                }
            }
        }
    }
}

void MakeAndSleep::decodeQunziPoint(const string& str)
{
    bool isPointDone = true;
    auto caijianPoint = _qunziNode->getChildByName("qunzi1Points");
    for(int i = 0; i < caijianPoint->getChildrenCount(); i++)
    {
        auto point = caijianPoint->getChildren().at(i);
        if(point->getName().find(str) != string::npos)
        {
            if(point->getTag() != WASCAIJIAN_TAG)
            {
                isPointDone = false;
                break;
            }
        }
    }
    if(isPointDone)
    {
        _caijianOK++;
        int index = GameOther::getStrNumber(str, "dian");
        auto node = _qunziNode->getChildByName("caijian")->getChildren().at(_selectClothIndex)->getChildren().at(5 - index);
        if(index == 2)
        {
            node->runAction(MoveBy::create(0.5, Vec2(-100, 0)));
        }else if(index == 3)
        {
            
            node->runAction(MoveBy::create(0.5, Vec2(-50, -100)));
        }else if(index == 4)
        {
            
            node->runAction(MoveBy::create(0.5, Vec2(0, 100)));
        }else if(index == 5)
        {
            node->runAction(MoveBy::create(0.5, Vec2(100, 0)));
        }
        if(_caijianOK == 4)
        {
            int count  = _qunziNode->getChildByName("caijian")->getChildren().at(_selectClothIndex)->getChildrenCount();
            for(int i = 0; i < 5; i++)
            {
                auto n = _qunziNode->getChildByName("caijian")->getChildren().at(_selectClothIndex)->getChildren().at(i);
                if(i != 5 - 1)//count 5
                {
                    n->runAction(FadeOut::create(2));
                    auto xian = _qunziNode->getChildByName("caijian")->getChildren().at(_selectClothIndex)->getChildByName("caijianxian_qunzi1");
                    auto pointParent = _qunziNode->getChildByName("qunzi1Points");
                    xian->runAction(FadeOut::create(2));
                    pointParent->runAction(FadeOut::create(2));
                    auto zhenxiantuan = _qunziNode->getChildByName("zhenxiantuan");
                    Vec2 vec = zhenxiantuan->getPosition();
                    zhenxiantuan->setVisible(true);
                    zhenxiantuan->setPositionX(vec.x + 300);
                    zhenxiantuan->runAction(MoveTo::create(0.5, vec));
                }
            }
        }
    }
}

Node* MakeAndSleep::decodeYingZi(Node* yingZiNode, bool isVisible)
{
    if(!yingZiNode || yingZiNode->getName() == "biankuang1")
        return NULL;
    
    string __name = yingZiNode->getName().c_str();
    Node* __targetNode = yingZiNode->getParent()->getChildByName("_" +__name);
    if(__targetNode)
        __targetNode->setVisible(isVisible);
    return __targetNode;
}

void MakeAndSleep::loadResources()
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

void MakeAndSleep::initListContent(int indexListType)
{
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);

    bool isDrop = true;
    bool isVertical = true;
    std::vector<ListIconMediator*> _iconList;
    char spriteName[40];
    int count = 0;
    if(indexListType == boxType)
    {
        count = 12;
    }else if(indexListType == tangzhiType)
    {
        count = 6;
    }else
    {
        count = 6;
    }
//    tangguoType,
//    tangzhiType,
//    tangguoboxType,
//    tangguoduandaiType,
    for(int i = 0 ; i < count; i++)
    {
        if(indexListType == boxType)
        {
            if(i < 6)
                sprintf(spriteName, "_hezi%d_zizhizuo.png", i + 1);
            else
                sprintf(spriteName, "_duandai%d_zizhizuo.png", i + 1 - 6);
        }else if(indexListType == tangguoType)
        {
            sprintf(spriteName, "_tangguo%d_zizhizuo.png", i + 1);
        }else if(indexListType == tangzhiType)
        {
            sprintf(spriteName, "_tangzhi%d_tangguo%d_zizhizuo.png", i + 1, _tangguoIndex + 1);
        }else if(indexListType == tangguoboxType)
        {
            sprintf(spriteName, "_hezi%d_zizhizuo.png", i + 1);
        }else if(indexListType == tangguoduandaiType)
        {
            sprintf(spriteName, "_duandai%d_zizhizuo.png", i + 1);
        }else if(indexListType == hudiejieType)
        {
            sprintf(spriteName, "_hudiejie%d_qunzi.png", i + 1);
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
    touming = toumingquyu;
    size =  touming->getContentSize();
    _list->setListView(&_iconList, isVertical, size, isDrop);
    _list->_tableView->setScrollTouch(false);
    int scrollCount = 6;
    if(count >= scrollCount)
    {
        isRunSlider = true;
        float deltatime = 0.02f;
        _list->runSlideEnd(Vec2(0, size.height));
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
    _iconList.clear();

    DropMediator::_curListType = indexListType;
    Node* listN;
//    if(indexListType == boxType)
//    {
        listN = _listNode;
//    }
//    else
//    {
//        listN = _listNodeTanguo;
//    }
    jiaziMoveIn(listN);
}

void MakeAndSleep::onListClick(Sprite* sprite, int index)
{
    bool isLaugh = false;
    if(DropMediator::_curListType == boxType)
    {
        if(index < 6)
        {
            isLaugh = true;
            dressFlyUp(sprite, "hezi_di", "hezi%d_1_zizhizuo.png", index + 1);
            dressFlyUp(sprite, "heigai", "hezi%d_2_zizhizuo.png", index + 1, false);
        }else
        {
            isLaugh = true;
            dressFlyUp(sprite, "duandai", "duandai%d_zizhizuo.png", index + 1 - 6);
        }
    }else if(DropMediator::_curListType == tangguoType)
    {
        char str[40];
        sprintf(str, "tangguo%d_zizhizuo.png", index + 1);
        dressFlyUpTangguo(sprite, "tangguo", str, index + 1);
        _tangguoIndex = index;
    }else if(DropMediator::_curListType == tangzhiType)
    {
        char str[40];
        sprintf(str, "tangzhi%d_tangguo%d_zizhizuo.png", index + 1, _tangguoIndex + 1);
        dressFlyUpTangguo(sprite, "tangzhi", str, (index + 1));
    }else if(DropMediator::_curListType == tangguoboxType)
    {
        dressFlyUp(sprite, "hezi_di", "hezi%d_1_zizhizuo.png", index + 1);
        dressFlyUp(sprite, "heigai", "hezi%d_2_zizhizuo.png", index + 1, false);
    }else if(DropMediator::_curListType == tangguoduandaiType)
    {
        dressFlyUp(sprite, "duandai", "duandai%d_zizhizuo.png", index + 1);
    }else if(DropMediator::_curListType == hudiejieType)
    {
        char str[40];
        sprintf(str, "hudiejie%d_qunzi.png", index + 1);
        dressFlyUpTangguo(sprite, "hudiejie", str, index + 1);
    }
    
}

void MakeAndSleep::dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite;
    int zorder = -1;
    if(strcmp(partName, "hezi_di") == 0)
    {
        partSprite = (Sprite*)_shuijiaoZiNode->getChildByName(partName);
    }else
    {
        zorder = 0;
        partSprite = (Sprite*)_shuijiaoZiNode->getChildByName("hezi")->getChildByName(partName);
    }
    
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);

    Vec2 vec = sprite->getPosition();
    Sprite* flySp = Sprite::create(meitongstr);
    _shuijiaoZiNode->addChild(flySp, zorder);
    flySp->setPosition(sprite->getParent()->convertToWorldSpace(sprite->getPosition()));
    flySp->setScale(0);
    flySp->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())),
                                                    ScaleTo::create(0.5, 1), NULL), RemoveSelf::create(), CallFunc::create([=](){
        partSprite->setTexture(meitongstr);
    }), NULL));



    if(sprite)
        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeAndSleep::dressFlyUpTangguo(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds)
{
    if(isSounds)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* partSprite;
    if(strcmp(partName, "tangguo") == 0)
    {
        for(int i = 0;i < 6; i++)
        {
            ((Sprite*)_tangguoNode->getChildren().at(i)->getChildren().at(0))->setTexture("touming.png");
            ((Sprite*)_tangguoNode->getChildren().at(i)->getChildren().at(1))->setTexture("touming.png");
        }
        partSprite = (Sprite*)_tangguoNode->getChildren().at(idx - 1)->getChildren().at(0);
        partSprite->getParent()->setVisible(true);
        
    }else if(strcmp(partName, "tangzhi") == 0)
    {
        partSprite = (Sprite*)_tangguoNode->getChildren().at(_tangguoIndex)->getChildren().at(1);
        partSprite->getParent()->setVisible(true);
    }else if(strcmp(partName, "hudiejie") == 0)
    {
        partSprite = (Sprite*)_qunziNode->getChildByName("hudiejie");
        partSprite->getParent()->setVisible(true);
    }
//    Vec2 vec = sprite->getPosition();
//    partSprite->setTexture(pngName);
    char str[40];
    sprintf(str, pngName);
    Sprite* flySp = Sprite::create(pngName);
    this->addChild(flySp);
    flySp->setPosition(sprite->getParent()->convertToWorldSpace(sprite->getPosition()));
    flySp->setScale(0);
    flySp->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5, partSprite->getParent()->convertToWorldSpace(partSprite->getPosition())),
                                                    ScaleTo::create(0.5, 1*GameOther::getWindowSmallScale()), NULL), RemoveSelf::create(), CallFunc::create([=](){
        partSprite->setTexture(str);
    }), NULL));
    
    
    
    if(sprite)
        GameOther::changeGRAYNodeToWhite(dynamic_cast<Node*>(sprite));
}

void MakeAndSleep::onVirtualDropBegin(Touch* pTouch)
{
}

void MakeAndSleep::onVirtualDropMove(Touch* pTouch)
{
    buouPointTouch(pTouch);
    qunziPointTouch(pTouch);
    if(_dropIcon)
    {
        Vec2 vec = pTouch->getLocation();
        _dropIcon->setPosition(vec);
        Node* parentNode;
        if(_stateIndex == STATE_BUOU)
        {
            parentNode = _buouNode;
        }else if(_stateIndex == STATE_DRESS)
        {
            char str[40];
            sprintf(str, "qunzi%d", _selectClothIndex + 1);
            parentNode = _qunziNode->getChildByName("caijian")->getChildByName(str);
        }
        if(GameOther::getIsClickRectNode(parentNode->getChildByName("toumingcheck1"), vec, _dropIcon->getContentSize().width) && !completeLoading1)
        {
            onEndCallBack();
            loadingIndex = 4;
            completeLoading1 = true;
            auto zhenxiantuan = parentNode->getChildByName("zhen_zizhizuo1");
            zhenxiantuan->setVisible(true);
            zhenxiantuan->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateBy::create(0.2, 10), NULL), 3), RemoveSelf::create(), NULL));
            scheduleUpdate();
        }else if(GameOther::getIsClickRectNode(parentNode->getChildByName("toumingcheck4"), vec, _dropIcon->getContentSize().width) && !completeLoading2)
        {
            onEndCallBack();
            loadingIndex = 3;
            completeLoading2 = true;
            auto zhenxiantuan = parentNode->getChildByName("zhen_zizhizuo4");
            zhenxiantuan->setVisible(true);
            zhenxiantuan->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateBy::create(0.2, 10), NULL), 3), RemoveSelf::create(), NULL));
            scheduleUpdate();
        }else if(GameOther::getIsClickRectNode(parentNode->getChildByName("toumingcheck3"), vec, _dropIcon->getContentSize().width) && !completeLoading3)
        {
            onEndCallBack();
            loadingIndex = 2;
            completeLoading3 = true;
            auto zhenxiantuan = parentNode->getChildByName("zhen_zizhizuo3");
            zhenxiantuan->setVisible(true);
            zhenxiantuan->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateBy::create(0.2, 10), NULL), 3), RemoveSelf::create(), NULL));
            scheduleUpdate();
        }else if(GameOther::getIsClickRectNode(parentNode->getChildByName("toumingcheck2"), vec, _dropIcon->getContentSize().width) && !completeLoading4)
        {
            onEndCallBack();
            loadingIndex = 1;
            completeLoading4 = true;
            auto zhenxiantuan = parentNode->getChildByName("zhen_zizhizuo2");
            zhenxiantuan->setVisible(true);
            zhenxiantuan->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateBy::create(0.2, 10), NULL), 3), RemoveSelf::create(), NULL));
            scheduleUpdate();
        }else if(GameOther::getIsClickRectNode(parentNode->getChildByName("buoukou"), vec, _dropIcon->getContentSize().width) && _dropIcon->getName().find("mianhua_buou") != string::npos)
        {
            onEndCallBack();
            mianhuaCount++;
            Sprite* sprite = Sprite::create("mianhua_buou.png");
            _buouNode->addChild(sprite);
            sprite->setName("mianhua");
            sprite->setPosition(parentNode->convertToNodeSpace(vec));
            sprite->runAction(Spawn::create(MoveTo::create(0.5, parentNode->getChildByName("buoukou")->getPosition()), ScaleTo::create(0.5, 0), NULL));
            if(mianhuaCount == 4)
            {
                auto zhenxiantuan = parentNode->getChildByName("zhen_zizhizuo");
                zhenxiantuan->runAction(Sequence::create(DelayTime::create(0.5), Show::create(), Repeat::create(Sequence::create(RotateBy::create(0.2, -10), RotateBy::create(0.2, 10), NULL), 2), CallFunc::create([=](){
                     loadingIndex = 5;
                     scheduleUpdate();
                }), RemoveSelf::create(), NULL));
            }
        }
    }
    if(isColorZhizhen)
    {
        auto colorBan = (Sprite*)_colorNode->getChildByName("tiaoseban2_zizhizuo");
        Vec2 vecTouch = pTouch->getLocation();
        if((vecTouch.y/GameOther::getWindowSmallScale() <= colorBan->getContentSize().height/2 + colorBan->getPositionY() + deltaY)&& (vecTouch.y/GameOther::getWindowSmallScale() >= -colorBan->getContentSize().height/2 + colorBan->getPositionY() + deltaY))
        {
            _tiaosezhenSprite->setPositionY(vecTouch.y/GameOther::getWindowSmallScale() - deltaY);
            Vec2 vec = colorBan->convertToNodeSpace(_tiaosezhenSprite->getParent()->convertToWorldSpace(_tiaosezhenSprite->getPosition()));
            int num = ((pImage->getHeight() - (int)(vec.y)) * pImage->getWidth() + (int)(vec.x)) * 4;
            if(num > 0 && num + 3 < pImage->getDataLen())
            {
                _r = (pImage->getData()[num]);
                _g = (pImage->getData()[num + 1]);
                _b = (pImage->getData()[num + 2]);
                _a = (pImage->getData()[num + 3]);
                
                _curQunzi->setColor(Color3B(_r, _g, _b));
                _curQunzi->setOpacity(_a);
                log("r: %f     g: %f      b: %f", _r, _g, _b);
                
            }
            
        }
    }
}

void MakeAndSleep::onVirtualDropEnd(Touch* pTouch)
{
}

void MakeAndSleep::update(float dt)
{
    int value = 10;
    bool ret = false;
    if(loadingIndex == 1)
    {
        if(loadingBar1->getPercent() < 100)
        {
            loadingBar1->setPercent(loadingBar1->getPercent() + value);
        }else
        {
            if(completeLoading1 && completeLoading2 && completeLoading3 && completeLoading4)
            {
                ret = true;
            }
            unscheduleUpdate();
        }
    }
    if(loadingIndex == 2)
    {
        if(loadingBar2->getPercent() < 100)
        {
            loadingBar2->setPercent(loadingBar2->getPercent() + value);
        }else
        {
            if(completeLoading1 && completeLoading2 && completeLoading3 && completeLoading4)
            {
                ret = true;
            }
            unscheduleUpdate();
        }
    }
    if(loadingIndex == 3)
    {
        if(loadingBar3->getPercent() < 60)
        {
            loadingBar3->setPercent(loadingBar3->getPercent() + value);
        }else
        {
            if(completeLoading1 && completeLoading2 && completeLoading3 && completeLoading4)
            {
                ret = true;
            }
            unscheduleUpdate();
        }
    }
    if(loadingIndex == 4)
    {
        if(loadingBar4->getPercent() < 100)
        {
            loadingBar4->setPercent(loadingBar4->getPercent() + value);
        }else
        {
            if(completeLoading1 && completeLoading2 && completeLoading3 && completeLoading4)
            {
                ret = true;
            }
            unscheduleUpdate();
        }
    }
    if(loadingIndex == 5)
    {
        if(loadingBar3->getPercent() < 100)
        {
            loadingBar3->setPercent(loadingBar3->getPercent() + value);
        }else
        {
            buouMakeDone();
            unscheduleUpdate();
        }
    }else
    {
        if(ret)
        {
            Node* parentNode;
            if(_stateIndex == STATE_BUOU)
            {
                parentNode = _buouNode;
            }else if(_stateIndex == STATE_DRESS)
            {
                parentNode = _qunziNode;
            }
            auto zhenxiantuan = parentNode->getChildByName("zhenxiantuan");
            Vec2 vec = zhenxiantuan->getPosition();
            //        zhenxiantuan->setPositionX(vec.x + 300);
            zhenxiantuan->runAction(Sequence::create(MoveTo::create(0.5, Vec2(vec.x + 300, vec.y)), CallFunc::create([=](){
                if(_stateIndex == STATE_BUOU)
                {
                    auto mianhua = _buouNode->getChildByName("mianhua_buou");
                    Vec2 vec = mianhua->getPosition();
                    mianhua->setVisible(true);
                    mianhua->setPositionX(vec.x + 300);
                    mianhua->runAction(MoveTo::create(0.5, vec));
                }else if(_stateIndex == STATE_DRESS)
                {
                    char str[40];
                    sprintf(str, "qunzi%d", _selectClothIndex + 1);
                    auto qunziParent = _qunziNode->getChildByName("qunzi");
                    qunziParent->setVisible(true);
                    auto qunzi = qunziParent->getChildByName(str);
                    qunzi->setVisible(true);
//                    qunzi->setOpacity(0);
//                    qunzi->runAction(FadeIn::create(0.5));
                    _curQunzi = (Sprite*)qunzi->getChildren().at(1);
                    _qunziNode->getChildByName("caijian")->runAction(FadeOut::create(0.5));
                    _colorNode->runAction(MoveBy::create(0.5, Vec2(-_colorNode->getChildren().at(0)->getContentSize().width, 0)));
                    initListContent(hudiejieType);
                }
                
            }), NULL));
        }
    }
    
}

void MakeAndSleep::showLoadingBarArrow(Node* jiantouParent)
{
    if(!completeLoading1)
    {
        if(_stateIndex == STATE_BUOU)
        {
            auto arrow = jiantouParent->getChildByName("jiantou_zizhizuo1");
            arrow->setVisible(true);
        }else if(_stateIndex == STATE_DRESS)
        {
            char str[40];
            sprintf(str, "qunzi%d", _selectClothIndex+ 1);
            auto arrow = jiantouParent->getChildByName("caijian")->getChildByName(str)->getChildByName("jiantou_zizhizuo1");
            arrow->setVisible(true);
        }
        
    }
    if(!completeLoading4)
    {
        if(_stateIndex == STATE_BUOU)
        {
            auto arrow = jiantouParent->getChildByName("jiantou_zizhizuo2");
            arrow->setVisible(true);
        }else if(_stateIndex == STATE_DRESS)
        {
            char str[40];
            sprintf(str, "qunzi%d", _selectClothIndex+ 1);
            auto arrow = jiantouParent->getChildByName("caijian")->getChildByName(str)->getChildByName("jiantou_zizhizuo2");
            arrow->setVisible(true);
        }
    }
    if(!completeLoading3)
    {
        if(_stateIndex == STATE_BUOU)
        {
            auto arrow = jiantouParent->getChildByName("jiantou_zizhizuo3");
            arrow->setVisible(true);
        }else if(_stateIndex == STATE_DRESS)
        {
            char str[40];
            sprintf(str, "qunzi%d", _selectClothIndex+ 1);
            auto arrow = jiantouParent->getChildByName("caijian")->getChildByName(str)->getChildByName("jiantou_zizhizuo3");
            arrow->setVisible(true);
        }
    }
    if(!completeLoading2)
    {
        if(_stateIndex == STATE_BUOU)
        {
            auto arrow = jiantouParent->getChildByName("jiantou_zizhizuo4");
            arrow->setVisible(true);
        }else if(_stateIndex == STATE_DRESS)
        {
            char str[40];
            sprintf(str, "qunzi%d", _selectClothIndex + 1);
            auto arrow = jiantouParent->getChildByName("caijian")->getChildByName(str)->getChildByName("jiantou_zizhizuo4");
            arrow->setVisible(true);
        }
    }
}

void MakeAndSleep::hideLoadingBarArrow(Node* jiantouParent)
{
    char str[40];
    char dressStr[40];
    sprintf(dressStr, "qunzi%d", _selectClothIndex + 1);
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "jiantou_zizhizuo%d", i);

        Node* arrow;
        if(_stateIndex == STATE_BUOU)
        {
            arrow = jiantouParent->getChildByName(str);
        }else if(_stateIndex == STATE_DRESS)
        {
            arrow = jiantouParent->getChildByName("caijian")->getChildByName(dressStr)->getChildByName(str);
        }else
        {
            return;
        }
        arrow->setVisible(false);
    }
}
void MakeAndSleep::buouMakeDone()
{
    loadingBar1->setVisible(false);
    loadingBar2->setVisible(false);
    loadingBar3->setVisible(false);
    loadingBar4->setVisible(false);
    
     _buouNode->getChildByName("buliaocaijian")->getChildren().at(_selectClothIndex)->setVisible(false);
    _buouNode->getChildByName("wanchengbuou")->getChildren().at(_selectClothIndex)->setVisible(true);
    _buouNode->getChildByName("mianhua_buou")->runAction(MoveBy::create(0.5, Vec2(300, 0)));
    initListContent(boxType);
}

bool MakeAndSleep::judgeListMove()
{
        ListMediator* templist = NULL;
        Node* touming;
        touming = toumingquyu;
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

void MakeAndSleep::addDropIconSprite(Sprite* sprite, const Vec2& vec)
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
    string str = sprite->getName();
    _dropIcon = (GameOther::cloneSprite(sprite));
//        this->addChild(_dropIcon, 1);
    GameEffectLayer::getInstance()->addChild(_dropIcon);
    _dropIcon->setPosition(vec);
    _dropIcon->setScale(sprite->getScale() * GameOther::getWindowSmallScale());
}

void MakeAndSleep::onEndCallBack()
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
}

void MakeAndSleep::jiaziMoveIn(Node* node)
{
    if(node->getActionByTag(99))
    {
    }
    if(isJiazi)
    {
        
    }else
    {
        node->setVisible(true);
        isJiazi = true;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(node->getContentSize().width/2, 0)), NULL);
        actionInterval->setTag(99);
        node->runAction(actionInterval);
    }
    
}

bool MakeAndSleep::jiaziMoveOut(Node* node)
{
    if(isJiazi && node->isVisible())
    {
        if(node->getActionByTag(99))
            return true;
        isJiazi = false;
        isListTouch = false;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(-node->getContentSize().width/2, 0)), CallFunc::create([=](){
            Node* quyu = node->getChildByName("quyu_snowman")->getChildByTag(VERTICAL_LIST_TAG);
            quyu->removeFromParent();
            node->setVisible(false);
            isTouch = true;
            
        }), NULL);
        actionInterval->setTag(99);
        node->runAction(actionInterval);
        return true;
    }
    return false;
}

bool MakeAndSleep::saveBuou(Touch* touch)
{
    if(!_buouNode->isVisible())
        return false;
    auto duihao = _shuijiaoZiNode->getChildByName("duihao_kapian");
    if(GameOther::getIsClickNode(duihao, touch->getLocation()))
    {
        auto tangguoParent = _buouNode->getChildByName("wanchengbuou")->getChildren().at(_selectClothIndex);
        Vec2 heziTanguoVec = _shuijiaoZiNode->getChildByName("hezi")->getChildByName("qunzi_dress")->getPosition();
        tangguoParent->runAction(Sequence::create(
                                                  Spawn::create(MoveTo::create(0.5, heziTanguoVec), ScaleTo::create(0.5, 0.5), NULL), DelayTime::create(0.2f), CallFunc::create([=](){
            auto layerColor = LayerColor::create(ccc4(255, 255, 255, 255),
                                                 Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                                 Director::getInstance()->getOpenGLView()->getFrameSize().height);
            layerColor->setName("noclick");
            layerColor->setTag(LAYER_TAG);
            GameEffectLayer::getInstance()->addChild(layerColor);
            layerColor->setOpacity(0);
            layerColor->runAction(Sequence::create(FadeIn::create(0.5), CallFunc::create([=](){
                GameMain::gameMainInstance->makeUpNode2->setVisible(false);
                clearHezi();
                tangguoParent->setVisible(false);
            }), RemoveSelf::create(), NULL));
        }), NULL));
        _csbNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
        _listNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
        return true;
    }
    return false;
}

bool MakeAndSleep::saveTangguo(Touch* touch)
{
    if(!_tangguoNode->isVisible())
        return false;
    auto duihao = _shuijiaoZiNode->getChildByName("duihao_kapian");
    if(GameOther::getIsClickNode(duihao, touch->getLocation()))
    {
        auto tangguoParent = _tangguoNode->getChildren().at(_tangguoIndex);
        Vec2 heziTanguoVec = _shuijiaoZiNode->getChildByName("hezi")->getChildByName("tangguo")->getPosition();
        tangguoParent->runAction(Sequence::create(
                                 Spawn::create(MoveTo::create(0.5, heziTanguoVec), ScaleTo::create(0.5, 0.5), NULL), DelayTime::create(0.2f), CallFunc::create([=](){
            auto layerColor = LayerColor::create(ccc4(255, 255, 255, 255),
                                                 Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                                 Director::getInstance()->getOpenGLView()->getFrameSize().height);
            layerColor->setName("noclick");
            layerColor->setTag(LAYER_TAG);
            GameEffectLayer::getInstance()->addChild(layerColor);
            layerColor->setOpacity(0);
            layerColor->runAction(Sequence::create(FadeIn::create(0.5), CallFunc::create([=](){
                GameMain::gameMainInstance->makeUpNode2->setVisible(false);
                clearHezi();
                tangguoParent->setVisible(false);
            }), RemoveSelf::create(), NULL));
        }), NULL));
        _csbNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
        _listNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
        return true;
    }
    return false;
}

bool MakeAndSleep::saveDress(Touch* touch)
{
    if(!_qunziNode->isVisible())
        return false;
    auto duihao = _shuijiaoZiNode->getChildByName("duihao_kapian");
    if(GameOther::getIsClickNode(duihao, touch->getLocation()) && DropMediator::_curListType != boxType)
    {
        auto tangguoParent = _qunziNode->getChildByName("qunzi")->getChildren().at(_selectClothIndex);
        auto tangguo = tangguoParent->getChildren().at(0);
        auto tangzhi = tangguoParent->getChildren().at(1);
        auto hudiejie = _qunziNode->getChildByName("hudiejie");
        Vec2 heziTanguoVec = _shuijiaoZiNode->getChildByName("hezi")->getChildByName("qunzi_dress")->getPosition();
        Vec2 hudiejieVec = _shuijiaoZiNode->getChildByName("hezi")->getChildByName("hudiejie")->getPosition();
        Vec2 vec = Vec2(heziTanguoVec.x - tangguo->getPositionX(), heziTanguoVec.y - tangguo->getPositionY());
        tangguoParent->runAction(MoveBy::create(0.5, vec));
        hudiejie->runAction(MoveTo::create(0.5, hudiejieVec));
        tangguo->runAction(ScaleTo::create(0.5, 0.5));
        tangzhi->runAction(ScaleTo::create(0.5, 0.5));
        hudiejie->runAction(ScaleTo::create(0.5, 0.5));
        initListContent(boxType);
        return true;
    }else if(GameOther::getIsClickNode(duihao, touch->getLocation()) && DropMediator::_curListType == boxType)
    {
        auto layerColor = LayerColor::create(ccc4(255, 255, 255, 255),
                                             Director::getInstance()->getOpenGLView()->getFrameSize().width,
                                             Director::getInstance()->getOpenGLView()->getFrameSize().height);
        layerColor->setName("noclick");
        layerColor->setTag(LAYER_TAG);
        GameEffectLayer::getInstance()->addChild(layerColor);
        layerColor->setOpacity(0);
        layerColor->runAction(Sequence::create(FadeIn::create(0.5), CallFunc::create([=](){
            GameMain::gameMainInstance->makeUpNode2->setVisible(false);
            clearHezi();
            _qunziNode->setVisible(false);
        }), RemoveSelf::create(), NULL));
        _colorNode->runAction(MoveTo::create(0.5, Vec2(_colorNode->getChildren().at(2)->getContentSize().width, _colorNode->getPositionY())));
        _csbNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
        _listNode->runAction(MoveTo::create(0.5, Vec2(-_listNode->getContentSize().width/2, _csbNode->getPositionY())));
    }
    return false;
}

void MakeAndSleep::enterBuou()
{
    enterMake();
    _stateIndex = STATE_BUOU;
    _buouNode->setVisible(true);
}

void MakeAndSleep::enterTanguo()
{
    enterMake();
    _stateIndex = STATE_TANGGUO;
    _csbNode->runAction(MoveBy::create(0.5, Vec2(_listNode->getContentSize().width/2, 0)));
    _tangguoNode->setVisible(true);
    
}

void MakeAndSleep::enterDressup()
{
    enterMake();
    _qunziNode->setVisible(true);
    _stateIndex = STATE_DRESS;
    auto dressNode = _shuijiaoZiNode->getChildByName("dress");
    dressNode->setVisible(true);
    auto xuanze = dressNode->getChildByName("xuanze");
    xuanze->setVisible(true);
    
    Node* _headKuang1 = xuanze->getChildren().at(0);
    Node* _headKuang2 = xuanze->getChildren().at(1);
    Node* _headKuang3 = xuanze->getChildren().at(2);
    Node* _headKuang4 = xuanze->getChildren().at(3);
  
    Vec2 girlVec1 = _headKuang1->getPosition();
    Vec2 girlVec2 = _headKuang2->getPosition();
    Vec2 girlVec3 = _headKuang3->getPosition();
    Vec2 girlVec4 = _headKuang4->getPosition();
    float girlW = _headKuang1->getContentSize().width;
    _headKuang1->setPosition(WINDOW_WIDTH + girlW, _headKuang1->getPositionY());
    _headKuang2->setPosition(WINDOW_WIDTH + girlW, _headKuang2->getPositionY());
    _headKuang3->setPosition(0 - girlW , _headKuang3->getPositionY());
    _headKuang4->setPosition(0 - girlW, _headKuang4->getPositionY());
//
    auto move1 = EaseBackOut::create(MoveTo::create(0.5, girlVec2));
    _headKuang2->runAction(move1);
    auto move2 = EaseBackOut::create(MoveTo::create(0.5, girlVec1));
    _headKuang1->runAction(Sequence::create(move1->clone(), DelayTime::create(0.01), move2, NULL));
    
    auto move3 = EaseBackOut::create(MoveTo::create(0.5, girlVec3));
    _headKuang3->runAction(move3);
    auto move4 = EaseBackOut::create(MoveTo::create(0.5, girlVec4));
    _headKuang4->runAction(Sequence::create(move3->clone(), DelayTime::create(0.01), move4, NULL));
}

void MakeAndSleep::enterMake()
{
    GameMain::gameMainInstance->makeUpNode2->setVisible(true);
    _shuijiaoZiNode->setVisible(true);
    Node* heziModel = _shuijiaoZiNode->getChildByName("heziModel");
    
    Sprite* hezidiSprite = (Sprite*)heziModel->getChildByName("hezi_di");
    Sprite* hezigaiSprite = (Sprite*)heziModel->getChildByName("heigai");
    char str[40];
    sprintf(str, "hezi%d_1_zizhizuo.png", _compareVector.at(0) + 1);
    hezidiSprite->setTexture(str);
    sprintf(str, "hezi%d_2_zizhizuo.png", _compareVector.at(0) + 1);
    hezigaiSprite->setTexture(str);
    Sprite* duandai = (Sprite*)heziModel->getChildByName("duandai");
    sprintf(str, "duandai%d_zizhizuo.png", _compareVector.at(3) + 1);
    duandai->setTexture(str);
    Sprite* wanjuSprite;
    int r3 = random(0, 5);//hudiejie
    int r2;
    if(_compareVector.at(4) == 0)
    {
        
        r2 = random(0, 3);//哪一个玩具
        sprintf(str, "buou%d_buou.png", _compareVector.at(1) + 1);
        wanjuSprite = (Sprite*)heziModel->getChildByName("wanchengbuou");
        wanjuSprite->setTexture(str);
    }else if(_compareVector.at(4) == 1)
    {
        r2 = random(0, 35);//哪一个玩具
        sprintf(str, "tangzhi%d_tangguo%d_zizhizuo.png", (_compareVector.at(1)/6) + 1, (_compareVector.at(1)%6) + 1);
        wanjuSprite = (Sprite*)heziModel->getChildByName("tangguo");
        wanjuSprite->setTexture(str);
    }else if(_compareVector.at(4) == 2)
    {
        r2 = random(0, 3);//哪一个玩具
        sprintf(str, "qunzi%d_2_zizhizuo.png", _compareVector.at(1) + 1);
        wanjuSprite = (Sprite*)heziModel->getChildByName("qunzi_dress");
        wanjuSprite->setTexture(str);
        
        sprintf(str, "qunzi%d_1_zizhizuo.png", _compareVector.at(1) + 1);
        wanjuSprite = (Sprite*)heziModel->getChildByName("qunzi1_1_zizhizuo");
        wanjuSprite->setTexture(str);
        
        sprintf(str, "hudiejie%d_qunzi.png", _compareVector.at(2) + 1);
        wanjuSprite = (Sprite*)heziModel->getChildByName("hudiejie");
        wanjuSprite->setTexture(str);
    }
}


void MakeAndSleep::qipaoLogic(int index)
{
    auto qipao = this->getReaderUINode()->getChildByName("qipao");
    auto qipaoneiwupin = this->getReaderUINode()->getChildByName("qipaoneiwupin");
    auto qipao1 = qipao->getChildren().at(index);
    char qipaoStr[10];
    sprintf(qipaoStr, "hezi%d", index + 1);
    auto qipaoneiwupin1 = this->getReaderUINode()->getChildByName(qipaoStr);
    int rand1 = random(0, 1);//多久出现
    int randWhichone = random(0, 2);//做哪一种玩具
    int r1 = random(0, 5);//hezi
    int r4 = random(0, 5);//duandai
    
    Sprite* hezidiSprite = (Sprite*)qipaoneiwupin1->getChildByName("hezi_di");
    Sprite* hezigaiSprite = (Sprite*)qipaoneiwupin1->getChildByName("heigai");
    char str[40];
    sprintf(str, "hezi%d_1_zizhizuo.png", r1 + 1);
    hezidiSprite->setTexture(str);
    sprintf(str, "hezi%d_2_zizhizuo.png", r1 + 1);
    hezigaiSprite->setTexture(str);
    Sprite* duandai = (Sprite*)qipaoneiwupin1->getChildByName("duandai");
    sprintf(str, "duandai%d_zizhizuo.png", r4 + 1);
    duandai->setTexture(str);
    Sprite* wanjuSprite;
    int r3 = random(0, 5);//hudiejie
    int r2;
    if(randWhichone == 0)
    {
        
        r2 = random(0, 3);//哪一个玩具
        sprintf(str, "buou%d_buou.png", r2 + 1);
        wanjuSprite = (Sprite*)qipaoneiwupin1->getChildByName("wanchengbuou");
        wanjuSprite->setTexture(str);
    }else if(randWhichone == 1)
    {
        r2 = random(0, 35);//哪一个玩具
        sprintf(str, "tangzhi%d_tangguo%d_zizhizuo.png", (r2/6) + 1, (r2%6) + 1);
        wanjuSprite = (Sprite*)qipaoneiwupin1->getChildByName("tangguo");
        wanjuSprite->setTexture(str);
    }else if(randWhichone == 2)
    {
        r2 = random(0, 3);//哪一个玩具
        sprintf(str, "qunzi%d_2_zizhizuo.png", r2 + 1);
        wanjuSprite = (Sprite*)qipaoneiwupin1->getChildByName("qunzi_dress");
        wanjuSprite->setTexture(str);
        
        sprintf(str, "qunzi%d_1_zizhizuo.png", r2 + 1);
        wanjuSprite = (Sprite*)qipaoneiwupin1->getChildByName("qunzi1_1_zizhizuo");
        wanjuSprite->setTexture(str);
        
        sprintf(str, "hudiejie%d_qunzi.png", r3 + 1);
        wanjuSprite = (Sprite*)qipaoneiwupin1->getChildByName("hudiejie");
        wanjuSprite->setTexture(str);
    }
    vector<int> v;
    v.push_back(r1);
    v.push_back(r2);
    v.push_back(r3);
    v.push_back(r4);
    v.push_back(randWhichone);
    if(index == 0)
    {
        randVector1 = v;
    }else if(index == 1)
    {
        randVector2 = v;
    }else if(index == 2)
    {
        randVector3 = v;
    }
    
    qipao1->runAction(RepeatForever::create(Sequence::create(DelayTime::create(rand1), Show::create(), CallFunc::create([=](){
        qipaoneiwupin1->setVisible(true);
    }), DelayTime::create(5), Hide::create(), CallFunc::create([=](){
        qipaoneiwupin1->setVisible(false);
    }), CallFunc::create([=]()mutable{
        v.clear();
    }), NULL)));
}

bool MakeAndSleep::qipaoTouch(Touch* touch)
{
    if(GameMain::gameMainInstance->makeUpNode2->isVisible())
        return false;
    auto qipao = this->getReaderUINode()->getChildByName("qipao");
    auto qipaoneiwupin = this->getReaderUINode()->getChildByName("qipaoneiwupin");
    for(int i = 0; i < 3; i++)
    {
        auto qipao1 = qipao->getChildren().at(i);
        if(GameOther::getIsClickNode(qipao1, touch->getLocation()))
        {
            clearQipao();
            
            if(i == 0)
            {
                _compareVector = randVector1;
                
            }else if(i == 1)
            {
                _compareVector = randVector2;
                
            }else if(i == 2)
            {
                _compareVector = randVector3;
                
            }
            int wanjuIndex = _compareVector.at(WANJU_INDEX);
            if(wanjuIndex == 0)
            {
                enterBuou();
            }else if(wanjuIndex == 1)
            {
                enterTanguo();
            }else if(wanjuIndex == 2)
            {
                enterDressup();
            }
            return true;
        }
    }
    return false;
}

void MakeAndSleep::clearHezi()
{
    ((Sprite*)_shuijiaoZiNode->getChildByName("hezi_di"))->setTexture("touming.png");
    auto hezi = _shuijiaoZiNode->getChildByName("hezi");
    for(auto heziChild : hezi->getChildren())
    {
        ((Sprite*)heziChild)->setTexture("touming.png");
    }
    auto heziModel = _shuijiaoZiNode->getChildByName("heziModel");
    for(auto heziChild : heziModel->getChildren())
    {
        ((Sprite*)heziChild)->setTexture("touming.png");
    }
}

void MakeAndSleep::clearQipao()
{
    auto qipao = this->getReaderUINode()->getChildByName("qipao");
    for(auto q : qipao->getChildren())
    {
        q->stopAllActions();
        q->setVisible(false);
    }
    auto heziModel = this->getReaderUINode()->getChildByName("hezi1");
    for(auto heziChild : heziModel->getChildren())
    {
        ((Sprite*)heziChild)->setTexture("touming.png");
    }
    heziModel = this->getReaderUINode()->getChildByName("hezi2");
    for(auto heziChild : heziModel->getChildren())
    {
        ((Sprite*)heziChild)->setTexture("touming.png");
    }
    heziModel = this->getReaderUINode()->getChildByName("hezi3");
    for(auto heziChild : heziModel->getChildren())
    {
        ((Sprite*)heziChild)->setTexture("touming.png");
    }
}