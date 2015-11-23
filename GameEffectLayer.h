//
//  GameEffectLayer.h
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#ifndef __makeup__GameEffectLayer__
#define __makeup__GameEffectLayer__
#include "cocos2d.h"
USING_NS_CC;
#include <vector>
struct EFFECTPARTICLE
{
    Node* __parentNode;
    ParticleSystemQuad* __patticleNode;
};
class GameEffectLayer : public Layer
{
private:
    std::vector<EFFECTPARTICLE> _particleList;
    Sprite* _dropIcon;
public:
    static GameEffectLayer* _s_instance;
    static GameEffectLayer* getInstance();
    CREATE_FUNC(GameEffectLayer);
    
    
    void addParticleSystemQuad(std::string pfile, Node* pNode, const Vec2& pVec2, Node* parent = NULL);
    void moveParticleSystemQuad(Node* pNode, const Vec2& pVec2);
    void removeParticleSystemQuad(Node* pNode);
};

#endif /* defined(__makeup__GameEffectLayer__) */
