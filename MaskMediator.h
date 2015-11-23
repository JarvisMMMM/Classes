//
//  MaskMediator.h
//  SeaSideSalon
//
//  Created by apple12 on 15/9/15.
//
//

#ifndef __SeaSideSalon__MaskMediator__
#define __SeaSideSalon__MaskMediator__

#include "ButtonMediator.h"
#include "GameData.h"
#include "DrawImageManager.h"

using namespace ui;

USING_NS_CC;

class MaskMediator : public ButtonMediator
{
private:
    ParticleSystemQuad *zhenglianqiEffect;
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
    void initParticleEffect();
    
    bool toolsFuncMianmo(Touch* touch);
    bool toolsFuncMianmo1(Touch* touch);
    bool toolsFuncMianmopentou(Touch* touch);
    bool toolsFuncYanmo(Touch* touch, bool isYanmo);
    void decodeQueBan(const Vec2& pVec2);
    void decodeZaMei(const Vec2& pVec2, Node* pNode);
    void toolsFuncBitie(Touch* touch);
    void toolsFuncQuebanFenpu(Touch* touch);
    void toolsFuncFendi(Touch* touch);
    void toolsFuncAcne(Touch* touch, bool isAcne);
    void toolsFuncZhi(Touch* touch);
    
    void changeJiemao(int jiemaoIndex);
    void changePage5Jiemao(int jiemaoIndex);
    void onInitPage();
    bool moveJudge(Touch* touch);
    void initMianmo(const char* str1, const char* str2, const char* str3, DRAWTYPE type, int size, bool isauto, const char* soundStr, Touch* touch);
    void setNodeOpcacity(Node* node, GLubyte opacity = 0);
    void checkLemonVisible();
    void checkYanmoVisible();
    void clearMianMo();
    void onVirtualPage();
public:
    bool isJiazi;
    bool _isRefresh;
    int _yanxianIndex;
    MaskMediator()
    :_yanxianIndex(0)
    {};
    cocos2d::Size winsize;
    static Node* _node;
    Node* _listNode;
    bool decodeGameEffect(Touch* touch);
    static MaskMediator* makeupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    CREATE_FUNC(MaskMediator);
    void touchEndFunc(Touch* touch, const string& str, int index);
    void refresh();
    
    virtual void onVirtualDropBegin(Touch* pTouch);
    virtual void onVirtualDropMove(Touch* pTouch);
    virtual void onVirtualDropEnd(Touch* pTouch);
    void onVirtualEnd(Touch* touch, const string& str);
};

#endif /* defined(__SeaSideSalon__MaskMediator__) */
