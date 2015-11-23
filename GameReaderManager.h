//
//  GameReaderManager.h
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#ifndef __makeup__GameReaderManager__
#define __makeup__GameReaderManager__

#include "cocos2d.h"
#include "ui/CocosGui.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;
using namespace ui;

#define CENTER "center"
#define BOTTOM "bottom"
#define BOTTOM_LEFT "bottom_left"
#define BOTTOM_RIGHT "bottom_right"
#define RIGHT_CENTER  "right_center"
#define LEFT_CENTER     "left_center"
class GameReaderManager
{
public:
    /**
     *  读取文件生成对象
     *  @param fileName 文件名
     *  @param position 对象的位置
     *  @param scale 缩放系数 0按照屏幕与768*1024比的最小缩放 1按照屏幕与768*1024比的最大缩放 2按照宽的比例缩放 3按照高缩放 4平铺
     */
    static Node* getNodeReaderFile(const char* fileName, const char* position, int scale = 0);
    
    static Node* getNodeFromParent(Node* parentNode, const char* nodeName);
    
    static Sprite* getSpriteFromParent(Node* parentNode, const char* nodeName);
};

#endif /* defined(__makeup__GameReaderManager__) */
