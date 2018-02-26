#pragma once

#include "base.h"
#include "cocos2d.h"

using namespace cocos2d;

#define UI_BATCH_RENDERER   //���������������UI��������Ⱦ��

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
	ccV3F_C4B_T2F_Quad* m_pQuads;
	GLushort*           m_pIndices;
	unsigned int		m_uTotalQuads;
	unsigned int		m_uCapacity;
	Texture2D*		m_pTexture;

	BlendFunc        m_sBlendFunc;
};