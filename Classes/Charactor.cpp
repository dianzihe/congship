#include "Charactor.h"
#include "GameScene.h"
#include "ActorManager.h"
//#include "Hero.h"
#include "CharDefine.h"
//#include "UIText.h"
/*
#include "MyMathExtension.h"
#include "effect.h"
#include "GameState.h"
#include "GameMainUI.h"
#include "../BaseModule/Combat/CombatModule.h"
#include "Target.h"
#include "ColorCfg.h"
#include "BuffCfg.h"
#include "../BaseModule/AbnormalState/AbnormalStateModule.h"
#include "../BaseModule/Motion/MotionManager.h"
#include "CCEGLView.h"
#include "../InputSystem/GameCMDSystem.h"
#include "HeroPet.h"
#include "Map.h"
#include "Teamlogic.h"
#include "SkillCfg.h"
#include "SitDown.h"
#include "GameHangUp.h"
#include "TargetList.h"
#include "ChampionSituation.h"
*/
bool	isPropertyShowRate( int type )
{
	switch( type )
	{
	case CharProperty_attack:
	case CharProperty_defence:
	case CharProperty_ph_def:
	case CharProperty_fire_def:
	case CharProperty_ice_def:
	case CharProperty_elec_def:
	case CharProperty_poison_def:
	case CharProperty_max_life:
	case CharProperty_life_recover:
	case CharProperty_been_attack_recover:
	case CharProperty_damage_recover:
	case CharProperty_coma_def:
	case CharProperty_hold_def:
	case CharProperty_silent_def:
	case CharProperty_move_def:
	case CharProperty_hit:
	case CharProperty_dodge:
	case CharProperty_block:
	case CharProperty_crit:
	case CharProperty_pierce:
	case CharProperty_attack_speed:
	case CharProperty_tough:
	case CharProperty_all_def:
	case CharProperty_all_exception:
		return false;
	case CharProperty_crit_damage_rate:
	case CharProperty_block_dec_damage:
	case CharProperty_phy_attack_rate:
	case CharProperty_fire_attack_rate:
	case CharProperty_ice_attack_rate:
	case CharProperty_elec_attack_rate:
	case CharProperty_poison_attack_rate:
	case CharProperty_phy_def_rate:
	case CharProperty_fire_def_rate:
	case CharProperty_ice_def_rate:
	case CharProperty_elec_def_rate:
	case CharProperty_poison_def_rate:
	case CharProperty_treat_rate:
	case CharProperty_treat_rate_been:
	case CharProperty_life_recover_MaxLife:
	case CharProperty_move_speed:
	case CharProperty_coma_def_rate:
	case CharProperty_hold_def_rate:
	case CharProperty_silent_def_rate:
	case CharProperty_move_def_rate:
	case CharProperty_hit_rate:
	case CharProperty_dodge_rate:
	case CharProperty_block_rate:
	case CharProperty_crit_rate:
	case CharProperty_pierce_rate:
	case CharProperty_attack_speed_rate:
	case CharProperty_tough_rate:
	case CharProperty_all_exception_rate:
	case CharProperty_def_damage:
	case CharProperty_all_damage:
		return true;
	}
	return false;
}
//, m_pMotionMananger(NULL)
Charactor::Charactor()
: m_CurCombatID(0)
, m_CharactorCombatState(eCharactorCombatState_Idle)
{
	m_nAttackSum = 0;
	m_nSkillMac = 0;
	m_camp	= 0;
	m_speed = 0;				//移动速度 每秒移动多少像素
	m_nLevel = 0;				//等级
	m_nFaction = 0;				//阵营
	m_nSex = 0;					//性别
	m_nLife = 0;				//生命
	m_nLifeMax = 0;				//最大生命
	m_percentage_Life = 1.0f;
	m_nNameColorType = CharNameColorType_CanNotAttack;
	//m_sitDownType = SitDown_None;

	m_bTianTiFight = false;
	//m_pStateMachine = new StateMachine(this);
	//m_pGameCMDSystem = new GameCMDSystem();
}

Charactor::~Charactor()
{
	//SAFE_DELETE(m_pStateMachine);
	//SAFE_DELETE(m_pGameCMDSystem);
	//SAFE_DELETE(m_pMotionMananger);
}


bool Charactor::init( void )
{
	//m_pMotionMananger = new MotionManager(this);
	Actor::onLookInfoSceneObject();
	return true;
}

void Charactor::update(float dt)
{
//#if defined WIN32 | _WIN32
//	if(dt > 1.0f)
//		return;
//#endif
	//m_pGameCMDSystem->UpdateCMDSystem();
	Actor::update(dt);
	/*
	if(m_animation.isEnd())
	{
		m_pStateMachine->setState(eCharactorState_Idle, m_dir);
	}
	
	if(!isDead())
	{
		m_pMotionMananger->Update(dt);
	}
	m_pStateMachine->updateMachine(dt);
	*/
}
/*
void Charactor::draw(void)
{
	Actor::draw();

	//选中的怪物与玩家攻击的怪物显示血条
	if( Target::instance().getTargetID() == getActorID()||(m_percentage_Life<1.0 && Target::instance().isInTargetList(getActorID())) && !m_bTianTiFight)
	{
		DrawHP();
		//checkCanBeenAttackByHero_DrawName();
	}
	if (m_bTianTiFight && getActorType() != ACTORTYPE_HERO)
	{
		DrawHP();
	}
}
*/
void Charactor::checkCanBeenAttackByHero_DrawName()
{
	/*
	CHero* pHero = GameScene::GetActorManager()->GetHero();
	if( !pHero || pHero == this )
		return;

	if( pHero->isDead() )
	{
		if( m_nNameColorType == CharNameColorType_Dead )
			return;

		UIText* nameTTF = (UIText*)getChildByTag(ACTORCHILD_NAME);
		if( nameTTF )
		{
			const ColorData* pColor = ColorCfg::instance().getHeroDeadColor();
// 			char str[256];
// 			sprintf(str, "<C=%d,%d,%d>%s</C>", pColor->color.r, pColor->color.g, pColor->color.b, m_nShowName.c_str());
// 			//nameTTF->m_width = 0;
// 			//nameTTF->m_height = 0;
// 			nameTTF->setText(str);
// 			nameTTF->setPositionX( -nameTTF->m_width/2);
			if (this->getActorType() == ACTORTYPE_PLAYER)
			{
				CPlayer* pTargetPlayer = (CPlayer*)this;
				if (NULL != pTargetPlayer)
				{
					pTargetPlayer->setNameColor(pColor->color.r, pColor->color.g, pColor->color.b);
				}
			}

			m_nNameColorType = CharNameColorType_Dead;
		}
		return;
	}

	bool bCanAttackTarget = pHero->canAttackTargetForNameColor( this );
	UIText* nameTTF = (UIText*)getChildByTag(ACTORCHILD_NAME);
	if( nameTTF )
	{
		if( bCanAttackTarget )
		{
			m_nNameColorType = CharNameColorType_CanAttack;
			ccColor3B color = ColorCfg::instance().getCanAttackColor()->color;
// 			char str[256];
// 			sprintf(str, "<C=%d,%d,%d>%s</C>", color.r, color.g, color.b, m_nShowName.c_str());
// 			//nameTTF->m_width = 0;
// 			//nameTTF->m_height = 0;
// 			nameTTF->setText(str);
// 			nameTTF->setPositionX( -nameTTF->m_width/2);
			if (this->getActorType() == ACTORTYPE_PLAYER)
			{
				CPlayer* pTargetPlayer = (CPlayer*)this;
				if (NULL != pTargetPlayer)
				{
					pTargetPlayer->setNameColor(color.r, color.g, color.b);
				}
			}
		}
		else
		{
			m_nNameColorType = CharNameColorType_CanNotAttack;
			ccColor3B color = ColorCfg::instance().getCanNotAttackColor()->color;
// 			char str[256];
// 			sprintf(str, "<C=%d,%d,%d>%s</C>", color.r, color.g, color.b, m_nShowName.c_str());
// 			//nameTTF->m_width = 0;
// 			//nameTTF->m_height = 0;
// 			nameTTF->setText(str);
// 			nameTTF->setPositionX( -nameTTF->m_width/2);
			if (this->getActorType() == ACTORTYPE_PLAYER)
			{
				CPlayer* pTargetPlayer = (CPlayer*)this;
				if (NULL != pTargetPlayer)
				{
					pTargetPlayer->setNameColor(color.r, color.g, color.b);
				}
			}
		}
	}
	*/
}

bool Charactor::getStateTransitionInfo( int src, int dest )
{
	static CharacterStateTransTable S_CharacterStateTransTable;
	return S_CharacterStateTransTable.mCharacterStateTransTable[src][dest];
}

void Charactor::onStateExit( int stateToExit, int stateParam /*= 0 */ )
{
	switch(stateToExit)
	{
	case eCharactorState_Idle:
		{
		}
		break;
	case eCharactorState_Attack:
		{
			m_CharactorCombatState = eCharactorCombatState_End;
			m_nAttackSum = 1;
			m_nSkillMac = 1;
		}
		break;
	}
}

void Charactor::onStateEnter( int stateToEnter, int stateParam /*= 0 */ )
{
	switch(stateToEnter)
	{
	case eCharactorState_Idle:
		{
		}
		break;
	case eCharactorState_Attack:
		{
			m_CharactorCombatState = eCharactorCombatState_Attack;
			//GetMotionManager()->StopMotion();
		}
		break;
	case eCharactorState_UnderAttack:
		{
			//ClearPath();
		}
		break;
	case eCharactorState_Death:
		{
			//GetMotionManager()->StopMotion();
			//Target::instance().HideTargetInfo();
		}
		break;
	case eCharactorState_DeleteSelf:
		{
			/*
			if(this->getActorType() != ACTORTYPE_PLAYER && this->getActorType() != ACTORTYPE_HERO)
				GameScene::GetActorManager()->DelayDelActor( getActorID() );
			if(Target::instance().getTargetID() == this->getActorID())
				Target::instance().HideTargetInfo();
			*/
		}
		break;
	default:
		break;
	}
}

bool Charactor::IsAbleToAttack( int skillId )
{
	/*
	if( isStateFlag(Actor_State_Flag_Dead) )
		return false;
	const SkillInfo *pSkillInfo = SkillCfg::instance().getSkillCfgData( skillId );
	if( pSkillInfo )
	{
		if( isStateFlag(Actor_State_Flag_Disable_Hold ) )
		{
			if( !(pSkillInfo->Use_Spec & SkillUseSpec_Comal ) )
				return false;
		}

		if( isStateFlag(Actor_State_Flag_Disable_Attack ) )
		{
			if( !(pSkillInfo->Use_Spec & SkillUseSpec_Silent ) )
				return false;
		}
		return true;
	}
	if( isStateFlag(Actor_State_Flag_Disable_Hold) ||
		isStateFlag(Actor_State_Flag_Disable_Attack) )
		return false;
	*/
	return true;
}

bool Charactor::IsAbleToBeenAttack()
{
	//if( isDead() )
	//	return false;

	if( getActorType() == ACTORTYPE_NPC )
		return false;

	return true;
}
/*
void Charactor::ProcessAnimaEvent( AnimaEvent* event )
{
	switch(event->_EventType)
	{
	case eAnimaEventType_Marker:
		{
			if( m_pStateMachine->getCurrentState() == eCharactorState_Attack )
			{
			
				CCPoint pos;
				pos.x = (float)event->_EventParamList[0]._Data._IntData;
				pos.y = (float)event->_EventParamList[1]._Data._IntData;
				string desc = event->_EventParamList[2]._Data._pStrData;
				if(desc == "ATK")
				{
					CombatModule::instance().HandleAttackSuccess(m_CurCombatID, pos);
					m_nSkillMac++;
				}
				else if(desc == "CBT")
					m_CharactorCombatState = eCharactorCombatState_CombatAccept;
			
			}
		}
	default:
		break;
	}
}
*/

void Charactor::DrawHP()
{
	CCPoint a;
	//if( Target::instance().getTargetID() != getActorID() )
	//	return;

	/*
	if( !GetSprite() )
		return;
    
    if (GetSprite()->IsDataLoaded() == false)
        return;
	
	int rc[4];
	GetSprite()->GetFrameRect(rc, 0, 0, 0, 0, 0, 0);
	if (rc)
	{
		a =  ccp(0, -rc[1] + 15);
	}

	SpriteInfo _spriteInfo;
	_spriteInfo._ActorType = ACTORTYPE_ANIMATION;
	_spriteInfo._ActorID = SPRITE_HP;
	ASprite *sprite = AspriteManager::instance().LoadSprite(_spriteInfo );
	if(sprite != NULL && sprite->IsDataLoaded())
	{
		int rcLift[4];
		sprite->GetFrameRect(rcLift, 0, (int)a.x, (int)a.y, 0, 0, 0);


		CCRect rect;
		rect.origin = convertToWorldSpaceAR(ccp(rcLift[0], rcLift[1]));
		rect.size.width = (float)(rcLift[2] - rcLift[0]);
		rect.size.height = (float)(rcLift[3] - rcLift[1]);

		rect.size.width = rect.size.width  * m_percentage_Life;

		sprite->PaintFrame(1, (int)a.x, (int)a.y,0,0,0);
        
        //float xScale = CCEGLView::sharedOpenGLView()->getFrameSize().width / CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width;
        //float yScale = CCEGLView::sharedOpenGLView()->getFrameSize().height / CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height;

        
        //rect.origin.x *= xScale;
        //rect.size.width *= xScale*GameScene::GetMap()->getSceneScale();
        //rect.origin.y *= yScale;
        //rect.size.height *= yScale*GameScene::GetMap()->getSceneScale();
        
		sprite->SetClip(rect);
		//glEnable(GL_SCISSOR_TEST);
		myGLEnableScissorTest();
		glScissor( (GLint)rect.origin.x, (GLint)rect.origin.y, (GLsizei)rect.size.width, (GLsizei)rect.size.height );


		sprite->PaintFrame(0,(int)a.x,(int)a.y,0,0,0);
		sprite->ResetClip();
		//glDisable(GL_SCISSOR_TEST);
		myGLDisableScissorTest();

		sprite->release();
	}
	*/
}


void Charactor::onDead()
{
	setLife( 0 );
	setperlife( 0.0f );
	//addStateFlag(Actor_State_Flag_Dead);
	//GetRoutingModule()->CleanPath();
}

void Charactor::onRevive( int nLife, int nMaxLife )
{
	setLife( nLife );
	setLifeMax( nMaxLife );
	setperlife( float(nLife)/float(nMaxLife) );
	//removeStateFlag( Actor_State_Flag_Dead );
	//m_pStateMachine->setStateForce(eCharactorState_Idle, m_dir);

	/*
	if( GameScene::GetActorManager()->GetHero() == this )
	{
		//复活自动找回宠物
		//CGameHangUp::GetInstance().setFuHuo(false);
		if (CGameHangUp::GetInstance().getGoOnGuaji())
		{
			CGameHangUp::GetInstance().StartAuto();
			CGameHangUp::GetInstance().setGoOnGuaji(false);
		}

		if( CHeroPet::instance().getFrontFightPetId() )
		{
			pk::PetOutFight toServer;
			toServer.petId = CHeroPet::instance().getFrontFightPetId();
			toServer.Send();
		}
		UI* death = UIManager::Instance()->findUI("MessageRevive.ui");
		if( death )
			death->setVisible(false);
		drawPkKillOtherName();
	}
	*/
}

void Charactor::drawPkKillOtherName()
{
	/*
	CHero* pHero = GameScene::GetActorManager()->GetHero();
	if (NULL == pHero)
	{
		return ;
	}
	const MapSettingData* pMapSettingData = GameScene::GetScene()->GetCurMap()->getMapSettingData();
	if(NULL == pMapSettingData)
	{
		return ;
	}
	if (!pMapSettingData->pkFlag_Camp) // 不在阵营
	{
		return ;
	}
	if (NULL != pHero)
	{
		ActorManager* pActorManager = GameScene::GetActorManager();
		if (NULL != pActorManager)
		{
			for( MAP_ACTORS::iterator iter = pActorManager->GetMapActors().begin(); iter != pActorManager->GetMapActors().end(); ++iter )
			{
				if (iter->second->getActorType() == ACTORTYPE_PLAYER)
				{
					CPlayer* pActor = dynamic_cast<CPlayer*>(iter->second);
					if (NULL != pActor && !CTeam_logicCfg::Instance()->isPlayerInTeam(pActor->getActorID() ))
					{
						if(pActor->getActorID() != pHero->getActorID())
						{
							bool bCanAttackTarget = pHero->canAttackTargetForNameColor(pActor);
							if (pActor->isStateFlag(Player_State_Flag_PK_Kill_Value))
							{
								pActor->setNameColor(PK_COLOR_EVIL);
							}
							else if(pActor->isStateFlag(Player_State_Flag_PK_Kill_Value))
							{
								pActor->setNameColor(PK_COLOR_VALUE);
							}
							//else if (bCanAttackTarget)
							//{
							//	pActor->setNameColor(PK_COLOR_VALUE);
							//}
							else
							{
								pActor->setNameColor(PK_COMMON_COLOR_VALUE);
							}

							//领地战名字颜色
							if(CChampionSituation::Instance().isInTerriorWarState())
							{
								if(pActor->getGuildID() == pHero->getGuildID()|| pActor->getGuildID() == pHero->getParnterID())
									pActor->setNameColor(PK_GUILD_SELF_COLOR);
								else
									pActor->setNameColor(PK_GUILD_OTHER_COLOR);
							}
						}
					}
				}
			}
		}
	}
	*/
}

/*
float Charactor::getStateAnimTime( CharactorState state, int stateParam )
{
	return 0.0f;
}
*/

void Charactor::AddBuff( CharactorBuff& buff )
{
	/*
	CharactorBuff *pBuff = FindBuff(buff.buff_id);
	if(pBuff)
	{
		pBuff->allValidTime = buff.allValidTime;
		pBuff->buff_id = buff.buff_id;
		pBuff->casterID = buff.casterID;
		pBuff->remainTriggerCount = buff.remainTriggerCount;
		pBuff->startTime = buff.startTime;
		return;
	}
	const BuffData *pBuffCfg = BuffCfg::instance().getBuffCfgData(buff.buff_id);
	if( pBuffCfg )
	{
		buff.buffIcon = pBuffCfg->BUFF_ICON;
		m_BuffList.push_back(buff);

		m_AbnormalStateModule->AddAbnormalState(pBuffCfg->id,
			pBuffCfg->BUFF_Show_Front, 
			(SFXLoaction)pBuffCfg->BUFF_Show_Front_Pos,
			pBuffCfg->BUFF_Show_Back,
			(SFXLoaction)pBuffCfg->BUFF_Show_Back_Pos);

		ChangeBuffBecauseBuff();
	}
	*/
}

void Charactor::DelBuff(int buff_id)
{
	/*
	vector<CharactorBuff>::iterator it = m_BuffList.begin();
	for( ; it != m_BuffList.end(); ++it)
	{
		if(it->buff_id == buff_id)
		{
			m_AbnormalStateModule->DelAbnormalState(it->buff_id);
			m_BuffList.erase(it);
			ChangeBuffBecauseBuff();
			return;
		}
	}
	*/
}

void Charactor::UpdateBuff( const CharactorBuff& buff )
{
	CharactorBuff *pBuff = FindBuff(buff.buff_id);
	if(pBuff)
	{
		pBuff->allValidTime = buff.allValidTime;
		pBuff->buff_id = buff.buff_id;
		pBuff->casterID = buff.casterID;
		pBuff->remainTriggerCount = buff.remainTriggerCount;
		pBuff->startTime = buff.startTime;
		return;
	}
	m_BuffList.push_back(buff);
}

CharactorBuff* Charactor::FindBuff( int buff_id )
{
	for( size_t i=0; i<m_BuffList.size(); ++i )
	{
		if(m_BuffList[i].buff_id == buff_id)
		{
			return &(m_BuffList[i]);
		}
	}
	return NULL;
}

void Charactor::DelayASpriteLoadCallBack()
{
	//m_pStateMachine->setState(m_pStateMachine->getCurrentState(), m_dir);
}

bool Charactor::IsAbleToMove()
{
	/*
	if(isDead())
		return false;
	if(m_pStateMachine->getCurrentState() == eCharactorState_Attack)
		return false;
		*/
	return true;
}

void Charactor::setSitDownState(int sitDownType)
{
	/*
	m_sitDownType = sitDownType;
	if(sitDownType != SitDown_None)
		m_pStateMachine->setStateForce(eCharactorState_Meditation, sitDownType);
	else
	{
		//int curState = m_pStateMachine->getCurrentState();
		int curStateParam = m_pStateMachine->getCurrentStateParam();
		m_pStateMachine->setStateForce( eCharactorState_Idle, 0);
	}
	*/
}
