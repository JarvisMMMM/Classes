//
//  GameOther.cpp
//  makeup
//
//  Created by apple13 on 14/12/1.
//
//

#include "GameOther.h"
#include "GameScene.h"

Sprite* GameOther::arrowSprite = NULL;
bool GameOther::isLightCircleShow = false;
int GameOther::_babyExp = 0;
int GameOther::_babyExpAddValue = 0;
int GameOther::_dangaoCount = 0;
int GameOther::_guozhCount = 0;
int GameOther::_bingjilingCount = 0;
int GameOther::_quqiCount = 0;
int GameOther::_chayeCount = 0;
Vector<Sprite*> GameOther::starVector;

float GameOther::getWindowBigScale()
{
    float __x = Director::getInstance()->getWinSize().width / WINDOW_WIDTH;
    float __y = Director::getInstance()->getWinSize().height / WINDOW_HEIGHT;
    return __x > __y ? __x : __y;
}

float GameOther::getWindowSmallScale()
{
    float __x = Director::getInstance()->getWinSize().width / WINDOW_WIDTH;
    float __y = Director::getInstance()->getWinSize().height / WINDOW_HEIGHT;
    return __x > __y ? __y : __x;
}

float GameOther::getWindwoWidthScale()
{
    return Director::getInstance()->getWinSize().width / WINDOW_WIDTH;
}

float GameOther::getWindwoHeightScale()
{
    return Director::getInstance()->getWinSize().height / WINDOW_HEIGHT;
}

bool GameOther::getIsClickNode(Node* pNode, const Vec2& pVec2)
{
    if(!pNode || !pNode->isVisible() || !pNode->getParent()->isVisible() || pNode->getOpacity() == 0)
        return false;
    Vec2 local = pNode->convertToNodeSpace(pVec2);
    Rect r = Rect( pNode->getPositionX() - pNode->getContentSize().width * pNode->getAnchorPoint().x,
                  pNode->getPositionY() - pNode->getContentSize().height * pNode->getAnchorPoint().y,
                  pNode->getContentSize().width, pNode->getContentSize().height);
    r.origin = Vec2::ZERO;
    bool ret = r.containsPoint(local);
    return ret;
}

bool GameOther::getIsClickRectNode(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity)
{
    if(!isOpacity)
    {
        if(!pNode || !pNode->isVisible() || pNode->getOpacity() == 0)
            return false;
    }else
    {
        if(!pNode)
            return false;
    }
    
    Vec2 local = pNode->convertToNodeSpace(pVec2);
    Rect __tr = Rect(local.x - rect / 2, local.y - rect / 2, rect, rect);
    Rect r = Rect( pNode->getPositionX() - pNode->getContentSize().width * pNode->getAnchorPoint().x,
                  pNode->getPositionY() - pNode->getContentSize().height * pNode->getAnchorPoint().y,
                  pNode->getContentSize().width, pNode->getContentSize().height);
    r.origin = Vec2::ZERO;
    
    return r.intersectsRect(__tr);
}

bool GameOther::getIsClickRectNodeSizeScale(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity)
{
    if(!isOpacity)
    {
        if(!pNode || !pNode->isVisible() || pNode->getOpacity() == 0)
            return false;
    }else
    {
        if(!pNode)
            return false;
    }
    
    Vec2 local = pNode->convertToNodeSpace(pVec2);
    Rect __tr = Rect(local.x - rect / 2, local.y - rect / 2, rect, rect);
    Rect r = Rect( pNode->getPositionX() - pNode->getContentSize().width * pNode->getAnchorPoint().x,
                  pNode->getPositionY() - pNode->getContentSize().height * pNode->getAnchorPoint().y,
                  5, 5);
    r.origin = Vec2::ZERO;
    
    return r.intersectsRect(__tr);
}

bool GameOther::getIsClickRectNodeScale(Node* pNode, const Vec2& pVec2, int rect, bool isOpacity)
{
    if(!isOpacity)
    {
        if(!pNode || !pNode->isVisible() || pNode->getOpacity() == 0)
            return false;
    }else
    {
        if(!pNode)
            return false;
    }
    
    Vec2 local = pNode->convertToNodeSpace(pVec2);
    Rect __tr = Rect(local.x - rect / 2, local.y - rect / 2, rect, rect);
    Rect r = Rect( (pNode->getContentSize().width/4) ,
                  (pNode->getContentSize().height/4),
                  pNode->getContentSize().width/4, pNode->getContentSize().height/4);
    //    r.origin = Vec2::ZERO;
    return r.intersectsRect(__tr);
}

bool GameOther::getIsChildClickNode(Node* pNode, const Vec2& pVec2)
{
    for(int i = 0 ; i < pNode->getChildrenCount(); i++)
    {
        if(!pNode || !pNode->isVisible() || pNode->getOpacity() == 0 || !pNode->getParent()->isVisible())
            return false;
        Node* sunziNode = pNode->getChildren().at(i);
        if(GameOther::getIsClickNode(sunziNode, pVec2)  &&
           sunziNode->getName() != "noclick" && sunziNode->getParent()->isVisible())
        {
            return true;
        }
    }
    return false;
    
}
//骨骼碰撞检测
bool GameOther::getIsBoneClickRectNode(cocostudio::Bone* pBone, cocostudio::Armature* armature, const Vec2& pVec2, int rect)
{
    if(!pBone || !pBone->isVisible() || pBone->getOpacity() == 0)
        return false;
    Vec2 local = pVec2;
    Rect __tr = Rect(local.x - rect / 2, local.y - rect / 2, rect, rect);
    Vec2 vec = armature->convertToWorldSpace(pBone->getDisplayManager()->getBoundingBox().origin);
    Size size = pBone->getDisplayManager()->getBoundingBox().size;
    Rect r = Rect( vec.x,vec.y,
                  size.width*GameOther::getWindowSmallScale(), size.height*GameOther::getWindowSmallScale());
    //    r.origin = Vec2::ZERO;
    return r.intersectsRect(__tr);
}

Vec2 GameOther::getNodeToParentScale(Node* pNode)
{
    Node* __parent  = pNode;
    float __x = __parent->getScaleX();
    float __y = __parent->getScaleY();
    while (true)
    {
        if(__parent->getParent())
        {
            __parent = __parent->getParent();
            __x *= __parent->getScaleX();
            __y *= __parent->getScaleY();
        }
        else
            return Vec2(__x, __y);
    }
    return Vec2(__x, __y);
}

void GameOther::changeGRAYNodeToWhite(Node* pNode)
{
    pNode->setColor(Color3B::GRAY);
    pNode->runAction(TintTo::create(1, 255, 255, 255));
    for(int i = 0; i < pNode->getChildrenCount(); i++)
    {
        pNode->getChildren().at(i)->setColor(Color3B::GRAY);
        pNode->getChildren().at(i)->runAction(TintTo::create(1, 255, 255, 255));
    }
}

std::string GameOther::getPlatformPlist(const char* pFile)
{
    std::stringstream __stream;
    __stream << pFile;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    __stream << "_android";
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    __stream << "_ios";
#endif
    __stream << ".plist";
    return __stream.str();
}

Node* GameOther::seekNodeByTag(Node* root, int tag){
    if (!root)
    {
        return nullptr;
    }
    if (root->getTag() == tag)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    ssize_t length = arrayRootChildren.size();
    for (ssize_t i=0;i<length;i++)
    {
        Node* child = dynamic_cast<Node*>(arrayRootChildren.at(i));
        if (child)
        {
            Node* res = seekNodeByTag(child,tag);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}

Node* GameOther::seekNodeByName(Node* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Node* child = dynamic_cast<Node*>(subWidget);
        if (child)
        {
            Node* res = seekNodeByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}


void GameOther::handFunc(Node* parent, Node* sourceNode, Node* targetNode, bool isBone)
{
    Sprite* helpHand = Sprite::create("xiaoshou.png");
    helpHand->setFlippedX(true);
    parent->addChild(helpHand);
    helpHand->setTag(HELPHANDTAG);
    helpHand->setScale(getWindowSmallScale());
    
    Vec2 sourceVec = sourceNode->getParent()->convertToWorldSpace(sourceNode->getPosition());
    sourceVec = Vec2(sourceVec.x - helpHand->getContentSize().width/2, sourceVec.y - helpHand->getContentSize().height/2);
    helpHand->setPosition(sourceVec);
    
    Vec2 targetVec;
    if(isBone)
    {
        cocostudio::Bone* bone = ((cocostudio::Bone*)targetNode);
        targetVec = bone->getArmature()->convertToWorldSpace(Vec2(bone->getWorldInfo()->x, bone->getWorldInfo()->y));
        targetVec = Vec2(targetVec.x + bone->getDisplayManager()->getBoundingBox().size.width/2, targetVec.y + bone->getDisplayManager()->getBoundingBox().size.height/2);
    }else
    {
        targetVec = targetNode->getParent()->convertToWorldSpace(targetNode->getPosition());
    }
    
    targetVec = Vec2(targetVec.x - helpHand->getContentSize().width/2, targetVec.y - helpHand->getContentSize().height/2);
    float xw = fabs(sourceVec.x - targetVec.x);
    float yh = fabs(sourceVec.y - targetVec.y);
    float distance = sqrt(xw*xw + yh*yh);
    MoveTo* move = MoveTo::create(distance / (HANDMOVESPEED*GameOther::getWindowSmallScale()), targetVec);
    
    helpHand->runAction(Sequence::create(Repeat::create(Sequence::create(move, FadeOut::create(0.5), CallFunc::create([=](){
        helpHand->setVisible(false);
        helpHand->setPosition(sourceVec);
        helpHand->setOpacity(255);
    }), DelayTime::create(1), Show::create(), NULL), 3), CallFunc::create([=]()mutable{
        helpHand->removeFromParent();
        helpHand = NULL;
    }), NULL));
}


void GameOther::removeHandFunc(Node* parent)
{
    Node* node = parent->getChildByTag(HELPHANDTAG);
    if(node)
    {
        node->removeFromParent();
        node = NULL;
    }
}

void GameOther::shakeHand(Node* shakePositionNode)
{
    Sprite* helpHand = Sprite::create("xiaoshou.png");
    helpHand->setFlippedX(true);
    shakePositionNode->getParent()->addChild(helpHand);
    helpHand->setTag(HELPHANDTAG);
    Vec2 vec = Vec2(shakePositionNode->getPositionX() - helpHand->getContentSize().width, shakePositionNode->getPositionY() - helpHand->getContentSize().height/2);
    helpHand->setPosition(vec);
    helpHand->runAction(Sequence::create(Repeat::create(Sequence::create(MoveBy::create(0.4, Vec2(helpHand->getContentSize().width*2, 0)), MoveBy::create(0.4, Vec2(-helpHand->getContentSize().width*2, 0)), NULL), 3), CallFunc::create([=]()mutable{
        helpHand->removeFromParent();
        helpHand = NULL;
    }), NULL));
}

void GameOther::arrowFunc(Node* parent, const Vec2& vec, int rotation)
{
    if(arrowSprite)
        return;
    arrowSprite = Sprite::create("arrow.png");
    arrowSprite->setName("noclick");
    //    sprite->setAnchorPoint(Vec2(0));
    float rotationValue = 0;
    int y = 0;
    if(rotation == 0)
    {
        rotationValue = 225;
        y = vec.y - arrowSprite->getContentSize().height/2;
    }else
    {
        rotationValue = 135;
        y = vec.y + arrowSprite->getContentSize().height;
    }
    Vec2 vec1 = Vec2(vec.x + arrowSprite->getContentSize().width - 15, y);
    arrowSprite->setPosition(vec1);
    
    arrowSprite->setRotation(rotationValue);
    parent->addChild(arrowSprite, 10);
    float tempdt = 0.3f;
    arrowSprite->runAction(Sequence::create(Repeat::create(Sequence::create(ScaleTo::create(tempdt, arrowSprite->getScale() + 0.1), ScaleTo::create(tempdt, arrowSprite->getScale() - 0.1), NULL), 5), CallFunc::create([=]{
        GameOther::arrowRemoveFunc();
    }), NULL));
}

void GameOther::arrowRemoveFunc()
{
    if(arrowSprite)
    {
        arrowSprite->removeFromParent();
        arrowSprite = NULL;
    }
}

void GameOther::clickHandFunc(Node* root, Node* parent, float scalexx, float scaleyy, bool isOff)
{
    float offX = 0;
    float offY = 0;
    if(isOff)
    {
        offX = parent->getContentSize().width;
        offY = -parent->getContentSize().height;
    }
    Sprite* hand1 = Sprite::create("handClick_1.png");
    hand1->setName("handClick_1");
    Vec2 vec = parent->getParent()->convertToWorldSpace(parent->getPosition());
    hand1->setPosition(Vec2(vec.x + hand1->getContentSize().width*scalexx/2, vec.y - hand1->getContentSize().height*scaleyy/2 ));
    root->addChild(hand1);
    hand1->setTag(1003);
    Sprite* hand2 = Sprite::create("handClick_2.png");
    hand2->setName("handClick_1");
    hand2->setPosition(Vec2(vec.x + hand1->getContentSize().width*scalexx/2, vec.y - hand2->getContentSize().height*scaleyy/2));
    root->addChild(hand2);
    hand2->setTag(1004);
    hand2->setVisible(false);
    hand1->setScale(getWindowSmallScale());
    hand2->setScale(getWindowSmallScale());
    hand1->runAction(Sequence::create(Repeat::create(Sequence::create(DelayTime::create(0.5), CallFunc::create([=](){
        hand1->setVisible(false);
        hand2->setVisible(true);
    }), DelayTime::create(0.5), CallFunc::create([=](){
        hand1->setVisible(true);
        hand2->setVisible(false);
    }), NULL), 3), CallFunc::create([=]()mutable{
        hand1->removeFromParent();
        hand1 = NULL;
        hand2->removeFromParent();
        hand2 = NULL;
    }), NULL));
}

void GameOther::removeClickHandFunc(Node* parent)
{
    if(parent->getChildByTag(1003))
    {
        Node* hand1 = parent->getChildByTag(1003);
        Node* hand2 = parent->getChildByTag(1004);
        hand1->removeFromParent();
        hand1 = NULL;
        hand2->removeFromParent();
        hand2 = NULL;
    }
}

void GameOther::lightCircleFunc(Node* lightCircle)
{
    if(isLightCircleShow)
        return;
    isLightCircleShow = true;
    lightCircle->setVisible(true);
    lightCircle->setOpacity(0);
    lightCircle->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1), FadeOut::create(1), NULL)));
}

void GameOther::lightCircleRemoveFunc(Node* lightCircle)
{
    lightCircle->setVisible(false);
    isLightCircleShow = false;
}

Sprite* GameOther::cloneSprite(Sprite *sprite)
{
    Sprite* rtnSprite = Sprite::createWithTexture(sprite->getTexture());
    rtnSprite->setRotation(sprite->getRotation());
    rtnSprite->setFlippedX(sprite->isFlippedX());
    rtnSprite->setFlippedY(sprite->isFlippedY());
    rtnSprite->setAnchorPoint(sprite->getAnchorPoint());
    rtnSprite->setName(sprite->getName());
    if(sprite->getChildrenCount() > 0)
    {
        for(int i = 0; i < sprite->getChildrenCount(); i++)
        {
            Sprite* childSprite = Sprite::createWithTexture(((Sprite*)sprite->getChildren().at(i))->getTexture());
            if(sprite->getChildren().at(i)->isVisible())
            {
                childSprite->setTag(sprite->getChildren().at(i)->getTag());
                childSprite->setName(sprite->getChildren().at(i)->getName());
                childSprite->setPosition(sprite->getChildren().at(i)->getPosition());
                childSprite->setScale(sprite->getChildren().at(i)->getScale());
                rtnSprite->addChild(childSprite);
                
            }
        }
    }
    return rtnSprite;
}


void GameOther::setIconAnimation(Node* node, bool isLoop, float scaleFix)
{
    float min = 60;
    float scaleSmall = 0.9*scaleFix;
    float scaleNormal = 1*scaleFix;
    float scaleBig = 1.1*scaleFix;
    if(isLoop)
    {
        node->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(5/min, scaleSmall, scaleBig), ScaleTo::create(20/min, scaleNormal, scaleNormal), ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal), NULL)));
    }else
    {
        node->runAction(Sequence::create(ScaleTo::create(5/min, scaleSmall, scaleBig), ScaleTo::create(20/min, scaleNormal, scaleNormal), ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal), NULL));
    }
    
}
//shang xia fudu xiao
void GameOther::setIconAnimation2(Node* node, bool isLoop, float scaleFix)
{
    float min = 60;
    float scaleSmall = 0.92*scaleFix;
    float scaleNormal = 1*scaleFix;
    float scaleBig = 1.02*scaleFix;
    if(isLoop)
    {
        node->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(5/min, scaleSmall, scaleBig), ScaleTo::create(20/min, scaleNormal, scaleNormal), ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal), NULL)));
    }else
    {
        node->runAction(Sequence::create(ScaleTo::create(5/min, scaleSmall, scaleBig), ScaleTo::create(20/min, scaleNormal, scaleNormal), ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal), NULL));
    }
    
}
//pinlv man
void GameOther::setIconAnimation3(Node* node, bool isLoop, float scaleFix)
{
    float min = 60;
    float scaleSmall = 0.9*scaleFix;
    float scaleNormal = 1*scaleFix;
    float scaleBig = 1.15*scaleFix;
    if(isLoop)
    {
        node->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal),DelayTime::create(2), NULL)));
    }else
    {
        node->runAction(Sequence::create(ScaleTo::create(20/min, scaleBig, scaleSmall), ScaleTo::create(5/min, scaleNormal, scaleNormal),DelayTime::create(2), NULL));
    }
    
}
void GameOther::addBabyExp(int addValue)
{
    _babyExpAddValue += addValue;
    CCLOG("exp +1");
}

void GameOther::starEffect(Node* bg, float scale)
{
    auto repeat = RepeatForever::create(Sequence::create(Spawn::create(RotateBy::create(0.5, -30), ScaleTo::create(0.5, 0.3 *GameOther::getWindowSmallScale()* scale), NULL), Spawn::create(
                                                                                                                                                                                     RotateBy::create(0.5, 30), ScaleTo::create(0.5, 0.05*GameOther::getWindowSmallScale()), NULL), NULL));
    auto repeat1 = RepeatForever::create(Sequence::create(Spawn::create(RotateBy::create(0.5, 30), ScaleTo::create(0.5, 0.05*GameOther::getWindowSmallScale()* scale), NULL), Spawn::create(
                                                                                                                                                                                     RotateBy::create(0.5, -30), ScaleTo::create(0.5, 0.3*GameOther::getWindowSmallScale()* scale), NULL), NULL));
    for(int i = 0; i < 30; i++)
    {
        Sprite* sprite = Sprite::create("starEffect.png");
        bg->addChild(sprite);
        
        sprite->setScale(GameOther::getWindowSmallScale() * 0.3 * scale);
        float randX = random(0.0f, bg->getContentSize().width);
        float randY = random(0.0f, bg->getContentSize().height);
        sprite->setPosition(randX, randY);
        sprite->setRotation(random(0, 359));
        sprite->setOpacity(0);
        sprite->runAction(FadeIn::create(0.5));
        if(i <= 15)
        {
            sprite->runAction(repeat->clone());
        }else
        {
            sprite->runAction(repeat1->clone());
        }
        starVector.pushBack(sprite);
    }
    
    
}

void GameOther::clearEffect()
{
    for(int i = starVector.size() - 1;i >= 0; i--)
    {
        Sprite* sprite = starVector.at(i);
        sprite->stopAllActions();
        sprite->runAction(Sequence::create(FadeOut::create(0.5), CallFunc::create([=]()mutable{
            sprite->removeFromParent();
            sprite = NULL;
        }), NULL));
        starVector.eraseObject(sprite);
    }
}

int GameOther::getStrNumber(const string& bigStr, const string& shortStr)
{
    int length = (int)shortStr.length();
    int length1 = (int)bigStr.length();
    string ss = bigStr.substr(length, length1);
    int number = std::atoi(ss.c_str());
    return number;
}

Image* GameOther::createImageFromSprite(cocos2d::Sprite *pSpr)
{
    Sprite* pNewSpr = Sprite::createWithSpriteFrame(pSpr->displayFrame());
    pNewSpr->setAnchorPoint(Vec2(0, 0));
    RenderTexture* pRender = RenderTexture::create(pNewSpr->getContentSize().width, pNewSpr->getContentSize().height, kCCTexture2DPixelFormat_RGBA8888);
    pRender->begin();
    pNewSpr->visit();
    pRender->end();
    auto renderer = Director::getInstance()->getRenderer();
    renderer->render();
    return pRender->newImage();
}