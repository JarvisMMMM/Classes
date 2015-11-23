//
//  DrawImageManager.h
//  test
//  画图
//  onBeganTouch onMovedTouch onEndTouch 一定要调用
//  Created by apple13 on 14/11/4.
//
//

#ifndef __test__DrawImageManager__
#define __test__DrawImageManager__

#include "DrawCopyManager.h"

class DrawImageManager : public DrawCopyManager
{
private:
    //上一个节点
    Vec2 _lastVec2;
    bool _isDrawEnd;
public:
    static DrawImageManager* _s_instance;
    DrawImageManager()
    : _isDrawEnd(false)
    {};
    ~DrawImageManager();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
public:
    static DrawImageManager* getInstance();
    /**
     *  设置画图
     *  @param initPngName      初始化的图片
     *  @param drawPngName      当前要画的图片
     *  @param pDRAWTYPE        画图的类型
     *  @paran drawCircle       笔刷的大小 半径
     *  @param isAuto           是否自动连接点
     */
    void addDrawImage(Sprite* pSprite, std::string initPngName, std::string drawPngName, std::string rangePngName, DRAWTYPE pDRAWTYPE, int radius, bool isAuto);
    /**
     *  *  @param pSprite          在哪个对象上画图
     *  began设置坐标,以便更新源画布,并返回源画布最新数据
     *  @param pVec2 touch坐标对应对象坐标
     */
    void onBeganTouch(const Vec2& pVec2);
    /**
     *  *  @param pSprite          在哪个对象上画图
     *  move设置坐标,以便更新源画布,并返回源画布最新数据
     *  @param pVec2 touch坐标对应对象坐标
     */
    void onMovedTouch(const Vec2& pVec2, bool _isChangeLastVec2 = true);
    /**
     *  松开手指调用
     */
    void onEndTouch();
    /**
     *  点处理
     */
    void decodePointVector(const Vec2& pVec2);
    /**
     *  线处理
     */
    void decodeLineVector(const Vec2& pVec2, bool isRow);
    
    CREATE_FUNC(DrawImageManager);
};

#endif /* defined(__test__DrawImage__) */
