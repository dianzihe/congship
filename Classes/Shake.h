#pragma once
#include "base.h"
#include "cocos2d.h"

using namespace cocos2d;

enum	eShakeType
{
	eShake_Type_Undefined,				//��
	eShake_Type_Direction,				//���򶶶�
	eShake_Type_AxisX,					//X�ᶶ��
	eShake_Type_AxisY,					//Y�ᶶ��
	eShake_Type_NotDirection,		//���򶶶� 
};


class CShake
{
public:
	CShake();
	~CShake();

	static CShake & instance()
	{
		static CShake s;
		return s;
	}

	void	StartShake(eShakeType type, Point dir = CCPointZero);
	void	StopShake();
	void	Update(float dt);

	Point	getCurPos(){ return m_curPos; };
	bool	IsShake(){ return m_bIsShake; };

private:
	eShakeType		m_eType;
	Point			m_curPos;
	Point			m_curDir;
	bool					m_bIsShake;
	float					m_fTime;
	int					m_iNonceDis;
	int					m_iCount;

	float					m_fTimeCounter;				//�����ƶ�ʱ�������
	float					m_fTimeCounterAll;			//���ж���ʱ�������
};