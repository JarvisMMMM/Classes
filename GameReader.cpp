//
//  GameReader.cpp
//  BabyGame
//
//  Created by apple12 on 15/1/12.
//
//

#include "GameReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

Node* getNodeFile(const std::string filename);

Node* GameReader::getNodeFile(const std::string &filename)
{
    Node* node = CSLoader::createNode(filename);
    return node;
}


