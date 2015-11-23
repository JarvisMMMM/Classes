//
//  GameReader.h
//  BabyGame
//
//  Created by apple12 on 15/1/12.
//
//

#ifndef __BabyGame__GameReader__
#define __BabyGame__GameReader__

#include "cocos2d.h"
USING_NS_CC;

class GameReader
{
public:
    static Node* getNodeFile(const std::string &filename);
};

#endif /* defined(__BabyGame__GameReader__) */
