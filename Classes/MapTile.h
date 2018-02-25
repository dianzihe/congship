#pragma once

#include "base.h"
#include "cocos2d.h"
//#include "BusPathSeeker.h"
#include "MapSettingCfg.h"
#include "MapCfg.h"
#include "ImageCenter.h"
//class CCamera;
//class CPlayer;
class ActorManager;
class Actor;

using namespace cocos2d;
class MapTile : public Node
{
public:
	MapTile()
		: m_sprite(NULL)
		, m_loaded(false)
		, m_totalUpdateTime(0.0f)
		, m_lastUpdateTime(0.0f)
	{
	}

	~MapTile()
	{
		releaseSprite();
	}

	void onAsyncLoadedTexture(Texture2D* pTexture);

	void SetRect(const Rect& rect);

	void Load(const char* pszFileName, const Rect& rect);
	
	void unLoad();

	//void draw();
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void setUsingTextureWhenUnloaded(RenderBatchData* pBatchData);

	void setIndexingData(int xIndex, int yIndex, int width, int height);

	void tick(float deltaTime);
private:
	void releaseSprite();
private:
	RenderBatchData m_RenderData;
	Sprite* m_sprite;
	std::string m_textureName;
	bool m_loaded;
	Rect m_rect;
	float m_xIndex;
	float m_yIndex;
	float m_width;
	float m_height;
	float m_totalUpdateTime;
	float m_lastUpdateTime;
};
