//
//  DrawCopyManager.cpp
//  huatu
//
//  Created by apple13 on 15/5/21.
//
//

#include "DrawCopyManager.h"

void DrawCopyManager::drawCopyData()
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
                            this->onDrawCopyImage(x, y);
                    }
                    else
                        this->onDrawCopyImage(x, y);
                }
            }
        }
    }
}

void DrawCopyManager::onDrawCopyImage(int pX, int pY)
{
    if(this->getIsRange(pX, pY))
    {
        int num = ((this->getInitImage()->getHeight() - pY) * this->getInitImage()->getWidth() + pX) * 4;
        if(num < this->getInitImage()->getDataLen())
        {
            this->getInitImage()->getData()[num] = this->getDrawImage()->getData()[num];
            this->getInitImage()->getData()[num + 1] = this->getDrawImage()->getData()[num + 1];
            this->getInitImage()->getData()[num + 2] = this->getDrawImage()->getData()[num + 2];
            this->getInitImage()->getData()[num + 3] = this->getDrawImage()->getData()[num + 3];
            _isDrawing = true;
        }
    }
}