//
//  MakeUpMediator.h
//  japanesesalon
//
//  Created by apple12 on 15/6/23.
//
//

#ifndef __japanesesalon__MakeUpMediator__
#define __japanesesalon__MakeUpMediator__

#include "ButtonMediator.h"
#include "GameData.h"
#include "DrawImageManager.h"

using namespace ui;

USING_NS_CC;

class MakeUpMediator : public ButtonMediator
{
private:
    Node* toumingquyu;
    Node* _csbNode;
    int _pageCount;
    Touch* _beginTouch;
    Event* _beginEvent;
    bool _isMove;
    bool isRunSlider;
    bool isListTouch;
    bool isTouch;
    bool isChangePage;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void initParticleEffect();
    void jiaziMoveIn();
    bool jiaziMoveOut(Touch* touch = NULL);
    
    void toolsFuncYanxian(Touch* touch);
    void toolsFuncYanmei(Touch* touch);
    void toolsFuncJiemao(Touch* touch);
    void toolsFuncYanying(Touch* touch);
    void toolsFuncSaihong(Touch* touch);
    void toolsFuncChuncai(Touch* touch);
    
    void changeJiemao(int jiemaoIndex);
    void changePage5Jiemao(int jiemaoIndex);
    void addJewel();
    void dressUp(const char* partName, const char* pngName, int idx, bool isSound = true);
    void onInitPage();
    bool moveJudge(Touch* touch);
    void initMianmo(const char* str1, const char* str2, const char* str3, DRAWTYPE type, int size, bool isauto, const char* soundStr, Touch* touch);
    void onVirtualPage();
public:
    bool isJiazi;
    int _yanxianIndex;
    MakeUpMediator()
    :_yanxianIndex(0)
    {};
    cocos2d::Size winsize;
    static Node* _node;
    Node* _listNode;
    bool decodeGameEffect(Touch* touch);
    static MakeUpMediator* makeupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    bool decodeJiaziMove(Touch* touch);
    CREATE_FUNC(MakeUpMediator);
    
    void onListClick(Sprite* sprite, int index);
    
    void initListContent(int indexListType);    
      
    void touchEndFunc(Touch* touch, const string& str, int index);
    void decodePrintScreenFace();

    virtual void onVirtualDropBegin(Touch* pTouch);
    virtual void onVirtualDropMove(Touch* pTouch);
    virtual void onVirtualDropEnd(Touch* pTouch);
    void onVirtualEnd(Touch* touch, const string& str);
};

#endif /* defined(__japanesesalon__MakeUpMediator__) */
