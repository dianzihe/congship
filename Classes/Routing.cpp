#include "Routing.h"
#include "Hero.h"
#include "MapCfg.h"
#include "Map.h"
//#include "NPCMissionUI.h"
//#include "HeroMount.h"
#include "GameScene.h"
#include "ActorManager.h"
#include "RoutingModule.h"
#include "GameCMDSystem.h"

CRouting::CRouting(void)/*:m_pHero(NULL)*/
{
}

CRouting::~CRouting(void)
{
}

void CRouting::init( /*CHero* p*/ )
{
	//m_pHero = p;
	m_destMapId = 0;
	m_destPos.x = 0;
	m_destPos.y = 0;
	m_dataId = 0;
	//m_pHero = p;
	//m_pHero->GetRoutingModule()->SetNavigation(this);
}


void CRouting::_SeekMapPath(int startMap, int destMap, int parent, vector<int> &pathIn, vector<int> &pathOut)
{
	MapData *pParent = (MapData*)MapCfg::instance().getMapCfgData(parent);
	if( !pParent )
		return;
	vector<TransportData>::iterator it = pParent->transport.begin();
	for( ; it != pParent->transport.end(); ++it ) {
		//Ŀ���ͼΪ��һ�����ҵĵ�ͼ��ֱ������
		if( it->getDestMapId() == parent )
			continue;

		bool isFind = false;
		vector<int>::iterator itIn = pathIn.begin();
		for( ; itIn != pathIn.end(); ++itIn ) {
			if( (*itIn) == it->getDestMapId() ) {
				isFind = true;
				break;
			}
		}

		if( isFind )
			continue;

		//����Ŀ���ͼ
		if(it->getDestMapId() == destMap ) {
			//�жϴ�·���Ƿ����
			if( pathOut.size()==0  || pathIn.size() < pathOut.size()-1 ) {
				pathOut = pathIn;
				pathOut.push_back(destMap);
			}
		} else {
			//�����Ѿ�����Ѱ�ҳ�����·�������ټ���Ѱ��
			if(pathOut.size() && pathIn.size() >= pathOut.size())
				return;

			vector<int> tmp;
			tmp = pathIn;
			tmp.push_back(it->getDestMapId());
			_SeekMapPath(startMap, destMap, it->getDestMapId(), tmp, pathOut);
		}
	}
}



//��ʼ������
//mapId�� ������Ŀ���ͼ��Ϊ0��ʾ��ǰ��ͼ
//pos�� ������Ŀ���
bool CRouting::runNavigation( const int mapId, CCPoint pos)
{
	//if( !m_pHero )
	//	return false;
	m_destMapId = mapId;
	m_destPos = pos;
	m_listMapPath.clear();
	/*
	RoutingCMD* newCMD = new RoutingCMD(m_pHero->getActorID());
	m_pHero->GetGameCMDSystem()->PushGameCMD(newCMD);

	//����ͼѰ·
	if( mapId==0 || m_pHero->GetMap()->getMapID() == mapId )
	{
		m_pHero->GetRoutingModule()->SetTargetPos(pos);
		m_destPos = CCPointZero;
		m_pHero->setIsRouting(true);
		if( fabs(m_pHero->getPositionX()-pos.x) >= 500 || fabs(m_pHero->getPositionY()-pos.y) >=500 )
		{
			if( GameScene::GetMap()->getMapSettingData()->type != Map_Type_Normal_Copy )
				CHeroMount::instance().MountUpRequest();
		}
	}
	//���ͼѰ·
	else
	{
		vector<int> pathIn, pathOut;
		_SeekMapPath(m_pHero->GetMap()->getMapID(), mapId, m_pHero->GetMap()->getMapID(), pathIn, pathOut );
		if(pathOut.size() == 0)
			return false;

		vector<int>::iterator it = pathOut.begin();
		for( ; it != pathOut.end(); ++it )
		{
			m_listMapPath.push_back(*it);
		}

		if( GameScene::GetMap()->getMapSettingData()->type != Map_Type_Normal_Copy )
			CHeroMount::instance().MountUpRequest();
		moveToDestMap();

	}
	*/
	return true;
}

void CRouting::moveToDestMap()
{
	/*
	MapData *pStartMap = (MapData*)MapCfg::instance().getMapCfgData(m_pHero->GetMap()->getMapID());
	if( !pStartMap )
		return ;

	if(m_listMapPath.size())
	{
		vector<TransportData>::iterator it = pStartMap->transport.begin();
		for( ; it != pStartMap->transport.end(); ++it )
		{
			if( it->getDestMapId() == m_listMapPath.front() )
			{
				m_pHero->GetRoutingModule()->SetTargetPos(ccp(it->x, it->y));
				m_pHero->setIsRouting(true);
				m_listMapPath.pop_front();
				return;
			}
		}
	}
	else
	{
		m_pHero->GetRoutingModule()->SetTargetPos(m_destPos);
		m_destPos = CCPointZero;
	}
	*/
}


void CRouting::onArriveNextPos()
{
	/*
	if( !m_listMapPath.size() && CCPoint::CCPointEqualToPoint( m_destPos,CCPointZero))
		m_pHero->setIsRouting( false );
	*/
}

void CRouting::flyTo(int map_id, int map_x, int map_y)
{
	// ����ʱclear֮ǰ��Ѱ··��
	m_listMapPath.clear();
	/*
	CHero* pHero = GameScene::GetActorManager()->GetHero();
	pHero->GetRoutingModule()->ClientStopMove();

	if(map_id == GameScene::GetScene()->GetCurMap()->getMapID())
	{
		pk::U2GS_TransForSameScence msgTrans;
		msgTrans.mapDataID = map_id;
		msgTrans.posX = map_x;
		msgTrans.posY = map_y;
		msgTrans.Send();
	}
	else
	{
		pk::U2GS_TransByWorldMap msgTrans;
		msgTrans.mapDataID = map_id;
		msgTrans.posX = map_x;
		msgTrans.posY = map_y;
		msgTrans.Send();
	}
	*/
}

bool CRouting::isNeedContinueDestMap()
{
	/*
	if(m_pHero == NULL || m_pHero->GetMap() == NULL)
		return false;

	if(m_destMapId == 0)
		return false;

	if( m_pHero->GetMap()->getMapID() != m_destMapId || !CCPoint::CCPointEqualToPoint( m_destPos,m_pHero->getPosition()))
		return true;
	*/
	return false;
}
