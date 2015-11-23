//
//  DropMediator.cpp
//  makeup
//
//  Created by apple13 on 14/12/2.
//
//

#include "DropMediator.h"
#include "MenuLayer.h"
#include "GameEffectLayer.h"

int DropMediator::_curListType;

void DropMediator::onEnter()
{
    GameMediator::onEnter();
}

void DropMediator::onExit()
{
    GameMediator::onExit();
}

void DropMediator::onDropBegin(Touch* pTouch)
{
    if(!this->getDropTargetNode())
        return;
    
    this->getDropTargetNode()->setVisible(false);
    
    this->addDropIcon(((Sprite *)this->getDropTargetNode())->getTexture(), pTouch->getLocation());
    
    this->onVirtualDropBegin(pTouch);
}

void DropMediator::onDropMove(Touch* pTouch)
{
    if(!this->getDropTargetNode())
        return;
    
    _dropIcon->setPosition(pTouch->getLocation());
    
    if(this->getDropIcon()->isVisible())
        this->onVirtualDropMove(pTouch);
}

void DropMediator::onDropEnd(Touch* pTouch)
{
    if(!this->getDropTargetNode())
        return;
    if(!_dropIcon)
        return;
    
    this->onVirtualDropEnd(pTouch);
    
    onDropEndBegin();
}

void DropMediator::addDropIcon(Texture2D* texture2D, const Vec2& pVec2)
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
    
    std::string str = this->getDropTargetNode()->getName();
    if(str == ITEMS_PENTOU)
    {
        _dropIcon = Sprite::create(ITEMS_PENTOU_2);
        _dropIcon->setAnchorPoint(Vec2(0.85, 0.4));
    }else if(str == ITEMS_LEMON_1)
    {
        _dropIcon = Sprite::create(ITEMS_LEMMON_1_PNG);
    }else if(str == ITEMS_LEMON_2)
    {
        _dropIcon = Sprite::create(ITEMS_LEMMON_2_PNG);
    }else if(str == ITEMS_YANMO_1)
    {
        _dropIcon = Sprite::create(ITEMS_YANMO_1_PNG);
    }else if(str == ITEMS_YANMO_2)
    {
        _dropIcon = Sprite::create(ITEMS_YANMO_2_PNG);
    }else
    {
        _dropIcon = Sprite::createWithTexture(texture2D);
        
    }
    this->addChild(_dropIcon, 1);
    //    GameEffectLayer::getInstance()->addChild(_dropIcon);
    _dropIcon->setPosition(pVec2);
    _dropIcon->setScale(GameOther::getWindowBigScale());
    
    if(str.find("mianmo_chongxi") != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.85, 0.4));
    }else if(str.find(ITEMS_MIANMO_1) != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.44, 0.25));
    }
//    else if(str == (ITEMS_MIANBANG))
//    {
//        _dropIcon->setAnchorPoint(Vec2(0.52, 0.25));
//    }
    else if(str == ("zameijia"))
    {
        _dropIcon->setAnchorPoint(Vec2(0.72, 0.47));
    }else if(str == ("zhenglianqi"))
    {
        _dropIcon->setAnchorPoint(Vec2(0.5, 0.28));
    }else if(str.find(ITEMS_JIEMAOSHUA) != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.5, 0.28));
    }else if(str.find(ITEMS_YANYING) != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.45, 0.24));
    }else if(str.find(ITEMS_BLUSH) != std::string::npos || str.find(ITEMS_FENDI) != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.5, 0.2));
    }else if(str.find(ITEMS_CHUNCAI) != std::string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.5, 0.2));
    }else if(str.find(ITEMS_MIAMNBANG) != string::npos || str.find(ITEMS_ACNE) != string::npos || str.find(ITEMS_NIEZI_1) != string::npos)
    {
        _dropIcon->setAnchorPoint(Vec2(0.8, 0.5));
    }
    
    if(GameScene::_houseIndex == makeupType || str.find(ITEMS_MIANMO_1) != std::string::npos)
    {
        if(str.find(ITEMS_MIANMO_2) == std::string::npos)
            _dropIcon->runAction(RotateTo::create(0.2, -30));
    }else if (str.find(ITEMS_NIEZI_1) != std::string::npos
             || str.find(ITEMS_ACNE) != std::string::npos
             || str.find(ITEMS_MIAMNBANG) != std::string::npos)
        _dropIcon->runAction(RotateTo::create(0.2, 45));
    else if(str.find(ITEMS_FENDI) != std::string::npos)
    {
        _dropIcon->runAction(Sequence::create(RotateTo::create(0.2, -45), CallFunc::create([=](){
            Vec2 __vec2 = pVec2;
            __vec2.x -= this->getDropIcon()->getContentSize().height * (1 - this->getDropIcon()->getAnchorPoint().y) * sinf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(this->getDropIcon()).x;
            __vec2.y += this->getDropIcon()->getContentSize().height * (1 - this->getDropIcon()->getAnchorPoint().y) * cosf(45.0f / 180.0f * M_PI) * GameOther::getNodeToParentScale(this->getDropIcon()).y;
            GameEffectLayer::getInstance()->addParticleSystemQuad(GameOther::getPlatformPlist("fendi"), this->getDropIcon(), __vec2, this);
        }), NULL));
    }
    _dropIcon->runAction(Repeat::create(Sequence::create(ScaleBy::create(0.125, 1.05), ScaleBy::create(0.125, 1), NULL), 2));
    

}

void DropMediator::onDropEndBegin()
{
    _dropIcon->runAction(Sequence::create(MoveTo::create(0.3f, this->getDropTargetNode()->getParent()->convertToWorldSpace(this->getDropTargetNode()->getPosition())),
                                          CallFunc::create(CC_CALLBACK_0(DropMediator::onDropEndCallBack, this)),
                                          NULL));
}

void DropMediator::onEndCallBackManural()
{
    if(_dropIcon)
    {
        _dropIcon->removeFromParent();
        _dropIcon = NULL;
    }
    string nodeName;
    if(this->getDropTargetNode())
    {
        nodeName = this->getDropTargetNode()->getName();
    }
    this->setDropTargetNode(NULL);
}

void DropMediator::onDropEndCallBack()
{
    _dropIcon->removeFromParent();
    _dropIcon = NULL;
    this->getDropTargetNode()->setVisible(true);
    this->setDropTargetNode(NULL);
}

void DropMediator::setMenuLayerTouch(MenuLayer* menuLayer, Touch* touch)
{
    menuLayer->menuButton(touch, true, true, true);
}

void DropMediator::yanhuaParticleEffect(Node* parent, Vec2 vec)
{
    ParticleSystemQuad* clothEffect = ParticleSystemQuad::create(("cloth_stars.plist"));
    parent->addChild(clothEffect);
    clothEffect->setScale(GameOther::getWindowSmallScale());
    clothEffect->setZOrder(100);
    GameSoundManager::getInstance()->playEffect(PAPERDIAPEREFFECT);
    clothEffect->setPosition(vec);
}
