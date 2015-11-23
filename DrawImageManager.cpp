//
//  DrawImage.cpp
//  test
//
//  Created by apple13 on 14/11/4.
//
//

#include "DrawImageManager.h"
DrawImageManager* DrawImageManager::_s_instance = 0;
DrawImageManager* DrawImageManager::getInstance()
{
    if(!_s_instance)
    {
        _s_instance = DrawImageManager::create();
        Director::getInstance()->getRunningScene()->addChild(_s_instance, 1000);
    }
    return _s_instance;
}

DrawImageManager::~DrawImageManager()
{
    _s_instance = NULL;
}

void DrawImageManager::addDrawImage(Sprite* pSprite, std::string initPngName, std::string drawPngName, std::string rangePngName, DRAWTYPE pDRAWTYPE, int radius, bool isAuto)
{
    _drawSprite = pSprite;
    
    this->setIsAuto(isAuto);
    this->setRadius(radius);
    this->setDrawType(pDRAWTYPE);
    
    this->setInitImage(this->getInitImageIcon(initPngName));
    
    this->setDrawImage(this->getDrawImageIcon(drawPngName));
    
    this->setRangeImage(this->getRangeImageIcon(rangePngName));
}

void DrawImageManager::onBeganTouch(const Vec2& pVec2)
{
    _isDrawEnd = false;
    
    _lastVec2 = pVec2;
    
    this->decodePointVector(pVec2);
}

void DrawImageManager::onMovedTouch(const Vec2& pVec2, bool _isChangeLastVec2)
{
    this->decodePointVector(pVec2);
    
    if(_isAuto)
    {
        float __x = pVec2.x - _lastVec2.x > 0.0f ? pVec2.x - _lastVec2.x : -(pVec2.x - _lastVec2.x);
        float __y = pVec2.y - _lastVec2.y > 0.0f ? pVec2.y - _lastVec2.y : -(pVec2.y - _lastVec2.y);
        bool is_direction = __x > __y ? false : true;
        float __tan_y_x = (pVec2.y - _lastVec2.y) / (pVec2.x - _lastVec2.x);
        if(is_direction)
        {
            int __height = abs(pVec2.y - _lastVec2.y + (pVec2.y - _lastVec2.y > 0.0f ? 0.5f : -0.5f));
            for(int i = 0; i < __height; i++)
            {
                float __y = pVec2.y - _lastVec2.y > 0 ? i : -i;
                float __x = __y / __tan_y_x;
                this->decodeLineVector(Vec2(_lastVec2.x + __x, _lastVec2.y + __y), is_direction);
            }
        }
        else
        {
            int __width = abs(pVec2.x - _lastVec2.x + (pVec2.x - _lastVec2.x > 0.0f ? 0.5f : -0.5f));
            for(int i = 0; i < __width; i++)
            {
                float __x = pVec2.x - _lastVec2.x > 0 ? i : -i;
                float __y = __x * __tan_y_x;
                this->decodeLineVector(Vec2(_lastVec2.x + __x, _lastVec2.y + __y), is_direction);
            }
        }
    }
    
    if(_isChangeLastVec2)
        _lastVec2 = pVec2;
}

void DrawImageManager::onEndTouch()
{
    _isDrawEnd = true;
}

void DrawImageManager::decodePointVector(const Vec2& pVec2)
{
    DrawRect __rect;
    __rect._s_x = pVec2.x - this->getRadius();
    __rect._e_x = pVec2.x + this->getRadius();
    __rect._s_y = pVec2.y - this->getRadius();
    __rect._e_y = pVec2.y + this->getRadius();
    __rect._c_x = pVec2.x;
    __rect._c_y = pVec2.y;
    __rect._isPoint = true;
    _allDrawList.push_back(__rect);
}

void DrawImageManager::decodeLineVector(const Vec2& pVec2, bool isRow)
{
    int __width;
    if(_drawType == DRAW_COPY)
        __width = 5;
    else
        __width = 0;
    DrawRect __rect;
    __rect._s_x = pVec2.x - (isRow ? this->getRadius() : __width);
    __rect._e_x = pVec2.x + (isRow ? this->getRadius() : __width);
    __rect._s_y = pVec2.y - (isRow ? __width : this->getRadius());
    __rect._e_y = pVec2.y + (isRow ? __width : this->getRadius());
    __rect._c_x = pVec2.x;
    __rect._c_y = pVec2.y;
    __rect._isPoint = false;
    _allDrawList.push_back(__rect);
}



/**
*   定时更新画图
*/
void DrawImageManager::onEnter()
{
    this->schedule(schedule_selector(DrawImageManager::update), 0.05f, kRepeatForever, 0.0f);
    Node::onEnter();
}

void DrawImageManager::onExit()
{
    this->unschedule(schedule_selector(DrawImageManager::update));
    Node::onExit();
}

void DrawImageManager::update(float dt)
{
    //没有数据 并且画图结束 清空所有数据
    if(_allDrawList.size() <= 0)
    {
        if(_isDrawEnd)
        {
            _isDrawEnd = false;
            for(int i = 0; i < _drawImageList.size(); i++)
            {
                CC_SAFE_RELEASE(_drawImageList.at(i)._pImage);
            }
            _drawImageList.clear();
            
            for(int i = 0; i < _rangeImageList.size(); i++)
            {
                CC_SAFE_RELEASE(_rangeImageList.at(i)._pImage);
            }
            _rangeImageList.clear();
            
            _drawSprite = NULL;
        }
        return;
    }
    
    //取数据处理 画图
    int __needMax;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(_drawType == DRAW_COVER)
        __needMax = 50;
    else
        __needMax = 100;
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    __needMax = 200;
#endif
    int __max;
    if(_allDrawList.size() >= __needMax)
        __max = __needMax;
    else
        __max = (int)_allDrawList.size();
    _drawList.clear();
    for(int i = 0; i < __max; i++)
    {
        _drawList.push_back(_allDrawList.at(i));
    }
    
    _allDrawList.erase(_allDrawList.begin(), _allDrawList.begin() + __max);
    
    if(_drawType == DRAW_COPY)
        this->drawCopyData();
    if(_drawType == DRAW_COVER)
        this->drawCoverData();
    if(_drawType == DRAW_CLEAR)
        this->drawClearData();
    _drawList.clear();
    
    this->addSpriteTexture();
}