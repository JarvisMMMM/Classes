//
//  ListIconMediator.cpp
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#include "ListIconMediator.h"
#include "GameOther.h"

void ListIconMediator::onEnter()
{
    Node::onEnter();
}

void ListIconMediator::onExit()
{
    Node::onExit();
}

void ListIconMediator::addFileName(Sprite* _spParam, const char* centerName, const char* topName, const char* bottomName)
{
    this->setFileName(std::string(_spParam->getName()));
    int offY = 20;
    Sprite* __sp = GameOther::cloneSprite(_spParam);
    
    this->addChild(__sp, 3);
    __sp->setTag(111);
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    Size size = Size(__sp->getContentSize().width/2, __sp->getContentSize().height + offY);
    this->setContentSize(size);
    __sp->setPosition(Vec2(0, 0));

    if(strcmp(centerName, "") != 0)
    {
        Sprite* __center = Sprite::create(centerName);
        __center->setName(centerName);
        this->addChild(__center, 3);
        __center->setTag(121);
        __center->setAnchorPoint(Vec2(0.5f, 0.5f));
        string centerStr = centerName;
        if(centerStr.find("toushi_") != string::npos || centerStr.find("yanbushuizuan_") != string::npos || centerStr.find("zuibushuizuan_") != string::npos
            || centerStr.find("erhuan_") != string::npos || centerStr.find("jinglingershi_") != string::npos)
        {
            __sp->setPosition(__sp->getPositionX(), __sp->getPositionY() - 20);
            __center->setPosition(__sp->getPosition());
            Size size = Size(__sp->getContentSize().width/2 + 40 + __center->getContentSize().width/2, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else if(centerStr.find("erding_") != string::npos)
        {
            __center->setPosition(__sp->getPosition());
            Size size = Size(__sp->getContentSize().width/2 + 40 + __center->getContentSize().width/2, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else if(centerStr.find("yanxianbi_") != string::npos || centerStr.find("erbuhuawenshua_") != string::npos)
        {
            __sp->setPosition(__sp->getPositionX() - 20, __sp->getPositionY() - 30);
            __center->setRotation(-28.0f);
            float w = sinf(28.0f / 180.0f * M_PI) * __center->getContentSize().height;
            __center->setPosition(Vec2(this->getContentSize().width / 2 - 30, 20 - 30));
            Size size = Size(__sp->getContentSize().width/2 + 40 + w, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else if(centerStr.find("yanyingbi_") != string::npos)
        {
            __sp->setPosition(__sp->getPositionX() - 20, __sp->getPositionY() - 35);
            __center->setRotation(-20.0f);
            float w = sinf(20.0f / 180.0f * M_PI) * __center->getContentSize().height;
            __center->setPosition(Vec2(this->getContentSize().width / 2 - 10 - 20, 20 - 30));
            Size size = Size(__sp->getContentSize().width/2 + 40 + w + 20, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else if(centerStr.find("jiemaoshua_") != string::npos || centerStr.find("chungaobishua_") != string::npos)
        {
            __sp->setPosition(-__sp->getContentSize().width + 10, __sp->getPositionY() - 23);
            __center->setRotation(-20.0f);
            float w = sinf(20.0f / 180.0f * M_PI) * __center->getContentSize().height;
            __center->setPosition(Vec2(__sp->getContentSize().width - __sp->getContentSize().width, 20 - 23));
            Size size = Size(__sp->getContentSize().width + 40 + w, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else if(centerStr.find("saihongshua_") != string::npos)
        {
            __center->setPosition(Vec2(this->getContentSize().width / 2 - __center->getContentSize().width*1/4, this->getContentSize().height / 2 + __sp->getPositionY() - 15));
            Size size = Size(__sp->getContentSize().width/2 + 40 + __center->getContentSize().width, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }else
        {
            __center->setPosition(Vec2(-30, 5));
            __center->setRotation(20);
            Size size = Size(__sp->getContentSize().width/2 + 80 + __center->getContentSize().width, __sp->getContentSize().height + offY);
            this->setContentSize(size);
        }
        
    }
    
    if(strcmp(topName, "") != 0)
    {
        Sprite* __bg = Sprite::create(topName);
        __bg->setName(topName);
        this->addChild(__bg, 1);
        __bg->setAnchorPoint(Vec2(0.5f, 1));
        __bg->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height));
    }
    
    if(strcmp(bottomName, "") != 0)
    {
        Sprite* __bg = Sprite::create(bottomName);
        __bg->setName(bottomName);
        this->addChild(__bg, 1);
        __bg->setAnchorPoint(Vec2(0.5f, 0.5f));
        __bg->setPosition(Vec2(0,  -__sp->getContentSize().height/2));
    }
    if(strcmp(centerName, "") == 0 && strcmp(topName, "") == 0 && strcmp(bottomName, "") == 0)
    {
        Size size = Size(__sp->getContentSize().width, __sp->getContentSize().height + offY);
        this->setContentSize(size);
    }
}

void ListIconMediator::addFadeFileNmae(const char* firstUrl, const char* secondUrl)
{
    Sprite* __first = Sprite::create(firstUrl);
    this->addChild(__first);
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->setContentSize(__first->getContentSize());
    __first->setAnchorPoint(Vec2(0.5f, 0.5f));
    __first->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    
    if(strcmp(secondUrl, "") != 0)
    {
        Sprite* __second = Sprite::create(secondUrl);
        this->addChild(__second);
        
        __second->setAnchorPoint(Vec2(0.5f, 0.5f));
        __second->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    }
}

void ListIconMediator::onClick()
{
    
}

void ListIconMediator::onBeginTouch(Touch* pTouch)
{
    
}
void ListIconMediator::onMoveTouch(Touch* pTouch)
{
    
}
void ListIconMediator::onEndTouch(Touch* pTouch)
{
    
}

void ListIconMediator::onClickVisi()
{
    this->getChildByTag(111)->setVisible(false);
}

void ListIconMediator::onClickAlpha()
{
    this->getChildByTag(111)->setOpacity(100);
}

void ListIconMediator::onNoClick()
{
    this->getChildByTag(111)->setVisible(true);
    this->getChildByTag(111)->setOpacity(255);
}

void ListIconMediator::addClickIcon()
{
    Sprite* __icon = Sprite::create("dui.png");
    __icon->setAnchorPoint(Vec2(1, 0));
    __icon->setTag(222);
    this->addChild(__icon, 100);
    __icon->setPosition(Vec2(this->getContentSize().width, 0));
}
void ListIconMediator::noClickIcon()
{
    this->removeChildByTag(222);
}