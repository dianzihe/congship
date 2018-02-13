#ifndef _IMOTIONMODULE_H__
#define _IMOTIONMODULE_H__


enum MotionType
{
	eMotionType_NULL,
	eMotionType_Routing,
	eMotionType_Direction,
	eMotionType_Teleport,
	eMotionType_Num,
};


class IMotionModule
{
public:
	virtual ~IMotionModule() {}

	virtual bool CanBeCancel() = 0;

	virtual void EnterMotion() = 0;

	virtual void UpdateMotion( float dt ) = 0;

	virtual void ExitMotion() = 0;

};


#endif 
