//
//  GameData.h
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#ifndef __makeup__GameData__
#define __makeup__GameData__

#include "cocos2d.h"
USING_NS_CC;


//资源名      mianmo node的名字 对应的png   涂抹对应的png

#define     MIANMO_NODE_NAME                "mianmo_kongbai"
#define     MIANMO_PNG                      "mianmo_kongbai_mask.png"
#define     MIANMO_TUMO_PNG                 "mask1_mask.png"

#define     MIANMO_TUMO_PNG_1                 "mask2_mask.png"

#define     MIANMO_TUMO_PNG_2                 "mask3_mask.png"

#define     HEIYANQUAN_NODE_NAME             "pouch_mask"

#define     YANXIAN_NODE_NAME                "eyeliner_kongbai"
#define     YANXIAN_PNG                      "eyeliner_kongbai.png"

#define     YANMEI_NODE_NAME                "brow_makeup"
#define     YANMEI_PNG                      "brow_makeup.png"

#define     YANJIEMAO_NODE_NAME                "brow_kongbai"
#define     YANJIEMAO_PNG                      "brow_kongbai.png"

#define     YANYING_NODE_NAME                "eye_shadow_kongbai"
#define     YANYING_PNG                      "eye_shadow_kongbai.png"

#define     ZHENGLIAN_NODE_NAME              "shuimo_mask"

#define     BLUSH_NODE_NAME                "blush_kongbai"
#define     BLUSH_PNG                      "blush_kongbai.png"

#define     CHUNCAI_NODE_NAME                "mouth_makeup"
#define     CHUNCAI_PNG                      "mouth_makeup.png"

#define     MAKEUP_PARENT                   "face_kongbai_makeup"     //make里化妆node的父
#define     DRESSUP_PARENT                  "girl_kongbai_dressup"

#define     ITEMS_JIEMAO                            "browbrushtong"
#define     ITEMS_JIEMAOSHUA                            "browbrush"

//桌子上的物品name
#define     ITEMS_MIANMO_NOCLICK_PINGZI           "bottle1_mask"
#define     ITEMS_QUDOUYE_NOCLICK_PINGZI           "qiedougao3_mask"
#define     ITEMS_MIANMO                          "spone1_mask"
#define     ITEMS_PENTOU                          "shower1_mask"
#define     ITEMS_PENTOU_2                        "_shower1_mask.png"

#define     ITEMS_MIANMO_NOCLICK_PINGZI_1           "bottle2_mask"
#define     ITEMS_MIANMO_1                          "brush2_mask"

#define     ITEMS_MIANMO_NOCLICK_PINGZI_2           "bottle5_mask"
#define     ITEMS_MIANMO_2                          "baoshishui4_mask"
 
#define     ITEMS_LEMON_1                           "lemon1_mask"
#define     ITEMS_LEMON_2                           "lemon2_mask"
#define     ITEMS_LEMMON_1_PNG                        "lemon1_mask.png"
#define     ITEMS_LEMMON_2_PNG                       "lemon2_mask.png"

#define     ITEMS_ACNE                              "acne_needle3_mask"

#define     ITEMS_MIAMNBANG                         "mianqian3_mask"

#define     ITEMS_ZHENGLIANQI                       "steamer3_mask"

#define     ITEMS_NIEZI_1                             "browclipper3_mask"
#define     ITEMS_NIEZI_2                             "browclipper_3_mask"

#define     ITEMS_YANMO_1                           "yanmo1_mask"
#define     ITEMS_YANMO_2                           "yanmo2_mask"

#define     ITEMS_YANMO_1_PNG                       "yanmo1_mask.png"
#define     ITEMS_YANMO_2_PNG                       "yanmo2_mask.png"

#define     ITEMS_FENPU_NOCLICK_PINGZI              "puffbox5_mask"
#define     ITEMS_FENDI_NOCLICK_PINGZI              "bottle5_mask"

#define     ITEMS_FENPU                             "puff5_mask"
#define     QUEBAN_NODE_NAME                        "freckles_mask"
#define     ITEMS_FENDI                             "brush5_mask"

#define     ITEMS_MEITONG                           "eye_box"
#define     ITEMS_YANXIAN_TONG                      "eyeliner_bottle"
#define     ITEMS_YANXIAN                           "eyeliner_pencil"

#define     ITEMS_YANMEI                            "eyebrow_pencil"

#define     ITEMS_YANYING                           "eye_shadow_brush"

#define     ITEMS_BLUSH                             "blush_brush"

#define     ITEMS_CHUNCAI                            "lipstick"
#define     ITEMS_CHUNCAISHUA                        "lipstickshua"

#define     ITEMS_HAIR                               "comb_makeup"

#define     ITEMS_EARRING                             "earring_box_makeup"

#define     ITEMS_NECKLACE                             "necklace_box_makeup"

#define     ITEMS_BLUSH_BOX                         "blush_box"
#define     ITEMS_EYE_SHADOW_BOX                    "eye_shadow_box"


#define     DRESS_PARENT_NAME                       "girl_kb_dressup"

enum DRESSTYPE
{
    INIT = 0,
    HAIR,
    EARRING,
    NECKLACE,
    DRESS,
    WAITAO,
    XIAYI,
    HEADWEAR,
    SHOES,
    EYE,
    SHOUCHI,
    SHOUTAO,
    TOUSHA,
    
    LIPSTICK,
    EYESHADOW,
    BLUSH,
    BROWBRUSH,
    YANJING,
    
    JIAOSHI_ZHUANGSHI,
    JIAOSHU_JIANGZHUO,
    JIAOSHI_ZHUOYI,
    JIAOSHI_CHUANGHU,
    JIAOSHI_QIANGZHI,
    
    JIAJU_BED,
    JIAJU_CARPET,
    JIAJU_CURTAIN,
    JIAJU_DRESSER,
    JIAJU_WARDROBE,
};


enum listType
{
    meitongType,
    yanxianType,
    hairType,
    earringType,
    necklaceType,
    
    
};


class GameData
{
public:
    void initData();
    GameData()
    : _hadIndex(5),
    _weijinIndex(0),
    _gloveIndex(0),
    _dressIndex(5),
    _shoseIndex(0)
    , _makeupRender(NULL)
    ,_appname("Halloween Salon"),
    _apppicname("halloweenSalon"),
    _appurl("https://itunes.apple.com/us/app/halloween-spa-salon/id1042883049?l=zh&ls=1&mt=8"),
    _bannerid("ca-app-pub-2467223217527321/8385869495"),
    _amobid("ca-app-pub-2467223217527321/9862602692"),
    _UACode("UA-65270608-12"),
    _cbid("55f2b42604b01655f1529e01"),
    _cbsig("9683aea89441756a7536374511af2511039bbbab"),
    _mobilecoreid("1DZ2WAOACSMORYXEWYZHFX8R6E7NA")
    {};
    static GameData* getInstance();
    static void refreshInstance();
    CC_SYNTHESIZE(int, _dressIndex, DressIndex);
    CC_SYNTHESIZE(int, _hadIndex, HadIndex);
    CC_SYNTHESIZE(int, _weijinIndex, WeijinIndex);
    CC_SYNTHESIZE(int, _gloveIndex, GloveIndex);
    CC_SYNTHESIZE(int, _shoseIndex, ShoseIndex);
    CC_SYNTHESIZE(RenderTexture* , _makeupRender, MakeUpRender);
    
    CC_SYNTHESIZE(std::string, _appname, appname);
    CC_SYNTHESIZE(std::string, _apppicname, apppicname);
    CC_SYNTHESIZE(std::string, _appurl, appurl);
    CC_SYNTHESIZE(std::string, _bannerid, bannerid);
    CC_SYNTHESIZE(std::string, _amobid, amobid);
    CC_SYNTHESIZE(std::string, _cbid, cbid);
    CC_SYNTHESIZE(std::string, _cbsig, cbsig);
    CC_SYNTHESIZE(std::string, _mobilecoreid, mobilecoreid);
    CC_SYNTHESIZE(std::string, _UACode, UACode);
};

#endif /* defined(__makeup__GameData__) */
