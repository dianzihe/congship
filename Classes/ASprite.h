#pragma  once

#include "base.h"
#include "ActorType.h"
#include "SimpleEventDefine.h"

enum MOUDLE_TYPE
{
	MOUDLE_NORMAL = 0,
	MOUDLE_MARK = 253,
};
enum AnimaEventType
{
	eAnimaEventType_Null,
	eAnimaEventType_Marker,
	eAnimaEventType_Count,
};

struct AnimaEvent
{
	AnimaEventType _EventType;
	std::vector<EventParam> _EventParamList;
};

struct mark_info
{
	bool m_markExist;
	int  mark_frame;
	int  mark_moudeID;
	string  mark_desc;

	mark_info()
	{
		m_markExist  = false;
		mark_moudeID = 0;
		mark_frame   = 0;
	}
};

struct IAnimaEventHandler
{
	virtual void ProcessAnimaEvent( AnimaEvent* event ) = 0;
};

struct TextureWrap
{
	TextureWrap() : texture(NULL)
		, isLoaded(false)
	{}
	
	~TextureWrap()
	{
		//CCTextureCache::sharedTextureCache()->removeTexture(texture);
		CC_SAFE_RELEASE(texture);
	}

	std::string fileName;
	CCTexture2D* texture;
	bool isLoaded;
	
};

class ASprite : public CCObject
{
public:	
	typedef std::vector<TextureWrap*> TextureVector;

	ASprite();
	~ASprite();

	bool Load(const char* resName, ACTORTYPE actorType, bool isMustLoad);
	bool IsTextureLoaded();
	bool IsDataLoaded() const;
	bool IsTextureDelayLoad();
	void ForceLoadTexture();
	int GetAFrameTime(int anim, int aframe);
	int GetAFrames(int anim);
	int GetRealAFrames(int anim);
	int GetFModules(int frame);
	int GetModuleWidth(int module);
	int GetModuleHeight(int module);
	int GetFrameWidth(int frame);
	int GetFrameHeight(int frame);
	int GetFrameCollisionLeft(int frame);
	int GetFrameCollisionTop(int frame);
	int GetFrameCollisionRight(int frame);
	int GetFrameCollisionBottom(int frame);
	int GetFrameModuleX(int frame, int fmodule);
	int GetFrameModuleY(int frame, int fmodule);
	int GetFrameModuleWidth(int frame, int fmodule);
	int GetFrameModuleHeight(int frame, int fmodule);
	int GetAnimFrame(int anim, int aframe);
	int GetAnimNumber ();
	void GetFrameRect(int * rc, int frame, int posX, int posY, int flags, int hx, int hy);
	void GetFModuleRect(int * rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy);
	void GetModuleRect(int * rc, int module, int posX, int posY, int flags);

	void PaintAFrame( int anim, int aframe, int posX, int posY, int flags, int hx, int hy, int opacity=255, bool isGray = false);
	void PaintFrame( int frame, int posX, int posY, int flags, int hx, int hy, int opacity=255, bool isGray = false);
	void PaintFModule( int frame, int fmodule, int posX, int posY, int flags, int hx, int hy, int opacity=255, bool isGray = false);
	void PaintModule(int frame, int module, int posX, int posY, int flags, int opacity=255, bool isGray = false);

	void clear_patch();
	
	mark_info CheckMarkExs(int ainmID,int aframe);
	void SetClip(const CCRect& rect  ) ;
	void ResetClip();

	const CCRect&				getRectSelect( void )		{ return m_rcSelect; }

	const std::string&			getSpriteName()				{ return mSpriteName; }

	void						setSpriteName( const std::string& name) { mSpriteName = name; }

public:
	void LoadData(char* data);

	void onLoadData(CCObject* obj);
	
	void onAsyncLoadedTexture(CCTexture2D* pTexture);

	void ReleaseTextureToDelayLoad();

	void tick(float deltaTime);

	// To Be Abandon
	TextureWrap* m_texture;
	// With
	TextureVector m_textures;
	// Square Texture Size
	int m_textureSquareSize;

	int			_nModules; //模型数量
	vector<short> _modules_x; //模型x   marker此项目为 0
	vector<short> _modules_y; //模型y   marker此项目为 0
	vector<short> _modules_w ; //模型宽
	vector<short> _modules_h;  //模型高
	vector<unsigned char>   _modules_flag;  //模型标志 MD_IMAGE=0 MD_MARKER=253


	short *	_frames_nfm;  //frame模型编号

	short *			_frames_fm_start; //frame的编号
	signed char  *	_frames_rc;
	signed char  *	_frames_coll;
	vector <signed char>	_fmodules;  //存放所有frame模型块  frame模型块=(frame编号（short） + ox（short） + oy（short） + flag(short))

	map <int, std::string> _MarkerDesc; //marker的秒速， int代表模块编号， string 代表描述。

	short *	_anims_naf;  //动画的帧数量
	vector<char> _real_anims_naf; //动画真实的帧数量，考虑到定帧
	short *	    _anims_af_start; //动画的起始帧
	short *	_aframes;    //存放动画的帧描述块   块=（编号（从1开始） + 时间(默认1) + ox + oy + flag(默认0)） 

	int animnumber;
	
	void DrawRegion( int texIdx, int texX, int texY, int texSizeX, int texSizeY, int flag, int posX, int posY, int rectWidth, int rectHeight, int opacity, bool isGray = false);

	CCRect* m_clipRect;

	CCRect			m_rcSelect;

	std::string		mSpriteName;

	bool			mIsTexAllLoaded;
	bool			mIsDataLoaded;
	/*
	int * *		_map;
	int * *		_pal;
	int			_palettes;
	int	        _crt_pal;
	bool		_alpha;
	*/

	float m_lastUpdateTime;
	float m_totalUpdateTime;
};

