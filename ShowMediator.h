//
//  ShowMediator.h
//  meijia
//
//  Created by apple12 on 15/9/8.
//
//

#ifndef __meijia__ShowMediator__
#define __meijia__ShowMediator__

#include "ButtonMediator.h"

#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

using namespace ui;

USING_NS_CC;

class ShowMediator : public ButtonMediator
{
private:
    void initData();
    void onAddZhijia(vector<RenderTexture*> *tempVector, Node* parent);
public:
    static Node* _node;
    virtual void onEnter();
    virtual void onExit();
    void onRun();
    CREATE_FUNC(ShowMediator);
    void setPeishi(Node* parent, const string& toushistr, const string& str, int pzorder);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);

};

#endif /* defined(__meijia__ShowMediator__) */
