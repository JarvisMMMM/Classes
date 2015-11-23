//
//  GameSoundManager.h
//  dentist
//  音效管理器
//  Created by apple13 on 14/10/23.
//
//

#ifndef __dentist__GameSoundManager__
#define __dentist__GameSoundManager__

struct LOOP_EFFECT
{
    const char* _url;
    unsigned int _nSoundId;
};
#include "cocos2d.h"
USING_NS_CC;
#include <vector>

#define         PENSHUI_MP3             "shower.mp3"
#define         PAPERDIAPEREFFECT       "buttonclothes.mp3"
#define         BUTTONUPSOUND           "buttonup.mp3"
#define         BUTTONDOWNSOUND          "buttondown.mp3"
#define         TAKEPHOTOS              "takephotos.mp3"
#define         PLAY                    "buttonup.mp3"

#define         NULL_MP3                                    ""
#define         MIANMO_MP3                                  "mianmo.mp3"
#define         FENPU                                       "fenpu.wav"
#define         TIEDONGXI                                   "tiedongxi.mp3"
#define         XUANZUAN                                    "liftbutton.mp3"
#define         JUMP_MP3                                    "jump.mp3"
#define         JIANZI_MP3                                  "jianzi.mp3"
#define         YANMEIJIA                                   "yanmeijia.mp3"
#define         QIPAO_MP3                                   "start.wav"

#define         QUBAN_MP3                                   "qubanyi.mp3"
#define         XIANGZAO_MP3                                "xiangzao.mp3"
#define         CUO_MP3                                     "cuo.mp3"

#define         START_BG                                    "start.mp3"
#define         MAKEUP_BG                                   "game.mp3"
#define         SHOW_BG                                     "show.mp3"

class GameSoundManager
{
private:
    std::vector<LOOP_EFFECT > loopList;
    unsigned int _nSoundId;
public:
    GameSoundManager()
    : _is_pause_sound(false)
    , _nSoundId(0)
    {};
    
    static GameSoundManager* getInstance();
    
    void pauseSound();
    
    void resumeSound();
    
    void playEffect(const char* pszFilePath);
    void playBgSound(const char* bgsound_url);
    
    void stopAllEffect();
    
    void playLoopEffect(const char* pszFilePath);
    void stopLoopEffect(const char* pszFilePath);
    
    void DidEnterBackground();
    void WillEnterForeground();
    
    CC_SYNTHESIZE(bool, _is_pause_sound, IsPauseSound);
    
};

#endif /* defined(__dentist__GameSoundManager__) */
