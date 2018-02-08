#pragma once

//#include "base.h"
//#include "Animation.h"
//#include "PlayerDefine.h"
#include "ActorType.h"
#include "cocos2d.h"
#include "AnimDef.h"
//#include "Animation.h"
//#include "AbnormalStateModule.h"
//#include "CreatePlayerState.h"
//#include "UI.h"
//#include "../gameui/Bath.h"
//class Map;

//enum CAREER
//{
//	ACTORCAREER_WARRIOR=1,    //职业 剑宗
//	ACTORCAREER_HUNTER=2,       //职业 靖羽
//	ACTORCAREER_MAGICIAN=3,     //职业 云裳
//	ACTORCAREER_WARLOCK=4,      //职业 幽冥
//};

const int DIRECTION_LEFT_UP = 0;
const int DIRECTION_RIGHT_UP = 1;
const int DIRECTION_LEFT_DOWN = 2;
const int DIRECTION_RIGHT_DOWN = 3;
const int DIRECTION_UP = 4;
const int DIRECTION_RIGHT = 5;
const int DIRECTION_DOWN = 6;
const int DIRECTION_LEFT = 7;


struct TransportDst
{
	int mapID;
	int x;
	int y;
};

#define ACTOR_ANIM_DIR_COUNT	3

#define BathRoom_MapID 600

enum ACTORCHILD_TAG
{
	ACTORCHILD_SHADOW = 1001,
	ACTORCHILD_NAME,
	ACTORCHILD_ICON,
	ACTORCHILD_CLICK,
	ACTORCHILD_SKILL,
	ACTORCHILD_PICK,
	ACTORCHILD_AOE,
	ACTORCHILD_PKPROCTEDICON,
	ACTORCHILD_VIPICON,
	ACTORCHILD_TITLE,
	ACTORCHILD_BUBBLE,
	//ACTORCHILD_LEVEL,
};

struct Tail_t
{
	bool valid;
	int opacity;
	int animID;
	int frame;
//	CCAffineTransform nodeToParentTransform;
	Tail_t()
	{
		valid = false;
		opacity = 255;
		animID = 0;
		frame = 0;
	}
};

#define MAX_TAILS_NUM 5

static const float Buttle_Life_Time_Max = 5.0f;

//class ASprite;
//class SFXModule;
//class AbnormalStateModule;
//class UIText;
//class AnimSFX;

typedef long long	ActorID;

class Actor : public cocos2d::Node
{
	CC_SYNTHESIZE(int, m_animID, animID);//ACTORSTATE
	CC_SYNTHESIZE(int, m_moveState, MoveState);//MOVESTATE
	CC_SYNTHESIZE(int, m_flyState, FlyState);//MOVESTATE
	CC_SYNTHESIZE(int, m_dir, Dir);//ACTORDIR	

//	CC_SYNTHESIZE(int, m_mapID, MapID);//地图ID

protected:
	ActorID				m_nActorID;		//	与服务器同步的，唯一的物件id
	ACTORTYPE			m_nActorType;	//	物件类型
	int					m_nDataID;		//	根据m_nActorType，可能是Monster的、Npc的配置ID
	bool				m_cleanFlag;	//	切换地图的时候是否清除 默认为true
	bool				m_canBeenClick;	//	能否被选中，默认=true
public:
	ActorID				getActorID()const				{ return m_nActorID; }
	void				setActorID( ActorID n )			{ m_nActorID = n; }

	ACTORTYPE			getActorType()const				{ return m_nActorType; }
	void				setActorType( ACTORTYPE n )		{ m_nActorType = n; }

	int					getDataID()const				{ return m_nDataID; }
	void				setDataID( int n )				{ m_nDataID = n; }

	bool				getCleanFlag( void )const		{ return m_cleanFlag; }
	void				setCleanFlag( bool b )			{ m_cleanFlag = b; }

	bool				getCanBeenClick( void )const	{ return m_canBeenClick; }
	void				setCanBeenClick( bool b )		{ m_canBeenClick = b; }

	//Rect&				getSelectRect( void );

	void                isShowName(bool b); 
public:
	static Actor*		node(void);
public:
	Actor(void);
	virtual ~Actor(void);

	virtual void		onLookInfoSceneObject( void );

//	static inline int Id2Tag(int type, int id )  { return SwitchTagAndID(type, id,false); }
//	static inline int Tag2Id(int type, int id )  { return SwitchTagAndID(type, id,true); }

//	static int SwitchTagAndID(int type, int id,  bool fromTag);

//	int GetType();
//	int GetID();

	virtual void update(float dt);		
	//virtual void draw(void);

	virtual int GetZOrder() { return (int)(getPositionX() + (getPositionY())*(-10000));};

	void ChangeAnimation(int animID, int dir, bool loop = true, int animaLayerIndex = 0);

	float GetAnimationTime( int animID );

	void ChangeFlyState(int flyState);

	//Map* GetMap();

	//void SetNewPos( Point& pos);

	//virtual void ProcessAnimaEvent( AnimaEvent* event ){}

	//inline SFXModule* GetSFXModule() { return m_SFXModule; }

	void setGray(GrayPart gray, bool trueOrFalse);

	bool isGray() { return mGrayInfo != eGrayPart_NotGray; }

	bool isPartGray(GrayPart partGray) { return !!(mGrayInfo & partGray); }

	virtual void DelayASpriteLoadCallBack();

	void EnableTail(bool enable);

	void startDisableTail();

	void SetTailNum(int num);

private:
	unsigned int mGrayInfo;
protected:

	int GetAnimID(int state, int dir);

	void updateShowNamePos();

protected:
	cocos2d::Animation m_animation;

	//SFXModule* m_SFXModule;

	//AnimSFX* m_pShadowSFX;

	//AbnormalStateModule*	m_AbnormalStateModule;

	//UIText *m_NameText;
	//UI*		m_PKProctedIcon;//pk 保护,，挂在玩家头顶的

	//UI* m_buttle;//玩家头顶文字气泡
	float m_buttleTime;//头顶气泡生存时间

	std::string m_name;
	std::string m_nShowName;
	std::string m_sShowNameNoPKAppend;
	bool   m_hasSetShowNamePos;

	// 屏蔽功能用
	bool   m_bIsSheild;

	bool   m_bEnableTails;
	bool   m_bStartDisableTails;
	bool   m_bIsTargetIconSheild;
	bool                m_bTianTiFight;
	int	   m_totalTails;

	Tail_t *m_tails;
	int	   m_curTailNum;

	float m_lastUpdateTailTime;
	float m_totalUpdateTailTime;

public:
	bool isSheild()	{return m_bIsSheild;}
	void setIsSheild(bool is) {m_bIsSheild = is;}

	bool isTargetIconSheild()	{return m_bIsTargetIconSheild;}
	void setTargetIconSheild(bool is) {m_bIsTargetIconSheild = is;}

public:
	//ASprite*			GetSprite()				{return m_animation.GetSprite();}
	
	inline cocos2d::Animation*	GetAnimation()			{ return &m_animation; }

	void				addAnimationSprite( int id, ACTORTYPE type, int sex = 0, int equipLevel = 1, bool isMustLoad = false );

	virtual void	SetShowName( const std::string& name);
	void				SetPKProctIcon(bool bShow);

	virtual std::string		GetPkProctedAppendName(){return "";}

	void				SetName(  const std::string& name ){ m_name = name; };
	const std::string&		GetName()const {return m_name;};
	const std::string&		GetShowName()const{return m_nShowName;};

	void				OnMountSetShowName(void);
	void				DownMountSetShowName(void);
	

	void setTianTiFight(bool bFight){m_bTianTiFight =bFight;}
	const bool getTianTiFight() {return m_bTianTiFight;}

//////////////////////////////////////////////////////////////////////////
private:
	unsigned int		m_nStateFlag;
public:
	unsigned int		getStateFlag( void )const		{ return m_nStateFlag; }
	void				setStateFlag( unsigned int nSetValue );

	bool				isStateFlag( unsigned int nFlag )const		{ return (m_nStateFlag & nFlag) != 0; }

	//bool				isDead( void )const			{ return isStateFlag(Actor_State_Flag_Dead); }

	virtual void		addStateFlag( unsigned int nFlag );
	virtual void		removeStateFlag( unsigned int nFlag );
	virtual void		onStateFlagChanged( unsigned int nChangeStateFlag, bool bAddOrRemove );
	virtual void		SetUnShowName();

	//设置玩家头顶气泡
	void showBubble( bool isShow, std::string text = "", int anim = 0);
	//初始化头顶气泡
	//UI* initBubble();
	void RemoveShadow();
	void AddShadow();
};

class CTransport : public Actor
{
public:
	CTransport();
	~CTransport();
	static CTransport* node(void);
	TransportDst m_dst;
private:
};