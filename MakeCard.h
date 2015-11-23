//
//  MakeCard.h
//  Christmas
//
//  Created by apple12 on 15/11/19.
//
//

#ifndef __Christmas__MakeCard__
#define __Christmas__MakeCard__

#include "ButtonMediator.h"

using namespace ui;

USING_NS_CC;

enum cardListType
{
    cardSealType,//印章
    cardStampType,
    cardBlessType,
    cardHuawenType,
    cardColorType,
    cardBiType,
    
    
    
    
};

class MakeCard : public ButtonMediator
{
private:
    Vec2 _beginVec2;
    Vec2 _moveVec2;
    bool _isDraw;
    bool _isSure;
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
    Node* toumingquyu;
    Node* signNameToumingquyu;
    void loadResources();
    void onListClick(Sprite* sprite, int index);
    void initListContent(int indexListType, bool isScale);
    void dressUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    void dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    bool buttonTouch(Touch* touch);
    void decodeSave();
    void gaiZhang(Sprite* sprite, int index);
    bool judgeListMove();
public:
    Node* _csbNode;
    MakeCard()
    : _ReaderUINode(NULL)
    {};
    CC_SYNTHESIZE(Node*, _ReaderUINode, ReaderUINode);
    Node* _cardUINode;
    Node* _zhengheNode;
    Node* _signNameNode;
    Node* _signNamePutNode;
    Node* _yinzhangParentNode;
//    static MakeCard* dressupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    
    CREATE_FUNC(MakeCard);
    
    
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
};

#endif /* defined(__Christmas__MakeCard__) */
