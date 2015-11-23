//
//  DrawClearManager.cpp
//  huatu
//
//  Created by apple13 on 15/5/21.
//
//

#include "DrawClearManager.h"

void DrawClearManager::drawClearData()
{
    _isDrawing = false;
    for(int i = 0; i < _drawList.size(); i++)
    {
        DrawRect __rect = _drawList.at(i);
        for(int x = __rect._s_x; x <= __rect._e_x; x++)
        {
            for(int y = __rect._s_y; y <= __rect._e_y; y++)
            {
                if(x >= 0 &&
                   x <= this->getInitImage()->getWidth() &&
                   y >= 0 &&
                   y <= this->getInitImage()->getHeight())
                {
                    if(__rect._isPoint)
                    {
                        if((x - __rect._c_x) * (x - __rect._c_x) + (y - __rect._c_y) * (y - __rect._c_y) < this->getRadius() * this->getRadius())
                            this->onDrawClearImage(x, y);
                    }
                    else
                        this->onDrawClearImage(x, y);
                }
            }
        }
    }
}

void DrawClearManager::onDrawClearImage(int pX, int pY)
{
    int num = ((this->getInitImage()->getHeight() - pY) * this->getInitImage()->getWidth() + pX) * 4;
    if(num < this->getInitImage()->getDataLen())
    {
        this->getInitImage()->getData()[num] = (unsigned char)(unsigned int)this->getInitImage()->getData()[num] * 0.6f + (unsigned int)this->getDrawImage()->getData()[num] * 0.4f;
        this->getInitImage()->getData()[num + 1] = (unsigned char)(unsigned int)this->getInitImage()->getData()[num + 1]* 0.6f + (unsigned int)this->getDrawImage()->getData()[num + 1]* 0.4f;
        this->getInitImage()->getData()[num + 2] = (unsigned char)(unsigned int)this->getInitImage()->getData()[num + 2]* 0.6f + (unsigned int)this->getDrawImage()->getData()[num + 2]* 0.4f;
        this->getInitImage()->getData()[num + 3] = (unsigned char)(unsigned int)this->getInitImage()->getData()[num + 3]* 0.6f + (unsigned int)this->getDrawImage()->getData()[num + 3]* 0.4f;
        _isDrawing = true;
    }
}