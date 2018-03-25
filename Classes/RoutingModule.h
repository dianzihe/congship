#ifndef _ROUTINGMODULE_H__
#define _ROUTINGMODULE_H__

#include "base.h"
#include "IMotionModule.h"
//#include "Routing.h"
#include <list>

using namespace std;

typedef list<Point> PathList;
struct PathToServer
{
	int distance;
	PathList  path;

	PathToServer()
	{
		distance = 0;
		path.clear();
	}
};

typedef list<PathToServer> PathToSeverList;
class CRouting;
class Charactor;
class RoutingModule : public IMotionModule
{
public:
	RoutingModule(Charactor* pHost);
	virtual ~RoutingModule();
public:
	virtual bool				CanBeCancel();

	virtual void				EnterMotion();

	virtual void				UpdateMotion( float dt );

	virtual void				ExitMotion();

public:
	Point						GetNextPos( void )const			{ return m_nextPos; }
	void						SetNextPos( const Point& st )	{ m_nextPos = st; }

	virtual bool				IsNear(const Point& pos, float speed);

	virtual void				MoveToNextPos(float realSpeed);

	virtual void				ResetNextPos(){ SetNextPos(ccp(-1, -1)); };

	virtual bool				IsInMovingState(){return (GetNextPos().x >= 0);};

	virtual void				AddTargetPath(const Point& pos);//移动到某个位置:

	virtual void				CleanPath();

	virtual void				CleanTargetPosition(){}
	virtual	void				CheckTargetPosition() {}
	virtual void				SetNavigation( CRouting *p){}
	virtual void				SetTargetPos(const Point& pos) {}
	virtual void				ClientStopMove() {}
	virtual void				SeverStopMove() {}
	virtual void				SetTargetPosAtOnce(const Point& pos) {}
	virtual PathToSeverList*	GetPathList() { return NULL; }
protected:
	Charactor* m_pHost;

	PathList					m_path;				//行走路径
	Point						m_nextPos;			//行走的下个目标拐点
};



#endif 
