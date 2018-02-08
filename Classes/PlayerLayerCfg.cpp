
#include "PlayerLayerCfg.h"
//#include "BinTable.h"

PlayerLayerCfg::PlayerLayerCfg()
{

}

PlayerLayerCfg::~PlayerLayerCfg()
{
	mPlayerLayerData.clear();
}

bool PlayerLayerCfg::init( const char* pszPlayerLayerCfgName )
{
	mAnimIndexMap["p"] = eAnimPart_Body;
	mAnimIndexMap["P"] = eAnimPart_Body;
	mAnimIndexMap["w"] = eAnimPart_Weapon;
	mAnimIndexMap["W"] = eAnimPart_Weapon;
	mAnimIndexMap["g"] = eAnimPart_Wing;
	mAnimIndexMap["G"] = eAnimPart_Wing;
	mAnimIndexMap["m"] = eAnimPart_Mount;
	mAnimIndexMap["M"] = eAnimPart_Mount;
	mAnimIndexMap["x"] = eAnimPart_Pet;
	mAnimIndexMap["X"] = eAnimPart_Pet;

	mAnimActionMap["attack_down"] = ANIM_PLAYER_ATTACK1_DOWN;
	mAnimActionMap["attack_left"] = ANIM_PLAYER_ATTACK1_LEFT;
	mAnimActionMap["attack_up"] = ANIM_PLAYER_ATTACK1_UP;
	mAnimActionMap["cast_down"] = ANIM_PLAYER_ATTACK2_DOWN;
	mAnimActionMap["cast_left"] = ANIM_PLAYER_ATTACK2_LEFT;
	mAnimActionMap["cast_up"] = ANIM_PLAYER_ATTACK2_UP;
	mAnimActionMap["cast_down"] = ANIM_PLAYER_ATTACK3_DOWN;
	mAnimActionMap["cast_left"] = ANIM_PLAYER_ATTACK3_LEFT;
	mAnimActionMap["cast_up"] = ANIM_PLAYER_ATTACK3_UP;
	mAnimActionMap["dead_down"] = ANIM_PLAYER_DEAD_DOWN;
	mAnimActionMap["dead_left"] = ANIM_PLAYER_DEAD_LEFT;
	mAnimActionMap["dead_up"] = ANIM_PLAYER_DEAD_UP;
	mAnimActionMap["idle_down"] = ANIM_PLAYER_IDLE_DOWN;
	mAnimActionMap["idle_left"] = ANIM_PLAYER_IDLE_LEFT;
	mAnimActionMap["idle_up"] = ANIM_PLAYER_IDLE_UP;
	mAnimActionMap["mountidle_down"] = ANIM_PLAYER_MOUNTIDLE_DOWN;
	mAnimActionMap["mountidle_left"] = ANIM_PLAYER_MOUNTIDLE_LEFT;
	mAnimActionMap["mountidle_up"] = ANIM_PLAYER_MOUNTIDLE_UP;
	mAnimActionMap["mountmove_down"] = ANIM_PLAYER_MOUNTMOVE_DOWN;
	mAnimActionMap["mountmove_left"] = ANIM_PLAYER_MOUNTMOVE_LEFT;
	mAnimActionMap["mountmove_up"] = ANIM_PLAYER_MOUNTMOVE_UP;
	mAnimActionMap["move_down"] = ANIM_PLAYER_MOVE_DOWN;
	mAnimActionMap["move_left"] = ANIM_PLAYER_MOVE_LEFT;
	mAnimActionMap["move_up"] = ANIM_PLAYER_MOVE_UP;
	mAnimActionMap["sitdown_up"] = ANIM_PLAYER_SIT1_DOWN;
	mAnimActionMap["sitdown_left"] = ANIM_PLAYER_SIT2_LEFT;

	if( pszPlayerLayerCfgName == NULL )
		return false;

	TTableGroup group;
	group.Load(pszPlayerLayerCfgName);

	TTable* pTable =  group.GetTable( "Sheet1" );
	if( !pTable )
		return false;

	mPlayerLayerData.resize(8);
	char key[64] = {0};
	for (int j = 0; j < 4; ++j ) // 四个职业
	{
		for (int n = 0; n < 2; ++n ) // 性别
		{
			int nPlayerIndex = (j * 2) + n;
			PlayerLayerDataPerPlayer* pPlayerLayerData = &mPlayerLayerData[nPlayerIndex];
			char nGender = n ? 'f' : 'm';
			for( int i = 0; i < pTable->m_recordCount; ++i )
			{
				int nRecordIndex = i + 1; // 动作列表
				std::string nAction = pTable->GetFieldString(nRecordIndex, "Animation");
				int layerGroup = 0;
				AnimPlayer nActionIdx;
				if(mAnimActionMap.find(nAction) == mAnimActionMap.end())
				{
					std::string actionName = nAction.substr(0, nAction.find(":"));
					nActionIdx = mAnimActionMap[actionName];
					actionName += ":%d";
					sscanf(nAction.c_str(), actionName.c_str(), &layerGroup);
					layerGroup--;
					assert(layerGroup >= 0);
				}
				else
				{
					nActionIdx = mAnimActionMap[nAction];
				}

				if((int)pPlayerLayerData->mActionLayerData[nActionIdx].size() <= layerGroup)
					pPlayerLayerData->mActionLayerData[nActionIdx].resize(layerGroup+1);
				for (int m = 0; m < eAnimPart_Count; ++m ) // 五种装备,武器特效插在武器之前
				{
					sprintf(key, "p%d%d_%c", j+1, m+1, nGender );
					AnimPart nAnimPart = mAnimIndexMap[pTable->GetFieldString( nRecordIndex, key )];
					pPlayerLayerData->mActionLayerData[nActionIdx][layerGroup]._AnimAction = nActionIdx;
					pPlayerLayerData->mActionLayerData[nActionIdx][layerGroup]._AnimPartSequence[m] = nAnimPart;
				}
			}
		}
	}

	mAnimIndexMap.clear();
	mAnimActionMap.clear();
	return true;
}

