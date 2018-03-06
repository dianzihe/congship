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
