//
//  GameMain.h
//  Marry
//
//  Created by apple12 on 15/6/2.
//
//

#ifndef __Marry__GameMain__
#define __Marry__GameMain__

#include "cocos2d.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class GameMain : public Layer
{
private:
    bool onTouchBegan(Touch* touch, Event* event);
public:
    Node* _zhuanpan;
    int _type;
    bool isListTouch;
    static GameMain* gameMainInstance;
    Node* makeUpNode;
    Node* makeUpNode1;
    Node* makeUpNode2;
    Node* menuNode;
    bool init();
    CREATE_FUNC(GameMain);
    void Renwuzhengyan();
    void RenwuBiyan();
};

#endif /* defined(__Marry__GameMain__) */
