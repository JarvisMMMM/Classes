//
//  DrawClearManager.h
//  huatu
//  慢慢擦出效果
//  Created by apple13 on 15/5/21.
//
//

#ifndef __huatu__DrawClearManager__
#define __huatu__DrawClearManager__

#include "DrawManager.h"

class DrawClearManager : public DrawManager
{
public:
    void drawClearData();
    
private:
    void onDrawClearImage(int pX, int pY);
};

#endif /* defined(__huatu__DrawClearManager__) */
