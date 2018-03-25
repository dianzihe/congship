#ifndef _DQMOTIONMANAGER_H__
#define _DQMOTIONMANAGER_H__

#include "IMotionModule.h"

class Charactor;

class DQMotionManager
{
public:
	DQMotionManager(Charactor* pHost);
	~DQMotionManager();

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
