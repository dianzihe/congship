#pragma once
#include "base.h"
#include "ActorType.h"
#include "ASpriteManager.h"
#include "AnimDef.h"
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
class DQAnimation : public Node
{
public:
	DQAnimation(void);
	~DQAnimation(void);

	void SetHostEventHandler( Actor* hostHandler );
	void LoadASprite(int id, ACTORTYPE type = ACTORTYPE_ANIMATION, int sex = 0, int equipLevel = 1, bool isMustLoad = false);	//
	void setAnim( int id, int flag = 0, int loop = -1, int animaLayerIndex = 0 ); // -1：loop 1：noloop
	int    getAnim(){ return m_animID;};
	void   setAnimID(int animID) { m_animID = animID; }
	virtual void update(float dt);
	virtual void draw();
	virtual void draw(int x, int y, bool isGray = false);
	float getAnimTime( int id );
	int	 getFrame() { return m_frame; }
	void setFrame(int frame) { m_frame = frame;}
	CCPoint GetMarkLOC();
	const char* GetMarkDesc();
	void MarkBeingCall(CCPoint pos, const char* desc);
	bool isEnd();
	static int GetWeaponMatch( int playerAnimId );
	static int GetWeaponSFXMatch( int playerAnimId );
	static int GetMountMatch( int playerAnimId );
	static int GetPetMatch(int playerAnimId);				//根据玩家动作活动小师妹动作
	inline ASprite* GetSprite(AnimPart nAnimPart = eAnimPart_Body) { return m_sprite[nAnimPart]; }
	void AddASprite(ASprite* sprite, ACTORTYPE type);

	bool GetAnimRect( CCRect& retRect, int animId, AnimPart nAnimPart = eAnimPart_Body );
	bool GetAnimRectFast( CCRect& retRect, int animId, AnimPart nAnimPart = eAnimPart_Body );
	void ChangeToReplaceASprite(Actor* host, ASprite* origin, ASprite* pReplace, ACTORTYPE type, GrayPart gpart);
	int m_opacity;

	void SetGray( bool isGray ) { mIsGray = isGray; }
	bool GetGray( ) { return mIsGray; }
	Actor*		m_pHostEventHandler;

	void SetCampAndSex( int camp, int sex ) { m_HostCamp = camp; m_HostSex = sex; } 
	float GetBaseFrameTime( int animId );
protected:
	struct AnimMatcher
	{
		typedef int (*AnimPartMatchFunc)( int );
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
private:
	ASprite*	m_sprite[eAnimPart_Count];
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

