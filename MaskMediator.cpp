//
//  MaskMediator.cpp
//  japanesesalon
//
//  Created by apple12 on 15/6/23.
//
//

#include "MaskMediator.h"
#include "GameScene.h"
#include "ADManager.h"
#include "GameListIconMediator.h"
#include "GameEffectLayer.h"

MaskMediator* MaskMediator::makeupMediatorInstance;
Node* MaskMediator::_node;

void MaskMediator::onEnter()
{
    
    isTouch = false;
    this->onRun();
    //    if(_isRefresh)
    //        refresh();
    ButtonMediator::onEnter();
}
void MaskMediator::onExit()
{
    refresh();
    makeupMediatorInstance = NULL;
    ButtonMediator::onExit();
}
void MaskMediator::onRun()
{
    _csbNode = GameReaderManager::getNodeReaderFile("mask_UI.csb", BOTTOM, 2);
    this->addChild(_csbNode);
    this->setReaderUINode(_csbNode);
    _node = _csbNode->getChildByName("page");
    
    makeupMediatorInstance = this;
    initParticleEffect();
}

void MaskMediator::initParticleEffect()
{
    zhenglianqiEffect = NULL;
}

void MaskMediator::onVirtualDropBegin(Touch* pTouch)
{
    string str = this->getDropTargetNode()->getName();
    if(str == ITEMS_MIANMO)
    {
        initMianmo(MIANMO_NODE_NAME, MIANMO_PNG, MIANMO_TUMO_PNG, DRAW_COPY, 30, true, MIANMO_MP3, pTouch);
        GameMain::gameMainInstance->RenwuBiyan();
    }else if(str == ITEMS_MIANMO_1)
    {
        initMianmo(MIANMO_NODE_NAME, MIANMO_PNG, MIANMO_TUMO_PNG_1, DRAW_COPY, 30, true, MIANMO_MP3, pTouch);
        GameMain::gameMainInstance->RenwuBiyan();
    }else if(str == ITEMS_MIANMO_2)
    {
        clearMianMo();
        initMianmo(MIANMO_NODE_NAME, MIANMO_PNG, MIANMO_TUMO_PNG_2, DRAW_COPY, 30, true, MIANMO_MP3, pTouch);
        Vec2 __vec2 = pTouch->getLocation();
        __vec2.x -= _dropIcon->getContentSize().width / 2 * GameOther::getNodeToParentScale(_dropIcon).x - 15*_dropIcon->getScale();
        __vec2.y += _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * GameOther::getNodeToParentScale(_dropIcon).y - 25*_dropIcon->getScale();
        GameEffectLayer::getInstance()->addParticleSystemQuad(GameOther::getPlatformPlist("shachong"), this->getDropIcon(), this->getDropIcon()->getParent()->convertToWorldSpace(__vec2), this);
        GameMain::gameMainInstance->RenwuBiyan();
    }else if(str == ITEMS_PENTOU)
    {
        initMianmo(MIANMO_NODE_NAME, MIANMO_PNG, MIANMO_PNG, DRAW_CLEAR, 30, false, PENSHUI_MP3, pTouch);
        this->checkLemonVisible();
        Vec2 __vec2 = pTouch->getLocation();
        __vec2.y += this->getDropIcon()->getContentSize().height * 0.3f * GameOther::getNodeToParentScale(this->getDropIcon()).y;
        GameEffectLayer::getInstance()->addParticleSystemQuad(GameOther::getPlatformPlist("penshui"), this->getDropIcon(), __vec2, this);
        GameMain::gameMainInstance->RenwuBiyan();
    }else if(str == ITEMS_FENDI)
    {
        GameSoundManager::getInstance()->playLoopEffect(FENPU);
    }else if(str == ITEMS_FENPU)
    {
        GameSoundManager::getInstance()->playLoopEffect(FENPU);
        GameEffectLayer::getInstance()->addParticleSystemQuad(GameOther::getPlatformPlist("fenshua"), this->getDropIcon(), this->getDropIcon()->getParent()->convertToWorldSpace(this->getDropIcon()->getPosition()), this);
    }
}
void MaskMediator::onVirtualDropMove(Touch* pTouch)
{
    decodeGameEffect(pTouch);
}
void MaskMediator::onVirtualDropEnd(Touch* pTouch)
{
    string str = this->getDropTargetNode()->getName();
    if(str == ITEMS_MIANMO || str == ITEMS_MIANMO_1)
    {
//        auto node = GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode->getChildByName("mask"), MIANMO_NODE_NAME);
//        node->stopAllActions();
        GameSoundManager::getInstance()->stopLoopEffect(MIANMO_MP3);
        GameMain::gameMainInstance->Renwuzhengyan();
    }else if(str == ITEMS_PENTOU)
    {
        log("pentou101");
        GameSoundManager::getInstance()->stopLoopEffect(PENSHUI_MP3);
        GameEffectLayer::getInstance()->removeParticleSystemQuad(this->getDropIcon());
        GameMain::gameMainInstance->Renwuzhengyan();
    }else if(str == ITEMS_MIANMO_2)
    {
        GameMain::gameMainInstance->Renwuzhengyan();
        GameEffectLayer::getInstance()->removeParticleSystemQuad(this->getDropIcon());
        GameSoundManager::getInstance()->stopLoopEffect(MIANMO_MP3);
        auto node = GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MIANMO_NODE_NAME);
        node->stopAllActions();
        zhenglianqiEffect = (CCParticleSystemQuad::create(GameOther::getPlatformPlist("zhenglianqi")));
        zhenglianqiEffect->setScale(GameOther::getWindwoWidthScale());
        this->addChild(zhenglianqiEffect);
        zhenglianqiEffect->resetSystem();
        zhenglianqiEffect->setPosition(node->getParent()->convertToWorldSpace(node->getPosition()));
        node->runAction(Sequence::create(FadeOut::create(1), CallFunc::create([=](){
            clearMianMo();
            node->setOpacity(255);
            //            GameEffectLayer::getInstance()->removeParticleSystemQuad(node);
        }), NULL));
    }else if(str == ITEMS_FENPU || str == ITEMS_FENDI)
    {
        GameEffectLayer::getInstance()->removeParticleSystemQuad(this->getDropIcon());
        GameSoundManager::getInstance()->stopLoopEffect(FENPU);
    }
    DrawImageManager::getInstance()->onEndTouch();
}

void MaskMediator::initMianmo(const char* str1, const char* str2, const char* str3, DRAWTYPE type, int size, bool isauto, const char* soundStr, Touch* touch)
{
    Sprite* __sp = (Sprite*)GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, str1);
    DrawImageManager::getInstance()->addDrawImage(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, str1), std::string(str2), std::string(str3), "", type, size, isauto);
    DrawImageManager::getInstance()->onBeganTouch(__sp->convertToNodeSpace(touch->getLocation()));
    if(strcmp(soundStr, "") != 0)
        GameSoundManager::getInstance()->playLoopEffect(soundStr);
}

bool MaskMediator::decodeGameEffect(Touch* touch)
{
    string str = this->getDropTargetNode()->getName();
    if(str == ITEMS_MIANMO)
    {
        toolsFuncMianmo(touch);
    }else if(str == ITEMS_MIANMO_1 || str == ITEMS_MIANMO_2)
    {
        toolsFuncMianmo1(touch);
    }else if(str == ITEMS_PENTOU)
    {
        toolsFuncMianmopentou(touch);
    }else if(str == ITEMS_LEMON_1 || str == ITEMS_LEMON_2)
    {
        toolsFuncYanmo(touch, false);
    }else if(str == ITEMS_YANMO_1 || str == ITEMS_YANMO_2)
    {
        toolsFuncYanmo(touch, true);
    }else if(str == ITEMS_NIEZI_1)
    {
        Vec2 __vec2 = touch->getLocation();
        Vec2 __vec3 = touch->getLocation();
        __vec2.x -= _dropIcon->getContentSize().width * (_dropIcon->getAnchorPoint().x) * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
        __vec2.y += _dropIcon->getContentSize().width * (_dropIcon->getAnchorPoint().x) * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
        decodeZaMei(__vec2, _dropIcon);
    }else if(str == ITEMS_ACNE)
    {
        toolsFuncAcne(touch, true);
    }else if(str == ITEMS_MIAMNBANG)
    {
        toolsFuncAcne(touch, false);
    }else if(str == ITEMS_FENPU)
    {
        toolsFuncQuebanFenpu(touch);
    }else if(str == ITEMS_FENDI)
    {
        toolsFuncFendi(touch);
    }
}



bool MaskMediator::moveJudge(Touch* touch)
{
    if(abs(touch->getLocation().x - this->_pBeginVec2.x) < 50)
    {
        return false;
    }
    return true;
}

void MaskMediator::changeJiemao(int jiemaoIndex)
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

void MaskMediator::changePage5Jiemao(int jiemaoIndex)
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

void MaskMediator::onVirtualEnd(Touch* touch, const string& str)
{
    touchEndFunc(touch, str, -1);
}

void MaskMediator::touchEndFunc(Touch* touch, const string& str, int index)
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
        }
    }
}

bool MaskMediator::toolsFuncMianmo(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    //    __vec2.x -= _dropIcon->getContentSize().height / 2 * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
    //    __vec2.y += _dropIcon->getContentSize().height / 2 * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
    DrawImageManager::getInstance()->onMovedTouch(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MIANMO_NODE_NAME)->convertToNodeSpace(__vec2));
}

bool MaskMediator::toolsFuncMianmo1(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    if(this->getDropTargetNode()->getName() == ITEMS_MIANMO_2)
    {
//        __vec2.x -= _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * GameOther::getNodeToParentScale(_dropIcon).x + 25*_dropIcon->getScale();
//        __vec2.y += _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y)* GameOther::getNodeToParentScale(_dropIcon).y - 25*_dropIcon->getScale();
        
//        Vec2 vec2temp = touch->getLocation();
        __vec2.x -= _dropIcon->getContentSize().width / 2 * GameOther::getNodeToParentScale(_dropIcon).x - 15*_dropIcon->getScale();
            __vec2.y += _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * GameOther::getNodeToParentScale(_dropIcon).y - 25*_dropIcon->getScale();
        GameEffectLayer::getInstance()->moveParticleSystemQuad(this->getDropIcon(), __vec2);
    }else
    {
        __vec2.x -= _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * sinf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
        __vec2.y += _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * cosf(30.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y;
    }
    
    DrawImageManager::getInstance()->onMovedTouch(GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MIANMO_NODE_NAME)->convertToNodeSpace(__vec2));
}

bool MaskMediator::toolsFuncMianmopentou(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= _dropIcon->getContentSize().height * (1 - _dropIcon->getAnchorPoint().y) * sinf(20.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x + _dropIcon->getContentSize().width * (_dropIcon->getAnchorPoint().x) * sinf(20.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x - 20*GameOther::getWindowSmallScale();
    __vec2.y += _dropIcon->getContentSize().height  * (1 - _dropIcon->getAnchorPoint().y) * cosf(20.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).y - _dropIcon->getContentSize().width * (_dropIcon->getAnchorPoint().x) * sinf(20.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x - 20*GameOther::getWindowSmallScale();
    
    Vec2 vec2Temp = touch->getLocation();
    Vec2 __parVec2 = Vec2(vec2Temp.x - 10*GameOther::getWindowSmallScale() + (0.5 - _dropIcon->getAnchorPoint().x)*_dropIcon->getContentSize().width*GameOther::getWindowSmallScale(), vec2Temp.y + 50*GameOther::getWindowSmallScale() + (0.5 - _dropIcon->getAnchorPoint().y)*_dropIcon->getContentSize().height*GameOther::getWindowSmallScale());
    GameEffectLayer::getInstance()->moveParticleSystemQuad(this->getDropIcon(), __parVec2);
    
    vec2Temp = touch->getLocation();
    Vec2 vec2 = Vec2(vec2Temp.x - 40*GameOther::getWindowSmallScale() + (0.5 - _dropIcon->getAnchorPoint().x)*_dropIcon->getContentSize().width*GameOther::getWindowSmallScale(), vec2Temp.y + 70*GameOther::getWindowSmallScale() + (0.5 - _dropIcon->getAnchorPoint().y)*_dropIcon->getContentSize().height*GameOther::getWindowSmallScale());
    Node* node = GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MIANMO_NODE_NAME);
    DrawImageManager::getInstance()->onMovedTouch(node->convertToNodeSpace(__vec2));
}

bool MaskMediator::toolsFuncYanmo(Touch* touch, bool isYanmo)
{
    Node* contactNode = NULL;
    string str = this->getDropTargetNode()->getName();
    string targetStr;
    if(isYanmo)
    {
        if(str == ITEMS_YANMO_1)
        {
            targetStr = "yanmo1_mask";
        }else if(str == ITEMS_YANMO_2)
        {
            targetStr = "yanmo2_mask";
        }
    }else
    {
        if(str == ITEMS_LEMON_1)
        {
            targetStr = "lemon1_mask";
        }else if(str == ITEMS_LEMON_2)
        {
            targetStr = "lemon2_mask";
        }
    }
    Node* parent = this->getPlayerNode();
    Node* target = parent->getChildByName(targetStr);
    vector<string> strVector = {"yanjing1_touming", "yanjing2_touming"};
    for(int i = 0; i < strVector.size(); i++)
    {
        contactNode = parent->getChildByName(strVector.at(i));
        if(GameOther::getIsClickRectNode(contactNode, touch->getLocation(), this->getDropTargetNode()->getContentSize().width) && !target->isVisible())
        {
            GameSoundManager::getInstance()->playEffect(TIEDONGXI);
            DropMediator::onEndCallBackManural();
            setClickTargetNode(NULL);
            GameMain::gameMainInstance->RenwuBiyan();
            
            target->setVisible(true);
            target->setOpacity(255);
            string str1;
            string str2;
            if(isYanmo)
            {
                str1 = "yanmo1_mask";
                str2 = "yanmo2_mask";
            }else
            {
                str1 = "lemon1_mask";
                str2 = "lemon2_mask";
            }
            Node* youyanmo = parent->getChildByName(str1);
            Node* zuoyanmo = parent->getChildByName(str2);
            if(youyanmo->isVisible() &&  zuoyanmo->isVisible() && isYanmo)
            {
                this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=](){
                    youyanmo->runAction(FadeOut::create(0.5));
                    zuoyanmo->runAction(FadeOut::create(0.5));
                    this->getPlayerNode()->getChildByName(HEIYANQUAN_NODE_NAME)->runAction(FadeOut::create(0.5));
                }), DelayTime::create(0.5), CallFunc::create([=](){
                    youyanmo->setVisible(false);
                    
                    zuoyanmo->setVisible(false);
                    //                    zuoyanmo->setOpacity(255);
                    Node* yanmo1 = _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_1);
                    Node* yanmo2 = _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_2);
                    yanmo1->setVisible(true);
                    yanmo2->setVisible(true);
                    yanmo1->setScale(0);
                    yanmo2->setScale(0);
                    auto scaleTo = ScaleTo::create(1, 1);
                    yanmo1->runAction(scaleTo);
                    yanmo2->runAction(scaleTo->clone());
                    GameMain::gameMainInstance->Renwuzhengyan();
                }), NULL));
            }
            break;
        }
    }
    
}

void MaskMediator::toolsFuncBitie(Touch* touch)
{
    Node* contactNode = NULL;
    string str = this->getDropTargetNode()->getName();
    contactNode = getReaderUINode()->getChildByName("_bitie_xuxian_sqj");
    if(GameOther::getIsClickRectNode(contactNode, touch->getLocation(), this->getDropTargetNode()->getContentSize().width/10))
    {
        DropMediator::onEndCallBackManural();
        GameSoundManager::getInstance()->playEffect(TIEDONGXI);
        setClickTargetNode(NULL);
        contactNode->setVisible(false);
        Node* bitie = getReaderUINode()->getChildByName("_bitie_sqj");
        bitie->setVisible(true);
        setNodeOpcacity(bitie);
        bitie->runAction(Sequence::create(FadeTo::create(0.5f, 255), DelayTime::create(3), CallFunc::create([&](){
            getReaderUINode()->getChildByName("biziheitou_lxy")->runAction(FadeTo::create(0.5f, 0));
        }), FadeTo::create(0.5f, 0), NULL));
    }
}

void MaskMediator::toolsFuncQuebanFenpu(Touch* touch)
{
    Vec2 __vec = touch->getLocation();
    decodeQueBan(__vec);
    GameEffectLayer::getInstance()->moveParticleSystemQuad(this->getDropIcon(), this->getDropIcon()->getParent()->convertToWorldSpace(this->getDropIcon()->getPosition()));
    
}

void MaskMediator::toolsFuncFendi(Touch* touch)
{
    Vec2 __vec2 = touch->getLocation();
    __vec2.x -= this->getDropIcon()->getContentSize().height * (1 - this->getDropIcon()->getAnchorPoint().y) * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(this->getDropIcon()).x;
    __vec2.y += this->getDropIcon()->getContentSize().height * (1 - this->getDropIcon()->getAnchorPoint().y) * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(this->getDropIcon()).y - 20*this->getDropIcon()->getScale();
    GameEffectLayer::getInstance()->moveParticleSystemQuad(this->getDropIcon(), __vec2);
}

void MaskMediator::toolsFuncAcne(Touch* touch, bool isAcne)
{
    vector<string> strVector = {"ance_Copy_0", "ance_Copy_1", "ance_Copy_2", "ance_Copy_3", "ance_Copy_4", "ance_Copy_5"};
    Vec2 vec = touch->getLocation();
    float cos = cosf(45.0f / 180.0f * M_PI) ;
    vec.x -= _dropIcon->getContentSize().width *(_dropIcon->getAnchorPoint().x) * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(_dropIcon).x;
    vec.y += _dropIcon->getContentSize().width *(_dropIcon->getAnchorPoint().x) * cos * GameOther::getNodeToParentScale(_dropIcon).y;
    for(int i = 0; i < strVector.size(); i++)
    {
        Node* node = this->getPlayerNode()->getChildByName(strVector.at(i));
        if(isAcne)
        {
            Node* acne = node->getChildByName("acne_mask1_Copy");
            if(GameOther::getIsClickRectNode(acne, vec, 1*GameOther::getWindowSmallScale()) && acne->getOpacity() == 255)
            {
                Vec2 dropVec = _dropIcon->getPosition();
                float offXY = 10.0f;
                _dropIcon->runAction(Repeat::create(Sequence::create(MoveBy::create(0.1, Vec2(offXY, offXY)), DelayTime::create(0.01),
                                                                     MoveBy::create(0.1, Vec2(-offXY, -offXY)), NULL), 3));
                acne->setOpacity(254);
                acne->runAction(FadeOut::create(1));
            }
        }else
        {
            Node* acne = node->getChildByName("acne_mask1_Copy");
            if(acne->getOpacity() != 255)
            {
                Node* dou = node->getChildByName("acne_mask2_Copy");
                if(GameOther::getIsClickRectNode(dou, vec, 10*GameOther::getWindowSmallScale()) && dou->getOpacity() == 255)
                {
                    dou->setOpacity(254);
                    dou->runAction(FadeOut::create(1));
                }
            }
            
        }
        
    }
}

void MaskMediator::decodeQueBan(const Vec2& pVec2)
{
    auto __node = this->getPlayerNode()->getChildByName(QUEBAN_NODE_NAME);
        if(__node->getOpacity() == 255)
        {
            if(GameOther::getIsClickNode(__node, pVec2))
            {
                __node->runAction(FadeTo::create(2, 0));
                return;
            }
    }
}

void MaskMediator::decodeZaMei(const Vec2& pVec2, Node* pNode)
{
    auto parent = this->getPlayerNode();
    for(int i = 0; i < parent->getChildrenCount(); i++)
    {
        Node* __node = parent->getChildren().at(i);
        if(__node->getName().find("zamei") != string::npos)
        {
            for(Node* tempNode : __node->getChildren())
            {
                if(tempNode->getOpacity() == 255 && tempNode->getName().find("brow") != string::npos && GameOther::getIsClickRectNode(tempNode, pVec2, 30))
                {
                    tempNode->setOpacity(254);
//                    if(_dropIcon->getActionManager()->getNumberOfRunningActionsInTarget(_dropIcon) == 0)
//                    {
                        tempNode->runAction(Sequence::create(FadeOut::create(1), CallFunc::create([=](){
                            tempNode->setVisible(false);
                        }), NULL));
                        ParticleSystemQuad* __par = ParticleSystemQuad::create(GameOther::getPlatformPlist("eyebrow"));
                        __node->getParent()->addChild(__par);
                        __par->setPosition(tempNode->getPosition());
                        log("123");
                        
                        GameSoundManager::getInstance()->playEffect(JIANZI_MP3);
                        _dropIcon->runAction(Sequence::create(CallFunc::create([=](){
                            string str = ITEMS_NIEZI_2;
                            str = str + ".png";
                            Sprite* sprite1 = Sprite::create(str);
                            _dropIcon->setTexture(sprite1->getTexture());
                        }), DelayTime::create(0.2), CallFunc::create([=](){
                            string str = ITEMS_NIEZI_1;
                            str = str + ".png";
                            Sprite* sprite = Sprite::create(str);
                            _dropIcon->setTexture(sprite->getTexture());
                        }), NULL));
//                    }
                    return;
                }
            }
            
        }
    }
}

void MaskMediator::checkLemonVisible()
{
    Node* node = this->getPlayerNode();
    Node* lemon1 = node->getChildByName(ITEMS_LEMON_1);
    Node* lemon2 = node->getChildByName(ITEMS_LEMON_2);
    Vec2 vec1 = lemon1->getPosition();
    Vec2 vec2 = lemon2->getPosition();
    if(lemon1->isVisible() && lemon1->getActionManager()->getNumberOfRunningActionsInTarget(lemon1) == 0)
    {
        auto action = Sequence::create(MoveTo::create(1, Vec2(lemon1->getPositionX(), -lemon1->getContentSize().height)), CallFunc::create([=](){
            lemon1->setVisible(false);
            lemon1->setPosition(vec1);
        }), NULL);
        lemon1->runAction(action);
        auto action1 = ScaleTo::create(1, 1);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_1)->setVisible(true);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_1)->setScale(0);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_1)->runAction(action1);
    }
    if(lemon2->isVisible() && lemon2->getActionManager()->getNumberOfRunningActionsInTarget(lemon2) == 0)
    {
        auto action = Sequence::create(MoveTo::create(1, Vec2(lemon2->getPositionX(), -lemon2->getContentSize().height)), CallFunc::create([=](){
            lemon2->setVisible(false);
            lemon2->setPosition(vec2);
        }), NULL);
        lemon2->runAction(action);
        auto action1 = ScaleTo::create(1, 1);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_2)->setVisible(true);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_2)->setScale(0);
        _node->getChildByName("page2")->getChildByName(ITEMS_LEMON_2)->runAction(action1);
    }
    GameMain::gameMainInstance->Renwuzhengyan();
}

void MaskMediator::checkYanmoVisible()
{
    Node* node = this->getPlayerNode();
    Node* lemon1 = node->getChildByName(ITEMS_YANMO_1);
    Node* lemon2 = node->getChildByName(ITEMS_YANMO_2);
    Vec2 vec1 = lemon1->getPosition();
    Vec2 vec2 = lemon2->getPosition();
    if(lemon1->isVisible() && lemon1->getActionManager()->getNumberOfRunningActionsInTarget(lemon1) == 0)
    {
        this->stopAllActions();
        auto action = Sequence::create(FadeOut::create(0.5), CallFunc::create([=](){
            lemon1->setVisible(false);
            lemon1->setPosition(vec1);
        }), NULL);
        lemon1->runAction(action);
        auto action1 = ScaleTo::create(1, 1);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_1)->setVisible(true);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_1)->setScale(0);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_1)->runAction(action1);
    }
    if(lemon2->isVisible() && lemon2->getActionManager()->getNumberOfRunningActionsInTarget(lemon2) == 0)
    {
        this->stopAllActions();
        auto action = Sequence::create(FadeOut::create(0.5), CallFunc::create([=](){
            lemon2->setVisible(false);
            lemon2->setPosition(vec2);
        }), NULL);
        lemon2->runAction(action);
        auto action1 = ScaleTo::create(1, 1);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_2)->setVisible(true);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_2)->setScale(0);
        _node->getChildByName("page4")->getChildByName(ITEMS_YANMO_2)->runAction(action1);
    }
    GameMain::gameMainInstance->Renwuzhengyan();
}

void MaskMediator::setNodeOpcacity(Node* node, GLubyte opacity)
{
    node->setVisible(true);
    node->setOpacity(opacity);
}

void MaskMediator::clearMianMo()
{
    if(zhenglianqiEffect)
    {
        zhenglianqiEffect->stopSystem();
    }
    GameReaderManager::getSpriteFromParent(GameMain::gameMainInstance->makeUpNode, MIANMO_NODE_NAME)->setTexture(MIANMO_PNG);
    DrawImageManager::getInstance()->clearDrawImage(std::string(MIANMO_PNG));
}

void MaskMediator::onVirtualPage()
{
    clearMianMo();
}

void MaskMediator::refresh()
{
    
}