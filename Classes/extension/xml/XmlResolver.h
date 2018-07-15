//
//  XmlResolver.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-13.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#ifndef SanguoHeros_XmlResolver_h
#define SanguoHeros_XmlResolver_h

#include "tinyxml.h"
#include "cocos2d.h"

USING_NS_CC;

class XmlResolverListener;

class XmlResolver
{
public:
    XmlResolver() {}
    virtual ~XmlResolver() {}
    
    virtual void loadXml(const char* xmlFile,XmlResolverListener* pListener);
    virtual void resolveAttribute(TiXmlElement* pElement,XmlResolverListener* pListener);
};

class XmlResolverListener
{
public:
    virtual void onResolveElement(const char* name) = 0;
    virtual void onResolveElementEnd(const char* name) = 0;
    virtual void onResolveAttribute(const char* name,const char* value) = 0;
};

#endif
