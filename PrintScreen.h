//
//  PrintScreen.h
//  dentist
//
//  Created by apple13 on 14/11/25.
//
//

#ifndef __dentist__PrintScreen__
#define __dentist__PrintScreen__

#include "GameMediator.h"
class PrintScreen : public GameMediator
{
private:
    Sprite* _close;
    Sprite* _fb;
    Sprite* _photo;
    Sprite* _email;
public:
    PrintScreen()
    : _close(NULL)
    , _fb(NULL)
    , _photo(NULL)
    , _email(NULL)
    {};
    virtual void onEnter();
    virtual void onExit();
    
    void onRun();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    CREATE_FUNC(PrintScreen);
};

#endif /* defined(__dentist__PrintScreen__) */
