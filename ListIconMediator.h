//
//  ListIconMediator.h
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#ifndef __makeup__ListIconMediator__
#define __makeup__ListIconMediator__

#include "GameMediator.h"
#include "DropMediator.h"

class ListIconMediator : public GameMediator
{
public:
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onBeginTouch(Touch* pTouch);
    virtual void onMoveTouch(Touch* pTouch);
    virtual void onEndTouch(Touch* pTouch);
    void addFileName(Sprite* __sp, const char* centerName = "", const char* topName = "", const char* bottomName = "");
    
    void addFadeFileNmae(const char* firstUrl, const char* secondUrl);
    /**
     *  被电击了调用这个方法
     */
    virtual void onClick();
    
    /**
     *  点击后隐藏icon
     */
    void onClickVisi();
    /**
     *  点击后半透明icon
     */
    void onClickAlpha();
    /**
     *  未点击恢复
     */
    void onNoClick();
    
    /**
     *  选中选中的icon
     */
    void addClickIcon();
    void noClickIcon();
    
    CC_SYNTHESIZE(std::string, _fileName, FileName);
};

#endif /* defined(__makeup__ListIconMediator__) */
