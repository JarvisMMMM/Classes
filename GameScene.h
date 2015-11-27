//
//  GameScene.h
//  BabyGame
//
//  Created by apple12 on 15/1/12.
//
//

#ifndef __BabyGame__GameScene__
#define __BabyGame__GameScene__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
//#include "ButtonMediator.h"
#include "MenuLayer.h"
#include "GameSoundManager.h"
#include <vector>
#include "GameData.h"
#include "GameOther.h"

#include "GameReaderManager.h"
#include "GameReader.h"
#include "GameMain.h"

USING_NS_CC;

enum houseType
{
    makeupType,
    maskType,
    dressupType,
    showType,
    stickType,
    makecardType,
    makesnowmanType,
    makesleepType,
    makechristmasType,
};

class GameScene : public Layer
{
private:
    static bool isrefresh;
    Node* bg;
    void createMenuLayer(bool hasLeft, bool hasRight);
    void initRoomContent();
    Vec2 backmenuPosition;
    Vec2 grilPosition;
public:
    static float menuOffY;
    bool _hasLeft;
    bool _hasRight;
    MenuLayer* menuLayerInstance;
    static GameScene* gameScene;
    static int _babyState;
    static int _babyIndex;
    static int _houseIndex;
    virtual void onEnter();
    virtual void onExit();
    static Scene* createScene(int houseIndex, bool isRefresh = false);
    virtual bool init();
    CREATE_FUNC(GameScene);
    bool onTouchBegan(Touch* touch, Event* event);
    void makeupRoom();
    void dressupRoom();
    void showRoom();
    void leaveStickRoom();
    void enterStickRoom(int index);
    static void refresh();
    static void refreshAll();
    static void setLoading(Node* node, houseType index);
};


#endif /* defined(__BabyGame__GameScene__) */
