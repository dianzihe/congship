//
//  LoadingScene.h
//  HelloCpp
//
//  Created by Zeyang Li on 8/15/13.
//
//

#pragma once

#include <cocos2d.h>
//#include <boost/shared_ptr.hpp>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define FONT_PREFIX "ttf/"
#define FONT_POSTFIX ".ttf"
#else //if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define FONT_PREFIX ""
#define FONT_POSTFIX ""
#endif

#define FONT_CN FONT_PREFIX "FZPangWa-M18S" FONT_POSTFIX
#define FONT_NUM FONT_PREFIX "DFPSumo-W12" FONT_POSTFIX


namespace PH
{
    USING_NS_CC;
	template<typename T>
	T clampx(T val, T min, T max)
	{
		return std::min(std::max(val, min), max);
	}
    class SplashScene : public Scene
    {
    public:
        CREATE_FUNC(SplashScene);
        virtual bool init();
    };
    
    class JSCSplashScene : public Scene
    {
    public:
        CREATE_FUNC(JSCSplashScene);
        virtual bool init();
    };
    
    //---------------------
    // LoadingScreen
    //class ResourceSyncMan;
    
    class LoadingScreen : public Scene
    {
    private:
        Sprite* mProgressBar;
        LabelTTF* mText;
        
    public:
        bool init(bool highResResource);
        
		static LoadingScreen* create(bool highResResource = false)
        {
            LoadingScreen* o = new LoadingScreen();
            if(o && o->init(highResResource)) {
                o->autorelease();
                return o;
            }
            assert(false && "loading screen cannot be created");
            CC_SAFE_DELETE(o);
            return NULL;
        }
        
        static std::string bytesToReadableString(int bytes);
        
        void setProgress(float progress);
        void setString(const std::string& str);
        void launchSyncMan(bool useHD = false);
        
    private:
        bool isGemAction;
        Sprite* logo;
        //shared_ptr<ResourceSyncMan> syncMan;
        
        void performGemsAction();
        Layer* createGem(const char* gemPath, const char* lightPath, float scale);
        Action* createGemOutAction(Point org, Point target);
    };
}