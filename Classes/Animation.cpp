#include "Animation.h"
#include "Actor.h"
#include "ASprite.h"
//#include "Player.h"
#include "PlayerLayerCfg.h"
//#include "../BaseModule/DelayASpriteLoad/DelayASpriteLoadManager.h"
//#include "Pet.h"
//#include "SitDown.h"
//#include "GameScene.h"
#include "ActorManager.h"
//#include "HeroPet.h"

DQAnimation::DQAnimation(void)
: m_pHostEventHandler(NULL)
, mIsMutiAsprite(false)
, mIsGray(false)
, m_animaLayerIndex(0)
, m_HostCamp(-1)
, m_HostSex(0)
, m_frameTime(0)
, m_loop(-1)
{
	memset(m_sprite, 0, sizeof(m_sprite));
	m_flipFlag = 0;
	m_opacity = 255;
    m_frame = 0;
	m_animID= 0;
}

DQAnimation::~DQAnimation(void)
{
	for (int n = eAnimPart_Body; n < eAnimPart_Count; ++n)
	{
		ASprite* p = m_sprite[n];
		if (p)
		{
			p->release();
		}
	}

	AspriteManager::instance().RemoveAnimationDelayLoad( this );
}
 
void DQAnimation::LoadASprite(int id, ACTORTYPE type, int sex, int equipLevel, bool isMustLoad)
{
	SpriteInfo _SpriteInfo;
	_SpriteInfo._ActorGender = sex;
	_SpriteInfo._ActorID = id;
	_SpriteInfo._ActorType = type;
	_SpriteInfo._EquipLevel = equipLevel;
	ASprite* p = AspriteManager::instance().LoadSprite(_SpriteInfo, isMustLoad);
	if( p && p->IsTextureDelayLoad() && m_pHostEventHandler)
	{
		ASprite* pReplace = AspriteManager::instance().FindReplaceSpriteWhenMemoryLack(_SpriteInfo);
		if(pReplace)
		{
			pReplace->retain();
			GrayPart gPart = eGrayPart_Body;
			if(type == ACTORTYPE_MOUNT)
				gPart = eGrayPart_Mount;
			else if(type == ACTORTYPE_WEAPON)
				gPart = eGrayPart_Weapon;
			else if(type == ACTORTYPE_WING)
				gPart = eGrayPart_Wing;
			AspriteManager::instance().AddAnimationDelayLoad( this, p, type, gPart );
			m_pHostEventHandler->setGray(gPart, true);
			AddASprite(pReplace, type);
		}
		else
		{
			AddASprite(p, type);
		}
	}
	else
	{
		AddASprite(p, type);
	}
}

void DQAnimation::ChangeToReplaceASprite(Actor* host, ASprite* origin, ASprite* pReplace, ACTORTYPE type, GrayPart gpart)
{
	if(origin == NULL || pReplace == NULL || pReplace == origin)
		return;
	m_pHostEventHandler = host;
	pReplace->retain();
	origin->retain();
	origin->ReleaseTextureToDelayLoad();
	AspriteManager::instance().AddAnimationDelayLoad( this, origin, type, gpart );
	m_pHostEventHandler->setGray(gpart, true);
	AddASprite(pReplace, type);
}

void DQAnimation::AddASprite(ASprite* p, ACTORTYPE type)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pHostEventHandler);
	if(type == ACTORTYPE_WEAPON)
	{
		if (m_sprite[eAnimPart_Weapon])
		{
			m_sprite[eAnimPart_Weapon]->release();
		}

		m_sprite[eAnimPart_Weapon] = p;
		mIsMutiAsprite = true;
	}
	else if(type == ACTORTYPE_MOUNT)
	{
		if (m_sprite[eAnimPart_Mount])
		{
			m_sprite[eAnimPart_Mount]->release();
		}

		m_sprite[eAnimPart_Mount] = p;
		mIsMutiAsprite = true;
	}
	else if(type == ACTORTYPE_WING)
	{
		if (m_sprite[eAnimPart_Wing])
		{
			m_sprite[eAnimPart_Wing]->release();
		}
		m_sprite[eAnimPart_Wing] = p;
		mIsMutiAsprite = true;
	}
	else if(type == ACTORTYPE_PET&&pPlayer/*&&pPlayer->IsInMount()*/)				//如果玩家在坐骑上,添加小师妹模型
	{
		if(m_sprite[eAnimPart_Pet])
		{
			m_sprite[eAnimPart_Pet]->release();
		}
		m_sprite[eAnimPart_Pet] = p;
		mIsMutiAsprite = true;
	}
	else
	{
		if (m_sprite[eAnimPart_Body])
		{
			m_sprite[eAnimPart_Body]->release();
		}
		if(p && m_pHostEventHandler && p->IsDataLoaded() == false)
		{
			DelayASpriteLoadManager::instance().AddDelayASpriteAndCallBack( p, m_pHostEventHandler->getActorID() );
		}
		m_sprite[eAnimPart_Body] = p;
	}
}

void DQAnimation::setAnim( int id, int flag, int loop, int animaLayerIndex )
{
    if(m_sprite[eAnimPart_Body] == NULL || id < 0)
	{
		return;
	}
	if ( m_sprite[eAnimPart_Body]->IsDataLoaded() == false && m_pHostEventHandler ) 
	{
		DelayASpriteLoadManager::instance().AddDelayASpriteAndCallBack( m_sprite[eAnimPart_Body], m_pHostEventHandler->getActorID() );
	}
	if ( m_sprite[eAnimPart_Body]->IsDataLoaded() == true && (id+1) > m_sprite[eAnimPart_Body]->GetAnimNumber() )
	{
		return;
	}

	m_flipFlag = flag;
	if ( loop == -1 )
	{
		if ( id == m_animID )
		{
			m_loop = loop;
			m_frameTime = 0.0;
			return;
		}
	}

	m_animID		= id;
	m_frame			= 0;
	m_frameTime		= 0.0;
	m_loop			= loop;
	m_animaLayerIndex = animaLayerIndex;
}

bool DQAnimation::isEnd()
{
	return (m_loop == 0 );
}

void DQAnimation::update(float dt)
{
	if ( m_sprite[eAnimPart_Body] == NULL ) return;
	if ( m_sprite[eAnimPart_Body]->IsDataLoaded() == false ) return;

	if ( isEnd() ) return;
	if(m_animID < 0 || (m_animID+1) > m_sprite[eAnimPart_Body]->GetAnimNumber())
		return;

	m_frameTime += dt;

	int frameCount	= m_sprite[eAnimPart_Body]->GetAFrames(m_animID);  //
	float frameTime	= m_sprite[eAnimPart_Body]->GetAFrameTime(m_animID, m_frame) * GetBaseFrameTime(m_animID);
	if ( m_frameTime > frameTime )
	{
		// next frame
		m_frame++;
		m_frameTime -= frameTime;

		if (m_markInfo.m_markExist)
		{
			m_markInfo.m_markExist = false;
			CCPoint pos = GetMarkLOC();
			const char* desc = GetMarkDesc();
			MarkBeingCall(pos, desc);
		}

		// clear frameTime
		// where less frame , e.g. debug
		if ( m_frameTime > 1.0 )
		{
			m_frameTime = 0.0;
		}

		// max frame
		if ( m_frame >= frameCount )
		{
			// loop anim deal
			if ( m_loop > 0 )
			{
				m_loop--;

				// set frame to 0 when end loop
				if ( m_loop == 0 ) 
				{
					m_frame = frameCount - 1;
					return;
				}
			}
			
			m_frame = 0;			
		}		
	}
}

void DQAnimation::draw()
{
	draw(0, 0, mIsGray);
}

void DQAnimation::MarkBeingCall(CCPoint pos, const char* desc)
{
	if(m_pHostEventHandler)
	{
		AnimaEvent marker;
		marker._EventType = eAnimaEventType_Marker;

		EventParam param1;
		param1._Type = eType_int;
		param1._Data._IntData = (int)pos.x;
		EventParam param2;
		param2._Type = eType_int;
		param2._Data._IntData = (int)pos.y;
		EventParam param3;
		param3._Type = eType_str;
		param3._Data._pStrData = new char[256];
		memset(param3._Data._pStrData, 0, 256);
		if(desc != NULL)
			strcpy(param3._Data._pStrData, desc);

		marker._EventParamList.push_back(param1);
		marker._EventParamList.push_back(param2);
		marker._EventParamList.push_back(param3);
		m_pHostEventHandler->ProcessAnimaEvent(&marker);
		SAFE_DELETE(param3._Data._pStrData);
	}
}

void DQAnimation::draw(int x, int y, bool isGray)
{
	if ( m_sprite[eAnimPart_Body] == NULL ) return;
	if ( m_sprite[eAnimPart_Body]->IsDataLoaded() == false ) return;

	if(m_animID < 0 || (m_animID+1) > m_sprite[eAnimPart_Body]->GetAnimNumber())
		return;
	
	m_markInfo = m_sprite[eAnimPart_Body]->CheckMarkExs(m_animID,m_frame);

	if(mIsMutiAsprite)
	{
		int mountHeight = 0;
		bool isShowPet = true;				//小师妹出战，坐骑上才显示小师妹
		if(m_pHostEventHandler)
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pHostEventHandler);
			if(pPlayer)
			{
				m_HostCamp = pPlayer->getCamp();
				m_HostSex = pPlayer->getSex();
				if(pPlayer->IsInMount())
					mountHeight = pPlayer->getMountHeight();
				//CPet* pPet = dynamic_cast<CPet*>(GameScene::GetActorManager()->FindActor(pPlayer->getPetID()));
				/*if( pPlayer->getPetID() <= 0)
					isShowPet = false;*/
				if(pPlayer->getFightPetModelId() < 0)
					isShowPet = false;
			}
		}
		for (int i = eAnimPart_Body; i < eAnimPart_Count; ++i)
		{
			AnimPart curPart = PlayerLayerCfg::instance().GetAnimPartBySequence(
				m_HostCamp,
				m_HostSex,
				(AnimPlayer)m_animID,
				i,
				m_animaLayerIndex );
			if(m_sprite[curPart] && m_sprite[curPart]->IsDataLoaded())
			{
				int realAnimID(m_animID);
				AnimMatcher::AnimPartMatchFunc nMatcher = _AnimMatcher._AnimPartMatchFunc[curPart];
				if(nMatcher)
					realAnimID = nMatcher(m_animID);

				if(eAnimPart_Pet == curPart&&!isShowPet)					//不显示小师妹
					realAnimID = -1;

				//检测换装的帧匹配
				if(m_sprite[eAnimPart_Body] && realAnimID >= 0)
				{
					if(m_sprite[eAnimPart_Body]->GetAFrames(m_animID) == m_sprite[curPart]->GetAFrames(realAnimID))
					{
						int addHeight = 0;
						if(m_animID >= ANIM_PLAYER_MOUNTIDLE_DOWN && m_animID <=ANIM_PLAYER_MOUNTMOVE_UP && mountHeight >= 0)
						{
							addHeight = mountHeight;
						}
						else
							addHeight = 0;

						if(m_animID == ANIM_PLAYER_SIT2_LEFT)		//根据玩家性别，改变玩家打坐方向
						{
							m_flipFlag = m_HostSex;
						}

						if(eAnimPart_Mount == curPart)
							m_sprite[curPart]->PaintAFrame(realAnimID,m_frame,x,y,m_flipFlag,0,0, m_opacity, isGray);
						else if(eAnimPart_Pet == curPart)
						{
							//根据方向，将小师妹偏移几个像素
							if((m_animID == ANIM_PLAYER_MOUNTIDLE_LEFT||m_animID == ANIM_PLAYER_MOUNTMOVE_LEFT) && m_flipFlag == 0)
								m_sprite[curPart]->PaintAFrame(realAnimID,m_frame,x-ANIMATION_PET_POS_X,y + addHeight,m_flipFlag,0,0, m_opacity, isGray);
							else if((m_animID == ANIM_PLAYER_MOUNTIDLE_LEFT||m_animID == ANIM_PLAYER_MOUNTMOVE_LEFT) && m_flipFlag == 1)
								m_sprite[curPart]->PaintAFrame(realAnimID,m_frame,x+ANIMATION_PET_POS_X,y + addHeight,m_flipFlag,0,0, m_opacity, isGray);
							else
								m_sprite[curPart]->PaintAFrame(realAnimID,m_frame,x,y + addHeight,m_flipFlag,0,0, m_opacity, isGray);
						}
						else
							m_sprite[curPart]->PaintAFrame(realAnimID,m_frame,x,y + addHeight,m_flipFlag,0,0, m_opacity, isGray);
					}
				}
			}
		}
	}
	else
	{
		//如果是小师妹，根据主人性别与打坐类型，改变小师妹打坐方向
		if(m_pHostEventHandler&&m_pHostEventHandler->getActorType() ==  ACTORTYPE_PET&&m_animID == ANIM_XSM_SIT2_LEFT)
		{
			CPet* pPet = dynamic_cast<CPet*>(m_pHostEventHandler);
			if(pPet)
			{
				CPlayer *pPlayer = dynamic_cast<CPlayer*>(GameScene::GetActorManager()->FindActor(pPet->getMasterID()));
				if(pPlayer)
				{
					if(pPlayer->getSex()==0)
					{
						if(pPlayer->getSitDownSate() == SitDown_XSM)
							m_flipFlag = 1;
						else if(pPlayer->getSitDownSate() == SitDown_Love)
							m_flipFlag = 0;
					}
					else
					{
						if(pPlayer->getSitDownSate() == SitDown_XSM)
							m_flipFlag = 0;
						else if(pPlayer->getSitDownSate() == SitDown_Love)
							m_flipFlag = 1;
					}
				}
			}		
		}
		m_sprite[eAnimPart_Body]->PaintAFrame(m_animID,m_frame,x,y,m_flipFlag,0,0, m_opacity, isGray);
	}
}

float DQAnimation::getAnimTime( int id )
{
	if ( m_sprite[eAnimPart_Body] == NULL ) return 0.0f;
	if (m_sprite[eAnimPart_Body]->IsDataLoaded() == false)
	{
		if(m_pHostEventHandler)
			DelayASpriteLoadManager::instance().AddDelayASpriteAndCallBack( m_sprite[eAnimPart_Body], m_pHostEventHandler->getActorID() );
		return 0.6f;
	}
	int frameCount	= m_sprite[eAnimPart_Body]->GetRealAFrames(id);  //
	return (frameCount * GetBaseFrameTime(id));
}

void DQAnimation::SetHostEventHandler( Actor* hostHandler )
{
	m_pHostEventHandler = hostHandler;
}

CCPoint DQAnimation::GetMarkLOC()
{
	if(m_sprite[eAnimPart_Body] == NULL || m_sprite[eAnimPart_Body]->IsDataLoaded() == false)
		return ccp(0,0);
	int rc[4];
	m_sprite[eAnimPart_Body]->GetFModuleRect(rc, m_markInfo.mark_frame, m_markInfo.mark_moudeID, 0,0,0,0,0);

	CCPoint pos  = ccp(rc[0],rc[1]);
    pos.x -= 515;
    pos.y -= 425;
	if(m_flipFlag == 1)
	{
		pos.x = -pos.x;
	}
	return pos;
}

const char* DQAnimation::GetMarkDesc()
{
	return m_markInfo.mark_desc.c_str();
}

int DQAnimation::GetWeaponMatch( int playerAnimId )
{
	struct WeaponMatch
	{
		WeaponMatch()
		{
			memset( sAinmPlayerToWeapon, 0, sizeof(sAinmPlayerToWeapon) );
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK1_DOWN] = ANIM_WEAPON_ATTACK1_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK1_LEFT] = ANIM_WEAPON_ATTACK1_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK1_UP] = ANIM_WEAPON_ATTACK1_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK2_DOWN] = ANIM_WEAPON_ATTACK2_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK2_LEFT] = ANIM_WEAPON_ATTACK2_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK2_UP] = ANIM_WEAPON_ATTACK2_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK3_DOWN] = ANIM_WEAPON_ATTACK3_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK3_LEFT] = ANIM_WEAPON_ATTACK3_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK3_UP] = ANIM_WEAPON_ATTACK3_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK4_DOWN] = ANIM_WEAPON_ATTACK4_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK4_LEFT] = ANIM_WEAPON_ATTACK4_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK4_UP] = ANIM_WEAPON_ATTACK4_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK5_DOWN] = ANIM_WEAPON_ATTACK5_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK5_LEFT] = ANIM_WEAPON_ATTACK5_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK5_UP] = ANIM_WEAPON_ATTACK5_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK6_DOWN] = ANIM_WEAPON_ATTACK6_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK6_LEFT] = ANIM_WEAPON_ATTACK6_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_ATTACK6_UP] = ANIM_WEAPON_ATTACK6_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_DEAD_DOWN] = ANIM_WEAPON_DEAD_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_DEAD_LEFT] = ANIM_WEAPON_DEAD_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_DEAD_UP] = ANIM_WEAPON_DEAD_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_IDLE_DOWN] = ANIM_WEAPON_IDLE_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_IDLE_LEFT] = ANIM_WEAPON_IDLE_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_IDLE_UP] = ANIM_WEAPON_IDLE_UP;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTIDLE_DOWN] = ANIM_WEAPON_MOUNTIDLE_DOWN;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTIDLE_LEFT] = ANIM_WEAPON_MOUNTIDLE_LEFT;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTIDLE_UP] = ANIM_WEAPON_MOUNTIDLE_UP;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTMOVE_DOWN] = ANIM_WEAPON_MOUNTMOVE_DOWN;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTMOVE_LEFT] = ANIM_WEAPON_MOUNTMOVE_LEFT;
 			sAinmPlayerToWeapon[ANIM_PLAYER_MOUNTMOVE_UP] = ANIM_WEAPON_MOUNTMOVE_UP;
			sAinmPlayerToWeapon[ANIM_PLAYER_SIT1_DOWN] = ANIM_WEAPON_SIT1_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_SIT2_LEFT] = ANIM_WEAPON_SIT2_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_MOVE_DOWN] = ANIM_WEAPON_MOVE_DOWN;
			sAinmPlayerToWeapon[ANIM_PLAYER_MOVE_LEFT] = ANIM_WEAPON_MOVE_LEFT;
			sAinmPlayerToWeapon[ANIM_PLAYER_MOVE_UP] = ANIM_WEAPON_MOVE_UP;
		}
		int sAinmPlayerToWeapon[NUM_ANIMS_LAYER];
	};
	static WeaponMatch sWeaponMatcher;
	return sWeaponMatcher.sAinmPlayerToWeapon[playerAnimId];
}

int DQAnimation::GetMountMatch( int playerAnimId )
{
	struct MountMatch
	{
		MountMatch()
		{
			memset( sAinmPlayerToMount, 0, sizeof(sAinmPlayerToMount) );
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK4_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK4_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK4_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK5_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK5_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK5_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK6_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK6_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK6_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_UP] = -1;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_DOWN] = ANIM_MONT_MOUNTIDLE_DOWN;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_LEFT] = ANIM_MONT_MOUNTIDLE_LEFT;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_UP] = ANIM_MONT_MOUNTIDLE_UP;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_DOWN] = ANIM_MONT_MOUNTMOVE_DOWN;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_LEFT] = ANIM_MONT_MOUNTMOVE_LEFT;
 			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_UP] = ANIM_MONT_MOUNTMOVE_UP;
			sAinmPlayerToMount[ANIM_PLAYER_MOVE_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_MOVE_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_MOVE_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_SIT1_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_SIT2_LEFT] = -1;
		}
		int sAinmPlayerToMount[NUM_ANIMS_LAYER];
	};
	static MountMatch sMountMatcher;
	return sMountMatcher.sAinmPlayerToMount[playerAnimId];
}

int DQAnimation::GetPetMatch( int playerAnimId )
{
	struct PetMatch
	{
		PetMatch()
		{
			memset( sAinmPlayerToMount, 0, sizeof(sAinmPlayerToMount) );
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK1_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK2_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_ATTACK3_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_DEAD_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_IDLE_UP] = -1;
			//小师妹坐骑动画
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_DOWN] = ANIM_XSM_MOUNTIDLE_DOWN;
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_LEFT] = ANIM_XSM_MOUNTIDLE_LEFT;
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTIDLE_UP] = ANIM_XSM_MOUNTIDLE_UP;
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_DOWN] = ANIM_XSM_MOUNTMOVE_DOWN;
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_LEFT] = ANIM_XSM_MOUNTMOVE_LEFT;
			sAinmPlayerToMount[ANIM_PLAYER_MOUNTMOVE_UP] = ANIM_XSM_MOUNTMOVE_UP;

			sAinmPlayerToMount[ANIM_PLAYER_MOVE_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_MOVE_LEFT] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_MOVE_UP] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_SIT1_DOWN] = -1;
			sAinmPlayerToMount[ANIM_PLAYER_SIT2_LEFT] = -1;
		}
		int sAinmPlayerToMount[NUM_ANIMS_LAYER];
	};
	static PetMatch sPetMatcher;
	return sPetMatcher.sAinmPlayerToMount[playerAnimId];
}

bool DQAnimation::GetAnimRectFast( CCRect& retRect, int animId, AnimPart nAnimPart /*= eAnimPart_Body */ )
{
	ASprite* pSprite = GetSprite(nAnimPart);
	if(pSprite == NULL || pSprite->IsDataLoaded() == false)
		return false;
	int frameCount = pSprite->GetAFrames(animId);
	if(frameCount <= 0)
		return false;
	if(animId >= pSprite->GetAnimNumber())
		return false;
	int frameIndex = pSprite->GetAnimFrame(animId, frameCount>>1);
	retRect.size.width = (float)pSprite->GetModuleWidth(frameIndex);
	retRect.size.height = (float)pSprite->GetModuleHeight(frameIndex);
	return true;
}

bool DQAnimation::GetAnimRect( CCRect& retRect, int animId, AnimPart nAnimPart /*= eAnimPart_Body */ )
{
	ASprite* pSprite = GetSprite(nAnimPart);
	if(pSprite == NULL || pSprite->IsDataLoaded() == false)
		return false;
	int frameCount = pSprite->GetAFrames(animId);
	if(frameCount <= 0)
		return false;
	if(animId >= pSprite->GetAnimNumber())
		return false;
	for(int i=0; i<frameCount; i++)
	{
		int frameIndex = pSprite->GetAnimFrame(animId, i);
		int curWidth = pSprite->GetModuleWidth(frameIndex);
		int curHeight = pSprite->GetModuleHeight(frameIndex);
		if(retRect.size.width < (float)curWidth)
		{
			retRect.size.width = (float)curWidth;
		}
		if(retRect.size.height < (float)curHeight)
		{
			retRect.size.height = (float)curHeight;
		}
	}
	return true;
}

float DQAnimation::GetBaseFrameTime( int animId )
{
	if(m_sprite[eAnimPart_Body] && m_sprite[eAnimPart_Body]->mSpriteName.at(0) == 'd') // ACTORTYPE_WEAPONSFX
	{
		return 0.07f;
	}
	if(m_HostCamp >= 0 && m_HostCamp < 4)
	{
		if(animId >= ANIM_PLAYER_ATTACK1_DOWN && animId < ANIM_PLAYER_DEAD_DOWN)
		{
			return 0.07f;
		}
	}
	if(m_pHostEventHandler &&
		( m_pHostEventHandler->getActorType() == ACTORTYPE_NPC || 
		  m_pHostEventHandler->getActorType() == ACTORTYPE_MONSTER ) )
		 return 0.15f;
	return 0.1f;
}

DQAnimation::AnimMatcher Animation::_AnimMatcher;


