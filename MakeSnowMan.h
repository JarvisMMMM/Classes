//
//  MakeSnowMan.h
//  Christmas
//
//  Created by apple12 on 15/11/20.
//
//

#ifndef __Christmas__MakeSnowMan__
#define __Christmas__MakeSnowMan__

#include "ButtonMediator.h"

using namespace ui;

USING_NS_CC;

enum snowListType
{
    snowWeijinType,
    snowHatType,
    snowFaceType,
    snowHeadType,
    snowBodyType,
};

class MakeSnowMan : public ButtonMediator
{
private:
    int _bodyIndex;
    int exp;
    int expValue;
    Node* _xuerenNode;
    Node* _xueqiu;
    Node* _chanzi;
    Node* _listNode;
    Node* touming;
    Vec2 xueqiuOutVec;
    Vec2 _beginVec2;
    Vec2 _moveVec2;
    bool _isDraw;
    bool _isSure;
    bool _isCanMove;
    bool isChanzi;
    DrawNode* _draw;
    RenderTexture* render;
    Vec2 _pMoveVec2_n;
    Vector<DrawNode*> _brushs;
    vector<Color4F> _color4FVector;
    int huabiIndex;
    Vec2 _curSelectVec;
    Sprite* _curSelectBi;
    bool _isMove;
    bool isRunSlider;
    bool isJiazi;
    bool isListTouch;
    bool isTouch;
    void loadResources();
    void onListClick(Sprite* sprite, int index);
    void initListContent(int indexListType, bool isScale);
    void dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    void dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    bool buttonTouch(Touch* touch);
    bool judgeListMove();
    bool jiaziMoveOut(Touch* touch = NULL);
    void jiaziMoveIn();
    void shakeHands();
    bool itemsBeganTouch(Touch* touch);
    void setChanziGuideShow(Node* node);
    void setChanziGuideHide(Node* node);
    void decodeGameEffect(Touch* touch);
    Animation* createAnimation(Node* node);
    void initXuerenBody(int index);
    void initXuerenHead(int index);
public:
    Node* _csbNode;
    MakeSnowMan()
    : _ReaderUINode(NULL)
    {};
    CC_SYNTHESIZE(Node*, _ReaderUINode, ReaderUINode);
    //    static MakeCard* dressupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    
    CREATE_FUNC(MakeSnowMan);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    
    
    void touchEnd(Touch *touch);
    /**
     *  根据点击的瓶子找到对应跳动的对象
     */
    Node* decodeClickToJump(Node* clickNode);
    /**
     *  根据点击对象找到影子
     */
    Node* decodeYingZi(Node* yingZiNode, bool isVisible);
    void onEndYingzi(Node* pNode);
    /**
     *  点击瓶子对应的对象跳动下
     */
    void onClickToJump(Node* jumpNode);
    void onClickToJumpCallBack();
    
    void setNodeOpcacity(Node* node, GLubyte opacity = 0);
    
    void touchEndFunc(const string& str, int index);
    void onClick();
    
    virtual void onVirtualDropBegin(Touch* pTouch);
    virtual void onVirtualDropMove(Touch* pTouch);
    virtual void onVirtualDropEnd(Touch* pTouch);
    void onEndCallBack();
    void onEnd();
    void addDropIconSprite(Sprite* sprite, const Vec2& vec);
};

#endif /* defined(__Christmas__MakeSnowMan__) */
