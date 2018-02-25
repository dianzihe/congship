#pragma once

#include "Actor.h"
//#include "package.h"
#include "SceneObjCfg.h"

enum eSceneObjLayer
{
	eSceneObjLayer_Actor,
	eSceneObjLayer_Ground,
	eSceneObjLayer_Air,
};

//class AnimSFX;
class SceneObj : public Actor
{
public:
	SceneObj();
	virtual ~SceneObj();

	static SceneObj* node(void);
	void onLookInfoSceneObject( int nSceneObjId, Point& position, const SceneObjData* pObjData );

	virtual	void	update(float dt);
	//virtual void	draw(void);

	const SceneObjData* GetSceneObjData() { return m_pSceneObjData; }
	bool loadParticle( const char *plistFile );
protected:
	const SceneObjData*	m_pSceneObjData;
	ParticleSystemQuad* m_pParticleSystem;
};