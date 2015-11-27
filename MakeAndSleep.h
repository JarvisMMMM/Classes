//
//  MakeAndSleep.h
//  Christmas
//
//  Created by apple12 on 15/11/25.
//
//

#ifndef __Christmas__MakeAndSleep__
#define __Christmas__MakeAndSleep__

#include "ButtonMediator.h"

using namespace ui;

USING_NS_CC;

#define     STATE_BUOU              0
#define     STATE_TANGGUO           1
#define     STATE_DRESS             2

enum sleeplistType
{
    boxType,
    tangguoType,
    tangzhiType,
    tangguoboxType,
    tangguoduandaiType,
    hudiejieType,
};

class MakeAndSleep : public ButtonMediator
{
private:
    vector<int> _compareVector;
    vector<int> randVector1;
    vector<int> randVector2;
    vector<int> randVector3;
    float  _a;
    float  _r;
    float  _g;
    float  _b;
    Image* pImage;
    float deltaX;
    float deltaY;
    int _stateIndex;//
    int _tangguoIndex;
    int mianhuaCount;
    bool completeLoading1;
    bool completeLoading2;
    bool completeLoading3;
    bool completeLoading4;
    int loadingIndex;
    LoadingBar* loadingBar1;
    LoadingBar* loadingBar2;
    LoadingBar* loadingBar3;
    LoadingBar* loadingBar4;
    int _caijianOK;
    int _selectClothIndex;
    Sprite* _tiaosezhenSprite;
    Sprite* _curQunzi;
    Node* _colorNode;
    Node* _buouNode;
    Node* _tangguoNode;
    Node* _qunziNode;
    Node* toumingquyu;
    Node* _listNode;
    Node* _listNodeTanguo;
    Node* _shuijiaoZiNode;
    Vec2 _beginVec2;
    Vec2 _moveVec2;
    bool isColorZhizhen;
    bool _isMove;
    bool isRunSlider;
    bool isJiazi;
    bool isListTouch;
    bool isTouch;
    void loadResources();
    void onListClick(Sprite* sprite, int index);
    void initListContent(int indexListType);
    void dressFlyUp(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    void dressFlyUpTangguo(Sprite* sprite, const char* partName, const char* pngName, int idx, bool isSounds = true);
    bool buttonTouch(Touch* touch);    bool judgeListMove();
    
    bool selectClothTouch(Touch* touch);
    bool buouPointTouch(Touch* touch);
    void decodePoint(const string& str);
    
    bool selectQunziTouch(Touch* touch);
    bool qunziPointTouch(Touch* touch);
    void decodeQunziPoint(const string& str);
    
    void zhentouTouch(Touch* touch);
    void mianhuatouTouch(Touch* touch);
    void showLoadingBarArrow(Node* jiantouParent);
    void hideLoadingBarArrow(Node* jiantouParent);
    void buouMakeDone();
    void addDropIconSprite(Sprite* sprite, const Vec2& vec);
    void update(float dt);
    void onEndCallBack();
    bool jiaziMoveOut(Node* node);
    void jiaziMoveIn(Node* node);
    bool saveBuou(Touch* touch);
    bool saveTangguo(Touch* touch);
    bool saveDress(Touch* touch);
    void enterDressup();
    void enterBuou();
    void enterTanguo();
    void enterMake();
    void qipaoLogic(int index);
    bool qipaoTouch(Touch* touch);
    void clearHezi();
    void clearQipao();
public:
    Node* _csbNode;
    MakeAndSleep()
    : _ReaderUINode(NULL)
    {};
    CC_SYNTHESIZE(Node*, _ReaderUINode, ReaderUINode);
    //    static MakeCard* dressupMediatorInstance;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    
    CREATE_FUNC(MakeAndSleep);
    
    
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

#endif /* defined(__Christmas__MakeAndSleep__) */
