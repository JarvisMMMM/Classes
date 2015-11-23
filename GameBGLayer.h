//
//  GameBGLayer.h
//  BabyGrow
//
//  Created by apple12 on 15/3/19.
//
//

#ifndef __BabyGrow__GameBGLayer__
#define __BabyGrow__GameBGLayer__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

class GameBGLayer : public Layer
{
private:
    static int _houseIndex;
    void dressupAnimation();
    void cardinalineMove(Node* parent, float dtime, const string& guiji, const string& guiji1, const string& name);
    void cardinalineMove1(Node* parent, float dtime, const string& guiji, const string& name);
public:
    static GameBGLayer* gameBGLayer;
    bool init();
    CREATE_FUNC(GameBGLayer);
    virtual void onEnter();
    virtual void onExit();
    bool onTouchBegan(Touch* touch, Event* event);
    static Node *create(int houseIndex);
    void setAnimationShow(houseType type);
};

#endif /* defined(__BabyGrow__GameBGLayer__) */
