#ifndef _WFadeOutHurtLable_include_file_
#define _WFadeOutHurtLable_include_file_

#include "typedefine.h"
#include "WBdefine.h"

class WFadeOutHurtLabel :public Node
{
private:
	virtual bool init();
	static WFadeOutHurtLabel *node();

public:
	WFadeOutHurtLabel();
	~WFadeOutHurtLabel();

	//    virtual void onEnter();
	//    virtual void onExit();
	//    
	//    
	enum
	{
		E_NORMAL = 0,//普通
		E_CRIT,//爆击
		E_SUPER,//超爆击
	};

	static WFadeOutHurtLabel *LabelWithString(Point pixelpos, int hurt, int hurtLevel);



};


#endif