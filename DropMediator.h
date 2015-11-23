//
//  DropMediator.h
//  makeup
//  脱拽
//  Created by apple13 on 14/12/2.
//
//

#ifndef __makeup__DropMediator__
#define __makeup__DropMediator__
#include "GameMediator.h"
#include "MenuLayer.h"
#include "GameScene.h"
class DropMediator : public GameMediator
{
public:
    DropMediator()
    : _dropTargetNode(NULL)
    , _dropIcon(NULL)
    {};
    virtual void onEnter();
    virtual void onExit();
    
    static int _curListType;
    /**
     *  begin 方法
     */
    void onDropBegin(Touch* pTouch);
    /**
     *  move方法
     */
    void onDropMove(Touch* pTouch);
    /**
     *  end方法
     */
    void onDropEnd(Touch* pTouch);
    
    virtual void onDropEndBegin();
    void onDropEndCallBack();
    /**
     *  添加拖拽图标
     */
    void addDropIcon(Texture2D* texture2D, const Vec2& pVec2);
    /**
     *  拖拽图标
     */
    CC_SYNTHESIZE(Sprite* , _dropIcon, DropIcon);
    /**
     *  当前拖拽的对象
     */
    CC_SYNTHESIZE(Node* , _dropTargetNode, DropTargetNode);
    
    CC_SYNTHESIZE(Node*, _userDataNode, UserDataNode);
    
//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－继承使用重写－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
    /**
     *  drop begin move end方法 要使用请重写
     */
    virtual void onVirtualDropBegin(Touch* pTouch) {};
    virtual void onVirtualDropMove(Touch* pTouch) {};
    virtual void onVirtualDropEnd(Touch* pTouch) {};
    void onEndCallBackManural();
    void setMenuLayerTouch(MenuLayer* menuLayer, Touch* touch);
    void yanhuaParticleEffect(Node* parent, Vec2 vec = Vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
};

#endif /* defined(__makeup__GameDropMediator__) */
