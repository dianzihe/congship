#ifndef _MOTIONMANAGER_H__
#define _MOTIONMANAGER_H__

#include "IMotionModule.h"
#include "Charactor.h"
//#include "RoutingModule.h"
#include "DirectionModule.h"
//#include "HeroRoutingModule.h"
//#include "TeleportModule.h"


class MotionManager
{
public:
	MotionManager(Charactor* pHost);
	~MotionManager();

public:
	inline IMotionModule* GetMotionModule( MotionType nMotionType ) { return mMotionModule[nMotionType]; }
	
	void Update(float dt);

	bool IsCurMotionCanExit();

	void ChangeToMotion( MotionType nMotion );

	MotionType GetCurMotion() { return mCurMotion; }

	void StopMotion();

protected:
	IMotionModule* mMotionModule[eMotionType_Num];
	MotionType mCurMotion;
	MotionType mNewMotion;
	Charactor* m_pHost;

};


#endif 
