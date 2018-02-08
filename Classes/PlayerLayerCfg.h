//////////////////////////////////////////////////////////////////////////
// 玩家职业定义
#pragma once

#include "base.h"
//#include "PlayerDefine.h"
#include "Animation.h"
#include "AnimDef.h"
#include <map>

//////////////////////////////////////////////////////////////////////////
// 玩家渲染层次
struct PlayerLayerDataPerAction
{
	AnimPart _AnimPartSequence[eAnimPart_Count]; 
	AnimPlayer _AnimAction;
};

struct PlayerLayerDataPerPlayer
{
	typedef std::vector<PlayerLayerDataPerAction> PlayerLayerGroup;
	PlayerLayerGroup mActionLayerData[NUM_ANIMS_LAYER];
};

class PlayerLayerCfg
{
public:
	PlayerLayerCfg();
	~PlayerLayerCfg();

	static PlayerLayerCfg& instance()
	{
		static PlayerLayerCfg s;
		return s;
	}

	bool			init( const char* pszPlayerLayerCfgName );

	// Gender : 0-male 1-female
	inline AnimPart		GetAnimPartBySequence( int playerId, int nGender, AnimPlayer action, int sequence, int animaLayerIndex )
	{
		int nPlayerIndex = playerId * 2 + nGender;
		if(action >= ANIM_PLAYER_ATTACK2_DOWN && action <= ANIM_PLAYER_ATTACK6_UP)
		{
			action = (AnimPlayer)(action % 3);
		}
		assert(animaLayerIndex >=0 && animaLayerIndex < (int)mPlayerLayerData[nPlayerIndex].mActionLayerData[action].size());
		return mPlayerLayerData[nPlayerIndex].mActionLayerData[action][animaLayerIndex]._AnimPartSequence[sequence];
	}

protected:
	std::map<std::string, AnimPart> mAnimIndexMap;
	std::map<std::string, AnimPlayer> mAnimActionMap;
	std::vector<PlayerLayerDataPerPlayer> mPlayerLayerData;
};
