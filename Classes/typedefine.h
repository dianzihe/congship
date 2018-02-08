

/**
*   完成一些经常使用的宏定义
*
*/


#ifndef  __wyd_typedefine_include__
#define __wyd_typedefine_include__ 

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "common.h"

using namespace cocos2d;
using namespace CocosDenshion;

//#include "Box2D.h"
using namespace std;

///////////////////////////////////////////
#define USE_UNKOWN_SDK 0
#define USE_WYD_SDK 1001
#define USE_91SDK 1025
#define USE_JY_SDK 1007
#define USE_UC_SDK 1003
#define USE_DJ_SDK 1002
#define USE_IFREE_KT_SDK 1036
#define USE_EF_SDK 1035
#define USE_IFREE_SK_SDK 1038
#define USE_IFREE_GOOGLE_PAY_SDK 1037
#define USE_IFREE_IOS_SDK  1054
#define USE_EGAME_SDK 1016
#define USE_MOBILE_SDK 1017
#define USE_360_SDK 1018
#define USE_91IOS_SDK	1004
#define USE_EFUN_IOS_SDK 1055
#define USE_WYD_GOOGLE_PAY_SDK 1056
#define USE_Mi_SDK     1049
#define USE_MP_SDK      1034
#define USE_KY_SDK      1051
#define USE_FACEBOOK_SDK 1057
#define USE_WYD_IOS_SDK		1053
#define USE_TB_IOS_SDK   1050
#define USE_DDD_IOS_CN 1058
#define USE_DDD_IOS_EN  1059
#define USE_OL_IOS_CN 1060
#define USE_OL_IOS_EN 1061
#define USE_BD_SDK     1064
#define USE_PP_IOS_SDK 1065
#define USE_UNISHOP_SDK 1067
#define USE_IAPPPAY_SDK 1070
#define USE_WANDOUJIA_SDK 1033
#define USE_ANZHI_SDK 1080
#define USE_GFAN_SDK 1005
#define USE_SKYCHEE_SDK 1085
#define USE_LX_SDK 1083

#define USE_OL_IOS_EN 1061
#define USE_UNICOM_SDK 3003
//默认使用友盟
#define USE_UMENG 1


//////////////////////////////////////////////////////////////////////////
//#undef USE_Download
//
//#define USE_Download 0
//////////////////////////////////////////////////////////////////////////

//强化宏定义
#define OPEN_STRONGLEN 0
//四期功能宏定义
#define OPEN_FOURTH 0
//五期功能宏定义
#define OPEN_FIFTH 0
//六期功能宏定义
#define OPEN_SIXTH 0
//八期功能宏定义
#define OPEN_EIGHTH 0
//九期功能宏定义
#define OPEN_NINTH 0

//副本4宏定义
#define OPEN_BOSS4 0

#define OPEN_NEWTEACH 0
#define OPEN_DEBUGSPEED 0

#define NOT_USE_STENCIL_SPRITE 1



#define GET_THIS_SCENE_SCALE() \
CCDirector::sharedDirector()->getRunningScene()->getScale()

#define GET_RIGHT_TXT_SIZE(x) \
((x)*(CC_CONTENT_SCALE_FACTOR()==2?1:2))

//#define SET_FIT_THE_SCREAN(pNode) \
//do{ \
//    if(!CCDirector::sharedDirector()->isRetinaDisplay()) \
//    {\
//        pNode->setAnchorPoint(ccp(0,0)); \
//        pNode->setScale(0.5); \
//    } \
//}while(0);

#define DEFAULT_SCR_WIDTH 960.0f
#define DEFAULT_SCR_HEIGHT 640.0f


#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)

#define SET_FIT_THE_SCREAN(pNode) \
do{ \
pNode->setAnchorPoint(ccp(0,0)); \
CCSize size=CCDirector::sharedDirector()->getWinSizeInPixels(); \
float scaleWidth=size.width/DEFAULT_SCR_WIDTH; \
float scale=size.height/DEFAULT_SCR_HEIGHT;\
if(scaleWidth<scale)\
{\
    scale=scaleWidth;\
}\
pNode->setScale(scale); \
pNode->setPositionInPixels(CCPointMake((size.width-DEFAULT_SCR_WIDTH*scale)/2, (size.height-DEFAULT_SCR_HEIGHT*scale)/2)); \
}while(0);

#define GET_EDGE_CUT() (((CCDirector::sharedDirector()->getWinSizeInPixels().height-DEFAULT_SCR_HEIGHT*GET_THIS_SCENE_SCALE())/2)/GET_THIS_SCENE_SCALE())

#define GET_X_EDGE_CUT() (((CCDirector::sharedDirector()->getWinSizeInPixels().width-DEFAULT_SCR_WIDTH*GET_THIS_SCENE_SCALE())/2)/GET_THIS_SCENE_SCALE())

#else ////////////////////////////////////////////////////////////////////

#define SET_FIT_THE_SCREAN(pNode) \
do{ \
pNode->setAnchorPoint(ccp(0,0)); \
CCSize size=CCDirector::sharedDirector()->getWinSizeInPixels(); \
float scaleWidth=size.width/DEFAULT_SCR_WIDTH; \
float scaleHeight=size.height/DEFAULT_SCR_HEIGHT;\
pNode->setScaleX(scaleWidth);\
pNode->setScaleY(scaleHeight);\
}while(0);

#define GET_EDGE_CUT() 0

#define GET_X_EDGE_CUT() 0

#endif

#define WBNODE(class_name)  \
static class_name* node()                   \
{                                           \
    class_name *pRet = new class_name();    \
    if (pRet->init())                               \
    {                                       \
        pRet->autorelease();                \
        return pRet;                        \
    }                                       \
    else                                    \
    {                                       \
        delete pRet;                        \
        pRet = NULL;                        \
    }     \
    return NULL;                            \
} 


#define WDDD_FONT "Helvetica"


/**
 * @brief 错误处理回调函数
 * @param data   发送通告时传过来的数据 @see WNotifyManager::SendNotifyToShow
 * @param msg   点击的了什么类型的按钮 @see WNotifyManager::E_MSG_SHOW_DONE
 * @param param1 留着以后使用
 * @param param2 
 */
typedef void (*pWErrCallBack)(void *data,int msg,int param1,int param2);

/**
 * @brief 处理回调函数
 * @param data   用户数据 
 * @param msg   消息类型
 * @param param1 留着以后使用
 * @param param2 
 */
typedef void (*pWMsgCallback)(void *data,int msg,int param1,int param2);


typedef struct
{
    string notify;
    int notify_show_type;
    pWErrCallBack callback_func;
    void *data;
    
}NOTIFY_MSG;

typedef void (*pWCallBack_Func)(void *data);//回调函数定义


class strtempString:public CCObject
{
    
    
public:
    
    char *m_pstr;
    
    strtempString(const char *str)
    {
        int len = strlen(str);
        m_pstr = new char[len+1];
        memset(m_pstr, 0, len+1);
        memcpy(m_pstr, str, len);
        autorelease();
    }
    
    ~strtempString()
    {
        CC_SAFE_DELETE_ARRAY(m_pstr);
    }
    
    
};



#endif
