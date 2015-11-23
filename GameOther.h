//
//  GameOther.h
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#ifndef __makeup__GameOther__
#define __makeup__GameOther__


#include "cocos2d.h"
#include "cocostudio/cocostudio.h"
USING_NS_CC;

#define WINDOW_WIDTH  768
#define WINDOW_HEIGHT 1024

#define         HELPHANDTAG         1001
#define         HANDMOVESPEED       330

enum HouseIndex
{
    keting,
    yushi,
    woshi,
    yuershi,
    yuanzi,
    liangyijia,
    pintu,
    
};


class GameOther
{
public:
    static Vector<Sprite*> starVector;
    static int _dangaoCount;
    static int _guozhCount;
    static int _bingjilingCount;
    static int _quqiCount;
    static int _chayeCount;
    static int _babyExp;
    static int _babyExpAddValue;
    static void addBabyExp(int addValue = 1);
    static void setIconAnimation(Node* node, bool isLoop = false, float scaleFix = 1);
    static void setIconAnimation2(Node* node, bool isLoop = false, float scaleFix = 1);
    static void setIconAnimation3(Node* node, bool isLoop = false, float scaleFix = 1);
    static bool isLightCircleShow;
    static Sprite* arrowSprite;
    static void handFunc(Node* parent, Node* sourceNode, Node* targetNode, bool isBone = false);
    static void removeHandFunc(Node* parent);
    static void shakeHand(Node* shakePositionNode);
    static void arrowFunc(Node* parent, const Vec2& vec, int rotation = 0);
    static void arrowRemoveFunc();
    static void clickHandFunc(Node* root, Node* parent, float scalexx, float scaleyy, bool isOff = false);
    static void removeClickHandFunc(Node* parent);
    static void lightCircleFunc(Node* lightCircle);
    static void lightCircleRemoveFunc(Node* lightCircle);
    static float getWindowBigScale();
    static float getWindowSmallScale();
    static float getWindwoWidthScale();
    static float getWindwoHeightScale();
    
    static Vec2 getNodeToParentScale(Node* pNode);
    
    static bool getIsClickNode(Node* pNode, const Vec2& pVec2);
    static bool getIsClickRectNode(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity = false);
    static bool getIsClickRectNodeSizeScale(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity = false);//精确一些的判断
    static bool getIsClickRectNodeScale(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity = false);
    static bool getIsChildClickNode(Node* pNode, const Vec2& pVec2);
    static bool getIsBoneClickRectNode(cocostudio::Bone* pBone, cocostudio::Armature* armature, const Vec2& pVec2, int rect);
    
    static void changeGRAYNodeToWhite(Node* pNode);
    
    static std::string getPlatformPlist(const char* pFile);
    static Node* seekNodeByName(Node* root, const std::string& name);
    static Node* seekNodeByTag(Node* root, int tag);
    static Sprite* cloneSprite(Sprite *sprite);
    static void starEffect(Node* bg, float scale = 1);
    static void clearEffect();
    static int getStrNumber(const std::string& bigStr, const std::string& shortStr);
    
};

#endif /* defined(__makeup__GameOther__) */
