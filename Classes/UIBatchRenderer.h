#pragma once

#include "base.h"
#include "cocos2d.h"

using namespace cocos2d;

//#define UI_BATCH_RENDERER   //定义这个宏来开启UI的批次渲染。

#define kCCShader_PositionTextureColor            "ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest    "ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor                    "ShaderPositionColor"
#define kCCShader_PositionTexture                "ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor        "ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color        "ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor                "ShaderPosition_uColor"

class UIBatchRenderer
{
public:
	UIBatchRenderer();
	~UIBatchRenderer();
	
	static UIBatchRenderer* instance()
	{
		static UIBatchRenderer inst;
		return &inst;
	}
	void initilize();

	void unintilize();

	void setTexture(Texture2D* pTexture);
	
	void drawImage(int u, int v, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int x, int y, int width, int height, const ccColor4B& color);
	
	void drawImage_Reverse(int u, int v, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int x, int y, int width, int height, const ccColor4B& color);

	void drawImage2(float u1, float v1, float u2, float v2, int texWidth, int texHeight, int atlasWidth, int atlasHeight, int mx1, int my1, int mx2, int my2, const ccColor4B& color);

	void flush();

	void setShader(GLProgram* program);

private:
	void resizeCapicity(unsigned int capacity);
	void setupIndices();
	//void setupVBOandVAO();

private:
	GLProgram*		m_pProgram;
	V3F_C4B_T2F_Quad* m_pQuads;
	GLushort*           m_pIndices;
	unsigned int		m_uTotalQuads;
	unsigned int		m_uCapacity;
	Texture2D*		m_pTexture;

	BlendFunc        m_sBlendFunc;
};