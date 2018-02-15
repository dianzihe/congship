//////////////////////////////////////////////////////////////////////////
// 物件定义
#pragma once

#include "base.h"
#include <map>
#include <string>
#include "Singleton.h"

using namespace std;

enum SceneObjType
{
	eSceneObjType_Particle,
	eSceneObjType_Animation,
};

struct SceneObjData
{
	int			m_nID;
	SceneObjType m_Type;
	string		m_Name;
	int			m_AnimationID;
	float		m_Scale;
	int			m_Layer;
};
typedef std::map< int, SceneObjData >	MAP_SceneObj;


class SceneObjCfg : public Singleton<SceneObjCfg, Tag_Singleton_Auto>
{
public:
	SceneObjCfg();
	~SceneObjCfg();

	static SceneObjCfg& instance( void )
	{
		static SceneObjCfg	s;
		return s;
	}

	bool init( const char* pszItemCfgName );

	const SceneObjData* findSceneObjDataByID( int nID )const
	{
		MAP_SceneObj::const_iterator iterFind = m_itemDatas.find( nID );
		return iterFind != m_itemDatas.end() ? &(iterFind->second) : NULL;
	}

	MAP_SceneObj & getSceneObjCfgMap(){ return m_itemDatas;};
private:
	MAP_SceneObj m_itemDatas;

};
