//
//  MenuLayer.h
//  BabyGrow
//
//  Created by apple12 on 15/4/3.
//
//

#ifndef __BabyGrow__MenuLayer__
#define __BabyGrow__MenuLayer__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MenuLayer : public Layer
{
private:
    bool isTouch;
    cocos2d::Size winsize;
    static Sprite* refreshMenuSprite;
    static Sprite* funcMenuSprite;
    static Sprite* noSoundMenuSprite;
    static Sprite* soundMenuSprite;
    
    static Sprite* photoMenuSprite;
    static Sprite* starMenuSprite;
    static Sprite* homeMenuSprite;
    static Sprite* XMenuSprite;
    static Sprite* _XMenuSprite;
    bool _backisChange;
    void backMenuFunc(Node* node);
    void _backMenuFunc(Node* node);
    void closeMenu();
    bool onTouchBegan(Touch* touch, Event* event);
public:
    MenuLayer();
    ~MenuLayer();
    static Sprite* backMenuSprite;
    static Sprite* _backMenuSprite;
    static MenuLayer* create();
    void callback();
    
    bool menuButton(Touch* touch, bool isClose, bool hasLeft, bool hasRight);
    
};

#endif /* defined(__BabyGrow__MenuLayer__) */
