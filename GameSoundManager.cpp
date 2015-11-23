//
//  GameSoundManager.cpp
//  dentist
//
//  Created by apple13 on 14/10/23.
//
//

#include "GameSoundManager.h"
#include "SimpleAudioEngine.h"
static GameSoundManager* instance = 0;
GameSoundManager* GameSoundManager::getInstance()
{
    if(!instance)
        instance = new GameSoundManager();
    return instance;
}

void GameSoundManager::pauseSound()
{
    this->setIsPauseSound(true);
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameSoundManager::resumeSound()
{
    this->setIsPauseSound(false);
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void GameSoundManager::playEffect(const char* pszFilePath)
{
    if(this->getIsPauseSound())
        return;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath);
}

void GameSoundManager::stopAllEffect()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void GameSoundManager::playBgSound(const char* bgsound_url)
{
    if(this->getIsPauseSound())
        return;
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgsound_url, true);
}

void GameSoundManager::playLoopEffect(const char* pszFilePath)
{
    if(this->getIsPauseSound())
        return;
    if(_nSoundId != 0)
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_nSoundId);
    _nSoundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pszFilePath, true);
}

void GameSoundManager::stopLoopEffect(const char* pszFilePath)
{
    if(_nSoundId != 0)
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_nSoundId);
}

void GameSoundManager::DidEnterBackground()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}
void GameSoundManager::WillEnterForeground()
{
    if(!this->getIsPauseSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}