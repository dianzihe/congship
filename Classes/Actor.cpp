#include "Actor.h"
//#include "ASprite.h"
#include "GameScene.h"
//#include "UIText.h"
//#include "Hero.h"
#include "ActorManager.h"
#include "AnimDef.h"

//#include "CharacterStateTransTable.h"
//#include "GraphicsExtension.h"
//#include "Map.h"
//#include "Camera.h"
//#include "../BaseModule/SFX/SFXModule.h"
//#include "../BaseModule/AbnormalState/AbnormalStateModule.h"
//#include "../BaseModule/DelayASpriteLoad/DelayASpriteLoadManager.h"
//#include "BuffCfg.h"
//#include "../gameui/TianTiSai/ChampionRankUI.h"
//#include "SystemSetUI.h"
//#include "../../cocos2dx/support/TransformUtils.h"

#define TAIL_INTERVAL 0.02f
const int TAIL_INIT_OPACITY = 150;

//: m_SFXModule(NULL)
//, m_AbnormalStateModule(NULL)
//, m_flyState(Object_FlyState_Land)
//, m_pShadowSFX(NULL)
//: m_NameText(NULL)
//, m_PKProctedIcon(NULL)
//, m_buttle(NULL)
Actor::Actor(void)
: m_hasSetShowNamePos(true)
, m_bIsSheild(false)
, m_bIsTargetIconSheild(false)
, m_bEnableTails(false)
, m_bStartDisableTails(false)
, m_totalTails(5)
, m_tails(NULL)

{
	m_nActorID = 0;
	m_nActorType = ACTORTYPE_ANIMATION;
	m_nDataID = 0;
	m_animID = -1;
	//m_dir = eDirection_Right;
	m_cleanFlag = true;
	//m_moveState = (Object_MoveState_Stand<<2) | Object_FlyState_Land;
	//m_AbnormalStateModule = new AbnormalStateModule(this);
	//m_SFXModule = new SFXModule;
	m_nStateFlag = 0;
	m_canBeenClick = true;
	mGrayInfo = false;
}

Actor::~Actor(void)
{
	//SAFE_DELETE(m_AbnormalStateModule);
	//SAFE_DELETE(m_SFXModule);
	//m_NameText = NULL;
	//SAFE_DELETE_ARRAY(m_tails);
	//m_buttle = NULL;
	//m_pShadowSFX = NULL;
}

void Actor::onLookInfoSceneObject()
{
	if(m_nActorType == ACTORTYPE_MONSTER || m_nActorType == ACTORTYPE_HERO || 
		m_nActorType == ACTORTYPE_NPC  ||  m_nActorType == ACTORTYPE_PLAYER ||
		m_nActorType == ACTORTYPE_PET || m_nActorType == ACTORTYPE_OTHERSFX )
	{
#if 0
		m_SFXModule->Initialize(m_nActorID);

		Map* pCurMap = GetMap();
		if(pCurMap)
		{
			if(pCurMap->getMapID() != BathRoom_MapID)//泡澡地图不显示阴影
			{
				AddShadow();
			}
			else
			{
				RemoveShadow();
			}
		}
#endif
	}
}

Actor* Actor::node(void)
{
	Actor* pRet = new Actor();
	pRet->autorelease();
	return pRet;
}

void Actor::AddShadow()
{
#if 0
	if(m_pShadowSFX)
	{
		m_SFXModule->DelSFX(m_pShadowSFX);
	}

	m_pShadowSFX = new AnimSFX;
	m_pShadowSFX->Initialize();
	m_pShadowSFX->GetAnimation()->LoadASprite(SPRITE_SHADOW, ACTORTYPE_ANIMATION);//加载阴影
	m_pShadowSFX->GetAnimation()->setAnim(0);
	m_pShadowSFX->SetSFXLocation(eSFXLocation_Back);
	m_pShadowSFX->SetLifeStyle( eLife_Allways );
	m_pShadowSFX->SetLifeTime( m_pShadowSFX->GetAnimation()->getAnimTime( 0 ) );
	m_SFXModule->AddSFX(m_pShadowSFX);
#endif
}

void Actor::RemoveShadow()
{
#if 0
	if(m_pShadowSFX)
	{
		m_SFXModule->DelSFX(m_pShadowSFX);
	}
#endif
}

void Actor::addAnimationSprite( int id, ACTORTYPE type, int sex, int equiplevel, bool isMustLoad )
{
	//m_animation.SetHostEventHandler(this);
	//m_animation.LoadASprite( id, type, sex, equiplevel, isMustLoad );
}
/*
Rect& Actor::getSelectRect()
{
	static CCRect tmp(0,0,0,0);
	
	ASprite* sprite = GetSprite();
	if(sprite)
		return sprite->getRectSelect();
	else
		return tmp;
	
	return tmp;
}
*/
//int Actor::GetType()
//{
//	if(m_nTag < 5000)
//		return ACTORTYPE_ANIMAL;
//	else if(m_nTag < 10000)
//		return ACTORTYPE_TRANSPORT;
//	else if(m_nTag < 20000)
//		return ACTORTYPE_NPC;
//	else if(m_nTag < 30000)
//		return ACTORTYPE_MONSTER;		
//	else 
//	{
//		return ACTORTYPE_PLAYER;
//	}
//}
//
//int Actor::GetID()
//{
//	if(m_nTag < 5000)
//	{
//		return m_nTag;
//	}
//	else if(m_nTag < 10000)
//		return m_nTag - 5000;
//	else if(m_nTag < 20000)
//		return m_nTag - 10000;
//	else if(m_nTag < 30000)
//		return m_nTag - 20000;
//	else 
//	{
//		return m_nTag - 30000;
//	}
//}

//Map* Actor::GetMap()
//{
//	return GameScene::GetScene()->GetCurMap();
//}


/*
void Actor::SetNewPos(  CCPoint& pos )
{
	setPosition(pos);
	getParent()->reorderChild(this, GetZOrder());
#if 0
	if(m_bTianTiFight)
	{
		if (CChampionRankUI::Instance().GetAttactID())
		{
			if (getActorID() == CChampionRankUI::Instance().GetAttactID())
			{
				Map* curMap = GetMap();
				if(curMap != NULL)
				{
					curMap->SetCameraTarget(pos);
				}
				return;
			}
		}
	}
	else
	{
		if(m_nActorType == ACTORTYPE_HERO)
		{
			Map* curMap = GetMap();
			if(curMap != NULL)
			{
				curMap->SetCameraTarget(pos);
			}

			GameScene::GetActorManager()->onHeroPosSet();
		}
	}
#endif
}
*/
//fromTag = true: TagID ->Normal ID
//fromTag = false: Normal ID -> TagID
//int Actor::SwitchTagAndID(int type, int id,  bool fromTag)
//{
//	int off = 0;
//	if(type == ACTORTYPE_TRANSPORT)
//		off = 5000;
//	else if(type == ACTORTYPE_NPC)
//		off = 10000;
//	else if(type == ACTORTYPE_MONSTER)
//		off = 20000;
//	else if(type == ACTORTYPE_PLAYER || type == ACTORTYPE_HERO)
//		off = 30000;
//	if(fromTag)
//		return id - off;
//	else
//		return id + off;
//
//}

void Actor::update(float dt)
{
	/*
	CCObject* child;
	CCARRAY_FOREACH(m_pChildren, child)
	{
		child->update(dt);
	}

	*/

	////屏蔽其他玩家名字
//	if (m_NameText )
//	{
//		if (m_nActorType == ACTORTYPE_PLAYER || m_nActorType == ACTORTYPE_PET)
//			m_NameText->setVisible(!m_bIsSheild && !CSystemSetUI::instance().isSet(ShieldSet_OthersName) );
// 		else if (m_nActorType == ACTORTYPE_PET)
// 			m_NameText->setVisible( !m_bIsSheild);
//	}
	
	updateShowNamePos();
#if 0
	if ( m_pChildren ) 
	{
		// need to do
		// bug: remove childe when update.....
		int pos  = 0;	
		while ( pos < (int)m_pChildren->count() )
		{
			CCObject* child = m_pChildren->objectAtIndex(pos);
			child->update(dt);

			if ( pos < (int)m_pChildren->count() )
			{
				CCObject* lastChild = m_pChildren->objectAtIndex(pos);

				if ( child == lastChild )
				{
					pos++;
				}
				else
				{

				}
			}
			else
			{
				pos++;
			}			
		}

	}
	
	m_animation.update(dt);

	if(m_SFXModule)
	{
		m_SFXModule->Update(dt);
	}
	

	if (m_bEnableTails)
	{
		
		m_totalUpdateTailTime += dt;
		if (m_totalUpdateTailTime - m_lastUpdateTailTime > TAIL_INTERVAL)
		{
			m_lastUpdateTailTime = m_totalUpdateTailTime;
			if (!m_bStartDisableTails)
			{
				m_curTailNum++;
				if (m_curTailNum == m_totalTails)
					m_curTailNum = 0;
			
				m_tails[m_curTailNum].valid = true;
				m_tails[m_curTailNum].opacity = TAIL_INIT_OPACITY;
				m_tails[m_curTailNum].animID = m_animation.getAnim();
				m_tails[m_curTailNum].frame = m_animation.getFrame();
				m_tails[m_curTailNum].nodeToParentTransform = this->nodeToParentTransform();
			}
		}
		
		bool allDisable = true;
		int alphaChange = (int)((TAIL_INIT_OPACITY/(m_totalTails * TAIL_INTERVAL)) * dt); 
		for (int n = 0; n < m_totalTails; ++n)
		{
			if (!m_tails[n].valid)
				continue;
			m_tails[n].opacity -= alphaChange;  
			if (m_tails[n].opacity < 0)
				m_tails[n].opacity = 0;
			else
				allDisable = false;
		}

		if (allDisable && m_bStartDisableTails)
		{
			EnableTail(false);
		}
	}

	if( m_buttle)
	{
		if( m_buttleTime > 0.1)
			m_buttleTime -= dt;
		else
			showBubble( false);
	}
#endif
}

/*
void Actor::draw(void)
{
	CCNode::draw();

	Map* curMap = GameScene::GetScene()->GetCurMap();
	if(curMap == NULL)
		return;

	if(m_SFXModule)
	{
		m_SFXModule->RenderBack();
	}

	if(!isDead())
	{
		if(curMap->IsTransparent((int)GetTileX(getPosition().x), (int)GetTileY(getPosition().y)))
		{
			m_animation.m_opacity = 150;
		}
		else
		{
			m_animation.m_opacity = 255;
		}
	}
	if(m_flyState == Object_FlyState_Flying)
	{
		m_animation.setPosition(0, Object_Fly_Height);
	}
	m_animation.SetGray(!!mGrayInfo);
	m_animation.visit();

	if(m_SFXModule)
	{
		m_SFXModule->RenderFront();
	}

	if (!m_bEnableTails)
		return;
	
	kmGLPushMatrix();

	// 渲染残影
	{
		// 保存动画参数
		int opacity = m_animation.m_opacity;
		//m_animation.
		int frame = m_animation.getFrame();
		int animID = m_animation.getAnim();
		
		kmMat4 transfrom4x4;
		CCAffineTransform tmpAffine = this->nodeToParentTransform();
		//CGAffineToGL(&tmpAffine, transfrom4x4.mat);
	
		kmMat4 inverse;
		kmMat4Inverse(&inverse, &transfrom4x4);
	
		// 变回父空间
		kmGLMultMatrix(&inverse);
		
		for (int n = 0; n < m_totalTails; ++n)
		{
			if (!m_tails[n].valid)
				continue;
			kmGLPushMatrix();
			
			tmpAffine = m_tails[n].nodeToParentTransform;

			//CGAffineToGL(&tmpAffine, transfrom4x4.mat);

			kmGLMultMatrix(&transfrom4x4);
			
			CCNode::draw();

			if(m_flyState == Object_FlyState_Flying)
			{
				m_animation.setPosition(0, Object_Fly_Height);
			}

			m_animation.m_opacity = m_tails[n].opacity;
			m_animation.setFrame(m_tails[n].frame);
			m_animation.setAnimID(m_tails[n].animID);

			m_animation.SetGray(!!mGrayInfo);
			m_animation.visit();
			kmGLPopMatrix();
		}

		m_animation.m_opacity = opacity;
		m_animation.setFrame(frame);
		m_animation.setAnimID(animID);
	}

	kmGLPopMatrix();
}
*/
void Actor::ChangeAnimation( int animID, int dir, bool loop, int animaLayerIndex )
{	
	if(m_animID != animID || m_dir != dir)
	{
		/*
		int flag = 0;
		if(dir == eDirection_Left || 
		   dir == eDirection_LeftUp)
		{
			flag |= ANIM_FLAG_FLIP_X;
		}
		int anim = GetAnimID(animID, dir);

		
		if(loop)
			m_animation.setAnim(anim, flag, -1, animaLayerIndex);
		else
			m_animation.setAnim(anim, flag, 1, animaLayerIndex);
		*/
	}

	m_animID = animID;
	m_dir = dir;
}

float Actor::GetAnimationTime( int animID )
{
	int anim = GetAnimID(animID, m_dir);
	//return m_animation.getAnimTime(anim);
	return 1;
}

void Actor::ChangeFlyState(int flyState)
{
	m_flyState = flyState;
}

int Actor::GetAnimID(int state, int dir)
{
	int anim = state;// * ACTOR_ANIM_DIR_COUNT;
	switch(dir)
	{
	case eDirection_Left:
	case eDirection_Right:
	case eDirection_LeftUp:
	case eDirection_RightUp:
		anim = anim + 1;
		break;
	case eDirection_Down:
	case eDirection_LeftDown:
	case eDirection_RightDown:
		anim = anim + 0;
		break;
	case eDirection_Up:
		anim = anim + 2;
	}
	return anim;
}

void Actor::updateShowNamePos()
{	
	/*
	if (!m_hasSetShowNamePos && m_NameText)
	{
		if(m_animation.getReferenceCount())
		{
			CCRect rect = GetSprite()->getRectSelect();
			m_NameText->setPosition(ccp(-m_NameText->m_width/2, rect.size.height + 20));
			m_hasSetShowNamePos = true;
			if (m_nShowName==m_sShowNameNoPKAppend||m_sShowNameNoPKAppend=="")
			{
				SetPKProctIcon(false);
			}
			else
			{
				SetPKProctIcon(true);
			}
		}
	}
	*/
}

void Actor::SetUnShowName()
{
	/*
	if(m_NameText)
	{
		removeChildByTag(ACTORCHILD_NAME, true);
		m_NameText = NULL;
	}

	if(m_PKProctedIcon)
	{
		removeChildByTag(ACTORCHILD_PKPROCTEDICON, true);
		m_PKProctedIcon = NULL;
	}
	*/
}

void Actor::SetPKProctIcon(bool bShow)
{
	/*
	removeChildByTag(ACTORCHILD_PKPROCTEDICON, true);
	if (!bShow)
	{
		return;
	}
	UIData pData;
	pData.type = UI_BASE;
	m_PKProctedIcon= pData.createUI();
	if (!m_PKProctedIcon)
	{
		return;
	}

	m_PKProctedIcon->setImageByFullPath("Icon/SkillIcon/s85.png", false);
	//m_PKProctedIcon->setScale(0.3);
	m_PKProctedIcon->m_width = 20;
	m_PKProctedIcon->m_height = 20;
	if (m_animation.getReferenceCount())
	{
		//名字长度杨全福搞不定，跟策划确认改为保护图标显示在名字上面

		CCRect rect = GetSprite()->getRectSelect();
		float xPos=0;
		if (m_NameText)
		{
			xPos=m_NameText->m_width/2;
		}
		xPos+=m_PKProctedIcon->m_width/2;
		*/

		/*
		CCRect rect = GetSprite()->getRectSelect();
		float xPos=0;
		float yPos=rect.size.height + 46;
		if (m_NameText)
		{
			yPos=m_NameText->getPositionY()+46;
		}
		
		xPos+=m_PKProctedIcon->m_width/2;
		m_PKProctedIcon->setPosition(ccp(-xPos, yPos));
		
	}

	addChild(m_PKProctedIcon, 0, ACTORCHILD_PKPROCTEDICON);
	*/
}

void Actor::SetShowName(const std::string& name)
{
	/*
	if (name.empty() )
	{
		return;
	}
	
	m_nShowName = name;
	m_sShowNameNoPKAppend=m_nShowName;
	//m_nShowName+=GetPkProctedAppendName();
	removeChildByTag(ACTORCHILD_NAME, true);

	m_NameText = UIText::initUITextWithString( m_nShowName, 18, CCSizeMake( 0, 0), tAlignCenterX | tAlignCenterY, false);
	m_NameText->setUseAlphaTest(true);
	
	if (m_animation.getReferenceCount())
	{
		//m_animation.get
		//CCRect rect = GetSprite()->getRectSelect();
		//m_NameText->setPosition(ccp(-m_NameText->m_width/2, rect.size.height + 40));
		m_hasSetShowNamePos = true;
	}
	else
	{
		m_hasSetShowNamePos = false;
	}

	if( !m_buttle)
	{
		m_buttle = initBubble();
		if( m_buttle)
		{
			m_buttle->setPosition( -m_buttle->m_width/2, (int)m_NameText->getPositionY() + m_buttle->m_height + 50);
		}
		addChild( m_buttle, 0, ACTORCHILD_BUBBLE);
	}

	addChild(m_NameText, 0, ACTORCHILD_NAME);

	if (m_nShowName==m_sShowNameNoPKAppend)
	{
		SetPKProctIcon(false);
	}
	else
	{
		SetPKProctIcon(true);
	}
	*/
}

void Actor::showBubble( bool isShow, std::string text, int anim)
{
#if 0
	if( isShow)
	{
		UIAnimation* pAnim = dynamic_cast<UIAnimation*>(m_buttle->findUI( "null1"));
		if( anim > 0)
		{
			pAnim->setAnimationInfo( SPRITE_EXPRESSION, ACTORTYPE_ANIMATION, anim);
			pAnim->setVisible( true);
		}
		else
			pAnim->setVisible( false);
		m_buttle->findUI( "null2")->setText( text); 

		m_buttle->setVisible( true);
		m_buttleTime = Buttle_Life_Time_Max;
	}
	else
	{
		m_buttle->setVisible( false);
		m_buttleTime = 0;
	}
#endif
}

/*
UI* Actor::initBubble()
{
	UI* ui = new UI();

	UIDataGroup group;
	group.Load("PZ_biaoqing.ui");

	ui->autorelease();
	ui->m_name = group.name;
	ui->m_align = group.align;

	for (int i = 0; i < group.count; i++ )
	{
		UI* pChild = group.data[i].createUI();
		ui->addChild(pChild);
	}
	ui->init();
	if( ui)
	{
		ui->findUI( "null1")->setIgnoreTouch( true);
		ui->findUI( "null2")->setIgnoreTouch( true);
		ui->findUI( "Npc_ChatText1")->setIgnoreTouch( true);
		ui->m_height = ui->findUI("Npc_ChatText1")->m_height;
		ui->m_width = ui->findUI( "Npc_ChatText1")->m_width;
		ui->setVisible( false);
		return ui;
	}
	return NULL;
}
*/
//玩家上马时，名字位置
void Actor::OnMountSetShowName(void)
{
	removeChildByTag(ACTORCHILD_NAME, true);
	//m_NameText = UIText::initUITextWithString( m_nShowName, 18, CCSizeMake( 0, 0), tAlignCenterX | tAlignCenterY);
	//m_NameText->setUseAlphaTest(true);
	//m_NameText->setAutoNewLine(false);

	if( m_animation.getReferenceCount() != NULL )
	{
		//CCRect rect = GetSprite()->getRectSelect();
		//m_NameText->setPosition(ccp(-m_NameText->m_width/2, rect.size.height+30));
	}
	
	//addChild(m_NameText, 0, ACTORCHILD_NAME);
}
//玩家下马时，名字位置
void Actor::DownMountSetShowName(void)
{
	removeChildByTag(ACTORCHILD_NAME, true);
	//m_NameText = UIText::initUITextWithString( m_nShowName, 18, CCSizeMake( 0, 0), tAlignCenterX | tAlignCenterY);
	//m_NameText->setUseAlphaTest(true);

	if( m_animation.getReferenceCount() )
	{
		//CCRect rect = GetSprite()->getRectSelect();
		//m_NameText->setPosition(ccp(-m_NameText->m_width/2, rect.size.height+10));
	}
	//addChild(m_NameText, 0, ACTORCHILD_NAME);
}



//////////////////////////////////////////////////////////////////////////
void Actor::setStateFlag( unsigned int nSetValue )
{
	unsigned int nOldValue = m_nStateFlag;

	m_nStateFlag = nSetValue;

	for( int i = 0; i < 32; ++i )
	{
		unsigned int nState = (1<<i);
		bool bSetOnOrOff = ( nState & nSetValue ) != 0;
		bool bOldOnOrOff = ( nState & nOldValue ) != 0;
		if( bSetOnOrOff )
		{
			if( !bOldOnOrOff )
			{
				onStateFlagChanged( nState, true );
			}
		}
		else
		{
			if( bOldOnOrOff )
			{
				onStateFlagChanged( nState, false );
			}
		}
	}
}

void Actor::addStateFlag( unsigned int nFlag )
{
	m_nStateFlag |= nFlag;
	onStateFlagChanged( nFlag, true );
}

void Actor::removeStateFlag( unsigned int nFlag )
{
	m_nStateFlag &= (~nFlag);
	onStateFlagChanged( nFlag, true );
}

void Actor::onStateFlagChanged( unsigned int nChangeStateFlag, bool bAddOrRemove )
{
}

void Actor::setGray( GrayPart gray, bool trueOrFalse )
{
	if( trueOrFalse )
	{
		mGrayInfo = mGrayInfo | gray;
	}
	else
	{
		mGrayInfo = mGrayInfo & (~gray);
	}
}

void Actor::DelayASpriteLoadCallBack()
{
	//m_animation.setAnim(m_animation.getAnim());
}

void Actor::EnableTail(bool enable)
{
	m_bEnableTails = enable;
	m_bStartDisableTails = false;
	if (m_bEnableTails)
	{
		//SAFE_DELETE_ARRAY(m_tails);
		m_tails = new Tail_t[m_totalTails];
		m_curTailNum = 0;
		m_lastUpdateTailTime = 0.f;
		m_totalUpdateTailTime = 0.f;
		
	}
	else
	{
		//SAFE_DELETE_ARRAY(m_tails);
	}
}

void Actor::startDisableTail()
{
	m_bStartDisableTails = true;
}

void Actor::SetTailNum(int num)
{
	if (num	== 0)
		return;
	
	if (m_totalTails != num)
	{
		m_totalTails = num;
		//SAFE_DELETE_ARRAY(m_tails);
		m_tails = new Tail_t[m_totalTails];
		m_curTailNum = 0;
		m_lastUpdateTailTime = 0.f;
		m_totalUpdateTailTime = 0.f;
	}
}

void Actor::isShowName( bool b )
{
	/*
	if (m_NameText)
	{
		m_NameText->setVisible(b);
	}
	*/
}

//////////////////////////////////////////////////////////////////////////
//
CTransport::CTransport()
{

}

CTransport::~CTransport()
{

}

CTransport* CTransport::node(void)
{
	CTransport* pRet = new CTransport();
	pRet->autorelease();
	return pRet;
}

