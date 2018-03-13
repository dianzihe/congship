#include "GameOverScene.h"
#include "GameScene.h"


SceneTestLayer1::SceneTestLayer1()
{
	auto item1 = MenuItemFont::create("Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
	auto item2 = MenuItemFont::create("Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
	auto item3 = MenuItemFont::create("Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));

	auto menu = Menu::create(item1, item2, item3, nullptr);
	menu->alignItemsVertically();

	addChild(menu);

	auto s = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("Origin/chouqian.png");
	addChild(sprite);
	sprite->setPosition(Vec2(s.width - 40, s.height / 2));
	auto rotate = RotateBy::create(2, 360);
	auto repeat = RepeatForever::create(rotate);
	sprite->runAction(repeat);

	schedule(CC_SCHEDULE_SELECTOR(SceneTestLayer1::testDealloc));
}

void SceneTestLayer1::testDealloc(float dt)
{
	//CCLOG("SceneTestLayer1:testDealloc");
}

void SceneTestLayer1::onEnter()
{
	CCLOG("SceneTestLayer1#onEnter");
	Layer::onEnter();
}

void SceneTestLayer1::onEnterTransitionDidFinish()
{
	CCLOG("SceneTestLayer1#onEnterTransitionDidFinish");
	Layer::onEnterTransitionDidFinish();
}

SceneTestLayer1::~SceneTestLayer1()
{
	//NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(Ref* sender)
{
	//auto scene = SceneTestScene::create(2);
	//Director::getInstance()->pushScene(scene);
}

void SceneTestLayer1::onPushSceneTran(Ref* sender)
{
	//auto scene = SceneTestScene::create(2);
	//Director::getInstance()->pushScene(TransitionSlideInT::create(1, scene));
}


void SceneTestLayer1::onQuit(Ref* sender)
{
	//getCocosApp()->exit();
	//CCDirector::getInstance()->poscene();

	//// HA HA... no more terminate on sdk v3.0
	//// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
	//if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
	//    [[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	Layer::init();

	log("game over!");

	auto winSize = Director::getInstance()->getWinSize();

	//添加背景
	auto bg = Sprite::createWithSpriteFrameName("gameover.png");
	bg->setScaleX(winSize.width / bg->getContentSize().width);
	bg->setScaleY(winSize.height / bg->getContentSize().height);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);

	//返回游戏按钮
	auto backlabel = Label::createWithTTF("Try again", "fonts/Marker Felt.ttf", 36);
	backlabel->setColor(Color3B::BLACK);
	auto backItem = MenuItemLabel::create(backlabel);
	backItem->setTarget(this, menu_selector(GameOverScene::onBackItemCallback));
	backItem->setPosition(Vec2(winSize.width / 2 - backItem->getContentSize().width / 2 - 15, -winSize.height / 2 + backItem->getContentSize().height / 2 + 10)); //位于左下角
	auto menu = Menu::create(backItem, nullptr);
	addChild(menu);

	//显示本次分数，位于中间
	auto score = UserDefault::getInstance()->getStringForKey("LastScore");

	auto labelscore = Label::createWithTTF(score, "fonts/Marker Felt.ttf", 36);
	labelscore->setColor(Color3B::BLACK);
	labelscore->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 50));
	addChild(labelscore);
	
	//显示最佳分数，位于左上
	auto bestscore = UserDefault::getInstance()->getStringForKey("BestScore");

	auto labelbestscore = Label::createWithSystemFont(bestscore, "Arial", 36);
	labelbestscore->setColor(Color3B::BLACK);
	labelbestscore->setPosition(Vec2(labelbestscore->getContentSize().width / 2 + 50, winSize.height - labelbestscore->getContentSize().height / 2 - 80));
	addChild(labelbestscore);

	return true;
}

void GameOverScene::onBackItemCallback(Ref*)
{
	//返回游戏
	/*
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
	*/
}


static unsigned short quadIndices[] = { 0, 1, 2, 3, 2, 1 };



MultiSprite::MultiSprite() :
Sprite(),
_lightTexture(nullptr)
{

}

MultiSprite * MultiSprite::create(std::string filename, std::string lightTexture)
{
	MultiSprite * sprite = new MultiSprite();
	if (sprite && sprite->init(filename, lightTexture)) {
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool MultiSprite::init(std::string baseFilename, std::string lightFilename)
{
	bool ret = Sprite::initWithFile(baseFilename);

	const char fragmentShader[] =
		"#ifdef GL_ES                                                   \n"
		"precision lowp float;                                          \n"
		"#endif                                                         \n"
		"varying vec4 v_fragmentColor;                                  \n"
		"varying vec2 v_texCoord;                                       \n"
		"varying vec2 v_texCoord1;                                      \n"
		"void main()                                                    \n"
		"{                                                              \n"
		"   vec4 baseColor;                                             \n"
		"   baseColor = texture2D( CC_Texture0, v_texCoord )*v_fragmentColor;                               \n"
		"   vec4 lightColor;                                            \n"
		"   if  (v_texCoord1.x>1.0 || v_texCoord1.y>1.0 || v_texCoord1.y < 0.0 || v_texCoord1.x<0.0 )                                        \n"
		"   {                                                           \n"
		"       lightColor = vec4(0, 0, 0, 1);                          \n"
		"   }                                                           \n"
		"   else                                                        \n"
		"   {                                                           \n"
		"       lightColor = texture2D( CC_Texture1, v_texCoord1 );     \n"
		"   }                                                           \n"
		"   gl_FragColor = baseColor * (lightColor + 0.25);             \n"
		"                                                               \n"
		"}                                                              \n";

	const char vectShader[] =
		"attribute vec4 a_position;                                     \n"
		"attribute vec2 a_texCoord;                                     \n"
		"attribute vec2 a_texCoord1;                                    \n"
		"attribute vec4 a_color;                                        \n"
		"#ifdef GL_ES                                                   \n"
		"varying lowp vec4 v_fragmentColor;                             \n"
		"varying mediump vec2 v_texCoord;                               \n"
		"varying mediump vec2 v_texCoord1;                              \n"
		"#else                                                          \n"
		"varying vec4 v_fragmentColor;                                  \n"
		"varying vec2 v_texCoord;                                       \n"
		"varying vec2 v_texCoord1;                                      \n"
		"#endif                                                         \n"
		"void main()                                                    \n"
		"{                                                              \n"
		"   gl_Position = CC_MVPMatrix * a_position;                    \n"
		"   v_fragmentColor = a_color;                                  \n"
		"   v_texCoord = a_texCoord;                                    \n"
		"   v_texCoord1 = a_texCoord1;                                  \n"
		"}                                                              \n";

	GLProgram * program = GLProgram::createWithByteArrays(vectShader, fragmentShader);
	setGLProgramState(GLProgramState::getOrCreateWithGLProgram(program));

	_multiCommand.func = CC_CALLBACK_0(MultiSprite::renderMultiSprite, this);

	setLightTexture(lightFilename);

	setRectInBase(Rect(Vec2::ZERO, _texture->getContentSize()));

	return ret;
}

void MultiSprite::setLightTexture(std::string filename)
{
	setLightTexture(Director::getInstance()->getTextureCache()->addImage(filename));
}

void MultiSprite::setLightTexture(cocos2d::Texture2D *texture)
{
	if (texture != _lightTexture) {
		CC_SAFE_RELEASE(_lightTexture);
		_lightTexture = texture;
		CC_SAFE_RETAIN(texture);
	}
}

void MultiSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	_multiCommand.init(_globalZOrder, transform, flags);
	renderer->addCommand(&_multiCommand);
}

void MultiSprite::setRectInBase(cocos2d::Rect rect)
{
	if (!_rectInBase.equals(rect)) {
		_rectInBase = rect;

		PolygonInfo baseInfo = _polyInfo;

		Size baseContentSize = _texture->getContentSize();

		//坐标确定，纹理坐标值越大，单张纹理（0到1）越小

		float lightScaleX = _rectInBase.size.width / baseContentSize.width;
		float lightScaleY = _rectInBase.size.height / baseContentSize.height;

		float originX = -(_rectInBase.origin.x / baseContentSize.width / lightScaleX);
		float originY = -((baseContentSize.height - _rectInBase.origin.y - _rectInBase.size.height) / baseContentSize.height / lightScaleY);

		// 0, 0       0, 1       1, 0          1, 1
		for (int i = 0; i<4; ++i) {
			_verts[i].color = Color4F::WHITE;
			_verts[i].vertices = baseInfo.triangles.verts[i].vertices;
			_verts[i].texCoords = baseInfo.triangles.verts[i].texCoords;
		}

		_verts[0].texCoords1 = Tex2F(originX, originY);
		_verts[1].texCoords1 = Tex2F(originX, 1 / lightScaleY + originY);
		_verts[2].texCoords1 = Tex2F(1 / lightScaleX + originX, originY);
		_verts[3].texCoords1 = Tex2F(1 / lightScaleX + originX, 1 / lightScaleY + originY);
	}
}

void MultiSprite::renderMultiSprite()
{
	//load mv
	_glProgramState->apply(_modelViewTransform);

	float size = sizeof(V3F_C4F_T2F2);

	// Load the vertex position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT,
		GL_FALSE, size, &_verts[0]);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT,
		GL_FALSE, size, &(_verts[0].color));
	// Load the texture coordinate
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT,
		GL_FALSE, size, &(_verts[0].texCoords));
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD1, 2, GL_FLOAT,
		GL_FALSE, size, &(_verts[0].texCoords1));

	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD1);

	//bind texture
	GL::bindTextureN(0, _texture->getName());
	glUniform1i(_glProgramState->getGLProgram()->getUniformLocation(GLProgram::UNIFORM_NAME_SAMPLER0), 0);

	GL::bindTextureN(1, _lightTexture->getName());
	glUniform1i(_glProgramState->getGLProgram()->getUniformLocation(GLProgram::UNIFORM_NAME_SAMPLER1), 1);

	//draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);
}






DQOPENGLSprite::DQOPENGLSprite() : Sprite()
{

}

DQOPENGLSprite * DQOPENGLSprite::create(std::string filename)
{
	DQOPENGLSprite * sprite = new DQOPENGLSprite();
	if (sprite && sprite->init(filename)) {
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool DQOPENGLSprite::init(std::string baseFilename)
{
	bool ret = Sprite::initWithFile(baseFilename);

	m_sBlendFunc.src = CC_BLEND_SRC;
	m_sBlendFunc.dst = CC_BLEND_DST;

	const char fragmentShader[] =
		"#ifdef GL_ES                                                   \n"
		"precision lowp float;                                          \n"
		"#endif                                                         \n"
		"varying vec4 v_fragmentColor;                                  \n"
		"varying vec2 v_texCoord;                                       \n"
		"varying vec2 v_texCoord1;                                      \n"
		"void main()                                                    \n"
		"{                                                              \n"
		"   vec4 baseColor;                                             \n"
		"   baseColor = texture2D( CC_Texture0, v_texCoord )*v_fragmentColor;                               \n"
		"   vec4 lightColor;                                            \n"
		"   if  (v_texCoord1.x>1.0 || v_texCoord1.y>1.0 || v_texCoord1.y < 0.0 || v_texCoord1.x<0.0 )                                        \n"
		"   {                                                           \n"
		"       lightColor = vec4(0, 0, 0, 1);                          \n"
		"   }                                                           \n"
		"   else                                                        \n"
		"   {                                                           \n"
		"       lightColor = texture2D( CC_Texture1, v_texCoord1 );     \n"
		"   }                                                           \n"
		"   gl_FragColor = baseColor * (lightColor + 0.25);             \n"
		"                                                               \n"
		"}                                                              \n";

	const char vectShader[] =
		"attribute vec4 a_position;                                     \n"
		"attribute vec2 a_texCoord;                                     \n"
		"attribute vec2 a_texCoord1;                                    \n"
		"attribute vec4 a_color;                                        \n"
		"#ifdef GL_ES                                                   \n"
		"varying lowp vec4 v_fragmentColor;                             \n"
		"varying mediump vec2 v_texCoord;                               \n"
		"varying mediump vec2 v_texCoord1;                              \n"
		"#else                                                          \n"
		"varying vec4 v_fragmentColor;                                  \n"
		"varying vec2 v_texCoord;                                       \n"
		"varying vec2 v_texCoord1;                                      \n"
		"#endif                                                         \n"
		"void main()                                                    \n"
		"{                                                              \n"
		"   gl_Position = CC_MVPMatrix * a_position;                    \n"
		"   v_fragmentColor = a_color;                                  \n"
		"   v_texCoord = a_texCoord;                                    \n"
		"   v_texCoord1 = a_texCoord1;                                  \n"
		"}                                                              \n";

	//GLProgram * program = GLProgram::createWithByteArrays(vectShader, fragmentShader);
	m_pProgram = ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
	//setGLProgramState(GLProgramState::getOrCreateWithGLProgram(m_pProgram));

	_multiCommand.func = CC_CALLBACK_0(DQOPENGLSprite::renderMultiSprite, this);

	setRectInBase(Rect(Vec2::ZERO, _texture->getContentSize()));

	m_uTotalQuads = 0;
	m_uCapacity = 10;

	unsigned int size = m_uCapacity * sizeof(ccV3F_C4B_T2F_Quad);
	m_pQuads = (V3F_C4B_T2F_Quad*)malloc(size);
	assert(m_pQuads);
	memset(m_pQuads, 0, size);

	size = m_uCapacity * 6 * sizeof(GLushort);
	m_pIndices = (GLushort*)malloc(size);
	assert(m_pIndices);
	memset(m_pIndices, 0, size);

	Mat4 out;
	kmGLGetMatrix(KM_GL_MODELVIEW, &out);

	V3F_C4B_T2F_Quad quad;

	Rect rectVertices;
	rectVertices.origin.x = (float)100;
	rectVertices.origin.y = (float)100;
	rectVertices.size.width = (float)50;
	rectVertices.size.height = (float)50;

	float x1 = rectVertices.origin.x;
	float y1 = rectVertices.origin.y;
	float x2 = x1 + rectVertices.size.width;
	float y2 = y1 + rectVertices.size.height;

	// update transform

	quad.bl.vertices = vertex3(x1, y1, 0);
	quad.br.vertices = vertex3(x2, y1, 0);
	quad.tl.vertices = vertex3(x1, y2, 0);
	quad.tr.vertices = vertex3(x2, y2, 0);

	quad.bl.vertices.x = (quad.bl.vertices.x * out.m[0] + quad.bl.vertices.y * out.m[4] + quad.bl.vertices.z * out.m[8] + out.m[12]);
	quad.bl.vertices.y = (quad.bl.vertices.x * out.m[1] + quad.bl.vertices.y * out.m[5] + quad.bl.vertices.z * out.m[9] + out.m[13]);
	quad.bl.vertices.z = (quad.bl.vertices.x * out.m[2] + quad.bl.vertices.y * out.m[6] + quad.bl.vertices.z * out.m[10] + out.m[14]);

	quad.br.vertices.x = (quad.br.vertices.x * out.m[0] + quad.br.vertices.y * out.m[4] + quad.br.vertices.z * out.m[8] + out.m[12]);
	quad.br.vertices.y = (quad.br.vertices.x * out.m[1] + quad.br.vertices.y * out.m[5] + quad.br.vertices.z * out.m[9] + out.m[13]);
	quad.br.vertices.z = (quad.br.vertices.x * out.m[2] + quad.br.vertices.y * out.m[6] + quad.br.vertices.z * out.m[10] + out.m[14]);

	quad.tl.vertices.x = (quad.tl.vertices.x * out.m[0] + quad.tl.vertices.y * out.m[4] + quad.tl.vertices.z * out.m[8] + out.m[12]);
	quad.tl.vertices.y = (quad.tl.vertices.x * out.m[1] + quad.tl.vertices.y * out.m[5] + quad.tl.vertices.z * out.m[9] + out.m[13]);
	quad.tl.vertices.z = (quad.tl.vertices.x * out.m[2] + quad.tl.vertices.y * out.m[6] + quad.tl.vertices.z * out.m[10] + out.m[14]);

	quad.tr.vertices.x = (quad.tr.vertices.x * out.m[0] + quad.tr.vertices.y * out.m[4] + quad.tr.vertices.z * out.m[8] + out.m[12]);
	quad.tr.vertices.y = (quad.tr.vertices.x * out.m[1] + quad.tr.vertices.y * out.m[5] + quad.tr.vertices.z * out.m[9] + out.m[13]);
	quad.tr.vertices.z = (quad.tr.vertices.x * out.m[2] + quad.tr.vertices.y * out.m[6] + quad.tr.vertices.z * out.m[10] + out.m[14]);

	Rect rectTexture;
	rectTexture.origin.x = (float)100;
	rectTexture.origin.y = (float)100;
	rectTexture.size.width = (float)50;
	rectTexture.size.height = (float)50;

	float left,
		right,
		top,
		bottom;

	left = (2 * rectTexture.origin.x + 1) / (2 * 70);
	right = left + (rectTexture.size.width * 2 - 2) / (2 * 70);
	top = (2 * rectTexture.origin.y + 1) / (2 * 70);
	bottom = top + (rectTexture.size.height * 2 - 2) / (2 * 70);

	quad.bl.texCoords.u = left;
	quad.bl.texCoords.v = bottom;
	quad.br.texCoords.u = right;
	quad.br.texCoords.v = bottom;
	quad.tl.texCoords.u = left;
	quad.tl.texCoords.v = top;
	quad.tr.texCoords.u = right;
	quad.tr.texCoords.v = top;

	Color4B color = Color4B(255, 255, 255, 255);
	quad.bl.colors =
		quad.br.colors =
		quad.tl.colors =
		quad.tr.colors = color;

	quad.bl.colors.r = quad.bl.colors.r * color.a >> 8;
	quad.bl.colors.g = quad.bl.colors.g * color.a >> 8;
	quad.bl.colors.b = quad.bl.colors.b * color.a >> 8;
	quad.bl.colors.a = color.a;

	quad.br.colors.r = quad.br.colors.r * color.a >> 8;
	quad.br.colors.g = quad.br.colors.g * color.a >> 8;
	quad.br.colors.b = quad.br.colors.b * color.a >> 8;
	quad.br.colors.a = color.a;

	quad.tl.colors.r = quad.tl.colors.r * color.a >> 8;
	quad.tl.colors.g = quad.tl.colors.g * color.a >> 8;
	quad.tl.colors.b = quad.tl.colors.b * color.a >> 8;
	quad.tl.colors.a = color.a;

	quad.tr.colors.r = quad.tr.colors.r * color.a >> 8;
	quad.tr.colors.g = quad.tr.colors.g * color.a >> 8;
	quad.tr.colors.b = quad.tr.colors.b * color.a >> 8;
	quad.tr.colors.a = color.a;

	m_uTotalQuads++;

	m_pQuads[m_uTotalQuads - 1] = quad;

	return ret;
}


void DQOPENGLSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	_multiCommand.init(_globalZOrder, transform, flags);
	renderer->addCommand(&_multiCommand);
}

void DQOPENGLSprite::setRectInBase(cocos2d::Rect rect)
{
	if (!_rectInBase.equals(rect)) {
		_rectInBase = rect;

		PolygonInfo baseInfo = _polyInfo;

		Size baseContentSize = _texture->getContentSize();

		//坐标确定，纹理坐标值越大，单张纹理（0到1）越小

		float lightScaleX = _rectInBase.size.width / baseContentSize.width;
		float lightScaleY = _rectInBase.size.height / baseContentSize.height;

		float originX = -(_rectInBase.origin.x / baseContentSize.width / lightScaleX);
		float originY = -((baseContentSize.height - _rectInBase.origin.y - _rectInBase.size.height) / baseContentSize.height / lightScaleY);

		// 0, 0       0, 1       1, 0          1, 1
		for (int i = 0; i<4; ++i) {
			_verts[i].color = Color4F::WHITE;
			_verts[i].vertices = baseInfo.triangles.verts[i].vertices;
			_verts[i].texCoords = baseInfo.triangles.verts[i].texCoords;
		}

		_verts[0].texCoords1 = Tex2F(originX, originY);
		_verts[1].texCoords1 = Tex2F(originX, 1 / lightScaleY + originY);
		_verts[2].texCoords1 = Tex2F(1 / lightScaleX + originX, originY);
		_verts[3].texCoords1 = Tex2F(1 / lightScaleX + originX, 1 / lightScaleY + originY);
	}
}

void DQOPENGLSprite::renderMultiSprite()
{
#if 0
	//load mv
	_glProgramState->apply(_modelViewTransform);

	float size = sizeof(V3F_C4F_T2F2);

	// Load the vertex position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, size, &_verts[0]);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, size, &(_verts[0].color));
	// Load the texture coordinate
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, size, &(_verts[0].texCoords));
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD1, 2, GL_FLOAT,	GL_FALSE, size, &(_verts[0].texCoords1));

	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD1);

	//bind texture
	GL::bindTextureN(0, _texture->getName());
	glUniform1i(_glProgramState->getGLProgram()->getUniformLocation(GLProgram::UNIFORM_NAME_SAMPLER0), 0);

	//draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);
#endif
	//---------------------------------------------------------------------------------------------------
#if 1
	kmGLPushMatrix();
	Mat4 proj;
	kmGLGetMatrix(KM_GL_PROJECTION, &proj);

	m_pProgram->use();
	//->setUniformLocationWithMatrix4fv(m_pProgram->getUniform[kCCUniformMVPMatrix], proj.m, 1);
	//m_pProgram->setUniformLocationwithMatrix4fv(m_pProgram->m_uUniforms[kCCUniformMVPMatrix], proj.mat, 1);
	glEnable(GL_BLEND);
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	GL::bindTextureN(0, _texture->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

	
#define kQuadSize sizeof(m_pQuads[0].bl)
	long offset = (long)&m_pQuads[0];

	/*
	// vertex
	int diff = offsetof(V3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	// texCoods
	diff = offsetof(V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	// color
	diff = offsetof(V3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	*/

	
	float size = sizeof(V3F_C4F_T2F2);

	// Load the vertex position
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, size, &_verts[0]);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, size, &(_verts[0].color));
	// Load the texture coordinate
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, size, &(_verts[0].texCoords));
	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD1, 2, GL_FLOAT, GL_FALSE, size, &(_verts[0].texCoords1));

	//glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	//glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	//glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
	//glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	

	//glDrawElements(GL_TRIANGLES, (GLsizei)m_uTotalQuads * 6, GL_UNSIGNED_SHORT, (GLvoid*)(m_pIndices));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);
	CC_INCREMENT_GL_DRAWS(1);

	kmGLPopMatrix();

	m_uTotalQuads = 0;
#endif
}


//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
DQNodeSprite::DQNodeSprite()
{
	setGLProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
	_textureAtlas = TextureAtlas::create("gem_dark.png", 3); 
	//_textureAtlas = Texture2D::create("gem_dark.png", 3);
	
	_textureAtlas->retain();

	auto s = Director::getInstance()->getWinSize();

	//
	// Notice: u,v tex coordinates are inverted
	//
	V3F_C4B_T2F_Quad quads[] =
	{
		{
			{ Vec3(0, 0, 0), Color4B(0, 0, 0, 0), Tex2F(0.0f, 1.0f), },    // bottom left
			{ Vec3(53, 0, 0), Color4B(0, 0, 0, 0), Tex2F(1.0f, 1.0f), },    // bottom right
			{ Vec3(0, 53, 0), Color4B(0, 0, 0, 0), Tex2F(0.0f, 0.0f), },    // top left
			{ Vec3(53, 53, 0), Color4B(0, 0, 0, 0), Tex2F(1.0f, 0.0f), },    // top right
		},

		/*
		{
			{ Vec3(0,       0,        0), Color4B(0, 0, 255, 255), Tex2F(0.0f, 1.0f), },    // bottom left
			{ Vec3(s.width, 0,        0), Color4B(0, 0, 255,   0), Tex2F(1.0f, 1.0f), },    // bottom right
			{ Vec3(0,       s.height, 0), Color4B(0, 0, 255,   0), Tex2F(0.0f, 0.0f), },    // top left
			{ Vec3(s.width, s.height, 0), Color4B(0, 0, 255, 255), Tex2F(1.0f, 0.0f), },    // top right
		},
		
		{
			{ Vec3(40, 40, 0), Color4B(255, 255, 255, 255), Tex2F(0.0f, 0.2f), },            // bottom left
			{ Vec3(120, 80, 0), Color4B(255, 0, 0, 255), Tex2F(0.5f, 0.2f), },            // bottom right
			{ Vec3(40, 160, 0), Color4B(255, 255, 255, 255), Tex2F(0.0f, 0.0f), },        // top left
			{ Vec3(160, 160, 0), Color4B(0, 255, 0, 255), Tex2F(0.5f, 0.0f), },            // top right
		},

		{
			{ Vec3(s.width / 2, 40, 0), Color4B(255, 0, 0, 255), Tex2F(0.0f, 1.0f), },        // bottom left
			{ Vec3(s.width, 40, 0), Color4B(0, 255, 0, 255), Tex2F(1.0f, 1.0f), },        // bottom right
			{ Vec3(s.width / 2 - 50, 200, 0), Color4B(0, 0, 255, 255), Tex2F(0.0f, 0.0f), },        // top left
			{ Vec3(s.width, 100, 0), Color4B(255, 255, 0, 255), Tex2F(1.0f, 0.0f), },        // top right
		},
		*/
	};


	for (int i = 0; i<3; i++)
	{
		_textureAtlas->updateQuad(&quads[i], i);
	}
}

DQNodeSprite::~DQNodeSprite()
{
	_textureAtlas->release();
}

void DQNodeSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(DQNodeSprite::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void DQNodeSprite::onDraw(const Mat4 &transform, uint32_t flags)
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins(transform);
	_textureAtlas->drawQuads();
}

