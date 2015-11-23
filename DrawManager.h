//
//  DrawManager.h
//  huatu
//
//  Created by apple13 on 15/5/21.
//
//

#ifndef __huatu__DrawManager__
#define __huatu__DrawManager__

#include "cocos2d.h"
USING_NS_CC;
#include <vector>

//类型
enum DRAWTYPE
{
    DRAW_COPY,
    DRAW_COVER,
    DRAW_CLEAR,
};

struct DrawImageIcon
{
    std::string _pngName;
    Image* _pImage;
};

struct DrawRect
{
    int _s_x;
    int _e_x;
    int _s_y;
    int _e_y;
    int _c_x;
    int _c_y;
    bool _isPoint;
};

class DrawManager : public Node
{
public:
    //当前画笔像素点数组的数组
    std::vector<DrawRect> _drawList;
    std::vector<DrawRect> _allDrawList;
    
    std::vector<DrawImageIcon > _initImageList;
    std::vector<DrawImageIcon > _drawImageList;
    std::vector<DrawImageIcon > _rangeImageList;
    /**
     *  控制没有绘制图像时不更新纹理
     */
    bool _isDrawing;
    
    Texture2D* _texture2D;
    
    Sprite* _drawSprite;
    
public:
    DrawManager()
    : _initImage(NULL)
    , _drawImage(NULL)
    , _texture2D(NULL)
    {};
    
    /**
     *  处理DrawImageList
     */
    Image* getInitImageIcon(std::string pngName);
    Image* getDrawImageIcon(std::string pngName);
    Image* getRangeImageIcon(std::string pngName);
    
    /**
     *  初始化一下image， 例如翻页后晴空 调用这个方法
     *  @param initPngName 必须跟上面那个方法里的initPngName 一样
     */
    void clearDrawImage(std::string initPngName);
    
    /**
     *  有控制画图区域时，判断是否在区域内
     */
    bool getIsRange(int pX, int pY);
    
    /**
     *  给sprite 赋纹理
     */
    void addSpriteTexture();
    
public:
    /**
     *  源画布
     */
    CC_SYNTHESIZE(Image* , _initImage, InitImage);
    /**
     *  当前要画得素材
     */
    CC_SYNTHESIZE(Image* , _drawImage, DrawImage);
    /**
     *  画图的范围
     */
    CC_SYNTHESIZE(Image* , _rangeImage, RangeImage);
    /**
     *  点与点之间是否自动连接线
     */
    CC_SYNTHESIZE(bool, _isAuto, IsAuto);
    /**
     *  笔刷半径
     */
    CC_SYNTHESIZE(int, _radius, Radius);
    /**
     *  画图类型
     */
    CC_SYNTHESIZE(DRAWTYPE, _drawType, DrawType);
};
#endif /* defined(__huatu__DrawManager__) */
