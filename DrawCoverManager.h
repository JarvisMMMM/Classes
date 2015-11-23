//
//  DrawCoverManager.h
//  andy
//  图片覆盖
//  Created by andy on 15/5/21.
//
//

#ifndef __huatu__DrawCoverManager__
#define __huatu__DrawCoverManager__

#include "DrawClearManager.h"

class DrawCoverManager : public DrawClearManager
{
public:
    void drawCoverData();
    
private:
    void onDrawCoverImage(DrawRect pDrawRect, int pX, int pY);
};

#endif /* defined(__huatu__DrawCoverManager__) */
