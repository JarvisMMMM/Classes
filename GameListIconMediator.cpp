#include "GameListIconMediator.h"
#include"cocostudio/CocoStudio.h"
//#include "GameMain.h"
#include "GameScene.h"
#include "ButtonMediator.h"

int GameListIconMediator::_selectIndex;
int GameListIconMediator::_xifashuiIndex;

void GameListIconMediator::onEnter()
{
    ListIconMediator::onEnter();
}

void GameListIconMediator::onExit()
{
    ListIconMediator::onExit();
}
void GameListIconMediator::onClick()
{
    int index = getnum();
    Sprite* sprite = NULL;
    sprite = (Sprite*)this->getChildByTag(111);
    ((ButtonMediator*)this->getparentNode())->onListClick(sprite, getnum());
    
}

void GameListIconMediator::onBeginTouch(Touch* pTouch)
{
    
    Sprite* sprite = NULL;
    Sprite* spriteCenter = NULL;
    Sprite* touchsprite = NULL;
    sprite = (Sprite*)this->getChildByTag(111);
    spriteCenter = (Sprite*)this->getChildByTag(121);
    if(!sprite)
        return;
    
    if(spriteCenter)
    {
        touchsprite = spriteCenter;
    }else
    {
        touchsprite = sprite;
    }
    ((ButtonMediator*)this->getparentNode())->onBeginTouch(touchsprite, pTouch, getnum());
}
void GameListIconMediator::onMoveTouch(Touch* pTouch)
{
    Sprite* sprite = NULL;
    Sprite* spriteCenter = NULL;
    Sprite* touchsprite = NULL;
    sprite = (Sprite*)this->getChildByTag(111);
    spriteCenter = (Sprite*)this->getChildByTag(121);
    if(!sprite)
        return;
    if(spriteCenter)
    {
        touchsprite = spriteCenter;
    }else
    {
        touchsprite = sprite;
    }
    ((ButtonMediator*)this->getparentNode())->onMoveTouch(pTouch, touchsprite, getnum());
}
void GameListIconMediator::onEndTouch(Touch* pTouch)
{
    Sprite* sprite = NULL;
    Sprite* spriteCenter = NULL;
    Sprite* touchsprite = NULL;
    sprite = (Sprite*)this->getChildByTag(111);
    spriteCenter = (Sprite*)this->getChildByTag(121);
    if(!sprite)
        return;
    if(spriteCenter)
    {
        touchsprite = spriteCenter;
    }else
    {
        touchsprite = sprite;
    }
    ((ButtonMediator*)this->getparentNode())->onEndTouch(pTouch, touchsprite, getnum());
}

GameListIconMediator* GameListIconMediator::initSprite(int type, Sprite* sprite, const char* centerName, const char* topName, const char* bottomName)
{
    GameListIconMediator* listIcon = static_cast<GameListIconMediator*>(GameListIconMediator::create());
    string cengstr = "";
    listIcon->addFileName(sprite, centerName, topName, bottomName);
    listIcon->setnum(type);
    listIcon->retain();
    return listIcon;
    
}