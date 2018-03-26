#include "RoutingModule.h"
#include "Charactor.h"
//#include "MyMathExtension.h"




RoutingModule::RoutingModule( Charactor* pHost )
: m_pHost(pHost)
{
	ResetNextPos();
}

RoutingModule::~RoutingModule()
{

}

void RoutingModule::AddTargetPath( const Point& pos )
{
	m_path.push_back(Point(pos.x, pos.y));
}

void RoutingModule::CleanPath()
{
	m_path.clear();
	if(IsInMovingState())
	{
		ResetNextPos();
	}
}

bool RoutingModule::CanBeCancel()
{
	return true;
}

void RoutingModule::EnterMotion()
{

}

void RoutingModule::ExitMotion()
{
	CleanPath();
}

void RoutingModule::UpdateMotion(float dt)
{
	log("RoutingModule::UpdateMotion---->[%lld %s]  Speed:%d-->[%d, %d]", 
		m_pHost->getActorID(),
		m_pHost->GetName().c_str(),
		m_pHost->getSpeed(), m_pHost->pos_x, m_pHost->pos_y);
	int newDir=0;
	float realSpeed = m_pHost->getSpeed() * dt;
	if (IsInMovingState()){
		//正在移动过程中
		MoveToNextPos(realSpeed);
	} else {
		//寻找下一个路点
		if(m_path.size() > 0) {
			Point p = m_path.front();
			SetNextPos(p);
			if(IsNear(GetNextPos(), realSpeed)) {
				//m_pHost->SetNewPos(GetNextPos());
				ResetNextPos();
			} else {
				//开始移动或者在拐点处切换移动方向 重新计算动画的位置和方向
				//SET_DIR_BY_TWOPOINT(m_pHost->getDQPosition(), GetNextPos(), newDir);
				//m_pHost->GetStateMachine()->setState(eCharactorState_Run, newDir);
			}
			if(m_path.size())
				m_path.pop_front();
		} else {
			//没有路点可以走了 玩家应退出移动状态
			//m_pHost->GetStateMachine()->setState(eCharactorState_Idle, m_pHost->getDir());
		}
	}
};

bool RoutingModule::IsNear( const Point& pos, float speed )
{
	return ccpDistance( /*m_pHost->getDQPosition()*/ Vec2(0, 0), pos) < speed;
}

void RoutingModule::MoveToNextPos(float realSpeed)
{	
	if(GetNextPos().x >= 0) {
		Point tPosition = Vec2(0, 0);// m_pHost->getDQPosition();
		float xoff = GetNextPos().x - tPosition.x;
		float yoff = GetNextPos().y - tPosition.y;
		float l = sqrtf(xoff*xoff+yoff*yoff);
		if(l < 0.0001f ) {
			//m_pHost->SetNewPos(GetNextPos());
			if( m_path.size() ) {
				SetNextPos(Point( m_path.front().x, m_path.front().y));
				m_path.pop_front();
				MoveToNextPos( realSpeed );
			}
		} else {
			float x = tPosition.x + xoff / l * realSpeed;
			float y = tPosition.y + yoff / l * realSpeed;
			if( m_pHost->getActorType() == ACTORTYPE_HERO ) {
				Point nextPos = GetNextPos();
				float realDis = sqrtf((tPosition.x-nextPos.x)*(tPosition.x-nextPos.x) + (tPosition.y-nextPos.y)*(tPosition.y-nextPos.y));
				if( realSpeed <= realDis ) {
					//m_pHost->SetNewPos(Point(x,y));
				} else {
					x = nextPos.x;
					y = nextPos.y;
					float diffDis = realSpeed - realDis;
					PathList::iterator it = m_path.begin();
					
					while (it != m_path.end())	{
						//					for( ; it != m_path.end(); ++it )
					
						float dis = sqrtf((x - it->x) * (x - it->x) + (y - it->y) * (y - it->y));
						if( dis < diffDis ) {
							// 此步越过了当前m_path的头上的路点
							diffDis = diffDis-dis;
							x = it->x;
							y = it->y;

							m_path.pop_front();

							if( m_path.size() <= 0 )
								ResetNextPos();
							else
								SetNextPos( Point( m_path.front().x,  m_path.front().y ) );

							it = m_path.begin();
						} else {
							xoff = it->x - x;
							yoff = it->y - y;
							l = sqrtf(xoff*xoff+yoff*yoff);
							x = x+xoff/l*diffDis;
							y = y+yoff/l*diffDis;
							SetNextPos(Point(it->x, it->y));
							m_path.pop_front();
							break;
						}
					}
					//m_pHost->SetNewPos(Point(x,y));
				}
			} else {
				//m_pHost->SetNewPos(Point(x,y));
			}
			if(IsNear(GetNextPos(), realSpeed)) {
				ResetNextPos();
			} else {
				int newDir = 0;
				//SET_DIR_BY_TWOPOINT(m_pHost->getDQPosition(), GetNextPos(), newDir);
				//m_pHost->GetStateMachine()->setState(eCharactorState_Run, newDir);
			}
		}
	}
}