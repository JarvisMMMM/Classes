//
//  GameListIconMediator.h
//  BabyGrow
//
//  Created by apple12 on 15/3/25.
//
//

#ifndef __BabyGrow__GameListIconMediator__
#define __BabyGrow__GameListIconMediator__

#include "cocos2d.h"
#include "ListIconMediator.h"
#include "ListMediator.h"


class GameListIconMediator : public ListIconMediator
{
private:
public:
    static int _selectIndex;
    static int _xifashuiIndex;
    static GameListIconMediator* initSprite(int type, Sprite* sprite, const char* centerName, const char* topName, const char* bottomName);
    Animate* daoyeti(int index);
    void onEnter();
    void onExit();
    void onClick();
    virtual void onBeginTouch(Touch* pTouch);
    virtual void onMoveTouch(Touch* pTouch);
    virtual void onEndTouch(Touch* pTouch);
    CREATE_FUNC(GameListIconMediator);
    CC_SYNTHESIZE(int, _num, num);
    CC_SYNTHESIZE(bool, _isvertical, isvertical);
    CC_SYNTHESIZE(Node*, _parentNode, parentNode);
};

#endif /* defined(__BabyGrow__GameListIconMediator__) */
