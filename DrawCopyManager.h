//
//  DrawCopyManager.h
//  andy
//  图片替换
//  Created by andy on 15/5/21.
//
//

#ifndef __huatu__DrawCopyManager__
#define __huatu__DrawCopyManager__

#include "DrawCoverManager.h"

class DrawCopyManager : public DrawCoverManager
{
public:
    void drawCopyData();
    
private:
    void onDrawCopyImage(int pX, int pY);
};

#endif /* defined(__huatu__DrawCopyManager__) */
