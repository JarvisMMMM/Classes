//
//  PrintScreenManager.h
//  testgame
//
//  Created by apple13 on 14-10-10.
//
//

#ifndef testgame_PrintScreenManager_h
#define testgame_PrintScreenManager_h
#include "cocos2d.h"
USING_NS_CC;

enum FLAG
{
    SAVE = 1,
    SHARE,
    SEND,
};
class PrintScreenManager
{
private:
    RenderTexture* _pRender;
    bool _is_save;
    FLAG _flag;
public:
    PrintScreenManager()
    : _pRender(NULL)
    , _is_save(false)
    {};
    
    static PrintScreenManager* getInstance();
    
    
    Node* printScreen();
    
    
    void savePrintScreen();
    void sharePrintScreen();
    void sendEmailPrintScreen();
protected:
    void beginSavePrintScreen();
    void savePrintScreening();
};

#endif
