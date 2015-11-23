//
//  DressUpMediator.h
//  japanesesalon
//
//  Created by apple12 on 15/6/23.
//
//

#ifndef __japanesesalon__DressUpMediator__
#define __japanesesalon__DressUpMediator__

#include "ButtonMediator.h"

using namespace ui;

USING_NS_CC;

enum dressupListType
{
    dressupClothesType,
    dressupHadType,
    dressupWeijinType,
    dressupGloveType,
    dressupShoesType,
};

class DressUpMediator : public ButtonMediator
{
private:
    bool isTouxiangGirl1;
    bool isTouxiangGirl2;
    bool isTouxiangGirl3;
    bool isTouxiangGirl4;
    int _girlIndex;
    Node* _girl;
    Node* _headKuang1;
    Node* _headKuang2;
    Node* _headKuang3;
    Node* _headKuang4;
    Node* _girl1;
    Node* _girl2;
    Node* _girl3;
    Node* _girl4;
    Vector<Node*> _headVector;
    Node* _headPortrait;
    Vec2 girlVec;
    Node* toumingquyu;
    Vec2 _pBeginVec2;
    Vec2 _pMoveVec2_b;
    Vec2 _pMoveVec2_n;
    Vec2 _sourceNodeVec;
    int _last_page_num;
    Layer* _pageNumBg;
    int _pageCount;
    Touch* _beginTouch;
    Event* _beginEvent;
    bool _isMove;
    bool isRunSlider;
    bool isJiazi;
    bool isListTouch;
    bool isTouch;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void initParticleEffect();
    void jiaziMoveIn();
    void dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    void addFace();
    void addJewel();
    
    void refreshButton();
    void touchDownButton(Sprite* node);
    void headPortraitMoveIn();
    void headTouch(Touch* touch);
    void setGirlLaugh(Node* node, int girlIndex, bool isBigRenwu = true);
    void setGirlNormal(Node* node, int girlIndex, bool isBigRenwu = true);
    void setTouxiangLaugh(Node* node);
    void setTouxiangNormal(Node* node);
    void setEyeBlink(Node* node);
    void setEyeBlinkOne(Node* node, int girlIndex, int laugh);
    void update(float dt);
    void loadResources();
public:
    Node* _csbNode;
    int _yanxianIndex;
    DressUpMediator()
    : _ReaderUINode(NULL)
    {};
    CC_SYNTHESIZE(Node*, _ReaderUINode, ReaderUINode);
    cocos2d::Size winsize;
    Node* _listNode;
    Node* _leftButtonNode;
    static DressUpMediator* dressupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    
    CREATE_FUNC(DressUpMediator);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    void onListClick(Sprite* sprite, int index);
    
    void initListContent(int indexListType);
    
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
    bool jiaziMoveOut(Touch* touch = NULL);
    void onClick();
    void funcButtonHide();
    void funcButtonShow();
    bool judgeListMove();
};


#endif /* defined(__japanesesalon__DressUpMediator__) */
