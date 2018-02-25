#include "MapTile.h"
//#include "CCMemoryMonitor.h"

void MapTile::onAsyncLoadedTexture( Texture2D* pTexture )
{
	m_sprite = new Sprite();

	// 保存当前引用计数
	unsigned int rt = pTexture->getReferenceCount();

	if (m_sprite->initWithTexture(pTexture, m_rect)){
		// 如果这个时候增加了引用计数
		unsigned int rt1 = pTexture->getReferenceCount();

		if (rt1 = rt + 1){
			// 降低一次。
			pTexture->release();
		}

		m_loaded = true;
		setContentSize(m_sprite->getContentSize());
	}else{
		m_loaded = false;
	}
}

void MapTile::Load( const char* pszFileName, const Rect& rect )
{
	m_rect = rect;
	m_textureName = pszFileName;
	if (pszFileName && FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(pszFileName).c_str())){
		/*
		if (CCMemoryMonitor::sharedMemoryMonitor()->availableMemory() > 5.0f){
			CCTextureCache::sharedTextureCache()->addImageAsync(pszFileName, this, (SEL_CallFuncO)(&MapTile::onAsyncLoadedTexture));
			m_loaded = true;
		}else{
			m_loaded = false;
		}
		*/
	}

	setContentSize(rect.size);
}

void MapTile::unLoad()
{
	releaseSprite();
	m_loaded = false;
}

//void MapTile::draw()
void MapTile::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	if (!m_loaded || m_sprite == NULL){
		if(m_RenderData._FullTexture == NULL)
			return;
		static Sprite _RenderSprite;
		Rect rect;
		rect.origin.x = (m_xIndex / m_width) * m_RenderData._OriginSizeX;
		rect.origin.y = (m_yIndex / m_height) * m_RenderData._OriginSizeY;
		rect.size.width = m_RenderData._OriginSizeX / m_width;
		rect.size.height = m_RenderData._OriginSizeY / m_height;

		_RenderSprite.initWithTexture(m_RenderData._FullTexture, rect, false);

		rect.origin.x = 0;
		rect.origin.y = 0;
		rect.size.width = m_rect.size.width;
		rect.size.height = m_rect.size.height;
		_RenderSprite.setVertexRect(rect);
//		_RenderSprite.setVertexRect
//		_RenderSprite.draw();
	}else{
		//m_sprite->setBlendFunc().src = GL_ONE;
		//m_sprite->getBlendFunc().dst = GL_ZERO;
		m_sprite->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
		//m_sprite->draw();
	}
}

void MapTile::setUsingTextureWhenUnloaded( RenderBatchData* pBatchData )
{
	if (pBatchData)
		m_RenderData = *pBatchData;
}

void MapTile::setIndexingData( int xIndex, int yIndex, int width, int height )
{
	m_xIndex = (float)xIndex;
	m_yIndex = (float)yIndex;
	m_width = (float)width;
	m_height = (float)height;
}

void MapTile::releaseSprite()
{
	if (m_sprite){
		m_sprite->release();
		m_sprite = NULL;
	}
}

void MapTile::SetRect( const Rect& rect )
{
	m_rect = rect;
}

void MapTile::tick(float deltaTime)
{
	m_totalUpdateTime += deltaTime;
	if (m_totalUpdateTime - m_lastUpdateTime > 2){
		m_lastUpdateTime = m_totalUpdateTime;
		/*
		if (CCMemoryMonitor::sharedMemoryMonitor()->availableMemory() > 5.0f){
			if (!m_loaded){
				CCTextureCache::sharedTextureCache()->addImageAsync(m_textureName.c_str(), this, (SEL_CallFuncO)(&MapTile::onAsyncLoadedTexture));
				m_loaded = true;
			}
		}
		*/
		m_loaded = true;
	}
}