//
//  ADManager.h
//  dentistsalon
//
//  Created by apple13 on 14/11/26.
//
//

#ifndef __dentistsalon__ADManager__
#define __dentistsalon__ADManager__

class ADManager
{
public:
    static float ADMenuOffY;
    static void showBanner();
    static void hideBanner();
    static void showCBInterstial();
    static void showAmobInterstial();
    
    static void showAlert();
    
    static void bannerCallBack();
    static void onEvaluation();
};

#endif /* defined(__dentistsalon__androidJNI__) */
