//
//  StartScene.h
//  BabyGrow
//
//  Created by apple12 on 15/3/18.
//
//

#ifndef __BabyGrow__StartScene__
#define __BabyGrow__StartScene__

#include "cocos2d.h"
#include"cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "GameMain.h"

USING_NS_CC;
using namespace cocostudio;
class StartScene : public Layer
{
private:
    static bool _isNoStart;
    bool isTouched;
    Node *bg;
    Node* rootNode;
    Node* playerNode;
    Node* titleNode;
    void setLoading(Node* node, houseType index);
    void initAnimation(Node* bg);
    void hudieAnimation(Node* hudie);
    void girlAnimation(Node* hudie);
    void scheduleUpdate(float dt);
    void scheduleUpdate1(float dt);
    void ManAction();
    void GirlAction();
public:
    static bool isSound;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    bool init();
    static Scene* createScene(bool isNoStart = true);
    CREATE_FUNC(StartScene);
};

#endif /* defined(__BabyGrow__StartScene__) */
