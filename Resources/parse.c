#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <map>

#define ALWAYS_BS_NFM_1_BYTE	0
#define ALWAYS_BS_NAF_1_BYTE    0
#define ALWAYS_BS_SKIP_FRAME_RC 1
#define FIXED_PRECISION         0

#define FLAG_FLIP_X            (1<<0) 
#define FLAG_FLIP_Y            (1<<1)   
#define FLAG_ROT_90            (1<<2)

#define USE_MODULE_MAPPINGS     0
#define MAX_FREAM_CORRECTION    10

using namespace std;

enum MOUDLE_TYPE
{
        MOUDLE_NORMAL = 0,
        MOUDLE_MARK = 253,
};

#if 1
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

int GetAFrameTime(int anim, int aframe) {
        if(anim < 0 || anim >= animnumber)
                return 0;
        return _aframes[(_anims_af_start[anim] + aframe) * 5 + 1] & 0xFFFF;
}


int GetAFrames(int anim) {
        if(anim < 0 || anim >= animnumber)
                return 0;
        return _anims_naf[anim]&0xFF;
}


int GetFrameModuleX(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;

	off += (_frames_fm_start[frame] + fmodule)<<2;
	return (_fmodules[off + 2] & 0xff) + ((_fmodules[off + 3])<<8);
}

int GetFrameModuleY(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;

	off += (_frames_fm_start[frame] + fmodule)<<2;
	return (_fmodules[off + 4] & 0xff) + ((_fmodules[off + 5])<<8);
}

int GetFrameModuleWidth(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;
	off += (_frames_fm_start[frame] + fmodule)<<2;
	int index = (_fmodules[off]&0xFF) + ((_fmodules[off+1])<<8);

	//assert(index < _nModules);
	//BS_MODULES_WH_SHORT
	return _modules_w[index]&0xFFFF;
}

int GetFrameModuleHeight(int frame, int fmodule)
{
	int off = (_frames_fm_start[frame] + fmodule) << 2;
	off += (_frames_fm_start[frame] + fmodule)<<2;
	int index = (_fmodules[off]&0xFF) + ((_fmodules[off+1])<<8);
	return _modules_h[index]&0xFFFF;
}


void GetFModuleRect(int * rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy)
{
	rc[0] = GetFrameModuleX(frame, fmodule) << FIXED_PRECISION;
	rc[1] = GetFrameModuleY(frame, fmodule) << FIXED_PRECISION;
	rc[2] = rc[0] + (GetFrameModuleWidth(frame, fmodule) << FIXED_PRECISION);
	rc[3] = rc[1] + (GetFrameModuleHeight(frame, fmodule) << FIXED_PRECISION);      
}


void GetFrameRect(int * rc, int frame, int posX, int posY, int flags, int hx, int hy)
{
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
}

#endif

int main(){
        ifstream is("m16.bsprite");

        is.seekg(0, is.end);
        int length = is.tellg();//返回当前位置指针到文件开头的距离
        is.seekg(0, is.beg);
        char *data = new char[length];   //开辟缓冲区
        is.read(data, length);    //把数据当成一个块来读
        is.close();
#if 1
	int offset = 0;
	//读取版本号 :1503
	short bs_version = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
	offset +=2 ;
	cout <<"VERSION:"<<bs_version<<endl;
	//读取生成标志位
	int bs_flags =  ((data[offset]&0xFF)    ) +
		((data[offset+1]&0xFF)<< 8) +
		((data[offset+2]&0xFF)<<16) +
		((data[offset+3]&0xFF)<<24);
	offset += 4 ;

	//读取模型
	_nModules = (data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8);
	offset += 2 ;
	cout <<"MODULES:"<<_nModules<<endl;

	//赋值模型参数  X Y  高 宽
	if (_nModules > 0) {
		for (int i = 0; i < _nModules; i++) {
			_modules_flag.push_back(data[offset]&0xFF); 
			offset++;
			if (_modules_flag[i] != MOUDLE_MARK){
				_modules_x.push_back((data[offset]&0xFF) + ((data[offset + 1]&0xFF)<<8));
				offset += 2;
				_modules_y.push_back((data[offset]&0xFF) + ((data[offset + 1]&0xFF)<<8));
				offset += 2;
			}else{
				_modules_x.push_back(0);
				_modules_y.push_back(0);
			}
			{


			_modules_w.push_back((data[offset]&0xFF) + ((data[offset + 1]&0xFF)<<8));
			offset += 2;
			_modules_h.push_back((data[offset]&0xFF) + ((data[offset + 1]&0xFF)<<8));
			offset += 2;
			if (_modules_flag[i] == MOUDLE_MARK) {
				short descLength = (data[offset]&0xFF) + ((data[offset + 1]&0xFF)<<8);
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
	int nFModules = (data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8);
	offset += 2 ;

	if (nFModules > 0) {
		if (nFModules >_nModules + MAX_FREAM_CORRECTION) {
			//char Tex[1024];
			//
			//ErrorLog("-----------------------------------------------------------");
			//sprintf(Tex,"Error : load the Bsprite:%s  is filed",pszFileName);
			//ErrorLog(Tex);
			//
			//sprintf(Tex,"when the error happen the variable offset's number is:%d",offset);
			//ErrorLog(Tex);
			//ErrorLog("-----------------------------------------------------------");
		}

		int len = nFModules<<2;

		{
			len += nFModules<<2;
		}
		//赋值模型参数  ID
		for (int i=0;i<len;i++){
			_fmodules.push_back(data[offset]);
			offset++;
		}

	}

	//读取frame   -  编号
	int nFrames = (data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8);
	offset += 2 ;

	if (nFrames > 0){
		_frames_nfm      = new short[nFrames + 1];
		_frames_fm_start = new short[nFrames + 1];

		memset(_frames_nfm, 0, sizeof(short) * (nFrames + 1));
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
	int nAFrames = (data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8);
	offset += 2 ;

	if (nAFrames > 0)
	{
		int len = nAFrames*5 ;
		_aframes = new short[len + 1];
		memset(_aframes, 0, sizeof(short) * (len + 1));
		//赋值动画帧
		for (int i = 0; i < len; i++)
		{
			_aframes[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;
		}
	}
	//读取动画
	int nAnims = (data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8);
	animnumber = nAnims;
	_real_anims_naf.resize(animnumber);
	offset += 2 ;

	if (nAnims > 0)
	{
		_anims_naf      = new  short[nAnims];
		_anims_af_start = new short[nAnims];

		memset(_anims_naf, 0, sizeof(short) * nAnims);
		memset(_anims_af_start, 0, sizeof(short) * nAnims);
		//赋值动画
		for (int i = 0; i < nAnims; i++)
		{
			_anims_naf[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;

			_anims_af_start[i] = (short)((data[offset]&0xFF) + ((data[offset+1]&0xFF)<<8));
			offset += 2 ;

			int realAnimNum = 0;
			for(int j = 0; j < GetAFrames(i); ++j)
			{
				realAnimNum += GetAFrameTime(i, j);
			}
			_real_anims_naf[i] = realAnimNum;
		}
	}	

	int rc[4];

	if(nFrames != 0)
	{
		GetFrameRect(rc, 0, 0, 0, 0, 0, 0);
		//m_rcSelect = CCRectMake(rc[0], -rc[3], rc[2]-rc[0], rc[3]-rc[1]);
	}

	// OMP: shrink-to-fit
	vector<short>( _modules_x  ).swap( _modules_x );
	vector<short>( _modules_y  ).swap( _modules_y );
	vector<short>( _modules_w  ).swap( _modules_w );
	vector<short>( _modules_h  ).swap( _modules_h );
	vector<unsigned char>( _modules_flag ).swap( _modules_flag );
	vector<signed char>( _fmodules  ).swap( _fmodules );
#endif
	return 1;
}
