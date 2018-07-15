//
//  XmlResolver.cpp
//  SanguoHeros
//
//  Created by 伟 李 on 12-10-13.
//  Copyright (c) 2012年 intelligame. All rights reserved.
//

#include <iostream>
#include "XmlResolver.h"

void XmlResolver::loadXml(const char *xmlFile, XmlResolverListener* pListener)
{
    assert(xmlFile && pListener);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    TiXmlDocument* pXmlDoc = new TiXmlDocument();
    unsigned long size;
    char* pFileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(xmlFile,"r",&size);
    pXmlDoc->Parse(pFileContent, 0, TIXML_ENCODING_UTF8);
    delete [] pFileContent;
#else
    TiXmlDocument* pXmlDoc = new TiXmlDocument(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xmlFile));
    pXmlDoc->LoadFile();
#endif
    TiXmlElement* pCurElement = pXmlDoc->RootElement();
    assert(pCurElement);
    TiXmlElement* pNextElement = NULL;
    bool traverse = false;
    do {
        assert(pCurElement);
        if(traverse)
        {
            pListener->onResolveElementEnd(pCurElement->Value());
            if(pCurElement->NextSiblingElement())
            {
                pNextElement = pCurElement->NextSiblingElement();
                traverse = false;
            }
            else if(pCurElement->Parent()->ToElement()){
                pNextElement = pCurElement->Parent()->ToElement();
            }
            else {
                break;
            }
        }
        else{
//            CCLog(pCurElement->Value());
            pListener->onResolveElement(pCurElement->Value());
            resolveAttribute(pCurElement, pListener);
            if(pCurElement->FirstChildElement()){
                pNextElement = pCurElement->FirstChildElement();
                traverse = false;
            }
            else{
                traverse = true;
                continue;
            }
        }
        assert(pNextElement);
        pCurElement = pNextElement;
        pNextElement = NULL;
    } while (true);
    delete pXmlDoc;
}

void XmlResolver::resolveAttribute(TiXmlElement *pElement,XmlResolverListener* pListener)
{
    assert(pElement && pListener);
    TiXmlAttribute* pAttr = pElement->FirstAttribute();
    while(pAttr)
    {
        pListener->onResolveAttribute(pAttr->Name(), pAttr->Value());
        pAttr = pAttr->Next();
    }
}