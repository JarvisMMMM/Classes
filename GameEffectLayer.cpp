//
//  GameEffectLayer.cpp
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#include "GameEffectLayer.h"
#include "GameOther.h"

GameEffectLayer* GameEffectLayer::_s_instance = 0;
GameEffectLayer* GameEffectLayer::getInstance()
{
    if(!_s_instance)
        _s_instance = GameEffectLayer::create();
    return _s_instance;
}

void GameEffectLayer::addParticleSystemQuad(std::string pfile, Node* pNode, const Vec2& pVec2, Node* parent)
{
    ParticleSystemQuad* __pa = ParticleSystemQuad::create(pfile.c_str());
    if(parent)
    {
        parent->addChild(__pa);
    }else
        this->addChild(__pa, -1);
    __pa->setPosition(pVec2);
    __pa->setScale(GameOther::getWindowSmallScale());
    __pa->setStartSize(__pa->getStartSize() / GameOther::getWindowSmallScale());
    __pa->setStartSizeVar(__pa->getStartSizeVar() / GameOther::getWindowSmallScale());
    EFFECTPARTICLE __effectParticle;
    __effectParticle.__parentNode = pNode;
    __effectParticle.__patticleNode = __pa;
    _particleList.push_back(__effectParticle);
}

void GameEffectLayer::moveParticleSystemQuad(Node* pNode, const Vec2& pVec2)
{
    for(int i = 0; i < _particleList.size(); i++)
    {
        if(_particleList.at(i).__parentNode == pNode)
        {
            _particleList.at(i).__patticleNode->setPosition(pVec2);
            return;
        }
    }
}

void GameEffectLayer::removeParticleSystemQuad(Node* pNode)
{
    for(int i = 0; i < _particleList.size(); i++)
    {
        if(_particleList.at(i).__parentNode == pNode)
        {
            _particleList.at(i).__patticleNode->stopSystem();
            _particleList.erase(_particleList.begin() + i);
            return;
        }
    }
}