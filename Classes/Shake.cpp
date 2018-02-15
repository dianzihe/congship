#include "Shake.h"
#include "GameScene.h"
//#include "Camera.h"

#define		Shake_Start_Dis		14				//抖动开始距离 （单位像素）
#define		Shake_End_Dis			1					//抖动结束距离 （单位像素）
#define		Shake_Speed			0.02f			//抖动速度（单位秒）
#define		Shake_Once_DecDis	4.0f				//抖动速度（单位秒）

CShake::CShake():
m_bIsShake(false)
{

}

CShake::~CShake()
{

}

void	CShake::StartShake(eShakeType type, CCPoint dir)
{
	switch( type )
	{
	case eShake_Type_Direction:
		{
			if( ! dir.equals(Point(0, 0)) )
			{
				float dis = sqrtf(dir.x*dir.x + dir.y*dir.y);
				m_curDir.x = dir.x / dis;
				m_curDir.y = dir.y / dis;
			}
			else
				return;
		}
		break;
		
	case eShake_Type_AxisX:
		{
			m_curDir = CCPointMake(1.0f, 0.0f);
		}
		break;

	case eShake_Type_AxisY:
		{
			m_curDir = CCPointMake(0.0f, 1.0f);
		}
		break;

	case eShake_Type_NotDirection:
		{

		}
		break;

	default:
		return;
	}
	m_eType = type;
	m_bIsShake = true;
	m_fTimeCounter = 0.0f;
	m_fTimeCounterAll = 0.0f;
	m_iNonceDis = Shake_Start_Dis;
	m_iCount = 0;
	//m_curPos = GameScene::instance().GetCamera()->getCurPos();
}

void	CShake::StopShake()
{
	m_bIsShake = false;
}

void	CShake::Update(float dt)
{
	/*x
	if(!IsShake())
		return;

	m_fTimeCounter += dt;

	if( m_fTimeCounter < Shake_Speed )
	{
		return;
	}

	CCPoint cameraPos = GameScene::instance().GetCamera()->getCurPos();

	m_iCount += 1;
	if( m_iCount%2 == 0 )
	{
		m_curPos = cameraPos;
	}
	else
	{
		if( m_eType == eShake_Type_NotDirection )
		{
			CCPoint dir;
			dir.x = (float)(rand()%10);
			dir.y = (float)(rand()%10);
			float dis = sqrtf(dir.x*dir.x + dir.y*dir.y);
			m_curDir.x = dir.x / dis;
			m_curDir.y = dir.y / dis;
		}
		m_curPos.x = cameraPos.x + m_curDir.x*m_iNonceDis;
		m_curPos.y = cameraPos.y + m_curDir.y*m_iNonceDis;
		m_iNonceDis -= (int)Shake_Once_DecDis;
	}

	m_fTimeCounter = 0.0f;
	if(m_iNonceDis <= Shake_End_Dis)
	{
		StopShake();
		return;
	}
	*/
}