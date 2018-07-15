//
//  UIFeiDiaoLayer.h
//  SpaceWarriors
//
//  Created by Nikita on 13-5-5.
//
//

#ifndef SpaceWarriors_UIFeiDiaoLayer_h
#define SpaceWarriors_UIFeiDiaoLayer_h

#include "cocos2d.h"

class UIFeiDiaoLayer
{
public:
    static inline std::string sdafwefc(FILE *pfile)
    {
        CCAssert(pfile, "ProjReader::readString(FILE *pfile)-pfile is null!");
        int len_num = 0;
        fread(&len_num, sizeof(int), 1, pfile);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        char buffer[1024];
#else
        char buffer[len_num];
#endif
        
        int len = fread(buffer, sizeof(char), len_num, pfile);
        buffer[len] = '\0';
        std::string re(buffer);
        return re;
    }
    
    static inline void UIFeiDiaoLayeewr(FILE* pfile,const std::string& str)
    {
        CCAssert(pfile, "pfile is null!");
        int len_num = (int)str.length();
        fwrite(&len_num, sizeof(int), 1, pfile);
        fwrite(str.c_str(), sizeof(char), len_num, pfile);
    }
    
    static inline int hel001(FILE *pfile)
    {
        CCAssert(pfile, "ProjReader::hel001(FILE *pfile)-pfile is null!");
        int num = 0;
        fread(&num, sizeof(int), 1, pfile);
        return num;
    }
    
    static inline void hel002(FILE* pfile,const int& num)
    {
        CCAssert(pfile, "pfile is null!");
        if(fwrite(&num, sizeof(int), 1, pfile) == 0)
        {
            CCAssert(false, "write error!");
        }
    }
    
    static inline float hel003(FILE *pfile)
    {
        CCAssert(pfile, "ProjReader::hel003(FILE *pfile)-pfile is null!");
        float num = 0;
        fread(&num, sizeof(float), 1, pfile);
        return num;
    }
    
    static inline void hel004(FILE* pfile,const float& num)
    {
        CCAssert(pfile, "pfile is null!");
        if(fwrite(&num, sizeof(float), 1, pfile) == 0)
        {
            CCAssert(false, "write error!");
        }
    }
    
    static inline bool hel0090558(FILE *pfile)
    {
        CCAssert(pfile, "ProjReader::hel0090558(FILE *pfile)-pfile is null!");
        bool num = false;
        fread(&num, sizeof(bool), 1, pfile);
        return num;
    }
    
    static inline void hel00905(FILE* pfile,const bool& num)
    {
        CCAssert(pfile, "pfile is null!");
        if(fwrite(&num, sizeof(bool), 1, pfile) == 0)
        {
            CCAssert(false, "write error!");
        }
    }
    
    static inline ccColor3B hel0090(int value)
    {
        int red = (value >> 16) & 0xff;
        int green = (value >> 8) & 0xff;
        int blue = value & 0xff;
        ccColor3B color = {red,green,blue};
        return color;
    }
    
    static inline const char* hel009(const char* path)
    {
        std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path);
        unsigned char* pData = NULL;
        unsigned long len = 0;
        pData = CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "rb", &len);
        std::string destpath = CCFileUtils::sharedFileUtils()->getWriteablePath();
        std::string buf = path;
        {
            for (int i = 0; i < buf.size(); i++)
            {
                if (buf[i] == '/')
                    buf[i] = '_';
            }
        }
        destpath += buf;
        CCLog("copy data from [%s] to [%s].",fullpath.c_str()
              ,destpath.c_str());
        FILE* fp = fopen(destpath.c_str(), "w");
        fwrite(pData, sizeof(char), len, fp);
        fclose(fp);
        delete pData;
        pData = NULL;
        return destpath.c_str();
    }
};
#endif
