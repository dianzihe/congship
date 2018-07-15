//
//  StringTools.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-12-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef SanguoHeros_StringTools_h
#define SanguoHeros_StringTools_h

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class StringTools
{
public:
    static void splitString(const string& src, const string& separator, vector<string>& dest)
    {
        string str = src;
        string substring;
        string::size_type start = 0, index;
        
        do
        {
            index = str.find_first_of(separator,start);
            if (index != string::npos)
            {    
                substring = str.substr(start,index-start);
                dest.push_back(substring);
                start = str.find_first_not_of(separator,index);
                if (start == string::npos) return;
            }
        }while(index != string::npos);
        //the last token
        substring = str.substr(start);
        dest.push_back(substring);
    }
    
    //! convert from wstring to UTF8 using self-coding-converting
    static inline void WStrToUTF8(std::string& dest, const wstring& src)
    {
        dest.clear();
        for (size_t i = 0; i < src.size(); i++)
        {
            wchar_t w = src[i];
            if (w <= 0x7f)
                dest.push_back((char)w);
            else if (w <= 0x7ff)
            {
                dest.push_back(0xc0 | ((w >> 6)& 0x1f));
                dest.push_back(0x80| (w & 0x3f));
            }
            else if (w <= 0xffff)
            {
                dest.push_back(0xe0 | ((w >> 12)& 0x0f));
                dest.push_back(0x80| ((w >> 6) & 0x3f));
                dest.push_back(0x80| (w & 0x3f));
            }            else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
            {
                dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
                dest.push_back(0x80| ((w >> 12) & 0x3f));
                dest.push_back(0x80| ((w >> 6) & 0x3f));
                dest.push_back(0x80| (w & 0x3f));
            }
            else
                dest.push_back('?');
        }
    }
    
    //! simple warpper
    static inline std::string WStrToUTF8(const std::wstring& str)
    {
        std::string result;
        WStrToUTF8(result, str);
        return result;
    }
};
#endif
