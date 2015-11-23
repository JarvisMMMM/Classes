//
//  MakeUpMediator.cpp
//  japanesesalon
//
//  Created by apple12 on 15/6/23.
//
//

#include "MakeUpMediator.h"
#include "GameScene.h"
#include "MenuLayer.h"
#include "ADManager.h"
#include "GameListIconMediator.h"

MakeUpMediator* MakeUpMediator::makeupMediatorInstance;
Node* MakeUpMediator::_node;

void MakeUpMediator::onEnter()
{
    isJiazi = false;
    isTouch = false;
    isChangePage = false;
    this->onRun();
    ButtonMediator::onEnter();
}
void MakeUpMediator::onExit()
{
//     refresh();
//    decodePrintScreenFace();
    makeupMediatorInstance = NULL;
    ButtonMediator::onExit();
}
void MakeUpMediator::onRun()
{
    _csbNode = GameReaderManager::getNodeReaderFile("makeup_UI.csb", BOTTOM, 2);
    this->addChild(_csbNode);
    this->setReaderUINode(_csbNode);
    _node = _csbNode->getChildByName("page");

    _listNode = GameReaderManager::getNodeReaderFile("makeup_UI1.csb", RIGHT_CENTER, 2);
    this->addChild(_listNode);
    _listNode->setVisible(false);
    _listNode->setPosition(Vec2(_listNode->getPositionX() + _listNode->getContentSize().width/2, _listNode->getPositionY()));
    
    toumingquyu = _listNode->getChildByName("quyu_makeup");
    makeupMediatorInstance = this;
    initParticleEffect();
    addJewel();
}

void MakeUpMediator::initParticleEffect()
{
//    decodePrintScreenFace();
}

void MakeUpMediator::onVirtualDropBegin(Touch* pTouch)
{
    string str = this->getDropTargetNode()->getName();
    if(str.find(ITEMS_YANXIAN) != string::npos)
    {
        initMianmo(MIANMO_NODE_NAME, MIANMO_PNG, MIANMO_TUMO_PNG, DRAW_COPY, 30, true, NULL_MP3, pTouch);
    }else if(str.find(ITEMS_YANMEI) != string::npos)
    {
//        toolsFuncYanmei(touch);
    }else if(str.find(ITEMS_JIEMAOSHUA) != string::npos)
    {
        int number = GameOther::getStrNumber(str, ITEMS_JIEMAOSHUA);
        char tumostr[40];
        sprintf(tumostr, "brow%d.png", number);
        initMianmo(YANJIEMAO_NODE_NAME, YANJIEMAO_PNG, tumostr, DRAW_COPY, 15, true, NULL_MP3, pTouch);
    }else if(str.find(ITEMS_YANYING) != string::npos)
    {
        int number = GameOther::getStrNumber(str, ITEMS_YANYING);
        char tumostr[40];
        sprintf(tumostr, "eye_shadow%d.png", number);
        initMianmo(YANYING_NODE_NAME, YANYING_PNG, tumostr, DRAW_COPY, 15, true, NULL_MP3, pTouch);
    }else if(str.find(ITEMS_BLUSH) != string::npos)
    {
        int number = GameOther::getStrNumber(str, ITEMS_BLUSH);
        char tumostr[40];
        sprintf(tumostr, "blush%d.png", number);
        initMianmo(BLUSH_NODE_NAME, BLUSH_PNG, tumostr, DRAW_COPY, 30, true, NULL_MP3, pTouch);
    }else if(str.find(ITEMS_CHUNCAI) != string::npos)
    {
        int number = GameOther::getStrNumber(str, ITEMS_CHUNCAI);
        if(number == 0)
        {
            number = GameOther::getStrNumber(str, ITEMS_CHUNCAISHUA);
        }
        char tumostr[40];
        sprintf(tumostr, "mouth%d.png", number);
        initMianmo(CHUNCAI_NODE_NAME, CHUNCAI_PNG, tumostr, DRAW_COPY, 10, true, NULL_MP3, pTouch);
    }
}
void MakeUpMediator::onVirtualDropMove(Touch* pTouch)
{
    decodeGameEffect(pTouch);
}
void MakeUpMediator::onVirtualDropEnd(Touch* pTouch)
{
    GameSoundManager::getInstance()->stopLoopEffect(MIANMO_MP3);
    DrawImageManager::getInstance()->onEndTouch();
}

void MakeUpMediator::initMianmo(const char* str1, const char* str2, const char* str3, DRAWTYPE type, int size, bool isauto, const char* soundStr, Touch* touch)
{
    Sprite* __sp = (Sprite*)GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode->getChildByName("face_kongbai_makeup"), str1);
    DrawImageManager::getInstance()->addDrawImage(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode->getChildByName("face_kongbai_makeup"), str1), std::string(str2), std::string(str3), "", type, size, isauto);
    DrawImageManager::getInstance()->onBeganTouch(__sp->convertToNodeSpace(touch->getLocation()));
    if(strcmp(soundStr, "") != 0)
        GameSoundManager::getInstance()->playLoopEffect(soundStr);
}

bool MakeUpMediator::decodeGameEffect(Touch* touch)
{
    string str = this->getDropTargetNode()->getName();
    if(str.find(ITEMS_YANXIAN) != string::npos)
    {
        toolsFuncYanxian(touch);
    }else if(str.find(ITEMS_YANMEI) != string::npos)
    {
        toolsFuncYanmei(touch);
    }else if(str.find(ITEMS_JIEMAOSHUA) != string::npos)
    {
        toolsFuncJiemao(touch);
    }else if(str.find(ITEMS_YANYING) != string::npos)
    {
        toolsFuncYanying(touch);
    }else if(str.find(ITEMS_BLUSH) != string::npos)
    {
        toolsFuncSaihong(touch);
    }else if(str.find(ITEMS_CHUNCAI) != string::npos)
    {
        toolsFuncChuncai(touch);
    }
}

void MakeUpMediator::toolsFuncYanxian(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
    __vec2.y += _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
    Sprite* sprite = GameReaderManager::getSpriteFromParent(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT), YANXIAN_NODE_NAME);
    DrawImageManager::getInstance()->onMovedTouch(sprite->convertToNodeSpace(__vec2));
}

void MakeUpMediator::toolsFuncYanmei(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height *_dropIcon->getAnchorPoint().x * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
    __vec2.y += _dropIcon->getContentSize().height *_dropIcon->getAnchorPoint().y * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
    Sprite* sprite = GameReaderManager::getSpriteFromParent(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT), YANMEI_NODE_NAME);
    DrawImageManager::getInstance()->onMovedTouch(sprite->convertToNodeSpace(__vec2));
}

void MakeUpMediator::toolsFuncJiemao(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(30.0f / 180.0f * M_PI)  * GameOther::getNodeToParentScale(_dropIcon).x - 10*GameOther::getWindowSmallScale();
    __vec2.y += _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * cosf(30.0f / 180.0f * M_PI)  * GameOther::getNodeToParentScale(_dropIcon).y - 5*GameOther::getWindowSmallScale();
    DrawImageManager::getInstance()->onMovedTouch(GameReaderManager::getSpriteFromParent(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT), YANJIEMAO_NODE_NAME)->convertToNodeSpace(__vec2));
    //    GameMain::gameMainInstance->RenwuBiyan();
}

void MakeUpMediator::toolsFuncYanying(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x - 10*GameOther::getWindowSmallScale();
    __vec2.y += _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * cosf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y - 5*GameOther::getWindowSmallScale();
    Node* eye = GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT);
    Node* yanying = GameReaderManager::getSpriteFromParent(eye, YANYING_NODE_NAME);
    DrawImageManager::getInstance()->onMovedTouch(yanying->convertToNodeSpace(__vec2));
}

void MakeUpMediator::toolsFuncSaihong(Touch* touch)
{
    float rotation;
    string strlength = ITEMS_BLUSH;
    int length = strlength.length();
    string s = this->getDropTargetNode()->getName();
    int length1 = s.length();
    string ss = s.substr(length, length1);
    int number = std::atoi(ss.c_str());
//    if(number <= 5)
//    {
//        rotation = 20.0f;
//    }else
//    {
//        rotation = 90.0f;
//    }
    rotation = 30.0f;
    
    Vec2 __vec2 = touch->getLocation();
    if(number <= 5)
    {
        __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(rotation / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x - 5*_dropIcon->getScale();
        __vec2.y += _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * cosf(rotation / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y - 20*_dropIcon->getScale();
    }else
    {
        __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(rotation / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
        __vec2.y += _dropIcon->getContentSize().height *(_dropIcon->getAnchorPoint().y) * GameOther::getNodeToParentScale(_dropIcon).y;
    }
    
    Node* eye = GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT);
    Node* yanying = GameReaderManager::getSpriteFromParent(eye, BLUSH_NODE_NAME);
    DrawImageManager::getInstance()->onMovedTouch(yanying->convertToNodeSpace(__vec2));
}

void MakeUpMediator::toolsFuncChuncai(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * sinf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
    __vec2.y += _dropIcon->getContentSize().height *(1 - _dropIcon->getAnchorPoint().y) * cosf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
    DrawImageManager::getInstance()->onMovedTouch(GameReaderManager::getSpriteFromParent(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MAKEUP_PARENT), CHUNCAI_NODE_NAME)->convertToNodeSpace(__vec2));
}

void MakeUpMediator::onListClick(Sprite* sprite, int index)
{
    if(DropMediator::_curListType == meitongType)
    {
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
        Sprite* eye = (Sprite*)getPlayerNode()->getChildByName(MAKEUP_PARENT);
        Sprite* meitong = (Sprite*)eye->getChildByName("eye_makeup");
        char meitongstr[40];
        sprintf(meitongstr, "eye%d.png", index + 1);
        meitong->setTexture(meitongstr);
        GameOther::changeGRAYNodeToWhite(meitong);
        GameOther::changeGRAYNodeToWhite(sprite);
    }else if(DropMediator::_curListType == hairType)
    {
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("hair");
        char meitongstr[40];
        sprintf(meitongstr, "hair%d_makeup.png", index + 1);
        hair->setTexture(meitongstr);
//        GameData::getInstance()->setHairIndex(index + 1);
        GameOther::changeGRAYNodeToWhite(hair);
        GameOther::changeGRAYNodeToWhite(sprite);
    }else if(DropMediator::_curListType == earringType)
    {
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("earring");
        char meitongstr[40];
        string str;
        if(index == 0)
        {
            str = "touming.png";
        }else
        {
            str = "earring%d_makeup.png";
        }
        sprintf(meitongstr, str.c_str(), index);
        hair->setTexture(meitongstr);
//        GameData::getInstance()->setearringIndex(index);

        GameOther::changeGRAYNodeToWhite(hair);
        GameOther::changeGRAYNodeToWhite(sprite);
    }else if(DropMediator::_curListType == necklaceType)
    {
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("necklace");
        char meitongstr[40];
        string str;
        if(index == 0)
        {
            str = "touming.png";
        }else
        {
            str = "necklace%d_makeup.png";
        }
        sprintf(meitongstr, str.c_str(), index);
        hair->setTexture(meitongstr);
        GameOther::changeGRAYNodeToWhite(hair);
//        GameData::getInstance()->setNecklaceIndex(index);
        GameOther::changeGRAYNodeToWhite(sprite);
    }
//    else if(DropMediator::_curListType == yanxianType)
//    {
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//        onClickToJump(_csbNode->getChildByName("page")->getChildByName("page1")->getChildByName(ITEMS_YANXIAN));
//        _yanxianIndex = index;
//    }else if(DropMediator::_curListType == hairType)
//    {
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("hair");
//        char meitongstr[40];
//        sprintf(meitongstr, "hair%d_makeup.png", index + 1);
//        hair->setTexture(meitongstr);
//        GameData::getInstance()->setHairIndex(index + 1);
//        GameOther::changeGRAYNodeToWhite(hair);
//        GameOther::changeGRAYNodeToWhite(sprite);
//    }else if(DropMediator::_curListType == earringType)
//    {
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("earring");
//        char meitongstr[40];
//        string str;
//        if(index == 0)
//        {
//            str = "touming.png";
//        }else
//        {
//            str = "earring%d_makeup.png";
//        }
//        sprintf(meitongstr, str.c_str(), index);
//        hair->setTexture(meitongstr);
//        GameData::getInstance()->setearringIndex(index);
//        
//        GameOther::changeGRAYNodeToWhite(hair);
//        GameOther::changeGRAYNodeToWhite(sprite);
//    }else if(DropMediator::_curListType == necklaceType)
//    {
//        GameSoundManager::getInstance()->playEffect(XUANZUAN);
//        Sprite* hair = (Sprite*)getPlayerNode()->getChildByName("necklace");
//        char meitongstr[40];
//        string str;
//        if(index == 0)
//        {
//            str = "touming.png";
//        }else
//        {
//            str = "necklace%d_makeup.png";
//        }
//        sprintf(meitongstr, str.c_str(), index);
//        hair->setTexture(meitongstr);
//        GameOther::changeGRAYNodeToWhite(hair);
//        GameData::getInstance()->setNecklaceIndex(index);
//        
//        
//        Sprite* earring = (Sprite*)getPlayerNode()->getChildByName("earring");
//        char earringstr[40];
//        string earringstr1;
//        if(index == 0)
//        {
//            earringstr1 = "touming.png";
//        }else
//        {
//            earringstr1 = "earring%d_makeup.png";
//        }
//        sprintf(earringstr, earringstr1.c_str(), index);
//        earring->setTexture(earringstr);
//        GameData::getInstance()->setearringIndex(index);
//        GameOther::changeGRAYNodeToWhite(earring);
//        GameOther::changeGRAYNodeToWhite(sprite);
//    }
}

bool MakeUpMediator::moveJudge(Touch* touch)
{
    if(abs(touch->getLocation().x - this->_pBeginVec2.x) < 50)
    {
        return false;
    }
    return true;
}

void MakeUpMediator::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        ADManager::showAlert();
}

void MakeUpMediator::initListContent(int indexListType)
{
    ListMediator* templist = NULL;
    templist = (ListMediator*)_listNode->getChildByName("quyu_makeup")->getChildByTag(100);
    if(templist)
    {
        int count1 = templist->_tableView->getContainer()->getActionManager()->getNumberOfRunningActionsInTarget(templist->_tableView->getContainer());
        if(count1 > 0)
        {
            return;
        }
    }
    
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    DropMediator::_curListType = indexListType;
    bool isDrop = true;
    bool isVertical = true;
    std::vector<ListIconMediator*> _iconList;
    char spriteName[40];
    char centerName[40];
    int count = 0;
    if(indexListType == meitongType)
    {
        count = 10;
    }else if(indexListType == hairType)
    {
        count = 10;
    }else if(indexListType == earringType || indexListType == necklaceType)
    {
        count = 11;
    }
    for(int i = 0 ; i < count; i++)
    {
        if(indexListType == meitongType)
        {
            sprintf(spriteName, "_eye%d.png", i + 1);
            sprintf(centerName, "");
        }else if(indexListType == yanxianType)
        {
            sprintf(spriteName, "_eyeliner%d.png", i + 1);
            sprintf(centerName, "");
        }else if(indexListType == hairType)
        {
            sprintf(spriteName, "_hair%d.png", i + 1);
            sprintf(centerName, "");
        }else if(indexListType == earringType)
        {
            if(i == 0)
            {
                sprintf(spriteName, "x.png");
            }else
            {
                sprintf(spriteName, "_earring%d.png", i);
            }
            sprintf(centerName, "");
        }else if(indexListType == necklaceType)
        {
            if(i == 0)
            {
                sprintf(spriteName, "x.png");
            }else
            {
                sprintf(spriteName, "_necklace%d.png", i);
            }
            sprintf(centerName, "");
        }
        Sprite* sprite = Sprite::create(spriteName);
        sprite->setName(spriteName);
        GameListIconMediator* listIcon = GameListIconMediator::initSprite(i, sprite, centerName, "", "");
        _iconList.push_back(listIcon);
        listIcon->setparentNode(this);
    }
    
    ListMediator* _list = ListMediator::create();
    Size size;
    size =  GameReaderManager::getNodeFromParent(_listNode, "quyu_makeup")->getContentSize();
    _list->setListView(&_iconList, isVertical, size, isDrop);
    _list->_tableView->setScrollTouch(false);
    int scrollCount = 6;
    if(count >= scrollCount)
    {
        isRunSlider = true;
        _list->runSlideEnd(Vec2(0, size.height));
        this->runAction(Sequence::create(DelayTime::create(0.02), CallFunc::create([=](){
            if(isRunSlider)
            {
                isRunSlider = false;
                ListMediator* _list = (ListMediator*)GameReaderManager::getNodeFromParent(_listNode, "quyu_makeup")->getChildByTag(100);
                if(_list)
                    _list->runEndSlideStart();
            }
        }), DelayTime::create(0.5), CallFunc::create([=](){
            isListTouch = true;
            ListMediator* _list1 = (ListMediator*)GameReaderManager::getNodeFromParent(_listNode, "quyu_makeup")->getChildByTag(100);
            if(_list1 && _list1->_tableView)
            {
                _list1->_tableView->setScrollTouch(true);
            }
        }), NULL));
    }
    
    
    Node* quyu = NULL;
    quyu = _listNode->getChildByName("quyu_makeup")->getChildByTag(100);
    
    if(quyu)
    {
        quyu->removeFromParent();
        quyu = NULL;
    }
    GameReaderManager::getNodeFromParent(_listNode, "quyu_makeup")->addChild(_list, 0, 100);
    _iconList.clear();
    
    jiaziMoveIn();
}

void MakeUpMediator::jiaziMoveIn()
{
    if(_listNode->getActionByTag(99))
        return;
    if(isJiazi)
    {
        
    }else
    {
        _listNode->setVisible(true);
        isJiazi = true;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(-_listNode->getContentSize().width/2, 0)), NULL);
        actionInterval->setTag(99);
        _listNode->runAction(actionInterval);
    }
}

bool MakeUpMediator::jiaziMoveOut(Touch* touch)
{
    if(isJiazi && _listNode->isVisible())
    {
        bool ret = false;
        if(touch)
        {
            for(int i = _node->getChildrenCount() - 1; i >=0 ; i--)
            {
                Node* parentNode = _node->getChildren().at(i);
                for(int x = parentNode->getChildrenCount() - 1; x >= 0; x--)
                {
                    Node* childNode = parentNode->getChildren().at(x);
                    if(childNode->getName() != "noclick" && GameOther::getIsClickNode(childNode, touch->getLocation()))
                    {
                        if(childNode->getName() == ITEMS_MEITONG)
                        {
                            this->setClickTargetNode(childNode);
                            ret = true;
                            return ret; 
                        }else if(childNode->getName() == ITEMS_YANXIAN_TONG)
                        {
                            this->setClickTargetNode(childNode);
                            ret = true;
                            return ret;
                        }else if(childNode->getName() == ITEMS_HAIR)
                        {
                            this->setClickTargetNode(childNode);
                            ret = true;
                            return ret;
                        }else if(childNode->getName() == ITEMS_EARRING)
                        {
                            this->setClickTargetNode(childNode);
                            ret = true;
                            return ret;
                        }else if(childNode->getName() == ITEMS_NECKLACE)
                        {
                            this->setClickTargetNode(childNode);
                            ret = true;
                            return ret;
                        }
                    }
                }
            }
        }
        if(_listNode->getActionByTag(99))
            return true;
        isJiazi = false;
        isListTouch = false;
        ActionInterval* actionInterval = Sequence::create(MoveBy::create(0.2, Vec2(_listNode->getContentSize().width/2, 0)), CallFunc::create([=](){
            Node* quyu = _listNode->getChildByName("quyu_makeup")->getChildByTag(100);
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

bool MakeUpMediator::decodeJiaziMove(Touch* touch)
{
    if(GameOther::getIsClickNode(toumingquyu, touch->getLocation()) && isJiazi)
    {
        return true;
    }else
    {
        if(jiaziMoveOut(touch))
            return true;
    }
}

void MakeUpMediator::changeJiemao(int jiemaoIndex)
{
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    char str[20];
    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 5; j++)
        {
            sprintf(str, "browbrush%d_%d", i, j);
            _csbNode->getChildByName("page")->getChildByName("page6")->getChildByName(str)->setVisible(false);
        }
    }
    char str1[20];
    for(int i = 1; i < 5; i++)
    {
        sprintf(str1, "browbrush%d_%d", i, jiemaoIndex);
        _csbNode->getChildByName("page")->getChildByName("page6")->getChildByName(str1)->setVisible(true);
    }
}

void MakeUpMediator::changePage5Jiemao(int jiemaoIndex)
{
    GameSoundManager::getInstance()->playEffect(JUMP_MP3);
    char str[20];
    for(int i = 5; i < 9; i++)
    {
        for(int j = 1; j < 5; j++)
        {
            sprintf(str, "browbrush%d_%d", i, j);
            _csbNode->getChildByName("page")->getChildByName("page7")->getChildByName(str)->setVisible(false);
        }
    }
    char str1[20];
    for(int i = 1; i < 5; i++)
    {
        sprintf(str1, "browbrush%d_%d", i + 4, jiemaoIndex );
        _csbNode->getChildByName("page")->getChildByName("page7")->getChildByName(str1)->setVisible(true);
    }
}

void MakeUpMediator::decodePrintScreenFace()
{
    Node* __face = GameReaderManager::getNodeFromParent(this->getPlayerNode(), MAKEUP_PARENT);
    RenderTexture* __render = RenderTexture::create(__face->getContentSize().width, __face->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
    
    auto node = GameOther::cloneSprite((Sprite*)__face);
    this->getPlayerNode()->addChild(node);
    Vec2 _faceVec2 = __face->getPosition();
    node->setPosition(_faceVec2);
    GameReaderManager::getNodeFromParent(this->getPlayerNode(), "necklace")->setZOrder(1);
    GameReaderManager::getNodeFromParent(this->getPlayerNode(), "hair")->setZOrder(2);
    GameReaderManager::getNodeFromParent(this->getPlayerNode(), "earring")->setZOrder(3);
    
    __render->begin();
    __face->setAnchorPoint(Vec2::ZERO);
    __face->setPosition(Vec2::ZERO);
    __face->visit();
    __face->setVisible(false);
    __render->end();
    CC_SAFE_RETAIN(__render);
    
    if(GameData::getInstance()->getMakeUpRender())
        CC_SAFE_RELEASE(GameData::getInstance()->getMakeUpRender());
    GameData::getInstance()->setMakeUpRender(__render);
}

void MakeUpMediator::addJewel()
{
//    int index = GameData::getInstance()->getHairIndex();
//    dressUp("hair", "hair%d_makeup.png", index, false);
//    if(GameData::getInstance()->getearringIndex() != 0)
//    {
//        dressUp("earring", "earring%d_makeup.png", GameData::getInstance()->getearringIndex(), false);
//    }
//    if(GameData::getInstance()->getNecklaceIndex() != 0)
//    {
//        dressUp("necklace", "necklace%d_makeup.png", GameData::getInstance()->getNecklaceIndex(), false);
//    }
}

void MakeUpMediator::dressUp(const char* partName, const char* pngName, int idx, bool isSound)
{
    if(isSound)
        GameSoundManager::getInstance()->playEffect(XUANZUAN);
    Sprite* hair = (Sprite*)getPlayerNode()->getChildByName(partName);
    char meitongstr[40];
    sprintf(meitongstr, pngName, idx);
    hair->setTexture(meitongstr);
}

void MakeUpMediator::onVirtualEnd(Touch* touch, const string& str)
{
    touchEndFunc(touch, str, -1);
}

void MakeUpMediator::touchEndFunc(Touch* touch, const string& str, int index)
{
    if(!isChangePage)
    {
        isChangePage = false;
        Node* childNode = this->getClickTargetNode();
        if(str == ITEMS_MIANMO || str == ITEMS_MIANMO_1 || str == ITEMS_MIANMO_2)
        {
            DrawImageManager::getInstance()->onEndTouch();
            GameMain::gameMainInstance->Renwuzhengyan();
            GameSoundManager::getInstance()->stopLoopEffect(MIANMO_MP3);
        }else if(str.find(ITEMS_YANXIAN) != string::npos)
        {
            DrawImageManager::getInstance()->onEndTouch();
        }else if(str.find(ITEMS_YANMEI) != string::npos)
        {
            DrawImageManager::getInstance()->onEndTouch();
        }else if(str.find(ITEMS_MEITONG) != string::npos)
        {
            if(moveJudge(touch))
                return;
//            GameSoundManager::getInstance()->playEffect(XUANZUAN);
            initListContent(meitongType);
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str.find(ITEMS_YANXIAN_TONG) != string::npos)
        {
            if(moveJudge(touch))
                return;
            string s = childNode->getName();
            int length = s.length();
            string ss;
            if(length == 16)
            {
                ss = s.substr(length - 1, length);
            }else
            {
                ss = s.substr(length - 2, length);
            }
            int number = std::atoi(ss.c_str());
            char shuazi[30];
            sprintf(shuazi, "eyeliner_pencil%d", number);
            onClickToJump(childNode->getParent()->getChildByName(shuazi));
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str == ITEMS_HAIR)
        {
            if(moveJudge(touch))
                return;
            initListContent(hairType);
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str == ITEMS_EARRING)
        {
            initListContent(earringType);
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str == ITEMS_NECKLACE)
        {
            if(moveJudge(touch))
                return;
            initListContent(necklaceType);
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str.find(ITEMS_JIEMAOSHUA) != string::npos && str.find(ITEMS_JIEMAO) == string::npos)
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
            int num = GameOther::getStrNumber(str, ITEMS_CHUNCAI);
            if(num >= 7)
            {
                char shuazi[30];
                sprintf(shuazi, "lipstickshua%d", num);
                onClickToJump(childNode->getParent()->getChildByName(shuazi));
                GameOther::changeGRAYNodeToWhite(childNode);
            }
            DrawImageManager::getInstance()->onEndTouch();
        }else if(str.find(ITEMS_JIEMAO) != string::npos)//点击瓶子 旁边跳动
        {
            if(moveJudge(touch))
                return;
            string s = childNode->getName();
            int length = s.length();
            string itemsStr = ITEMS_JIEMAO;
            int itemsLength = itemsStr.length();
            string ss;
            ss = s.substr(itemsLength, length);
            int number = std::atoi(ss.c_str());
            char shuazi[30];
            sprintf(shuazi, "browbrush%d", number);
            onClickToJump(childNode->getParent()->getChildByName(shuazi));
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str.find(ITEMS_EYE_SHADOW_BOX) != string::npos)
        {
            if(moveJudge(touch))
                return;
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
            GameOther::changeGRAYNodeToWhite(childNode);
        }else if(str.find(ITEMS_BLUSH_BOX) != string::npos)
        {
            if(moveJudge(touch))
                return;
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
            GameOther::changeGRAYNodeToWhite(childNode);
        }
    }
}

void MakeUpMediator::onVirtualPage()
{
    jiaziMoveOut();
}