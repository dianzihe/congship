#ifndef _SHIP_BASE_H__
#define _SHIP_BASE_H__

#include "cocos2d.h"

using namespace cocos2d;
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <deque>
//#include "FontCharacter.h"
*/
/*
#if defined _MSC_VER
#include <Windows.h>
#include <tchar.h>
#endif


#ifndef WIN32
#define UPDATE_START
#endif

using namespace std;

#include "Log.h"
*/
// cocos2d-x include
//#include "cocos2d.h"
//USING_NS_CC;

/*
#define CHECK_MEM	1

#define Readint(buf,data)	data =*((int*)(buf)); buf += 4;

#if CHECK_MEM	

#ifdef _DEBUG
#define new   DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK  new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#endif

*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)          { if (p) { delete(p); (p) = 0;} }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)    { if (p) { delete[] (p); (p) = 0; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)         { if (p) { (p)->release(); (p) = 0; } }
#endif


struct ObjectBuff
{
	int buff_id;
	short allValidTime;
	unsigned char remainTriggerCount;
};
void WriteObjectBuff(char*& buf, ObjectBuff& value);
void ReadObjectBuff(char*& buf, ObjectBuff& value);

#define READ_BEGIN( file ) while(1) { ssize_t _len; int _pos=0;\
	char* _buf = (char*)FileUtils::getInstance()->getFileData(FileUtils::getInstance()->fullPathForFilename(filePath), "rb", &_len);

#define READ_END() if ( _buf ) delete[] _buf; break;}

#define READ_INT( data ) data = *((int*)&_buf[_pos]); _pos+=4;
#define READ_INT16( data ) data = *((short*)&_buf[_pos]); _pos+=2;
#define Readint(buf,data)	data =*((int*)(buf)); buf += 4;
#define Readint64(buf,data) memcpy(&data,buf,8); buf += 8;
#define Readint16(buf,data) data =*((short*)(buf)); buf += 2;
#define Readint8(buf,data)	data =*((signed char*)(buf)); buf += 1;

#define ReadArray(buf,t,data) {int len; Readint16(buf,len); data.resize(len); for(int i=0;i<len;i++){Read##t(buf,data[i]);}  }

#define Writeint64(buf,data) memcpy(buf,&data,8); buf += 8;
#define Writeint(buf,data)	memcpy(buf,&data,4); buf += 4;
#define Writeint16(buf,data) memcpy(buf,&data,2); buf += 2;
#define Writeint8(buf,data)	memcpy(buf,&data,1); buf += 1;
#define Writestring(buf,data) { int len = data.length(); Writeint16(buf,len); memcpy(buf,data.c_str(),len); buf += len;}
#define WriteArray(buf,t, data) { int len=data.size(); Writeint16(buf,len); for(int i=0;i<len;i++){ Write##t(buf,data[i]); }  }


#define READ_STRING( data ) while(1){\
	int _size;\
	char _data[1024];\
	READ_INT(_size);\
	memcpy(_data, &_buf[_pos], _size);\
	_data[_size] = '\0';\
	data = _data;\
	_pos+=_size;\
	break;\
	}

#define FLOAT_PI	(3.14159265358979323846)//(3.1415926535f)
#define GET_SIN(x)	(sinf(2*FLOAT_PI*x/360))

#define GET_SPEED_SUB(v1, v2, speed) (speed * fabsf(v1) / sqrtf(v1*v1 + v2*v2))

void SET_DIR_BY_TWOPOINT(const Point &p1, const Point &p2, int& dir);
int DQ_SET_DIR_BY_TWOPOINT(const Point &pos1, const Point &pos2);
/*
#define GET_SPEED_SUB(v1, v2, speed) (speed * fabsf(v1) / sqrtf(v1*v1 + v2*v2))

#define MOVE_V1_TO_V2(v1, v2, speed)\
	if(v1 > v2) {\
	v1 -= speed;\
			}\
				else {\
	v1 += speed;\
				}\
	if(fabsf(v1 - v2) <= speed)\
	v1 = v2;

inline float CHECK_SET_POS(float v, float minV, float maxV)
{
	float v1;
	v1 = v;
	if (v1 < minV)
		v1 = minV;
	else if (v1 >= maxV)
		v1 = maxV - 1;
	return v1;
}

*/
//typedef long	ActorID;

/*
#define DEBUG_LOG( format, ... )	Log::GetInstance().debug_out( format, ##__VA_ARGS__ );
#define INFO_LOG( format, ... )		Log::GetInstance().info_out( format, ##__VA_ARGS__ );
#define ERROR_LOG( format, ... )	Log::GetInstance().error_out( format, ##__VA_ARGS__ );

#ifdef PLATFORM_553_FOR_ZNM //// 20130807, add for "zhao ni mei"
#define FID_553  "206225"
#elif  PLATFORM_553_FOR_DIYIAPP //// 20130813, add for "di yi app"
#define FID_553  "206229"
#else
#define FID_553  "206001"
#endif


#define FID_PP   "206002"
#define FID_APPSTORE "206003"
#define FID_91_IOS "206006"


#define FID_DL_ANDROID "206008"
#define FID_4399_ANDROID "206009"
#define FID_UC_ANDROID "206004 "
#define FID_360_ANDROID "206005"
#define FID_91_ANDROID "206007"

#define SOURCEID_553      1
#define SOURCEID_PP       2
#define SOURCEID_91       3
#define SOURCEID_UC       4



// 返回一段内存数据的crc值，32位的
extern unsigned long MakeCRC32( const void* pBuffer, unsigned long nBufferSize, unsigned long crc = 0 );

enum 
{
	Operation_Platform_Test     = 100,	//	测试平台
	Operation_Platform_553      = 101,	//	553平台
	Operation_Platform_PP       = 102,	//	PP平台
    Operation_Platform_APPSTORE	= 103,	//	appstore
    Operation_Platform_91       = 104,	//	91 ios
    Operation_Platform_UC       = 105,
	Operation_Platform_360		= 111,	//	360
    Operation_Platform_337TW    = 112,  //  台湾凡仙传
	Operation_Platform_TWYH     = 138,  //tai'wan yao hu
    Operation_Platform_DL = 174, // DangLe ios

	Operation_Platform_553_ANDROID		= 108,	//	553 android
	Operation_Platform_UC_ANDROID		= 110,	//	uc android
	Operation_Platform_91_ANDROID		= 109,	//	91 android
	Operation_Platform_QQ_ANDROID		= 112,	//	qq android
	Operation_Platform_DL_ANDROID		= 113,	//	dl android
	Operation_Platform_4399_ANDROID		= 115,	//	dl android
	Operation_Platform_XM_ANDROID		= 116,	//	dl android
	Operation_Platform_baidu_ANDROID    = 119,  //  baidu android

	Operation_Platform_337TW_ANDROID    = 114,  //  baidu android
	Operation_Platform_337YHZ_ANDROID   = 118,  //  台湾妖狐传

    Operation_Platform_OPPO_ANDROID     = 121,  //  OPPO android
	Operation_Platform_Lenovo_ANDROID   = 122,  //  Lenovo android
    Operation_Platform_KY               = 162,  //  KY IOS
    Operation_Platform_TB               = 168,  //  KY IOS
	Operation_Platform_3G_ANDROID       = 124,  //  3G android
	Operation_Platform_WDJ_ANDROID      = 125,  //  WDJ android
	Operation_Platform_AZ_ANDROID       = 127,  //  AZ android
	Operation_Platform_YYH_ANDROID      = 129,  //  YYH android
	Operation_Platform_UNICOM_ANDROID   = 130, // 联通 android
	Operation_Platform_HW_ANDROID      = 133,  //  HW android
	Operation_Platform_BR_ANDROID      = 134,  //  BR android
    Operation_Platform_SX_ANDROID      = 136,  //  SX android
	Operation_Platform_UM_ANDROID      = 137,  //  UM android
	Operation_Platform_37WAN_ANDROID      = 140,  //  37wan android
	Operation_Platform_JF_ANDROID      = 141,  //  SX android

	Operation_Platform_Korea_ANDROID       = 107, //korea,易幻韩国

};
*/
//平台接入用到的ID
enum 
{
	Platform_360_ANDROID		= 1,	//	360
	Platform_553_ANDROID		= 2,	//	553 android
	Platform_553_Other_ANDROID	= 2553,	//	553 android
	Platform_UC_ANDROID			= 3,	//	uc android
	Platform_91_ANDROID			= 4,	//	91 android
	Platform_DL_ANDROID			= 5,	//	dl android
	Platform_XM_ANDROID			= 6,	//	dl android
	Platform_4399_ANDROID		= 7,	//	dl android
	Platform_DK_ANDROID         = 8,	//  baidu
	Platform_3G_ANDROID         = 9,    //  3G android
	Platform_PPS_ANDROID        = 10,   //  PPS android
	Platform_OPPO_ANDROID       = 11,   //  OPPO android
	Platform_WDJ_ANDROID			= 12,	//	WDJ android
	Platform_Lenovo_ANDROID     = 13,   //  Lenovo android
/*    Platform_QQ_ANDROID			= 14,	//	qq android*/
	Platform_YYH_ANDROID			= 14,	//	YYH android
	Platform_SX_ANDROID			= 15,	//	qq android
	Platform_AZ_ANDROID			= 16,	//	AZ android
	Platform_UM_ANDROID			= 17,	//	UM android
	Platform_HW_ANDROID			= 18,	//	HW android
    Platform_GF_ANDROID			= 19,	//	GF android
	Platform_BR_ANDROID			= 20,	//	BR android
	Platform_37WAN_ANDROID			= 21,	//	37wan android
	Platform_UNICOM_ANDROID			= 22,  //   Unicon android
	Platform_TW_ANDROID			= 337,	//	taiwan android
	Platform_TW_YHZ_ANDROID		= 3370,	//	taiwan android
	Platform_GKOREA_ANDROID			= 338,	//	taiwan android
	Platform_TKOREA_ANDROID			= 339,	//	taiwan android
};

enum Language
{
	LT_Invalid = -1,
	LT_Default = 0,
	LT_CHS = LT_Default,
	LT_CHT,
	LT_KOR,
	LT_YHZ,
	LT_MAX,
};

static Language _curLanguage = LT_Default;

Language GetCurrentLanguage();
const char* GetLanguageTypeString(Language type);
bool _isTextUTF8(const char* str, size_t length);
Sprite *GetSprite(const std::string& filename);

#define FONT_BMP_24					"Font/ms_font.fnt"

#define REVERSE_Y(y, maxY)	(maxY - y -1)
#define SCREEN_SIZE	(CCDirector::sharedDirector()->getWinSize())


/*
void			SetupLanguage( Language type = LT_Invalid );
bool			IsLanguageEnable( Language type );
bool			IsCHTOnly();
bool			IsCHSOnly();
bool			IsKOROnly();
bool			IsYHZOnly();
int				GetSupportedLanguages( bool lan[ LT_MAX ] );
const char*		GetLanguageTypeString( Language type );
Language		GetLanguageTypeFromString( const char* name );
bool			ChangeLanguage( Language type, bool reload = true );
Language		GetCurrentLanguage();
void			LoadTask();

std::string _fixPathByLanguage( const char* resName );

#ifdef TARGET_PACKAGE
extern int      GetCurretnSourceID();
#endif
//网络协议版本号
#define PROTOCOL_VERSION	3

//执行端版本号,win32
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define LOCALAPPVERSION_win32		"40"
#endif

#define kOFFSET_FOR_KEYBOARD 150.0 

//
//template<class A> A* Node()
//{
//	A* pRet = new A();
//	pRet->autorelease();
//	return pRet;
//}

//#define USED_JUMP

#ifndef WIN32

typedef unsigned int  UINT;
typedef unsigned char BYTE;
typedef unsigned long  DWORD;
typedef unsigned short  WORD;
#define FONT_TTF	"Thonburi-Bold"

#else
#define FONT_TTF	"微软雅黑"

#endif



#define		Check_Name_Result_Succ							1			//名字可用
#define		Check_Name_Result_TooLong						-1			//名字太长，不可用
#define		Check_Name_Result_TooShort						-2			//名字太短，不可用
#define		Check_Name_Result_ErrorCharacter				-3			//有空格，换行符，制表符，问号，百分号，等不能使用的字符
#define		Check_Name_Result_Not_Chinese					-4			//不是汉字
#define		Min_Name_Length										4			//4个字符，2个汉字
#define		Max_Name_Length										12		//12个字符，6个汉字

inline int CheckName( const char *str )
{
	int len = strlen(str);
	int realLen = 0;
	for( int i=0; i<len; ++i )
	{
		char c = str[i];
		if( c == '%' )
			return Check_Name_Result_ErrorCharacter;
        
		if( c == '?' )
			return Check_Name_Result_ErrorCharacter;
        
		if( c == '\n' )
			return Check_Name_Result_ErrorCharacter;
        
		if( c == '\t' )
			return Check_Name_Result_ErrorCharacter;
        
		if( c== ' ' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '\\' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '/' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '#' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '$' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '^' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '<' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '>' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '&' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '*' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '(' )
			return Check_Name_Result_ErrorCharacter;

		if( c== ')' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '!' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '~' )
			return Check_Name_Result_ErrorCharacter;

		if( c== ';' )
			return Check_Name_Result_ErrorCharacter;

		if( c== ':' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '\"' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '\'' )
			return Check_Name_Result_ErrorCharacter;

		if( c== ',' )
			return Check_Name_Result_ErrorCharacter;

		if( c== '.' )
			return Check_Name_Result_ErrorCharacter;
        
		if( c < 0 )
		{
			i += 2;
			realLen += 2;
		}
		else
		{
			realLen += 1;
		}
	}
    
	if( realLen < Min_Name_Length )
		return Check_Name_Result_TooShort;
	if( realLen > Max_Name_Length )
		return Check_Name_Result_TooLong;

	if(!(CFontCharacter::IsUTF8Chinese(str)))
		return Check_Name_Result_Not_Chinese;

	return Check_Name_Result_Succ;
}

bool	isNeedChangeName( string name );

#ifdef WIN32

void CheckMemoryHeap();

inline string ANSI2UTF8( const string& str )
{
	if(str=="")
		return str;
	const int SIZE = 10240;

	char result[SIZE];

	WCHAR w[SIZE]={0};
	int erg=0;

	erg=MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, w, SIZE / sizeof(WCHAR));	// ANSI to UNICODE
	erg=WideCharToMultiByte(CP_UTF8, 0, w, -1, result, SIZE, 0, 0);		// UNICODE to UTF-8

	return result;
}

inline long long	CharToInt64( const char *pChar )
{
	return _atoi64(pChar);
}

inline string UTF82ANSI( const string str )
{
	const int SIZE = 10240;

	char result[SIZE];

	WCHAR w[SIZE]={0};
	int erg=0;

	MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)str.c_str(), -1, w, SIZE-1 );
	WideCharToMultiByte( CP_ACP, 0, w, -1, result, SIZE-1,	NULL,NULL);

	return result;
}


#else

int GBKToUTF8(string & gbkStr);  

inline string ANSI2UTF8( const string& str )
{
	if(str=="")
		return str;
	string  str1 = str;
	
	GBKToUTF8(str1);

	return str1;
}

inline long long CharToInt64( const char *pChar )
{
	return atoll(pChar);
}


inline void CheckMemoryHeap() {}
#endif

bool _isTextUTF8( const char* str, size_t length );


#include "Net.h"
#include "GameEvent.h"

#define ClientSetupFileName		"ClientSetup.xml"

void myGLEnableScissorTest();
void myGLDisableScissorTest();
bool myIsScissorTestEnabled();

// 曹春久
// 专门用于护送，生成一个64位的actorID
static long long gStaticConvoyActorID = 0;
#define MakeConvoyActorID64 ++gStaticConvoyActorID
*/
#endif