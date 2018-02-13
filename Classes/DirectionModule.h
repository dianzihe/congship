#ifndef _DIRECTIONMODULE_H__
#define _DIRECTIONMODULE_H__

#include "base.h"
#include "IMotionModule.h"
#include "AnimDef.h"
#include "Charactor.h"

#define		DirectionArray_Count		16

class Charactor;
class DirectionModule : public IMotionModule
{
public:
	DirectionModule(Charactor* pHost);
	virtual ~DirectionModule();

public:
	virtual bool CanBeCancel();

	virtual void EnterMotion();

	virtual void UpdateMotion( float dt );

	virtual void ExitMotion();

public:
	eDirection GetDirection() { return mCurDirection; } 
	void SetDirection(eDirection dir);

	static void initDirectionVec();

private:
	bool	UpdateDirection( eDirection dir, float realSpeed, bool isEnter=true );
public:
	eDirection mOldDirection;
	eDirection mCurDirection;
	eDirection m_RealDirection;

	Charactor* m_pHost;

	static Point m_sDirVec[16];

};



#endif 
