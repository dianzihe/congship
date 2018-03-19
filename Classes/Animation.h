#pragma once
#include "base.h"
#include "ActorType.h"
#include "ASpriteManager.h"
#include "AnimDef.h"
#include "MonsterCfg.h"
class ASprite;

#define ANIM_FLAG_FLIP_X            (1<<0) 
#define ANIM_FLAG_FLIP_Y            (1<<1)   
#define ANIM_FLAG_ROT_90            (1<<2)
#define ANIMATION_PET_POS_X			30						//坐骑上的宠物偏移量

enum AnimPart
{
	eAnimPart_Body = 0,
	eAnimPart_Weapon,
	eAnimPart_Mount,
	eAnimPart_Wing,
	eAnimPart_Pet,					//小师妹
	eAnimPart_Count,
};



class Actor;

/*
1, build relationship between animation and event
2, multi layer animation
*/

class DQAnimation : public Node
{
public:
	DQAnimation(void);
	~DQAnimation(void);



	/**
	* @brief 获取输入串(如:bhead=”head1”)中的键名和键值
	* @param KeyName [out] 键名
	* @param Value        [out] 键值
	*/
	static bool getKeyAndValue(const char * pLine, string &KeyName, string &Value);

	/**
	*   @brief 把服务器存的装备描述组合列表转换为动画描述表
	*   @param strList { bhead=”head1”, bface=”face1”, bbody=”body1”, weapon=”weapon1”}
	*/
	static map<string, string> TransToAnimationDesc(const vector<string> &strList);


	/**
	* @brief 获取一个简单的动画
	*
	*/
	//static cwSngSprite *GetSampleAnimation(const string &iwconame, const string &animationName, float delay = 0.1);

	//void addAnimationToCharater(const string &actorName, float aniDelay = 0.2, bool filter = false);

	//WAnimationManagerSng::addAnimationToCharater(iwco_name, "melee_attack1", lpGuai, MonsterAnimationType::DEF_MOVE, desc, 0.1);
	
	void SetHostEventHandler( Actor* hostHandler );
	void LoadASprite(int id, ACTORTYPE type = ACTORTYPE_ANIMATION, int sex = 0, int equipLevel = 1, bool isMustLoad = false);	//
	bool addAnimation(int id, ACTORTYPE type, int sex, int equiplevel, bool isMustLoad);
	void setAnim( int id, int flag = 0, int loop = -1, int animaLayerIndex = 0 ); // -1：loop 1：noloop
	int    getAnim(){ return m_animID;};
	void   setAnimID(int animID) { m_animID = animID; }
	virtual void update(float dt);
	//virtual void draw();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)override;
	virtual void draw(int x, int y, bool isGray = false);
	float getAnimTime( int id );
	int	 getFrame() { return m_frame; }
	void setFrame(int frame) { m_frame = frame;}
	Point GetMarkLOC();
	const char* GetMarkDesc();
	void MarkBeingCall(Point pos, const char* desc);
	bool isEnd();
	static int GetWeaponMatch( int playerAnimId );
	static int GetWeaponSFXMatch( int playerAnimId );
	static int GetMountMatch( int playerAnimId );
	static int GetPetMatch(int playerAnimId);				//根据玩家动作活动小师妹动作
	inline ASprite* GetSprite(AnimPart nAnimPart = eAnimPart_Body) { return m_sprite[nAnimPart]; }
	void AddASprite(ASprite* sprite, ACTORTYPE type);

	bool GetAnimRect( Rect& retRect, int animId, AnimPart nAnimPart = eAnimPart_Body );
	bool GetAnimRectFast( Rect& retRect, int animId, AnimPart nAnimPart = eAnimPart_Body );
	void ChangeToReplaceASprite(Actor* host, ASprite* origin, ASprite* pReplace, ACTORTYPE type, GrayPart gpart);
	int m_opacity;

	void SetGray( bool isGray ) { mIsGray = isGray; }
	bool GetGray( ) { return mIsGray; }
	Actor*		m_pHostEventHandler;

	void SetCampAndSex( int camp, int sex ) { m_HostCamp = camp; m_HostSex = sex; } 
	float GetBaseFrameTime( int animId );

	struct AnimMatcher
	{
		typedef int(*AnimPartMatchFunc)(int);
		AnimMatcher()
		{
			_AnimPartMatchFunc[eAnimPart_Body] = NULL;
			_AnimPartMatchFunc[eAnimPart_Weapon] = &GetWeaponMatch;
			_AnimPartMatchFunc[eAnimPart_Mount] = &GetMountMatch;
			_AnimPartMatchFunc[eAnimPart_Pet] = &GetPetMatch;
			_AnimPartMatchFunc[eAnimPart_Wing] = NULL;
		}
		AnimPartMatchFunc _AnimPartMatchFunc[eAnimPart_Count];
	};
protected:
public:
	ASprite*	m_sprite[eAnimPart_Count];
	Animation*  m_stdAnimationp[MonsterAnimationType::DEF_GUAI_ANIMATION_MAX];
	
	std::map< std::string, Animation* >		m_mapAnimation;

	static AnimMatcher _AnimMatcher;
	mark_info   m_markInfo;
	int			m_loop;
	int			m_animID;
	int			m_animaLayerIndex;
	int			m_frame;
	float		m_frameTime;
	int			m_flipFlag;
	int			m_HostCamp;
	int			m_HostSex;

	bool		mIsMutiAsprite;
	bool		mIsGray;
};

