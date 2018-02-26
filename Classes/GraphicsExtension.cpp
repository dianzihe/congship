#include "GraphicsExtension.h"
#include "ImageCenter.h"
//#include "UIBatchRenderer.h"
#ifdef _MSC_VER
	#pragma warning( disable: 4244 )
#endif
/*
Aim: Draw texture with 9-grid.
Description:
Within this process, you can use a buffer to store all 9 quads data with just one call of glDraw...
You can finish it if you understand opengl, and this just a practice I left to you! Thank you!
At this block, I do not follow the definition of Rect as you can find it out, just codes in the way you like. :)
*/
void RenderBatch9( Texture2D *tex, int u, int v, int texW, int texH, int atlasWidth, int atlasHeight, int x, int y, int nW, int nH, const Color4B& color, const Rect& rt )
{
	// this atlas is the tex rendered by gl api

	float coordinates_u_max = texW / atlasWidth;
	float coordinates_v_max = texH / atlasHeight;

	// calculate the coordinates for center block of texture
	Rect centerCoords(rt.origin.x / atlasWidth, 
		rt.origin.y / atlasHeight, 
		(rt.origin.x + rt.size.width) / atlasWidth, 
		(rt.origin.y + rt.size.height) / atlasHeight);

#ifdef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
	centerCoords.origin.x     = (2 * rt.origin.x + 1) / (2 * atlasWidth);
	centerCoords.origin.y     = (2 * rt.origin.y + 1) / (2 * atlasHeight);
	centerCoords.size.width   = (2 * (rt.origin.x + rt.size.width) - 2)  / (2 * atlasWidth);
	centerCoords.size.height  = (2 * (rt.origin.y + rt.size.height) - 2) / (2 * atlasHeight);
#else
	centerCoords.origin.x     = rt.origin.x / atlasWidth;
	centerCoords.origin.y     = rt.origin.y / atlasHeight;
	centerCoords.size.width   = (rt.origin.x + rt.size.width)  / atlasWidth;
	centerCoords.size.height  = (rt.origin.y + rt.size.height) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

	ccV3F_C4B_T2F_Quad m_sQuad;
	memset(&m_sQuad, 0xff, sizeof(m_sQuad));	

	m_sQuad.bl.colors = color;
	m_sQuad.br.colors = color;
	m_sQuad.tl.colors = color;
	m_sQuad.tr.colors = color;

	bool newBlend = false;
	if ( color.a != 255 )
	{ 
		newBlend = true;
	}

	glBindTexture(GL_TEXTURE_2D, tex->getName());
	if( newBlend ) 
	{ 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	}

	Rect texRect[9]  = {Rect(0,0,0,0)};
	Rect posRects[9] = {Rect(0,0,0,0)};	

	// It's opengl coordinates following
	// tl $
	texRect[0].origin.x     = 0.0f;
	texRect[0].origin.y     = 0.0f;                    
	texRect[0].size.width   = centerCoords.origin.x;   
	texRect[0].size.height  = centerCoords.origin.y;

	posRects[0].origin.x    = x;
	posRects[0].origin.y    = y + (nH - rt.origin.y);
	posRects[0].size.width  = x + rt.origin.x;
	posRects[0].size.height = y + nH;

	// tc $
	texRect[1].origin.x     = centerCoords.origin.x;    
	texRect[1].origin.y     = 0.0f;                     
	texRect[1].size.width   = centerCoords.size.width;
	texRect[1].size.height  = centerCoords.origin.y;    

	posRects[1].origin.x    = x + rt.origin.x;
	posRects[1].origin.y    = y + (nH - rt.origin.y);
	posRects[1].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[1].size.height = y + nH;

	// tr $
	texRect[2].origin.x     = centerCoords.size.width;  
	texRect[2].origin.y     = 0.0f;                    
	texRect[2].size.width   = coordinates_u_max;                     
	texRect[2].size.height  = centerCoords.origin.y;   

	posRects[2].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[2].origin.y    = y + (nH - rt.origin.y);
	posRects[2].size.width  = x + nW;
	posRects[2].size.height = y + nH;

	// cl $
	texRect[3].origin.x     = 0.0f;
	texRect[3].origin.y     = centerCoords.origin.y;    
	texRect[3].size.width   = centerCoords.origin.x;   
	texRect[3].size.height  = centerCoords.size.height;

	posRects[3].origin.x    = x;
	posRects[3].origin.y    = y + (texH - rt.origin.y -  rt.size.height);
	posRects[3].size.width  = x + rt.origin.x;
	posRects[3].size.height = y + (nH - rt.origin.y);

	// cc $
	texRect[4].origin.x     = centerCoords.origin.x;   
	texRect[4].origin.y     = centerCoords.origin.y;    
	texRect[4].size.width   = centerCoords.size.width;  
	texRect[4].size.height  = centerCoords.size.height; 

	posRects[4].origin.x    = x + rt.origin.x;
	posRects[4].origin.y    = y + (texH - rt.origin.y - rt.size.height);
	posRects[4].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[4].size.height = y + (nH - rt.origin.y);

	// cr $
	texRect[5].origin.x     = centerCoords.size.width;   
	texRect[5].origin.y     = centerCoords.origin.y;     
	texRect[5].size.width   = coordinates_u_max;                     
	texRect[5].size.height  = centerCoords.size.height;  

	posRects[5].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[5].origin.y    = y + (texH - rt.origin.y - rt.size.height);
	posRects[5].size.width  = x + nW;
	posRects[5].size.height = y + (nH - rt.origin.y);

	// bl $
	texRect[6].origin.x     = 0.0f;
	texRect[6].origin.y     = centerCoords.size.height;  
	texRect[6].size.width   = centerCoords.origin.x;      
	texRect[6].size.height  = coordinates_v_max;

	posRects[6].origin.x    = x;
	posRects[6].origin.y    = y;
	posRects[6].size.width  = x + rt.origin.x;
	posRects[6].size.height = y + (texH - rt.origin.y - rt.size.height);

	// bc $
	texRect[7].origin.x     = centerCoords.origin.x;      
	texRect[7].origin.y     = centerCoords.size.height;  
	texRect[7].size.width   = centerCoords.size.width;    
	texRect[7].size.height  = coordinates_v_max;                      

	posRects[7].origin.x    = x + rt.origin.x;
	posRects[7].origin.y    = y;
	posRects[7].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[7].size.height = y + (texH - rt.origin.y - rt.size.height);

	// br $
	texRect[8].origin.x     = centerCoords.size.width;     
	texRect[8].origin.y     = centerCoords.size.height;    
	texRect[8].size.width   = coordinates_u_max;                       
	texRect[8].size.height  = coordinates_v_max;                        

	posRects[8].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[8].origin.y    = y;
	posRects[8].size.width  = x + nW;
	posRects[8].size.height = y + (texH - rt.origin.y - rt.size.height);

	// all this can be in one draw call if you use buffer
	for (int i=0; i<9; i++)
	{
		Rect rect =  texRect[i];

		float x1 = posRects[i].origin.x;
		float y1 = posRects[i].origin.y;
		float x2 = posRects[i].size.width;
		float y2 = posRects[i].size.height;

		m_sQuad.bl.vertices = vertex3(x1, y1, 0);
		m_sQuad.br.vertices = vertex3(x2, y1, 0);
		m_sQuad.tl.vertices = vertex3(x1, y2, 0);
		m_sQuad.tr.vertices = vertex3(x2, y2, 0);

		long offset   = (long)&m_sQuad;

		float left	  = rect.origin.x;
		float right	  = rect.size.width;
		float top	  = rect.origin.y;
		float bottom  = rect.size.height;

		m_sQuad.bl.texCoords.u = left;
		m_sQuad.bl.texCoords.v = bottom;
		m_sQuad.br.texCoords.u = right;
		m_sQuad.br.texCoords.v = bottom;
		m_sQuad.tl.texCoords.u = left;
		m_sQuad.tl.texCoords.v = top;
		m_sQuad.tr.texCoords.u = right;
		m_sQuad.tr.texCoords.v = top;

#define kQuadSize sizeof(m_sQuad.bl)	
//XP.cocos2d.2.0
//		// vertex
//		int diff = offsetof(ccV3F_C4B_T2F, vertices);
//		glVertexPointer(3, GL_FLOAT, kQuadSize, (void*)(offset + diff));
//       
//		// color
//		diff = offsetof( ccV3F_C4B_T2F, colors);
//		glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*)(offset + diff));
//
//		// texture coordinates
//		diff = offsetof( ccV3F_C4B_T2F, texCoords);
//		glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*)(offset + diff));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	
	}

	if( newBlend ) 
	{
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
}

void DrawImage9( RenderBatchData *pRenderBatch, int x, int y, int nW, int nH, const Color4B& color, const Rect& rt )
{
	int texW = pRenderBatch->_SourceSizeX;
	int texH = pRenderBatch->_SourceSizeY;

	// calculate the coordinates for center block of texture
	Rect centerCoords(rt.origin.x, 
		rt.origin.y, 
		(rt.origin.x + rt.size.width), 
		(rt.origin.y + rt.size.height));

	Rect texRect[9]  = {Rect(0,0,0,0)};
	Rect posRects[9] = {Rect(0,0,0,0)};	

	// It's opengl coordinates following
	// tl $
	texRect[0].origin.x     = 0.0f;
	texRect[0].origin.y     = 0.0f;                    
	texRect[0].size.width   = centerCoords.origin.x;   
	texRect[0].size.height  = centerCoords.origin.y;

	posRects[0].origin.x    = x;
	posRects[0].origin.y    = y + (nH - rt.origin.y);
	posRects[0].size.width  = x + rt.origin.x;
	posRects[0].size.height = y + nH;

	// tc $
	texRect[1].origin.x     = centerCoords.origin.x;    
	texRect[1].origin.y     = 0.0f;                     
	texRect[1].size.width   = centerCoords.size.width;
	texRect[1].size.height  = centerCoords.origin.y;    

	posRects[1].origin.x    = x + rt.origin.x;
	posRects[1].origin.y    = y + (nH - rt.origin.y);
	posRects[1].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[1].size.height = y + nH;

	// tr $
	texRect[2].origin.x     = centerCoords.size.width;  
	texRect[2].origin.y     = 0.0f;                    
	texRect[2].size.width   = texW;                     
	texRect[2].size.height  = centerCoords.origin.y;   

	posRects[2].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[2].origin.y    = y + (nH - rt.origin.y);
	posRects[2].size.width  = x + nW;
	posRects[2].size.height = y + nH;

	// cl $
	texRect[3].origin.x     = 0.0f;
	texRect[3].origin.y     = centerCoords.origin.y;    
	texRect[3].size.width   = centerCoords.origin.x;   
	texRect[3].size.height  = centerCoords.size.height;

	posRects[3].origin.x    = x;
	posRects[3].origin.y    = y + (texH - rt.origin.y -  rt.size.height);
	posRects[3].size.width  = x + rt.origin.x;
	posRects[3].size.height = y + (nH - rt.origin.y);

	// cc $
	texRect[4].origin.x     = centerCoords.origin.x;   
	texRect[4].origin.y     = centerCoords.origin.y;    
	texRect[4].size.width   = centerCoords.size.width;  
	texRect[4].size.height  = centerCoords.size.height; 

	posRects[4].origin.x    = x + rt.origin.x;
	posRects[4].origin.y    = y + (texH - rt.origin.y - rt.size.height);
	posRects[4].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[4].size.height = y + (nH - rt.origin.y);

	// cr $
	texRect[5].origin.x     = centerCoords.size.width;   
	texRect[5].origin.y     = centerCoords.origin.y;     
	texRect[5].size.width   = texW;                     
	texRect[5].size.height  = centerCoords.size.height;  

	posRects[5].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[5].origin.y    = y + (texH - rt.origin.y - rt.size.height);
	posRects[5].size.width  = x + nW;
	posRects[5].size.height = y + (nH - rt.origin.y);

	// bl $
	texRect[6].origin.x     = 0.0f;
	texRect[6].origin.y     = centerCoords.size.height;  
	texRect[6].size.width   = centerCoords.origin.x;      
	texRect[6].size.height  = texH;

	posRects[6].origin.x    = x;
	posRects[6].origin.y    = y;
	posRects[6].size.width  = x + rt.origin.x;
	posRects[6].size.height = y + (texH - rt.origin.y - rt.size.height);

	// bc $
	texRect[7].origin.x     = centerCoords.origin.x;      
	texRect[7].origin.y     = centerCoords.size.height;  
	texRect[7].size.width   = centerCoords.size.width;    
	texRect[7].size.height  = texH;                      

	posRects[7].origin.x    = x + rt.origin.x;
	posRects[7].origin.y    = y;
	posRects[7].size.width  = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[7].size.height = y + (texH - rt.origin.y - rt.size.height);

	// br $
	texRect[8].origin.x     = centerCoords.size.width;     
	texRect[8].origin.y     = centerCoords.size.height;    
	texRect[8].size.width   = texW;                       
	texRect[8].size.height  = texH;                        

	posRects[8].origin.x    = x + (nW - (texW - rt.origin.x - rt.size.width));
	posRects[8].origin.y    = y;
	posRects[8].size.width  = x + nW;
	posRects[8].size.height = y + (texH - rt.origin.y - rt.size.height);

	for ( int i = 0; i < 9; ++i )
	{
		RenderBatchData _RenderBatch;
#if defined _DEBUG | DEBUG
		_RenderBatch._TextureName = pRenderBatch->_TextureName;
#endif
		_RenderBatch._BatchID = pRenderBatch->_BatchID;
		_RenderBatch._FullTexture = pRenderBatch->_FullTexture;
		CC_SAFE_RETAIN(_RenderBatch._FullTexture);
		_RenderBatch._ConvertU = texRect[i].origin.x + pRenderBatch->_ConvertU;
		_RenderBatch._ConvertV = texRect[i].origin.y + pRenderBatch->_ConvertV;
		_RenderBatch._SourceSizeX = texRect[i].size.width - texRect[i].origin.x;
		_RenderBatch._SourceSizeY = texRect[i].size.height - texRect[i].origin.y;
		_RenderBatch._SourceU = pRenderBatch->_SourceU;
		_RenderBatch._SourceV = pRenderBatch->_SourceV;
		_RenderBatch._OriginSizeX = _RenderBatch._SourceSizeX;
		_RenderBatch._OriginSizeY = _RenderBatch._SourceSizeY;
		_RenderBatch._HostImageResource = pRenderBatch->_HostImageResource;
		DrawImage( &_RenderBatch, posRects[i].origin.x, posRects[i].origin.y, posRects[i].size.width - posRects[i].origin.x, posRects[i].size.height - posRects[i].origin.y, color );
	}
}

void DrawImage9( Texture2D *tex, int x, int y, int nW, int nH, const Color4B& color, const Rect& rt )
{
	RenderBatch9(tex, 0, 0, tex->getContentSize().width, tex->getContentSize().height, tex->getPixelsWide(), tex->getPixelsHigh(), x, y, nW, nH, color, rt);
}
void RenderBatch( Texture2D *tex, int u, int v, int texW, int texH, int atlasWidth, int atlasHeight, int x, int y, int nW, int nH, const Color4B& color)
{
	static Sprite _RenderSprite;
	Rect rectTex;
	Rect rectVer;
	rectTex.origin.x = u;
	rectTex.origin.y = v;

	rectTex.size.width = texW;
	rectTex.size.height = texH;

	rectVer.origin.x = x;
	rectVer.origin.y = y;

	rectVer.size.width = nW;
	rectVer.size.height = nH;

	_RenderSprite.initWithTexture(tex, rectTex, false);

	_RenderSprite.setColor(Color3B(color.r, color.g, color.b));

	_RenderSprite.setOpacity(color.a);
    
    //_RenderSprite.updateBlendFunc();
	
	_RenderSprite.setVertexRect(rectVer);
	
	//_RenderSprite.draw();
	_RenderSprite.visit();
}


void DrawImage( RenderBatchData *pRenderBatch, int x, int y, int nW, int nH, const Color4B& color )
{
#if defined _DEBUG | DEBUG
	const char* texturName = pRenderBatch->_TextureName.c_str();
#endif
	if(pRenderBatch == NULL || pRenderBatch->_TextureName == "null")
		return;

	if(pRenderBatch->_FullTexture)
	{
#ifndef UI_BATCH_RENDERER
		RenderBatch( pRenderBatch->_FullTexture,
			pRenderBatch->_ConvertU,
			pRenderBatch->_ConvertV,
			pRenderBatch->_SourceSizeX,
			pRenderBatch->_SourceSizeY,
			pRenderBatch->_FullTexture->getContentSize().width,
			pRenderBatch->_FullTexture->getContentSize().height,
			x,
			y,
			nW,
			nH,
			color);
#else

		UIBatchRenderer::instance()->setTexture(pRenderBatch->_FullTexture);
		UIBatchRenderer::instance()->drawImage(
			pRenderBatch->_ConvertU,
			pRenderBatch->_ConvertV,
			pRenderBatch->_SourceSizeX,
			pRenderBatch->_SourceSizeY,
			pRenderBatch->_FullTexture->getContentSize().width,
			pRenderBatch->_FullTexture->getContentSize().height,
			x,
			y,
			nW,
			nH,
			color);
#endif
		return;
	}

	if(pRenderBatch->_HostImageResource == NULL)
		return;

	int border = 0;
	int squareSize = pRenderBatch->_HostImageResource->GetSquareSize();
	int perHeight = squareSize-border*2;
	int texIdx = pRenderBatch->_ConvertV / perHeight;
	int realTexY = pRenderBatch->_ConvertV % perHeight;
	int realTexSizeY = realTexY + pRenderBatch->_SourceSizeY;
	ImageResource::TextureContainer& textures = pRenderBatch->_HostImageResource->GetTextureContainer();
	if( realTexSizeY > perHeight)
	{
#ifndef UI_BATCH_RENDERER
 		RenderBatch( textures[texIdx],
 			pRenderBatch->_ConvertU,
 			realTexY + border,
 			pRenderBatch->_SourceSizeX, 
 			perHeight - realTexY,
 			squareSize, 
 			squareSize,
 			x + pRenderBatch->_SourceU, 
 			y + realTexSizeY + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV - perHeight, 
 			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
 			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY - realTexSizeY + perHeight,
 			color );
#else	
  			UIBatchRenderer::instance()->setTexture(textures[texIdx]);
  			UIBatchRenderer::instance()->drawImage(
  				pRenderBatch->_ConvertU,
  				realTexY + border,
  				pRenderBatch->_SourceSizeX, 
  				perHeight - realTexY,
  				squareSize, 
  				squareSize,
  				x + pRenderBatch->_SourceU, 
  				y + realTexSizeY + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV - perHeight, 
  				nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
  				nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY - realTexSizeY + perHeight,
  				color );
#endif

#ifndef UI_BATCH_RENDERER

     		RenderBatch( textures[texIdx + 1],
     			pRenderBatch->_ConvertU,
     			border,
     			pRenderBatch->_SourceSizeX, 
     			realTexSizeY - perHeight,
     			squareSize, 
     			textures[texIdx + 1]->getPixelsHigh(),
     			x + pRenderBatch->_SourceU, 
     			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV, 
     			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
     			realTexSizeY - perHeight,
     			color );
#else
 			UIBatchRenderer::instance()->setTexture(textures[texIdx + 1]);
 			UIBatchRenderer::instance()->drawImage(
 				pRenderBatch->_ConvertU,
 				border,
 				pRenderBatch->_SourceSizeX, 
 				realTexSizeY - perHeight,
 				squareSize, 
 				textures[texIdx + 1]->getPixelsHigh(),
 				x + pRenderBatch->_SourceU, 
 				y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV, 
 				nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
 				realTexSizeY - perHeight,
 				color );
#endif
	}
	else
	{
#ifndef UI_BATCH_RENDERER
      		RenderBatch( textures[texIdx],
      			pRenderBatch->_ConvertU, 
      			realTexY + border, 
      			pRenderBatch->_SourceSizeX, 
      			pRenderBatch->_SourceSizeY, 
      			squareSize, 
      			textures[texIdx]->getPixelsHigh(), 
      			x + pRenderBatch->_SourceU,
      			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV,
      			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
      			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY,
      			color);
#else
        		UIBatchRenderer::instance()->setTexture(textures[texIdx]);
        		UIBatchRenderer::instance()->drawImage(
        			pRenderBatch->_ConvertU, 
        			realTexY + border, 
        			pRenderBatch->_SourceSizeX, 
        			pRenderBatch->_SourceSizeY, 
        			squareSize, 
        			textures[texIdx]->getPixelsHigh(), 
        			x + pRenderBatch->_SourceU,
        			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV,
        			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
        			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY,
        			color);
#endif
	}
}

void DrawImage_Reverse( RenderBatchData *pRenderBatch, int x, int y, int nW, int nH, const Color4B& color/* = ccc4(255,255,255,255)*/ )
{
#if defined _DEBUG | DEBUG
	const char* texturName = pRenderBatch->_TextureName.c_str();
#endif
	if(pRenderBatch == NULL || pRenderBatch->_TextureName == "null")
		return;

	if(pRenderBatch->_FullTexture)
	{
#ifndef UI_BATCH_RENDERER
		RenderBatch( pRenderBatch->_FullTexture,
			pRenderBatch->_ConvertU,
			pRenderBatch->_ConvertV,
			pRenderBatch->_SourceSizeX,
			pRenderBatch->_SourceSizeY,
			pRenderBatch->_FullTexture->getContentSize().width,
			pRenderBatch->_FullTexture->getContentSize().height,
			x,
			y,
			nW,
			nH,
			color);
#else

		UIBatchRenderer::instance()->setTexture(pRenderBatch->_FullTexture);
		UIBatchRenderer::instance()->drawImage_Reverse(
			pRenderBatch->_ConvertU,
			pRenderBatch->_ConvertV,
			pRenderBatch->_SourceSizeX,
			pRenderBatch->_SourceSizeY,
			pRenderBatch->_FullTexture->getContentSize().width,
			pRenderBatch->_FullTexture->getContentSize().height,
			x,
			y,
			nW,
			nH,
			color);
#endif
		return;
	}

	if(pRenderBatch->_HostImageResource == NULL)
		return;

	int border = 0;
	int squareSize = pRenderBatch->_HostImageResource->GetSquareSize();
	int perHeight = squareSize-border*2;
	int texIdx = pRenderBatch->_ConvertV / perHeight;
	int realTexY = pRenderBatch->_ConvertV % perHeight;
	int realTexSizeY = realTexY + pRenderBatch->_SourceSizeY;
	ImageResource::TextureContainer& textures = pRenderBatch->_HostImageResource->GetTextureContainer();
	if( realTexSizeY > perHeight)
	{
#ifndef UI_BATCH_RENDERER
		RenderBatch( textures[texIdx],
			pRenderBatch->_ConvertU,
			realTexY + border,
			pRenderBatch->_SourceSizeX, 
			perHeight - realTexY,
			squareSize, 
			squareSize,
			x + pRenderBatch->_SourceU, 
			y + realTexSizeY + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV - perHeight, 
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY - realTexSizeY + perHeight,
			color );
#else	
		UIBatchRenderer::instance()->setTexture(textures[texIdx]);
		UIBatchRenderer::instance()->drawImage_Reverse(
			pRenderBatch->_ConvertU,
			realTexY + border,
			pRenderBatch->_SourceSizeX, 
			perHeight - realTexY,
			squareSize, 
			squareSize,
			x + pRenderBatch->_SourceU, 
			y + realTexSizeY + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV - perHeight, 
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY - realTexSizeY + perHeight,
			color );
#endif

#ifndef UI_BATCH_RENDERER

		RenderBatch( textures[texIdx + 1],
			pRenderBatch->_ConvertU,
			border,
			pRenderBatch->_SourceSizeX, 
			realTexSizeY - perHeight,
			squareSize, 
			textures[texIdx + 1]->getPixelsHigh(),
			x + pRenderBatch->_SourceU, 
			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV, 
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			realTexSizeY - perHeight,
			color );
#else
		UIBatchRenderer::instance()->setTexture(textures[texIdx + 1]);
		UIBatchRenderer::instance()->drawImage_Reverse(
			pRenderBatch->_ConvertU,
			border,
			pRenderBatch->_SourceSizeX, 
			realTexSizeY - perHeight,
			squareSize, 
			textures[texIdx + 1]->getPixelsHigh(),
			x + pRenderBatch->_SourceU, 
			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV, 
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			realTexSizeY - perHeight,
			color );
#endif
	}
	else
	{
#ifndef UI_BATCH_RENDERER
		RenderBatch( textures[texIdx],
			pRenderBatch->_ConvertU, 
			realTexY + border, 
			pRenderBatch->_SourceSizeX, 
			pRenderBatch->_SourceSizeY, 
			squareSize, 
			textures[texIdx]->getPixelsHigh(), 
			x + pRenderBatch->_SourceU,
			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV,
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY,
			color);
#else
		UIBatchRenderer::instance()->setTexture(textures[texIdx]);
		UIBatchRenderer::instance()->drawImage_Reverse(
			pRenderBatch->_ConvertU, 
			realTexY + border, 
			pRenderBatch->_SourceSizeX, 
			pRenderBatch->_SourceSizeY, 
			squareSize, 
			textures[texIdx]->getPixelsHigh(), 
			x + pRenderBatch->_SourceU,
			y + pRenderBatch->_OriginSizeY - pRenderBatch->_SourceSizeY - pRenderBatch->_SourceV,
			nW - pRenderBatch->_OriginSizeX + pRenderBatch->_SourceSizeX,
			nH - pRenderBatch->_OriginSizeY + pRenderBatch->_SourceSizeY,
			color);
#endif
	}
}

void DrawImage2( Texture2D *tex, float u1, float v1, float u2, float v2, int x1, int y1, int x2, int y2, const Color4B& color )
{	
#ifndef UI_BATCH_RENDERER
	RenderBatch(
		tex, 
		0, 
		0, 
		tex->getContentSize().width,
		tex->getContentSize().height,
		tex->getPixelsWide(),
		tex->getPixelsHigh(),
		x1,
		y1,
		x2,
		y2,
		color);
#else
	UIBatchRenderer::instance()->setTexture(tex);
	UIBatchRenderer::instance()->drawImage2(
		u1, 
		v1,
		u2,
		v2,
		tex->getContentSize().width,
		tex->getContentSize().height,
		tex->getPixelsWide(),
		tex->getPixelsHigh(),
		x1,
		y1,
		x2,
		y2,
		color);
#endif
}

void DrawImage( Texture2D *tex, int x, int y, int nW, int nH, const Color4B& color )
{
#ifndef UI_BATCH_RENDERER
	RenderBatch(
		tex, 
		0, 
		0, 
		tex->getContentSize().width,
		tex->getContentSize().height,
		tex->getPixelsWide(),
		tex->getPixelsHigh(),
		x,
		y,
		nW,
		nH,
		color);
#else
	UIBatchRenderer::instance()->setTexture(tex);
	UIBatchRenderer::instance()->drawImage(
		0, 
		0, 
		tex->getContentSize().width,
		tex->getContentSize().height,
		tex->getPixelsWide(),
		tex->getPixelsHigh(),
		x,
		y,
		nW,
		nH,
		color);
#endif

}
