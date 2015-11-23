//
//  DrawCoverManager.cpp
//  huatu
//
//  Created by apple13 on 15/5/21.
//
//

#include "DrawCoverManager.h"

void DrawCoverManager::drawCoverData()
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
                            this->onDrawCoverImage(__rect, x, y);
                    }
                    else
                        this->onDrawCoverImage(__rect, x, y);
                }
            }
        }
    }
}

void DrawCoverManager::onDrawCoverImage(DrawRect pDrawRect, int pX, int pY)
{
    if(this->getIsRange(pX, pY))
    {
        int __juli;
        if(pX == pDrawRect._c_x)
            __juli = abs(pDrawRect._c_y - pY);
        else if(pY == pDrawRect._c_y)
            __juli = abs(pDrawRect._c_x - pX);
        else
            __juli = pow(pow(pX - pDrawRect._c_x, 2) + pow(pY - pDrawRect._c_y, 2), 0.5f);
        float __alpha = float(this->getRadius() - __juli) / float(this->getRadius()) * 0.2f;
        int num = ((this->getInitImage()->getHeight() - pY) * this->getInitImage()->getWidth() + pX) * 4;
        if(num < this->getInitImage()->getDataLen())
        {
            this->getInitImage()->getData()[num] = (unsigned char)((unsigned int)this->getInitImage()->getData()[num] * (1.0f - __alpha) + (unsigned int)this->getDrawImage()->getData()[num] * __alpha);
            this->getInitImage()->getData()[num + 1] = (unsigned char)((unsigned int)this->getInitImage()->getData()[num + 1]* (1.0f - __alpha) + (unsigned int)this->getDrawImage()->getData()[num + 1]* __alpha);
            this->getInitImage()->getData()[num + 2] = (unsigned char)((unsigned int)this->getInitImage()->getData()[num + 2]* (1.0f - __alpha) + (unsigned int)this->getDrawImage()->getData()[num + 2]* __alpha);
            this->getInitImage()->getData()[num + 3] = (unsigned char)((unsigned int)this->getInitImage()->getData()[num + 3]* (1.0f - __alpha) + (unsigned int)this->getDrawImage()->getData()[num + 3]* __alpha);
            _isDrawing = true;
        }
    }
}