#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
	bool init();

private:
	void onBackItemCallback(Ref*);
};

class SceneTestLayer1 : public cocos2d::Layer
{
public:
	CREATE_FUNC(SceneTestLayer1);

	SceneTestLayer1();
	~SceneTestLayer1();

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;

	void testDealloc(float dt);
	void onPushScene(cocos2d::Ref* sender);
	void onPushSceneTran(cocos2d::Ref* sender);
	void onQuit(cocos2d::Ref* sender);
};


struct V3F_C4F_T2F2
{
	/// vertices (2F)
	Vec3            vertices;

	Color4F         color;
	/// tex coords (2F)
	Tex2F           texCoords;
	Tex2F           texCoords1;
};


class MultiSprite :public Sprite
{

public:

	MultiSprite();
	~MultiSprite() {}

	static MultiSprite * create(std::string baseFilename, std::string lightFilename);

	bool init(std::string filename, std::string lightTexture);

	void setLightTexture(std::string filename);
	void setLightTexture(Texture2D * texture);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	void setRectInBase(Rect rect);
	Rect getRectInBase() { return _rectInBase; }

protected:

	void renderMultiSprite();
	CustomCommand               _multiCommand;
	Texture2D *                 _lightTexture;
	Rect                        _rectInBase;
	V3F_C4F_T2F2                _verts[4];
};


class DQOPENGLSprite :public Sprite
{
public:
	DQOPENGLSprite();
	~DQOPENGLSprite() {}

	static DQOPENGLSprite * create(std::string filename);

	bool init(std::string filename);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	void setRectInBase(Rect rect);
	Rect getRectInBase() { return _rectInBase; }

protected:

	void renderMultiSprite();
	CustomCommand               _multiCommand;
	//Texture2D *                 _lightTexture;
	Rect                        _rectInBase;
	V3F_C4F_T2F2                _verts[4];
	GLProgram*		m_pProgram;
	BlendFunc        m_sBlendFunc;
	V3F_C4B_T2F_Quad* m_pQuads;
	GLushort*           m_pIndices;
	unsigned int		m_uCapacity;
	unsigned int		m_uTotalQuads;
};

class DQNodeSprite : public Node
{
	TextureAtlas*        _textureAtlas;
public:
	CREATE_FUNC(DQNodeSprite);

	DQNodeSprite();
	~DQNodeSprite();
	virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
protected:
	void onDraw(const Mat4& transform, uint32_t flags);
protected:
	CustomCommand _customCommand;
};


class DQTestFlushSprite : public Node
{
	TextureAtlas*        _textureAtlas;
	Texture2D*           m_texture;
	V3F_C4B_T2F_Quad*	m_pQuads;
	unsigned int		m_uTotalQuads;
	unsigned int		m_uCapacity;
	GLushort*           m_pIndices;

public:
	CREATE_FUNC(DQTestFlushSprite);
	void setupIndices();
	void resizeCapicity(unsigned int capacity);
	DQTestFlushSprite();
	~DQTestFlushSprite();
	virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
protected:
	void onDraw(const Mat4& transform, uint32_t flags);
protected:
	CustomCommand _customCommand;
};

#endif