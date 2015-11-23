//
//  GameMediator.h
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#ifndef __makeup__GameMediator__
#define __makeup__GameMediator__
#include "cocos2d.h"
USING_NS_CC;

class GameMediator : public Layer
{
private:
    Vec2 _headPosition;
    bool _isEnd;
    Node* _readerUIBgNode;
    Node* _readerUINode;
public:
    static GameMediator* instance;
    GameMediator()
    : _readerUINode(NULL)
    , _callbackNode(NULL)
    , _clickTargetNode(NULL)
    , _readerUIBgNode(NULL)
    , _head(NULL)
    , _isEnd(false)
    , _swallowTouches(true)
    {};
    virtual void onEnter();
    virtual void onExit();
    /**
     *  当前界面
     */
    void setReaderUINode(Node* pNode);
    Node* getReaderUINode();
    /**
     *  当前界面背景
     */
    void setReaderUIBgNode(Node* pNode);
    Node* getReaderUIBgNode();
    /**
     *  回调使用node
     */
    CC_SYNTHESIZE(Node* , _callbackNode, CallBackNode);
    CC_SYNTHESIZE(Node* , _playerNode, PlayerNode);
    /**
     *  当前点击的对象
     */
    CC_SYNTHESIZE(Node* , _clickTargetNode, ClickTargetNode);
    
    CC_SYNTHESIZE(Sprite* , _head, Head);
    
    CC_SYNTHESIZE(bool, _swallowTouches, SwallowTouches);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void decodeNodeVisibleTrue(Node* pNode);
    void decodeNodeVisibleFalse(Node* pNode);
    
private:
    void addHead(Node* parentNode, const Vec2& pVec2);
public:
    void addOneMoveHead(Node* parentNode, const Vec2& startVec2, const Vec2& endVec2);
    void addMoveHead(Node* parentNode, const Vec2& startVec2, const Vec2& endVec2);
    void changeOneMoveHead(Node* pNode);
    void removeHead();
    
    void onAction();
    void onEnd();
    
    /**
     *  界面打开方式
     *  @param 1 打开界面慢慢放大  关闭界面慢慢缩小
     *  @param 2 打开界面从上掉下  关闭界面往上飞出
     */
    void onStartAction(int pInt = 1);
    void onStartActionCallBack();
    void onEndAction(int pInt = 1);
    void onEndActionCallBack();
    virtual void onVirtualEndAction(){};
};

#endif /* defined(__makeup__GameMediator__) */
