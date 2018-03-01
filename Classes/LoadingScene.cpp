//
//  LoadingScene.cpp
//  HelloCpp
//
//  Created by Zeyang Li on 8/15/13.
//
//

//#include "DebugMisc.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "base.h"
//#include "Common.h"
//#include "PuzzleRPC.h"
//#include "ResourceSyncMan.h"
//#include "CCCallLambda.h"
//#include "support/tar_support/TarArchive.h"

//#include <boost/make_shared.hpp>
//#include <extensions/native/CCNative.h>

namespace PH
{

    class SFXConfirmLayer : public Layer
    {
    public:
        CREATE_FUNC(SFXConfirmLayer);
        virtual bool init();
        
        void yes(Ref* o);
		void no(Ref* o);
        void transitionToNextLayer();
    };
    
    class SlotMachineLayer : public Layer
    {
    public:
        CREATE_FUNC(SlotMachineLayer);
        virtual bool init();
    };
    

    //--------------------
    // SFXConfirmLayer
    //--------------------
    bool SFXConfirmLayer::init()
    {
        if(!Layer::init())
            return false;
        
        Menu* menu = Menu::create();
        this->addChild(menu);
        
        MenuItemImage* yesButton = MenuItemImage::create("jscmcc/g_yes.png",
                                                             "jscmcc/g_yes_hl.png",
                                                             this,
                                                             menu_selector(SFXConfirmLayer::yes));
        yesButton->setAnchorPoint(Point(0, 0));
        yesButton->setPosition(Point(-320, -480));
        menu->addChild(yesButton);
        
        MenuItemImage* noButton = MenuItemImage::create("jscmcc/g_no.png",
                                                            "jscmcc/g_no_hl.png",
                                                            this,
                                                            menu_selector(SFXConfirmLayer::no));
        noButton->setAnchorPoint(Point(1.0, 0));
        noButton->setPosition(Point(320, -480));
        menu->addChild(noButton);
        
        Sprite* logo = GetSprite("jscmcc/yidongyinxiao.png");
        logo->setPosition(Point(320, 600));
        this->addChild(logo);
        
        Sprite* text = GetSprite("jscmcc/g_sound_ask.png");
        text->setPosition(Point(320, 300));
        this->addChild(text);
        
        return true;
    }
        
    void SFXConfirmLayer::yes(CCObject* o)
    {
        //GameConfig::shared()->setSFXEnabled(true);
        //GameConfig::shared()->setBGMEnabled(true);
        transitionToNextLayer();
    }
        
    void SFXConfirmLayer::no(CCObject* o)
    {
        //GameConfig::shared()->setSFXEnabled(false);
        //GameConfig::shared()->setBGMEnabled(false);
        transitionToNextLayer();
    }
        
    void SFXConfirmLayer::transitionToNextLayer()
    {
        Node* parent = this->getParent();
        parent->addChild(SlotMachineLayer::create());
        this->removeFromParent();
    }
    
    //---------------------
    // SlotMachineLayer
    //---------------------
    bool SlotMachineLayer::init()
    {
        if(!Layer::init())
            return false;
        
        Sprite* slotBG = GetSprite("jscmcc/g_rocker.png");
        slotBG->setPosition(Point(320, 480));
        this->addChild(slotBG);
        
        Sprite* cover = GetSprite("jscmcc/g_logo_cmgc.png");
        cover->setPosition(Point(320, 480));
        cover->runAction(Sequence::create(DelayTime::create(1.0f),
                                          Hide::create(),
                                          NULL));
        this->addChild(cover);
        
        {
            Sprite* leftIcon = GetSprite("jscmcc/g_logo_ourpalm.png");
            leftIcon->setPosition(Point(80, 195));
            leftIcon->setVisible(false);
            slotBG->addChild(leftIcon);
            
            Sprite* left  = GetSprite("jscmcc/g_rotate_left.png");
            left->setPosition(Point(80, 195));
            left->runAction(Sequence::create(DelayTime::create(1.0),
                                             Show::create(),
                                             Blink::create(1.0, 10),
                                             Hide::create(),
											 ([=](){ leftIcon->setVisible(true); }),
											 NULL));
            left->setVisible(false);
            slotBG->addChild(left);
        }
        
        {
            Sprite* midIcon = GetSprite("jscmcc/g_logo_cmcc.png");
            midIcon->setPosition(Point(235, 195));
            midIcon->setVisible(false);
            slotBG->addChild(midIcon);
            
            Sprite* mid   = GetSprite("jscmcc/g_rotate_mid.png");
            mid->setPosition(Point(235, 195));
            mid->runAction(Sequence::create(DelayTime::create(1.3),
                                            Show::create(),
                                            Blink::create(1.0, 10),
                                            Hide::create(),
                                            ([=](){ midIcon->setVisible(true); }),
                                            NULL));
            mid->setVisible(false);
            slotBG->addChild(mid);
        }
        
        {
            Sprite* rightIcon = GetSprite("jscmcc/icon.png");
            rightIcon->setPosition(Point(390, 195));
            rightIcon->setVisible(false);
            slotBG->addChild(rightIcon);
            
            Sprite* right = GetSprite("jscmcc/g_rotate_right.png");
            right->setPosition(Point(390, 195));
            right->runAction(Sequence::create(DelayTime::create(1.6),
                                              Show::create(),
                                              Blink::create(1.0, 10),
                                              Hide::create(),
                                              ([=](){ rightIcon->setVisible(true); }),
                                              NULL));
            right->setVisible(false);
            slotBG->addChild(right);
        }
        
        this->runAction(
			Sequence::create(
				DelayTime::create(4.0),
				([]()
					{
						/*
						PH::runOnMainThread([=](){
						PH::runOnMainThread([=]()
						{
							CCDirector *director = CCDirector::sharedDirector();
							director->replaceScene(PH::LoadingScreen::create(
								GameConfig::shared()->isAndroidHDEnabled()));
							});
						});
						*/
					}),
				NULL));
        
        return true;
    }
    
    bool JSCSplashScene::init()
    {
        if(!Scene::init())
            return false;
        
        this->addChild(SFXConfirmLayer::create());
        
        return true;
    }
    
    //-------------------------
    // Normal Splash Screen
    //-------------------------
    bool SplashScene::init()
    {
        if(!Scene::init())
            return false;
        
        Sprite* splash = GetSprite("loading_bg.jpg");
        splash->setAnchorPoint(Point(0.0f, 0.0f));
        this->addChild(splash);

        Sprite* logo = GetSprite("loading_logo.png");
        logo->setPosition(Point(320, 200));
        this->addChild(logo);
        
        return true;
    }
    
    //-------------------------
    // LoadingScreen
    //-------------------------
    bool LoadingScreen::init(bool useHD = false)
    {
        if(!Scene::init())
            return false;
		isGemAction = false;
		
		logo = GetSprite("loading_logo.png");
		logo->setPosition(Point(320, 200));
		this->addChild(logo, 100);
		/*
        // launch network thread.
        //PuzzleRPC::getInstance()->launch();

        // create UI elements
        Sprite* background = GetSprite("loading_bg.jpg");
        background->setPosition(Point(320, 480));
        this->addChild(background);



        mProgressBar = GetSprite("loading_b_2.png");
        mProgressBar->setAnchorPoint(Point(0, 0.5));
        mProgressBar->setPosition(Point(103, 70));
        setProgress(0);
        this->addChild(mProgressBar);
        
        // this must be created after progress bar
        Sprite* barBG = GetSprite("loading_b_1.png");
        barBG->setAnchorPoint(Point(0, 0.5));
        barBG->setPosition(Point(97, 70));
        this->addChild(barBG);
        
        mText = LabelTTF::create("正在检查资源更新...", FONT_CN, 30);
        mText->setColor(Color3B(0x43, 0x00, 0x00));
        mText->setAnchorPoint(Point(0.5, 1));
        mText->setPosition(Point(320, 47));
        this->addChild(mText);
        */
		//launchSyncMan(useHD);
		this->performGemsAction();
        // manage resources
        //std::string sourceArchiveName = (useHD ? "iphonehd.Head.tar" : "iphone.Head.tar");
        //std::string mainArchiveName = (useHD ? "iphonehd." PH_VERSION ".tar" : "iphone." PH_VERSION ".tar");
        //std::string mainResourceArchivePath = CCNative::getDocPath() + mainArchiveName;

#if PH_USE_BUNDLE_RESOURCE
        // force removal of local resource tar
        CCNative::removeFile(mainResourceArchivePath);
#endif
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        // mark everything off icloud
        CCNative::addSkipBackupAttributeToItem(mainResourceArchivePath);
        CCNative::addSkipBackupAttributeToItem(mainResourceArchivePath + ".temp");
        CCNative::addSkipBackupAttributeToItem(mainResourceArchivePath + ".zsync");
        
        TarArchive* tarArchive = TarArchive::create(CCFileUtils::sharedFileUtils()->fullPathForFilename(sourceArchiveName.c_str()),
                                                    mainResourceArchivePath);
        CCFileUtils::sharedFileUtils()->setTarArchive(tarArchive);
        
        launchSyncMan(useHD);
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        // can not use the tar in apk. files in apk won't seek.
        barBG->setVisible(false);
        mProgressBar->setVisible(false);
        
        if (!CCFileUtils::sharedFileUtils()->isFileExist(mainResourceArchivePath))
        {
            mText->setString("正在优化资源，可能需要几秒时间....");
            runOnBackgroundThread([=]()
            {
                  LOGD("* copy asset %s -> %s\n", sourceArchiveName.c_str(), mainResourceArchivePath.c_str());
                  CCNative::copyAssetToPath(sourceArchiveName, mainResourceArchivePath);
                  runOnMainThread([=]()
                  {
                      if(!CCFileUtils::sharedFileUtils()->isFileExist(mainResourceArchivePath))
                      {
                          ResourceSyncMan syncMan(useHD);
                          syncMan.resetLastMod();

                          CCNative::createAlert("游戏资源出错",
                                                "请彻底关闭游戏重新进入，如果问题没有解决，请检查网络连接是否正常和是否有足够的空间，或者联系我们.",
                                                "确定");
                          CCNative::showAlert();
                          LOGD("Cannot load appriopriate resources. Hanging...\n");
                      }
                      else
                      {
                          barBG->setVisible(true);
                          mProgressBar->setVisible(true);
                          launchSyncMan(useHD);
                      }
                  });
            });
        }
        else
        {
            barBG->setVisible(true);
            mProgressBar->setVisible(true);
            launchSyncMan(useHD);
        }
#endif
        return true;
    }
    
    void LoadingScreen::launchSyncMan(bool useHD)
    {
		/*
        syncMan = make_shared<ResourceSyncMan>(useHD);
        syncMan->startSync([=](const ResourceSyncMan& man, const SyncProgress& s)
        {
            if (s.state < DATA_DOWNLOADING)
                setProgress(0.1 * s.state);
            else if (s.state == DATA_DOWNLOADING)
            {
                setProgress(0.2 + 0.6*((float)s.downloadedBytes/(float)s.totalBytes));
                char stringBuf[256] = {0};
                sprintf(stringBuf, "更新下载中: %s/%s...",
                        bytesToReadableString(s.downloadedBytes).c_str(), 
                        bytesToReadableString(s.totalBytes).c_str());
                
                mText->setString(stringBuf);
                this->performGemsAction();
            }
            else if (s.state == DECOMPRESS)
            {
                setProgress(0.9);
                LOGD("decompressing resource tar\n");
                mText->setString("解压资源中....");
                this->performGemsAction();
            }
            else if (s.state == DONE)
            {
                setProgress(1);
                LOGD("resource update done\n");
                mText->setString("更新完成....");
                
                std::string mainArchiveName = (useHD ? "iphonehd." PH_VERSION ".tar" : "iphone." PH_VERSION ".tar");
                std::string mainResourceArchivePath = CCNative::getDocPath() + mainArchiveName;
                // add tar as resource archive.
                
                if (CCFileUtils::sharedFileUtils()->isFileExist(mainResourceArchivePath))
                {
                    TarArchive* tarArchive = TarArchive::create(mainResourceArchivePath);
                    TarArchive* oldArchive = CCFileUtils::sharedFileUtils()->setTarArchive(tarArchive);
                    delete oldArchive;
                }

                // Explicit
                GameScene::initInstance();
                GameScene::getInstance()->sync();
                
                runOnMainThread([](){
                    runOnMainThread([]()
                                    {
                                        CCDirector::sharedDirector()->replaceScene(PH::GameScene::getInstance());
                                    });
                });
            }
            else if (s.state == NOUPDATE)
            {
                setProgress(1);
                LOGD("resources already update to date\n");
                mText->setString("已是最新版本....");
                
                std::string mainArchiveName = (useHD ? "iphonehd." PH_VERSION ".tar" : "iphone." PH_VERSION ".tar");
                std::string mainResourceArchivePath = CCNative::getDocPath() + mainArchiveName;
                // add tar as resource archive.
                TarArchive* tarArchive = TarArchive::create(mainResourceArchivePath);
                if(tarArchive)
                {
                    TarArchive* old = CCFileUtils::sharedFileUtils()->setTarArchive(tarArchive);
                    delete old;
                }
                
                // Explicit
                GameScene::initInstance();
                GameScene::getInstance()->sync();
                
                runOnMainThread([](){
                    runOnMainThread([]()
                                    {
                                        CCDirector::sharedDirector()->replaceScene(PH::GameScene::getInstance());
                                    });
                });
            }
            else
            {
                LOGD("network error in syncman\n");
                mText->setString("更新错误，3秒后重试。请检查你的网络设置....");
                
                // rerun launchSyncMan
                auto* seq = CCSequence::create(CCDelayTime::create(3.0f),
                                               CCCallLambda::create([=]()
                                                                    {
                                                                        mText->setString("重试更新....");
                                                                        this->launchSyncMan(useHD);
                                                                    }),
                                               NULL);
                this->runAction(seq);
            }
            
            PuzzleRPC::getInstance()->setNetworkTimeOut(10);
        });
		*/
    }
    
    std::string LoadingScreen::bytesToReadableString(int bytes)
    {
        char stringBuf[256] = {};
        const char* postfixes[] = {"Bytes", "KB", "MB", "GB"};
        int pfixCount = sizeof(postfixes) / sizeof(postfixes[0]);
        int pfix = 0;
        float fbytes = bytes;
        
        while (fbytes > 1100.f && pfix < pfixCount-1) {
            fbytes /= 1024.f;
            pfix++;
        }
        
        sprintf(stringBuf, "%.2f%s", fbytes, postfixes[pfix]);
        return stringBuf;
    }
    
    void LoadingScreen::setProgress(float progress)
    {
        float val = clampx(progress, 0.0f, 1.0f);
        mProgressBar->setScaleX(val);
    }
    
    void LoadingScreen::setString(const std::string& str)
    {
        mText->setString(str.c_str());
    }
    
    void LoadingScreen::performGemsAction()
    {
        if(!isGemAction)
        {
            Point desPos[5] = {Point(80, 260), Point(110, 540), Point(280, 800), Point(520, 530), Point(525, 180)};
            Layer* gems[5] = {
				createGem("gem_fire.png", "guangquan_hong.png", 0.86),
                createGem("gem_light.png", "guangquan_huang.png", 0.76),
                createGem("gem_water.png", "guangquan_lan.png", 0.8),
                createGem("gem_wood.png", "guangquan_lv.png", 0.9),
                createGem("gem_dark.png", "guangquan_zi.png", 0.8)};
            for(int i = 0; i < 5; i++)
            {
                gems[i]->setPosition(logo->getPosition());
                this->addChild(gems[i]);
                gems[i]->runAction(
					Sequence::create(DelayTime::create(0.15 * i),
						createGemOutAction(logo->getPosition(), desPos[i]),
						NULL));
                Sprite* light = (Sprite*)gems[i]->getChildByTag(1001);
                if(light && true) {
                    float orgScale = light->getScale();
					log("---->%f", orgScale);
                    light->runAction(
						Sequence::create(
							DelayTime::create(0.15 * i + 0.8),
							Repeat::create(
								Sequence::create(
									DelayTime::create(1.0),
									([=](){
										light->setOpacity(255);
										//light->setScale(orgScale);
									}),
									Spawn::create(
										ScaleTo::create(0.6, 1.3),
										FadeOut::create(0.6),
										NULL),
									NULL), 
								100000),
							NULL));
				}
			}
            isGemAction = true;
        }
        
    }
    
    Layer* LoadingScreen::createGem(const char* path, const char* lightPath, float scale)
    {
        Layer* layer = Layer::create();
        Sprite* gem = GetSprite(path);
        gem->setScale(scale);
        layer->addChild(gem, 10);
        
        Sprite* light = GetSprite(lightPath);
        light->setOpacity(0);
        light->setTag(1001);
        light->setScale(scale);
        layer->addChild(light);
		if (NULL == layer)
			log("=====createGem is null======");
        return layer;
    }
    
    Action* LoadingScreen::createGemOutAction(Point org, Point target)
    {
        double angle = atan2(target.y - org.y, target.x - org.x);
        Point middle = Point(50*cos(angle), 50*sin(angle));
        return Sequence::create(MoveTo::create(0.5, target+middle),
                                MoveTo::create(0.2, target),
                                Repeat::create(
									Sequence::create(
										MoveTo::create(0.8, Point(target.x, target.y+15)),
										MoveTo::create(0.8, Point(target.x, target.y-15)),
										NULL),
									100000),
                                  NULL);
    }
}
