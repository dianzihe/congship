#include "DirectionModule.h"
#include "Charactor.h"
//#include "MyMathExtension.h"
#include "Map.h"
#include "GameScene.h"
//#include "../../BaseModule/Navigation/NavigationModule.h"

inline int GetSign( float num )
{
	if(num < 0)
	{
		return -1;
	}
	else if(num > 0)
	{
		return 1;
	}
	return 0;
}

Point DirectionModule::m_sDirVec[DirectionArray_Count];


DirectionModule::DirectionModule( Charactor* pHost )
	: mOldDirection(eDirection_NULL)
, mCurDirection(eDirection_NULL)
, m_RealDirection(eDirection_NULL)
, m_pHost(pHost)
{
}

DirectionModule::~DirectionModule()
{

}

void DirectionModule::initDirectionVec()
{
	m_sDirVec[eDirection_NULL] = ccp( 0.0f, 0.0f );
	m_sDirVec[eDirection_Left] = ccp( -1.0f, 0.0f );
	m_sDirVec[eDirection_Right] = ccp( 1.0f, 0.0f );
	m_sDirVec[eDirection_Up] = ccp( 0.0f, 1.0f );
	m_sDirVec[eDirection_Down] = ccp( 0.0f, -1.0f );

	m_sDirVec[eDirection_LeftUp] = ccp( -0.707107f, 0.707107f );
	m_sDirVec[eDirection_RightUp] = ccp( 0.707107f, 0.707107f );
	m_sDirVec[eDirection_LeftDown] = ccp( -0.707107f, -0.707107f );
	m_sDirVec[eDirection_RightDown] = ccp( 0.707107f, -0.707107f );
}

void DirectionModule::UpdateMotion( float dt )
{
	switch( mCurDirection )
	{
	case eDirection_Left:
	case eDirection_Right:
	case eDirection_Up:
	case eDirection_Down:
	case eDirection_LeftUp:
	case eDirection_RightUp:
	case eDirection_LeftDown:
	case eDirection_RightDown:
		{
			float realSpeed	= dt*m_pHost->getSpeed();
			UpdateDirection( mCurDirection, realSpeed );
		}
		break;
	default:
		{
			if(mOldDirection != eDirection_NULL && mCurDirection == eDirection_NULL)
			{
				//m_pHost->GetStateMachine()->setState(eCharactorState_Idle, m_pHost->getDir());
			}
		}
	}
	mOldDirection = mCurDirection;
}

bool	DirectionModule::UpdateDirection( eDirection dir, float realSpeed, bool isEnter )
{
	DQMap *pMap = GameScene::GetMap();
	if( !pMap )
		return false;
	/*
	CPlayer *pPlayer = dynamic_cast<CPlayer*>(m_pHost);
	if( !pPlayer )
		return false;
	if( !pPlayer->canMove() )
		return false;
	*/
	CCPoint dirVec = m_sDirVec[dir];
	CCPoint curPosition = m_pHost->getPosition();
	CCPoint nextPosition = ccp( curPosition.x+dirVec.x*realSpeed, curPosition.y+dirVec.y*realSpeed);
	int col = ((int)nextPosition.x)/MAP_PHY_TILE_W;
	int row = ((int)nextPosition.y)/MAP_PHY_TILE_H;

	if( dir == mCurDirection )
	{
		col = (int)(((int)curPosition.x+dirVec.x*MAP_PHY_TILE_W/2)/MAP_PHY_TILE_W);
		row = (int)(((int)curPosition.y+dirVec.y*MAP_PHY_TILE_H/2)/MAP_PHY_TILE_H);
	}

	bool	bIsPassByBlock = false;
	if( realSpeed > 5 )
	{
		int col2, row2;
		for( int i=1; i<=((int)realSpeed)/5; ++i )
		{
			col2 = (int)(((int)curPosition.x+dirVec.x*i*5)/MAP_PHY_TILE_W);
			row2 = (int)(((int)curPosition.y+dirVec.y*i*5)/MAP_PHY_TILE_H);
			if( pMap->getCost(col, row) < 0 )
			{
				bIsPassByBlock = true;
			}
		}
	}

	//判断是否可通过
	if( pMap->getCost(col, row) < 0 || bIsPassByBlock )
	{
		if( isEnter )
		{
			if( m_RealDirection != mCurDirection && m_RealDirection != eDirection_NULL  )
			{
				if( UpdateDirection( m_RealDirection, realSpeed, false ) )
				{
					return true;
				}
			}

			eDirection eDir1;
			eDirection eDir2;
			switch( dir )
			{
			case eDirection_Left:
				eDir1 = eDirection_Up;
				eDir2 = eDirection_Down;
				break;
			case eDirection_Right:
				eDir1 = eDirection_Down;
				eDir2 = eDirection_Up;
				break;
			case eDirection_Up:
				eDir1 = eDirection_Right;
				eDir2 = eDirection_Left;
				break;
			case eDirection_Down:
				eDir1 = eDirection_Left;
				eDir2 = eDirection_Right;
				break;
			case eDirection_LeftUp:
				eDir1 = eDirection_Up;
				eDir2 = eDirection_Left;
				break;
			case eDirection_RightUp:
				eDir1 = eDirection_Right;
				eDir2 = eDirection_Up;
				break;
			case eDirection_LeftDown:
				eDir1 = eDirection_Left;
				eDir2 = eDirection_Down;
				break;
			case eDirection_RightDown:
				eDir1 = eDirection_Down;
				eDir2 = eDirection_Right;
				break;
			}

			if( UpdateDirection( eDir1, realSpeed, false ) )
			{
				return true;
			}
			else
			{
				return UpdateDirection( eDir2, realSpeed, false );
			}
		}
		return false;
	}

	m_RealDirection = dir;
	int newDir=0;
	SET_DIR_BY_TWOPOINT(curPosition, nextPosition, newDir);
	//m_pHost->GetStateMachine()->setState(eCharactorState_Run, dir);
	//m_pHost->SetNewPos(nextPosition);
	
	return true;
}


void DirectionModule::SetDirection( eDirection dir )
{
	mCurDirection = dir;
}

bool DirectionModule::CanBeCancel()
{
	return true;
}

void DirectionModule::EnterMotion()
{
	/*
	if(m_pHost->getActorType() == ACTORTYPE_HERO)
	{
		NavigationModule *heroNavigation = GameScene::GetHeroNavigation();
		heroNavigation->CancelNavigation();
	}
	*/
}

void DirectionModule::ExitMotion()
{
	/*
	if(m_pHost->getActorType() == ACTORTYPE_HERO)
	{
		pk::PlayerStopMove dirInfo;
		dirInfo.posX = (int16)m_pHost->getPositionX();
		dirInfo.posY = (int16)m_pHost->getPositionY();
		dirInfo.Send();
	}
	*/
}
