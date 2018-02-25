#include "SceneObj.h"
#include "SceneObjCfg.h"
#include "GameScene.h"
#include "ActorManager.h"
#include "Map.h"
//#include "../BaseModule/SFX/SFXModule.h"
//#include "SceneInstance.h"
//#include "./Task.h"
#include "Text.h"
#include "TextDef.h"
#include "cocos2d.h"

using namespace cocos2d;

SceneObj::SceneObj()
: m_pSceneObjData(NULL)
, m_pParticleSystem(NULL)
{
	setActorType(ACTORTYPE_SCENEOBJECT);
}

SceneObj::~SceneObj()
{
	if (m_pParticleSystem)
		m_pParticleSystem->release();		
}

SceneObj* SceneObj::node( void )
{
	SceneObj* pRet = new SceneObj();
	pRet->autorelease();
	return pRet;
}

void SceneObj::onLookInfoSceneObject( int nSceneObjId, Point& position, const SceneObjData* pObjData )
{
	if( !pObjData ){
		log( "SceneObj::onLookInfoSceneObjList SceneObj_data_id[%d] can not find", nSceneObjId );
		return;
	}
	m_pSceneObjData = pObjData;

	ActorID id = rand() * rand();
	setActorID( id );

	setDataID( nSceneObjId );

	setActorType(ACTORTYPE_SCENEOBJECT);

	setScale( m_pSceneObjData->m_Scale );

	if(pObjData->m_Type == eSceneObjType_Particle){
		loadParticle(m_pSceneObjData->m_Name.c_str());
	}else if(pObjData->m_Type == eSceneObjType_Animation){
		m_animation.SetHostEventHandler(this);
		m_animation.LoadASprite(m_pSceneObjData->m_AnimationID, ACTORTYPE_SCENEOBJECT);
		m_animation.setAnim(0);
	}

	if(pObjData->m_Layer == eSceneObjLayer_Actor){
		GameScene::GetActorManager()->AddActor(this);
		SetNewPos(position);
	}

	setPosition(position);
	log( "onLookInfoSceneObjList [%lld %s] pos[%d %d]", 
		getActorID(),
		GetName().c_str(),
		(int)getPosition().x,
		(int)getPosition().y );

}

void SceneObj::update(float dt)
{
	if (m_pParticleSystem)
	{
		m_pParticleSystem->update(dt);
	}
	Actor::update(dt);
	if(eSceneObjLayer_Air == m_pSceneObjData->m_Layer){
		//GameScene::instance().GetCurMap().addActorToAirNode(this);
		//GameScene::instance().GetActorManager()->AddActor(this);
	}else if(eSceneObjLayer_Ground == m_pSceneObjData->m_Layer){
		//GameScene::GetScene()->GetCurMap()->addActorToGroundNode(this);
	}
}

bool SceneObj::loadParticle( const char *plistFile )
{
	assert(m_pParticleSystem == NULL);
	char name[256];
	sprintf(name, "Particle/%s.plist", plistFile);
	m_pParticleSystem = new ParticleSystemQuad();
	if(!m_pParticleSystem->initWithFile(name))
		SAFE_DELETE(m_pParticleSystem);
	return true;
}
/*
void SceneObj::draw( void )
{
	Actor::draw();
	if(m_pParticleSystem)             
		m_pParticleSystem->visit();
}
*/