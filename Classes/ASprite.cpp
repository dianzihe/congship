
#include "ASprite.h"
//#include "Actor.h"
#include "GameScene.h"
//#include "Player.h"
#include "ActorManager.h"
#include "tinyxml2\tinyxml2.h"
//#include "Hero.h"
//#include "assert.h"
//#include "CCFileUtils.h"
//#include "CCMemoryMonitor.h"
//#include "ASpriteManager.h"
//#include "CCResourceThread.h"
//#include "DelayASpriteLoadManager.h"

using namespace tinyxml2;

#define ALWAYS_BS_NFM_1_BYTE	0
#define ALWAYS_BS_NAF_1_BYTE    0
#define ALWAYS_BS_SKIP_FRAME_RC 1
#define FIXED_PRECISION         0

#define FLAG_FLIP_X            (1<<0) 
#define FLAG_FLIP_Y            (1<<1)   
#define FLAG_ROT_90            (1<<2)

#define USE_MODULE_MAPPINGS     0
#define MAX_FREAM_CORRECTION    10


void arraycopy( char * src, int srcPos, char * dest, int destPos, int length )
{
	memcpy( &dest[destPos], &src[srcPos], length * sizeof(char) );
}

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__A__) ( (int)(__A__))
#endif


/*
void TextureDrawInRect::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	TextureDemo::draw(renderer, transform, flags);

	_renderCmd.init(_globalZOrder, transform, flags);
	_renderCmd.func = CC_CALLBACK_0(TextureDrawInRect::onDraw, this, transform, flags);
	renderer->addCommand(&_renderCmd);
}

void TextureDrawInRect::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when setting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	auto s = Director::getInstance()->getWinSize();

	auto rect1 = Rect(s.width / 2 - 80, 20, _tex1->getContentSize().width * 0.5f, _tex1->getContentSize().height * 2);
	auto rect2 = Rect(s.width / 2 + 80, s.height / 2, _tex1->getContentSize().width * 2, _tex1->getContentSize().height * 0.5f);

	_tex1->drawInRect(rect1);
	_Tex2F->drawInRect(rect2);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
*/
void ASprite::DrawRegion( int texIdx, int texX, int texY, int texSizeX, int texSizeY, int flag, int posX, int posY, int rectWidth, int rectHeight, int opacity, bool isGray)
{ 
	log("---------ASprite::DrawRegion texIdx[%d], texX[%d], texY[%d], texSizeX[%d], texSizeY[%d], flag[%d], posX[%d], posY[%d], rectWidth[%d], rectHeight[%d], opacity[%d]", 
		texIdx, texX, texY, texSizeX, texSizeY, flag, posX, posY, rectWidth, rectHeight, opacity);
	//if (!mIsTexAllLoaded)
	//	return;
#if 1
	/*
	//GL::bindTexture2D(_texture->getName());
	GL::bindTexture2D(m_texture->texture->getName());
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
	
	V3F_C4B_T2F_Quad quad;
	//reset to custome 
	quad.bl.vertices = Vec3(0, 0, 0);
	quad.br.vertices = Vec3(53, 0, 0);
	quad.tl.vertices = Vec3(0, 53, 0);
	quad.tr.vertices = Vec3(53, 53, 0);

	quad.bl.colors =
		quad.br.colors =
		quad.tl.colors =
		quad.tr.colors = Color4B(255, 255, 255, 255);

	quad.bl.texCoords = Tex2F(0.0f, 1.0f);
	quad.br.texCoords = Tex2F(1.0f, 1.0f);
	quad.tl.texCoords = Tex2F(0.0f, 0.0f);
	quad.tr.texCoords = Tex2F(1.0f, 0.0f);


#define kQuadSize sizeof(_quad.bl) 
	size_t offset = (size_t)&_quad;

	offset = (size_t)&quad;
	// vertex
	int diff = offsetof(V3F_C4B_T2F, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoords
	diff = offsetof(V3F_C4B_T2F, texCoords);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(V3F_C4B_T2F, colors);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, quadIndices);

	CHECK_GL_ERROR_DEBUG();
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
	*/
#else

	Sprite _RenderSprite;
	
	Rect rect;
	rect.origin.x = (float)texX;
	rect.origin.y = (float)texY;

	rect.size.width = (float)texSizeX;
	rect.size.height = (float)texSizeY;

	if(flag&FLAG_FLIP_X){
		rect.origin.x = (float)(texX + texSizeX);
		rect.size.width = (float)-texSizeX;
	}
	if(flag&FLAG_FLIP_Y){
		rect.origin.y = (float)(texY + texSizeY);
		rect.size.height = (float)-texSizeY;
	}

 	kmMat4 modelView;
 	kmGLGetMatrix(KM_GL_MODELVIEW, &modelView);

	kmMat4 proj;
	kmGLGetMatrix(KM_GL_PROJECTION, &proj);

	kmMat4 out;
	kmMat4Multiply(&out, &modelView, &proj);
 
	Vec4 bl, br, tl, tr;
 	
 	float x1 = rect.origin.x;
 	float y1 = rect.origin.y;
 	float x2 = x1 + rect.size.width;
 	float y2 = y1 + rect.size.height;

	float cameraFar = Director::getInstance()->getZEye();
 
 	bl = Vec4(x1, y1, cameraFar, 1);
	br = Vec4(x2, y1, cameraFar, 1);
	tl = Vec4(x1, y2, cameraFar, 1);
	tr = Vec4(x2, y2, cameraFar, 1);
	
	bl.x = RENDER_IN_SUBPIXEL(bl.x * out.m[0] + bl.y * out.m[4] + bl.z * out.m[8] + bl.w * out.m[12]);
	bl.y = RENDER_IN_SUBPIXEL(bl.x * out.m[1] + bl.y * out.m[5] + bl.z * out.m[9] + bl.w * out.m[13]);
	bl.z = RENDER_IN_SUBPIXEL(bl.x * out.m[2] + bl.y * out.m[6] + bl.z * out.m[10] + bl.w *out.m[14]);
	bl.w = RENDER_IN_SUBPIXEL(bl.x * out.m[3] + bl.y * out.m[7] + bl.z * out.m[11] + bl.w *out.m[15]);

	br.x = RENDER_IN_SUBPIXEL(br.x * out.m[0] + br.y * out.m[4] + br.z * out.m[8] + br.w * out.m[12]);
	br.y = RENDER_IN_SUBPIXEL(br.x * out.m[1] + br.y * out.m[5] + br.z * out.m[9] + br.w * out.m[13]);
	br.z = RENDER_IN_SUBPIXEL(br.x * out.m[2] + br.y * out.m[6] + br.z * out.m[10] + br.w *out.m[14]);
	br.w = RENDER_IN_SUBPIXEL(br.x * out.m[3] + br.y * out.m[7] + br.z * out.m[11] + br.w *out.m[15]);

	tl.x = RENDER_IN_SUBPIXEL(tl.x * out.m[0] + tl.y * out.m[4] + tl.z * out.m[8] + tl.w * out.m[12]);
	tl.y = RENDER_IN_SUBPIXEL(tl.x * out.m[1] + tl.y * out.m[5] + tl.z * out.m[9] + tl.w * out.m[13]);
	tl.z = RENDER_IN_SUBPIXEL(tl.x * out.m[2] + tl.y * out.m[6] + tl.z * out.m[10] + tl.w * out.m[14]);
	tl.w = RENDER_IN_SUBPIXEL(tl.x * out.m[3] + tl.y * out.m[7] + tl.z * out.m[11] + tl.w * out.m[15]);

	tr.x = RENDER_IN_SUBPIXEL(tr.x * out.m[0] + tr.y * out.m[4] + tr.z * out.m[8] + tr.w * out.m[12]);
	tr.y = RENDER_IN_SUBPIXEL(tr.x * out.m[1] + tr.y * out.m[5] + tr.z * out.m[9] + tr.w * out.m[13]);
	tr.z = RENDER_IN_SUBPIXEL(tr.x * out.m[2] + tr.y * out.m[6] + tr.z * out.m[10] + tr.w * out.m[14]);
	tr.w = RENDER_IN_SUBPIXEL(tr.x * out.m[3] + tr.y * out.m[7] + tr.z * out.m[11] + tr.w * out.m[15]);

	bl.x = bl.x/bl.w;
	bl.y = bl.y/bl.w;
	bl.z = bl.z/bl.w;
	bl.w = bl.w/bl.w;

	br.x = br.x/br.w;
	br.y = br.y/br.w;
	br.z = br.z/br.w;
	br.w = br.w/br.w;

	tl.x = tl.x/tl.w;
	tl.y = tl.y/tl.w;
	tl.z = tl.z/tl.w;
	tl.w = tl.w/tl.w;

	tr.x = tr.x/tr.w;
	tr.y = tr.y/tr.w;
	tr.z = tr.z/tr.w;
	tr.w = tr.w/tr.w;

	if (tl.x>= -1.f && tr.x <= 1.f && tl.y <= 1.f && bl.y>=-1.f){
		Texture2D *tex(NULL);
		if (m_textures.empty()){
			tex = m_texture->texture;
		}else if(texIdx < (int)m_textures.size()){
			tex = m_textures[texIdx]->texture;
		}
	#if defined _WIN32 | WIN32
		else
			assert(0);//请检查资源
	#endif

		if(tex == NULL)
			return;

		if(modelView.m[0] == 1 && modelView.m[5] == 1){
			if(mSpriteName != "otherSFX")
				tex->setAliasTexParameters();
		}else{
			//if(tex->isAliasTexParameter())
				tex->setAntiAliasTexParameters();
		}

		//_RenderSprite.initWithTexture(tex, rect, false);

		rect.origin.x = (float)posX;
		rect.origin.y = (float)posY;

		rect.size.width = (float)rectWidth;
		rect.size.height = (float)rectHeight;

		//_RenderSprite.setVertexCoords(rect);

		if ( m_clipRect ){
			//glEnable(GL_SCISSOR_TEST);
			//myGLEnableScissorTest();

			glScissor( (GLint)m_clipRect->origin.x,
				(GLint)m_clipRect->origin.y,
				(GLsizei)m_clipRect->size.width,
				(GLsizei)m_clipRect->size.height);
		}

		if (isGray){
			ccColor3B color;
			color.r = 22;
			color.g = 22;
			color.b = 22;
			_RenderSprite.setColor(color);

			if (opacity > 150)
				opacity = 150;
		}


		_RenderSprite.setOpacity(opacity);
		_RenderSprite.visit();
		//_RenderSprite.updateBlendFunc();

		//_RenderSprite.draw();

		if ( m_clipRect ){
			//glDisable(GL_SCISSOR_TEST);
			//myGLDisableScissorTest();
		}
	}
#endif
}

ASprite::ASprite()
: m_textureSquareSize(0)
, mIsTexAllLoaded(false)
, mIsDataLoaded(false)
, animnumber(0)
, _nModules(0)
{
	m_texture = NULL;

	_frames_nfm = NULL;
	_frames_fm_start = NULL;
	_frames_rc = NULL;
	_frames_coll = NULL;

	//_fmodules = NULL;
	_anims_naf = NULL;
	_anims_af_start = NULL;
	_aframes = NULL;
	m_clipRect = NULL;
    //ResetClip();

	m_lastUpdateTime = 0.f;
	m_totalUpdateTime = 0.f;
}

void ASprite::clear_patch()
{

	// free frames data
	SAFE_DELETE_ARRAY( _frames_nfm );	
	SAFE_DELETE_ARRAY( _frames_fm_start );	
	SAFE_DELETE_ARRAY( _frames_rc );	
	SAFE_DELETE_ARRAY( _frames_coll );	
	//SAFE_DELETE_ARRAY( _fmodules );	

	// free anims data
	SAFE_DELETE_ARRAY( _anims_naf );	
	SAFE_DELETE_ARRAY( _anims_af_start );	
	SAFE_DELETE_ARRAY( _aframes );

	SAFE_DELETE(m_clipRect);
}

ASprite::~ASprite()	
{
	//AspriteManager::instance().RemoveSprite(this);

	//DelayASpriteLoadManager::instance().RemoveDelayASprite( this );
	/*
	SAFE_DELETE(m_texture);

	for (TextureVector::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		SAFE_DELETE(*it);
	}

	// free frames data
	SAFE_DELETE_ARRAY( _frames_nfm );	
	SAFE_DELETE_ARRAY( _frames_fm_start );	
	SAFE_DELETE_ARRAY( _frames_rc );	
	SAFE_DELETE_ARRAY( _frames_coll );	
//	SAFE_DELETE_ARRAY( _fmodules );	

	// free anims data
	SAFE_DELETE_ARRAY( _anims_naf );	
	SAFE_DELETE_ARRAY( _anims_af_start );	
	SAFE_DELETE_ARRAY( _aframes );

	SAFE_DELETE(m_clipRect);
	*/
}

int ASprite::GetAnimNumber ()
{
	return animnumber;
}

bool ASprite::Load(const char* resName, ACTORTYPE actorType, bool isMustLoad)
{ 
	bool ret = false;
	mIsDataLoaded = false;
	int imageIndex = 0;
	char fileNameBuffer[256];
	char plistfileNameBuffer[256];
	ssize_t len = 0;
	
#if 0
	//1113
	sprintf(fileNameBuffer, "%s.bsprite" ,resName );
	if (!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(fileNameBuffer).c_str())){
		log("---file %s not find", fileNameBuffer);
		return false;
	}
	char *data = (char*)FileUtils::getInstance()->getFileData(fileNameBuffer, "rb", &len);
	LoadData(data);
	
	do {
		sprintf(fileNameBuffer, "%s_%d.png" ,resName, imageIndex );

		mIsTexAllLoaded = false;
		if ( FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(fileNameBuffer).c_str())){
			TextureWrap* tw = new TextureWrap();
			tw->fileName = fileNameBuffer;

			TextureCache::getInstance()->addImageAsync(fileNameBuffer, CC_CALLBACK_1(ASprite::onAsyncLoadedTexture, this));
			tw->isLoaded = true;
			m_textures.push_back(tw);
		} else {
			char logError[512];
			sprintf(logError, "File not found: %s", fileNameBuffer);
			log(logError, "File not found");
			break;
		}
		++imageIndex;
	} while (1);

	if (m_textures.empty()) {
		sprintf(fileNameBuffer, "%s.png" ,resName );

		std::string path = fileNameBuffer;
		if (FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(fileNameBuffer).c_str())){
			m_texture = new TextureWrap();
			m_texture->fileName = fileNameBuffer;

			m_texture->isLoaded = true;
			mIsTexAllLoaded = false;
		} else {
			return false;
		}
	}

	return true;
#endif
	
#if 0
	std::string plist_content = FileUtils::getInstance()->getStringFromFile(fileNameBuffer);

	sprintf(fileNameBuffer, "%s.png", resName);
	Data image_content = FileUtils::getInstance()->getDataFromFile(fileNameBuffer);
	log("ASprite::Load-->%s, actorType:%d", fileNameBuffer, actorType);
	Image* image = new (std::nothrow) Image();
	image->initWithImageData((const uint8_t*)image_content.getBytes(), image_content.getSize());
	Texture2D* texture = new (std::nothrow) Texture2D();
	texture->initWithImage(image);
	texture->autorelease();

	CC_SAFE_RELEASE(image);

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFileContent(plist_content, texture);

	
	bool ret = false;
	mIsDataLoaded = false;
	int imageIndex = 0;

	len = 0;
	sprintf(fileNameBuffer, "%s.bsprite", resName);
	if (!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(fileNameBuffer).c_str())){
		log("---file %s not find", fileNameBuffer);
		return false;
	}
	else
		log("---find file %s", fileNameBuffer);
	/*
	CCResourceThread::LoadingCommand *loadingCmd = new CCResourceThread::LoadingCommand();
	loadingCmd->filePath = fileNameBuffer;
	loadingCmd->loader = (DQ_LoadDataFunc)&(ASprite::LoadData);
	loadingCmd->afterProcess = (DQ_CallFuncO)&ASprite::onLoadData;
	loadingCmd->target = this;
	CCResourceThread::instance()->postCommand(loadingCmd);
	*/
	char *data = (char*)FileUtils::getInstance()->getFileData(fileNameBuffer, "rb", &len);
	LoadData(data);
	log("-----get continue");

	do{
#if defined _WIN32 | WIN32
		sprintf(fileNameBuffer, "%s_%d.png" ,resName, imageIndex );
#else
		sprintf(fileNameBuffer, "%s_%d.pvr.ccz" ,resName, imageIndex );
#endif
		std::string path = fileNameBuffer;
		
		mIsTexAllLoaded = false;

		if (FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(path))){
			log("-----get find %s", fileNameBuffer);
			TextureWrap* tw = new TextureWrap();
			tw->fileName = fileNameBuffer;
			/*
			if (!CCMemoryMonitor::sharedMemoryMonitor()->isMemoryLackEmergence() || isMustLoad){
				CCTextureCache::sharedTextureCache()->addImageAsync(fileNameBuffer, this, (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
				tw->isLoaded = true;
			}else{
				tw->isLoaded = false;
			}
			*/
			TextureCache::getInstance()->addImageAsync(fileNameBuffer, CC_CALLBACK_1(ASprite::onAsyncLoadedTexture, this));
			tw->isLoaded = true;
			m_textures.push_back(tw);
		}else{
			log("=====get find not %s", fileNameBuffer);
			char logError[512];
			sprintf(logError, "File not found: %s", path.c_str());
			//Log::PrintAndroidErrorLog(logError, "File not found");
			break;
		}
		++imageIndex;
	}while (1);
#endif

#if 1
	/*
	sprintf(fileNameBuffer, "%s.bsprite", resName);
	if (!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(fileNameBuffer).c_str())){
		log("---file %s not find", fileNameBuffer);
		return false;
	} else
		log("---find file %s", fileNameBuffer);
	char *data = (char*)FileUtils::getInstance()->getFileData(fileNameBuffer, "rb", &len);
	*/
	//LoadData(data);
	//分析plist并填充至动画组织结构
	sprintf(plistfileNameBuffer, "%s.plist", resName);

	if (!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(plistfileNameBuffer).c_str())){
		log("---ERROR---file %s not find", plistfileNameBuffer);
		return false;
	}

	//tinyxml2::XMLDocument doc;
	tinyxml2::XMLDocument docXml;
	XMLError errXml = docXml.LoadFile(plistfileNameBuffer);
	log("ASprite::Load-->%s====%d", plistfileNameBuffer, errXml);
	
	if (XML_SUCCESS == errXml) {
		for (XMLNode* ele = docXml.FirstChildElement("plist")->FirstChildElement("dict")->FirstChildElement("dict")->FirstChild();
			ele;
			ele = ele->NextSibling()){
			std::string key = "key";
			std::string value = "dict";
			if (key == ele->Value()){
				log("->%s\n", ele->ToElement()->GetText());
				TextureWrap* tw = new TextureWrap();
				tw->fileName = ele->ToElement()->GetText();
				m_textures.push_back(tw);

			}
			/*
			if (value == ele->Value()){
				log("=>%s\n", ele->ToElement()->FirstChildElement("key")->GetText());
			}
			*/
		}
	}
	
	if (0){
	//if (m_textures.empty()){
		sprintf(fileNameBuffer, "%s.png" ,resName );
		log("----ASprite::Load-->fileNameBuffer:%s", fileNameBuffer);
		std::string plist_content = FileUtils::getInstance()->getStringFromFile(plistfileNameBuffer);
			
		Data image_content = FileUtils::getInstance()->getDataFromFile(fileNameBuffer);

		Image* image = new (std::nothrow) Image();
		image->initWithImageData((const uint8_t*)image_content.getBytes(), image_content.getSize());
		Texture2D* texture = new (std::nothrow) Texture2D();
		texture->initWithImage(image);
		texture->autorelease();

		CC_SAFE_RELEASE(image);
		 
		SpriteFrameCache::getInstance()->addSpriteFramesWithFileContent(plist_content, texture);

		std::string path = fileNameBuffer;
		if (FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->fullPathForFilename(path.c_str()))){	
			m_texture = new TextureWrap();
			m_texture->fileName = fileNameBuffer;
			/*
			if (!CCMemoryMonitor::sharedMemoryMonitor()->isMemoryLackEmergence() || isMustLoad){
				CCTextureCache::sharedTextureCache()->addImageAsync(fileNameBuffer, this, (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
				m_texture->isLoaded = true;
			}else{
				m_texture->isLoaded = false;
			}
			*/
			TextureCache::getInstance()->addImageAsync(fileNameBuffer, CC_CALLBACK_1(ASprite::onAsyncLoadedTexture, this));
			m_texture->isLoaded = true;
			mIsTexAllLoaded = false;
		} else {
			return false;
		}
	}
#endif
	return true;
}

void ASprite::LoadData(char* data)
{
	int offset = 0;
	//读取版本号 :1503
	short bs_version = (short)((data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8));
	log("===========LoadData version:%d", bs_version);
	offset +=2 ;

	//读取生成标志位
	int bs_flags =  ((data[offset] & 0xFF)) +
		((data[offset + 1] & 0xFF)<< 8) +
		((data[offset + 2] & 0xFF)<<16) +
		((data[offset + 3] & 0xFF)<<24);
	offset += 4 ;

	//读取模型
	_nModules = (data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8);
	offset += 2 ;
	log("===========_nModules:%d", _nModules);
	//赋值模型参数  X Y  高 宽
	if (_nModules > 0) {
		for (int i = 0; i < _nModules; i++) {
			_modules_flag.push_back(data[offset] & 0xFF); 
			offset++;
			if (_modules_flag[i] != MOUDLE_MARK) {
				_modules_x.push_back((data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8));
				offset += 2;
				_modules_y.push_back((data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8));
				offset += 2;
			} else {
				_modules_x.push_back(0);
				_modules_y.push_back(0);
			}
			{
				_modules_w.push_back((data[offset] & 0xFF) + ((data[offset + 1] & 0xFF)<<8));
				offset += 2;
				_modules_h.push_back((data[offset] & 0xFF) + ((data[offset + 1] & 0xFF)<<8));
				offset += 2;
				if (_modules_flag[i] == MOUDLE_MARK) {
					short descLength = (data[offset] & 0xFF) + ((data[offset + 1] & 0xFF)<<8);
					offset += 2;
					char descChar[1024] = {0};
					memcpy(descChar, data + offset, descLength);
					offset += descLength;
					_MarkerDesc[i] = descChar;
					memset(descChar, 0, 1024);
				}
			}
		}
	}
	//读取frame 模型
	int nFModules = (data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8);
	offset += 2 ;
	log("===========nFModules:%d", nFModules);
	if (nFModules > 0) {
		int len = nFModules<<2;
		len += nFModules<<2;
		//赋值模型参数  ID
		for (int i = 0;i < len; i++) {
			_fmodules.push_back(data[offset]);
			offset++;
		}

	}

	//读取frame   -  编号
	int nFrames = (data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8);
	offset += 2 ;
	log("===========nFrames:%d", nFrames);
	if (nFrames > 0) {
		_frames_nfm      = new short[nFrames + 1];
		_frames_fm_start = new short[nFrames + 1];

		memset(_frames_nfm,      0, sizeof(short) * (nFrames + 1));
		memset(_frames_fm_start, 0, sizeof(short) * (nFrames + 1));
		//赋值frame
		for (int i = 0; i < nFrames; i++) {
			_frames_nfm[i]      = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));;
			offset += 2 ;
			_frames_fm_start[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;
		}
	}
	//读取动画帧
	int nAFrames = (data[offset]&0xFF) + ((data[offset + 1] & 0xFF) << 8);
	offset += 2 ;
	log("===========nAFrames:%d", nAFrames);
	if (nAFrames > 0) {
		int len = nAFrames*5 ;
		_aframes = new short[len + 1];
		memset(_aframes, 0, sizeof(short) * (len + 1));
		//赋值动画帧
		for (int i = 0; i < len; i++) {
			_aframes[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;
		}
	}
	//读取动画
	int nAnims = (data[offset] & 0xFF) + ((data[offset + 1] & 0xFF) << 8);
	animnumber = nAnims;
	log("===========nAnims:%d", nAnims);
	_real_anims_naf.resize(animnumber);
	offset += 2 ;

	if (nAnims > 0) {
		_anims_naf      = new  short[nAnims];
		_anims_af_start = new short[nAnims];

		memset(_anims_naf,      0, sizeof(short) * nAnims);
		memset(_anims_af_start, 0, sizeof(short) * nAnims);
		//赋值动画
		for (int i = 0; i < nAnims; i++) {
			_anims_naf[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;

			_anims_af_start[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;

			int realAnimNum = 0;
			for(int j = 0; j < GetAFrames(i); ++j) {
				realAnimNum += GetAFrameTime(i, j);
			}
			_real_anims_naf[i] = realAnimNum;
		}
	}	

	int rc[4];

	if(nFrames != 0) {
		GetFrameRect(rc, 0, 0, 0, 0, 0, 0);
		m_rcSelect = Rect(rc[0], -rc[3], rc[2]-rc[0], rc[3]-rc[1]);
	}

	// OMP: shrink-to-fit
	vector<short>( _modules_x  ).swap( _modules_x );
	vector<short>( _modules_y  ).swap( _modules_y );
	vector<short>( _modules_w  ).swap( _modules_w );
	vector<short>( _modules_h  ).swap( _modules_h );
	vector<unsigned char>( _modules_flag ).swap( _modules_flag );
	vector<signed char>( _fmodules  ).swap( _fmodules );
	
}


void ASprite::onLoadData(Ref* obj)
{
	mIsDataLoaded = true;

	//DelayASpriteLoadManager::instance().DelayASpriteLoadedCallBack( this );
	/*
	Actor* pCallBack = GameScene::GetActorManager()->FindActor(*itCB);
	if (pCallBack)
		pCallBack->DelayASpriteLoadCallBack();
	*/
}

void ASprite::onAsyncLoadedTexture(Texture2D* pTexture)
{
	onLoadData(pTexture);
	log("ASprite::onAsyncLoadedTexture-----%s", pTexture->getPath().c_str());
	if (m_texture) {
		m_texture->texture = pTexture;
		m_texture->isLoaded = true;
		mIsTexAllLoaded = true;
		AspriteManager::instance().AnimationDelayLoadCall(this);
	} else {
		bool allLoaded = true;
		for (int n = 0; n < (int)m_textures.size(); ++n) {
			TextureWrap* tw = m_textures[n];
			if (tw->texture == NULL) {
				tw->texture = TextureCache::getInstance()->textureForKey(tw->fileName.c_str());
				if (tw->texture == NULL)
					allLoaded = false;
				else {
					tw->isLoaded = true;
					if (n == 0)
						m_textureSquareSize = tw->texture->getPixelsWide();
				}
			}
		}

		mIsTexAllLoaded = allLoaded;
		if(mIsTexAllLoaded)
			AspriteManager::instance().AnimationDelayLoadCall(this);
	}
}


void ASprite::tick(float deltaTime)
{
	log("ASprite tick");
#if 0
	if (mIsTexAllLoaded)
		return;

 	m_totalUpdateTime += deltaTime;
 	if (m_totalUpdateTime - m_lastUpdateTime > 2)
 	{
 		m_lastUpdateTime = m_totalUpdateTime;
 		
		/*
 		if (!CCMemoryMonitor::sharedMemoryMonitor()->isMemoryLackEmergence())
 		{
 			if (m_texture)
 			{
 				if (!m_texture->isLoaded)
 				{
 					CCTextureCache::sharedTextureCache()->addImageAsync(m_texture->fileName.c_str(), this, (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
					m_texture->isLoaded = true;
 				}
 			}
 			else
 			{
 				for (size_t n = 0; n < m_textures.size(); ++n)
 				{
 					TextureWrap* tw = m_textures[n];
 					if (!tw->isLoaded)
 					{
 						CCTextureCache::sharedTextureCache()->addImageAsync(tw->fileName.c_str(), this, (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
						tw->isLoaded = true;
 					}
 				}
 			}
 		}
		*/
 	}
#endif
}

int ASprite::GetAFrameTime(int anim, int aframe)
{
	if(anim < 0 || anim >= animnumber)
		return 0;
	return _aframes[(_anims_af_start[anim] + aframe) * 5 + 1] & 0xFFFF;
}


int ASprite::GetAFrames(int anim)
{
	if(anim < 0 || anim >= animnumber)
		return 0;
	return _anims_naf[anim]&0xFF;
}

int ASprite::GetRealAFrames(int anim)
{
	if(anim < 0 || anim >= animnumber)
		return 0;
	return _real_anims_naf[anim];
}

int ASprite::GetFModules(int frame)
{
	//return _frames_nfm[frame]&0xFF;
	return _frames_nfm[frame]&0xFF;
}

int ASprite::GetModuleWidth(int module)
{
	//BS_MODULES_WH_SHORT
	return _modules_w[module]&0xFFFF;
}

int ASprite::GetModuleHeight(int module)
{
	return _modules_h[module]&0xFF;
}

int ASprite::GetFrameWidth(int frame)
{
	return _frames_rc[frame*4 + 2]&0xFF;
}

int ASprite::GetFrameHeight(int frame)
{
	return _frames_rc[frame*4 + 3]&0xFF;
}


int ASprite::GetFrameCollisionLeft(int frame)
{
	return _frames_coll[frame*4 + 0];
}

int ASprite::GetFrameCollisionTop(int frame)
{
	return _frames_coll[frame*4 + 1];
}

int ASprite::GetFrameCollisionRight(int frame)
{
	return _frames_coll[frame*4 + 2];
}

int ASprite::GetFrameCollisionBottom(int frame)
{
	return _frames_coll[frame*4 + 3];
}


int ASprite::GetFrameModuleX(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;

	off += (_frames_fm_start[frame] + fmodule)<<2;
	return (_fmodules[off + 2] & 0xff) + ((_fmodules[off + 3])<<8);
}

int ASprite::GetFrameModuleY(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;

	off += (_frames_fm_start[frame] + fmodule)<<2;
	return (_fmodules[off + 4] & 0xff) + ((_fmodules[off + 5])<<8);
}

int ASprite::GetFrameModuleWidth(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;
	off += (_frames_fm_start[frame] + fmodule)<<2;
	int index = (_fmodules[off]&0xFF) + ((_fmodules[off+1])<<8);

	assert(index < _nModules);
	//BS_MODULES_WH_SHORT
	return _modules_w[index]&0xFFFF;
}

int ASprite::GetFrameModuleHeight(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;
	off += (_frames_fm_start[frame] + fmodule)<<2;
	int index = (_fmodules[off]&0xFF) + ((_fmodules[off+1])<<8);
	return _modules_h[index]&0xFFFF;
}


int ASprite::GetAnimFrame(int anim, int aframe)
{
	int off = (_anims_af_start[anim] + aframe) * 5;
	return _aframes[off]&0xFFFF;
}

void ASprite::GetFrameRect(int * rc, int frame, int posX, int posY, int flags, int hx, int hy)
{
#if 1
	/*if (USE_PRECOMPUTED_FRAME_RECT)
	{
		int frame4 = frame<<2;
		int fx = _frames_rc[frame4++];
		int fy = _frames_rc[frame4++];
		int fw = _frames_rc[frame4++]&0xFF;
		int fh = _frames_rc[frame4++]&0xFF;

		if ((flags & FLAG_FLIP_X) != 0)	
			hx += fx + fw;
		else
			hx -= fx;
		if ((flags & FLAG_FLIP_Y) != 0)	
			hy += fy + fh;
		else
			hy -= fy;

		rc[0] = posX - (hx << FIXED_PRECISION);
		rc[1] = posY - (hy << FIXED_PRECISION);
		rc[2] = rc[0] + (fw << FIXED_PRECISION);
		rc[3] = rc[1] + (fh << FIXED_PRECISION);
	}
	else*/
	{
		int fx = 0;
		int fy = 0;
		int fw = 0;
		int fh = 0;

		//int nFModules = _frames_nfm[frame]&0xFF;
		int nFModules = _frames_nfm[frame]&0xFFFF;

		for (int fmodule = 0; fmodule < nFModules; fmodule++)
		{
			GetFModuleRect(rc, frame, fmodule, posX, posY, flags, hx, hy);

			if (rc[0] < fx)
			{
				fw = (fx+fw) - rc[0];
				fx = rc[0];
			}

			if (rc[1] < fy)
			{
				fh = (fy+fh) - rc[1];
				fy = rc[1];
			}

			if (rc[2] > fx + fw)
			{
				fw = rc[2] - fx;
			}

			if (rc[3] > fy + fh)
			{
				fh = rc[3] - fy;
			}
		}

		hx <<= FIXED_PRECISION;
		hy <<= FIXED_PRECISION;

		if ((flags & FLAG_FLIP_X) != 0)	
			hx += fx + fw;
		else
			hx -= fx;
		if ((flags & FLAG_FLIP_Y) != 0)	
			hy += fy + fh;
		else
			hy -= fy;

		rc[0] = posX - hx;
		rc[1] = posY - hy;
		rc[2] = rc[0] + fw;
		rc[3] = rc[1] + fh;
	}
#endif
}


void ASprite::GetFModuleRect(int * rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy)
{
	rc[0] = GetFrameModuleX(frame, fmodule) << FIXED_PRECISION;
	rc[1] = GetFrameModuleY(frame, fmodule) << FIXED_PRECISION;
	rc[2] = rc[0] + (GetFrameModuleWidth(frame, fmodule) << FIXED_PRECISION);
	rc[3] = rc[1] + (GetFrameModuleHeight(frame, fmodule) << FIXED_PRECISION);      
}

void ASprite::GetModuleRect(int * rc, int module, int posX, int posY, int flags)
{
	rc[0] = posX;
	rc[1] = posY;
	//BS_MODULES_WH_SHORT
	rc[2] = posX + ((_modules_w[module]&0xFFFF) << FIXED_PRECISION);
	rc[3] = posY + ((_modules_h[module]&0xFFFF) << FIXED_PRECISION);
}


void ASprite::PaintAFrame( int anim, int aframe, int posX, int posY, int flags, int hx, int hy, int opacity, bool isGray)
{
	if (!mIsTexAllLoaded || !mIsDataLoaded)
		return;
	if (GetAFrames(anim) <= aframe)
		return;

	int off = (_anims_af_start[anim] + aframe) * 5;
	int frame = _aframes[off] & 0xFFFF;

	log("-----ASprite:PaintAFrame anim:%d, aframe:%d, off:%d, frame:%d", anim, aframe, off, frame);

	//if ( this == GetSprite( 2, ACTORTYPE_SKILL_F ) )
	//{
	//	int z = 0;
	//}
	/* TODO: 
	if(USE_INDEX_EX_AFRAMES)
	{
		frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
	}
	//*/

	if ((flags & FLAG_FLIP_X) != 0)
		hx += _aframes[off + 2];
	else
		hx -= _aframes[off + 2];
	if ((flags & FLAG_FLIP_Y) != 0)	
		hy -= _aframes[off + 3];
	else
		hy += _aframes[off + 3];

	PaintFrame( frame, posX - hx, posY - hy, flags ^ (_aframes[off + 4] & 0x000F), hx, hy, opacity, isGray);
}

void ASprite::PaintFrame( int frame, int posX, int posY, int flags, int hx, int hy, int opacity, bool isGray)
{
	/*int nFModules = _frames_nfm[frame]&0xFF;*/
	int nFModules = (_frames_nfm[frame] & 0xFF);
	log("------ASprite::PaintFrame==%d", nFModules);
	
	for (int fmodule = 0; fmodule < nFModules; fmodule++) {
		PaintFModule( frame, fmodule, posX, posY, flags, hx, hy, opacity, isGray);
	}
}

void ASprite::PaintFModule( int frame, int fmodule, int posX, int posY, int flags, int hx, int hy, int opacity, bool isGray)
{
	
#if 1
	int off = (_frames_fm_start[frame] + fmodule) << 2;
	off += (_frames_fm_start[frame] + fmodule) << 2;
	int fm_flags = (_fmodules[off + 6] & 0xFF) + ((_fmodules[off + 7]) << 8);
	int index = (_fmodules[off] & 0xFF) + ((_fmodules[off+1]) << 8);

	log("-------ASprite:PaintFModule off:%d, index:%d", off, index);
	//if (USE_INDEX_EX_FMODULES)
	//	index |= ((fm_flags&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
	{
		if ((flags & FLAG_FLIP_X) != 0)
			posX -= GetFrameModuleX(frame, fmodule);
		else						
			posX += GetFrameModuleX(frame, fmodule);
		if ((flags & FLAG_FLIP_Y) != 0)	
			posY += GetFrameModuleY(frame, fmodule);
		else							
			posY -= GetFrameModuleY(frame, fmodule);

		posY -=  GetFrameModuleHeight(frame, fmodule);
	}
	

	/*
	if (USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0))
	{
		PaintFrame( index, posX, posY, flags ^ (fm_flags&0x0F), hx, hy);
	}
	else ./*/
	{
		//BS_MODULES_WH_SHORT
		if ((flags & FLAG_FLIP_X) != 0)	posX -= _modules_w[index]&0xFFFF;
		if ((flags & FLAG_FLIP_Y) != 0)	posY -= _modules_h[index]&0xFFFF;

		PaintModule(frame ,index, posX, posY, flags ^ (fm_flags&0x0F), opacity, isGray);
	}
#endif
}



void ASprite::PaintModule(int frame, int module, int posX, int posY, int flags, int opacity, bool isGray)
{
#if 1
	log("--------ASprite::PaintModule--name=%s f=%d module=%d posx=%d posy=%d",this->mSpriteName.c_str(), frame, module, posX, posY);
	int texSizeX = _modules_w[module] & 0xFFFF;
	int texSizeY = _modules_h[module] & 0xFFFF;
	if (texSizeX <= 0 || texSizeY <= 0) return;

	const int texX = _modules_x[module];
	const int texY = _modules_y[module];

	if (_modules_flag[module] != MOUDLE_MARK) {
		if(m_textures.empty()) {
			int rectWidth(texSizeX), rectHeight(texSizeY);
			DrawRegion( 0, texX, texY, texSizeX, texSizeY, flags, posX, posY, rectWidth, rectHeight, opacity, isGray );
		} else {
			int perHeight = m_textureSquareSize;
			int texIdx = texY / perHeight;
			int realTexY = texY % perHeight;
			int realTexSizeY = realTexY + texSizeY;
			int rectWidth;
			int rectHeight;
			int rectX;
			int rectY;
			if( realTexSizeY > perHeight) {
				rectX = posX;
				rectY = posY + realTexSizeY - perHeight;
				rectWidth = texSizeX;
				rectHeight = perHeight - realTexY;
				DrawRegion( texIdx,
					texX,
					realTexY,
					texSizeX,
					perHeight - realTexY,
					flags,
					rectX,
					rectY,
					rectWidth,
					rectHeight,
					opacity,isGray );

				rectX = posX;
				rectY = posY;
				rectWidth = texSizeX;
				rectHeight = realTexSizeY - perHeight;
				DrawRegion( texIdx + 1,
					texX, 
					0, 
					texSizeX, 
					realTexSizeY - perHeight,
					flags,
					rectX,
					rectY,
					rectWidth, 
					rectHeight,
					opacity, isGray );
			} else {
				int rectWidth(texSizeX), rectHeight(texSizeY);
				DrawRegion( texIdx,
					texX,
					realTexY,
					texSizeX,
					texSizeY,
					flags,
					posX, 
					posY, 
					rectWidth,
					rectHeight,
					opacity, isGray );
			}
		}
	}
#endif
}

void ASprite::SetClip( const Rect& rect )
{
    
	if (!m_clipRect) m_clipRect = new Rect();

	*m_clipRect = rect;
}

void ASprite::ResetClip()
{
	SAFE_DELETE(m_clipRect);
}

mark_info ASprite::CheckMarkExs(int ainmID,int aframe)
{
	mark_info info;
#if 0
	int off = (_anims_af_start[ainmID] + aframe) * 5;
	int frame = _aframes[off] & 0xFFFF;
	//int nFModules = _frames_nfm[frame]&0xFF;
	int nFModules = _frames_nfm[frame]&0xFF;


	if (nFModules<2)
	{
		info.m_markExist =false;
		return info;
	}
	for (int i = 0; i<nFModules ; i++)
	{
		int off = (_frames_fm_start[frame] + i) << 2;
		off += (_frames_fm_start[frame] + i)<<2;
		int fm_flags =  (_fmodules[off+6]&0xFF) + ((_fmodules[off+7])<<8);
		int index = (_fmodules[off]&0xFF) + ((_fmodules[off+1])<<8);

		if(_modules_flag[index] == MOUDLE_MARK)
		{
			info.m_markExist=true;
			info.mark_frame =frame;
			info.mark_moudeID = i;
			info.mark_desc = _MarkerDesc[index];
		}
	}
#endif
	return info;
}

void ASprite::ForceLoadTexture()
{
	if(mIsTexAllLoaded)
		return;
	if (m_texture) {
		if (!m_texture->isLoaded) {
			//TextureCache::getInstance()->addImageAsync(m_texture->fileName.c_str(), (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
			TextureCache::getInstance()->addImageAsync(m_texture->fileName.c_str(), CC_CALLBACK_1(ASprite::onAsyncLoadedTexture, this));
			m_texture->isLoaded = true;
		}
	} else {
		for (size_t n = 0; n < m_textures.size(); ++n) {
			TextureWrap* tw = m_textures[n];
			if (!tw->isLoaded) {
				//TextureCache::getInstance()->addImageAsync(tw->fileName.c_str(), (SEL_CallFuncO)(&ASprite::onAsyncLoadedTexture));
				TextureCache::getInstance()->addImageAsync(m_texture->fileName.c_str(), CC_CALLBACK_1(ASprite::onAsyncLoadedTexture, this));
				tw->isLoaded = true;
			}
		}
	}
}

bool ASprite::IsTextureLoaded()
{
	return mIsTexAllLoaded;
}

bool ASprite::IsDataLoaded() const
{
	return mIsDataLoaded;
}

bool ASprite::IsTextureDelayLoad()
{
	if(mIsTexAllLoaded)
		return false;
	if (m_texture) {
		return !m_texture->isLoaded;
	} else {
		if(m_textures.empty())
			return true;
		return !m_textures[0]->isLoaded;
	}
}

void ASprite::ReleaseTextureToDelayLoad()
{
	mIsTexAllLoaded = false;

	if(m_texture) {
// 		CCTextureCache::sharedTextureCache()->removeTexture(m_texture->texture);
// 		m_texture->texture = NULL;
// 		
		CC_SAFE_RELEASE_NULL(m_texture->texture);
		m_texture->isLoaded = false;
	}

	for (TextureVector::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		TextureWrap* pTexture = (*it);
		//CCTextureCache::sharedTextureCache()->removeTexture(pTexture->texture);
		//pTexture->texture = NULL;
		CC_SAFE_RELEASE_NULL(pTexture->texture);
		pTexture->isLoaded = false;
	}
}
