//
//  GameData.cpp
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#include "GameData.h"

static GameData* instance = 0;
GameData* GameData::getInstance()
{
    if(!instance)
    {
        instance = new GameData();
    }
    return instance;
}

void GameData::refreshInstance()
{
    instance = NULL;
}

void GameData::initData()
{
    //    setHairIndex(9);
    //    setDressIndex(5);
    //    setHatIndex(0);
    //    setNecklaceIndex(0);
    //    setShoseIndex(0);
    //    setearringIndex(0);
}