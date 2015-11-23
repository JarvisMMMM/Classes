//
//  DrawManager.cpp
//  huatu
//
//  Created by apple13 on 15/5/21.
//
//

#include "DrawManager.h"
Image* DrawManager::getInitImageIcon(std::string pngName)
{
    for(int i = 0; i < _initImageList.size(); i++)
    {
        if(strcmp(_initImageList.at(i)._pngName.c_str(), pngName.c_str()) == 0)
        {
            return _initImageList.at(i)._pImage;
        }
    }
    
    Image* __image = new Image();
    __image->initWithImageFile(pngName);
    
    
    DrawImageIcon __drawImageIcon;
    __drawImageIcon._pngName = pngName;
    __drawImageIcon._pImage = __image;
    _initImageList.push_back(__drawImageIcon);
    
    return __image;
}

Image* DrawManager::getDrawImageIcon(std::string pngName)
{
    for(int i = 0; i < _drawImageList.size(); i++)
    {
        if(strcmp(_drawImageList.at(i)._pngName.c_str(), pngName.c_str()) == 0)
        {
            return _drawImageList.at(i)._pImage;
        }
    }
    
    Image* __image = new Image();
    __image->initWithImageFile(pngName);
    
    
    DrawImageIcon __drawImageIcon;
    __drawImageIcon._pngName = pngName;
    __drawImageIcon._pImage = __image;
    _drawImageList.push_back(__drawImageIcon);
    
    return __image;
}

Image* DrawManager::getRangeImageIcon(std::string pngName)
{
    if(strcmp(pngName.c_str(), "") == 0)
        return NULL;
    if(pngName.find(".png") == pngName.npos)
        return NULL;
    for(int i = 0; i < _rangeImageList.size(); i++)
    {
        if(strcmp(_rangeImageList.at(i)._pngName.c_str(), pngName.c_str()) == 0)
        {
            return _rangeImageList.at(i)._pImage;
        }
    }
    
    Image* __image = new Image();
    __image->initWithImageFile(pngName);
    
    
    DrawImageIcon __drawImageIcon;
    __drawImageIcon._pngName = pngName;
    __drawImageIcon._pImage = __image;
    _rangeImageList.push_back(__drawImageIcon);
    
    return __image;
}

void DrawManager::clearDrawImage(std::string initPngName)
{
    for(int i = 0; i < _initImageList.size(); i++)
    {
        if(strcmp(_initImageList.at(i)._pngName.c_str(), initPngName.c_str()) == 0)
        {
            _initImageList.at(i)._pImage->initWithImageFile(initPngName);
        }
    }
}

bool DrawManager::getIsRange(int pX, int pY)
{
    if(this->getRangeImage())
    {
        int __range = ((this->getRangeImage()->getHeight() - pY) * this->getRangeImage()->getWidth() + pX) * 4;
        if(__range < this->getRangeImage()->getDataLen())
        {
            unsigned int __alpha = (unsigned int)this->getRangeImage()->getData()[__range + 3];
            if(__alpha <= 0)
                return false;
        }
    }
    return true;
}

void DrawManager::addSpriteTexture()
{
    if(!_isDrawing)
        return;
    
    if(!_drawSprite)
        return;
    
    if(_texture2D)
    {
//        CC_SAFE_RELEASE(_texture2D);
        _texture2D = NULL;
    }
    Texture2D* __texture2D1 = new Texture2D();
    __texture2D1->autorelease();
    __texture2D1->initWithImage(_initImage);
    _drawSprite->setTexture(__texture2D1);
    
//    _texture2D = new Texture2D();
//    _texture2D->initWithImage(this->getInitImage());
//    _drawSprite->setTexture(_texture2D);
}