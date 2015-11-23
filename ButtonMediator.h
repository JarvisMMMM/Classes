//
//  ButtonMediator.h
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#ifndef __makeup__ButtonMediator__
#define __makeup__ButtonMediator__

#include "DropMediator.h"
USING_NS_CC;
using namespace std;

class ButtonMediator : public DropMediator
{
private:
    int _last_page_num;
    /**
     *  按住一会后自动调用move
     */
    Touch* _beginTouch;
    Event* _beginEvent;
    bool _isMove;
    
    bool isChangePage;
    Layer* _pageNumBg;
public:
    Vec2 _pBeginVec2;
    Vec2 _pMoveVec2_b;
    Vec2 _pMoveVec2_n;
    ButtonMediator()
    : _isDropHeight(true)
    {};
    virtual void onEnter();
    virtual void onExit();
    
    void onInitPage();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual void onBeginTouch(Sprite* sprite, Touch* pTouch, int index){};
    virtual void onMoveTouch(Touch* pTouch, Sprite* sprite, int index){};
    virtual void onEndTouch(Touch* pTouch, Sprite* listIconNode, int index){};
    
    virtual void onListClick(Sprite* sprite, int index){};
    
    void touchEnd(Touch *touch);
    
    /**
     *  长按时间响应move
     */
    void decodeTouch();
    void decodeTouchTimer(float dt);
    
    /**
     *  拖拽后重新布局
     */
    void decodePage(bool is_left);
    
    /**
     *  根据点击的瓶子找到对应跳动的对象
     */
    Node* decodeClickToJump();
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
    
    /**
     *  添加页书的标记
     */
    void decodePageFlag();
    
    int getCurrentPage();
    
//-------------------------------------------------继承该button的需要时重写这些方法------------------------------
    /**
     *  是否可以长按自动开始拖拽
     */
    virtual bool onVirtualAutoDrop(){return true;};
    /**
     *  判断是否可以点击拖拽
     */
    virtual bool onVirtualDrop(){return true;};
    /**
     *  点击结束后有什么操作
     */
    virtual void onVirtualEnd(Touch* touch, const string& str){};
    /**
     *  当翻页时候做什么操作
     */
    virtual void onVirtualPage(){};
    
    /**
     *  是否要拖拽起来一定高度才会触发拖拽
     */
    CC_SYNTHESIZE(bool, _isDropHeight, IsDropHeight);
    
    /**
     *  工具栏有几页
     */
    CC_SYNTHESIZE(int, _pageMaxNum, PageMaxNum);
};

#endif /* defined(__makeup__ButtonMediator__) */
