//
//  Header.h
//  SpaceWarriors
//
//  Created by Nikita on 13-6-24.
//
//

#ifndef SpaceWarriors_Header_h
#define SpaceWarriors_Header_h

#include "cocos2d.h"

USING_NS_CC;

class ColorHelper
{
public:
    inline static int getValue(const ccColor3B& color)
    {
        GLubyte r = color.r;
        GLubyte g = color.g;
        GLubyte b = color.b;
        int value = (r << 16) + (g << 8) + b;
        return value;
    }
    
    inline static ccColor3B valueOf(int value)
    {
        GLubyte r = (value & 0xff0000) >> 16;
        GLubyte g = (value & 0x00ff00) >> 8;
        GLubyte b = (value & 0xff);
        ccColor3B color = {r,g,b};
        return color;
    }
    
    inline static ccColor3B Add(const ccColor3B& color1,const ccColor3B& color2)
    {
        GLubyte r = (color1.r + color2.r)%0xff;
        GLubyte g = (color1.r + color2.r)%0xff;
        GLubyte b = (color1.r + color2.r)%0xff;
        ccColor3B color = {r,g,b};
        return color;
    }
    
    inline static ccColor3B reduce(const ccColor3B& color1,const ccColor3B& color2)
    {
        GLubyte r = (color1.r - color2.r)%0xff;
        GLubyte g = (color1.r - color2.r)%0xff;
        GLubyte b = (color1.r - color2.r)%0xff;
        ccColor3B color = {r,g,b};
        return color;
    }
};

#endif
