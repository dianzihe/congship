//
//  UserRecord.cpp
//  SpaceWarriors
//
//  Created by Nikita on 13-7-22.
//
//

#include "UserRecord.h"
#include "../utils/base64.h"
#include "../utils/sha1.h"

UserRecord* UserRecord::m_pSingle = NULL;

UserRecord* UserRecord::shared()
{
    if(!m_pSingle)
    {
        m_pSingle = new UserRecord();
        m_pSingle->init();
    }
    return m_pSingle;
}

void UserRecord::purge()
{
    CC_SAFE_DELETE(m_pSingle);
}

UserRecord::UserRecord():m_sCRCCache(""),m_bFirstPlay(false)
{
    
}

UserRecord::~UserRecord()
{
    
}

void UserRecord::init()
{
    CCUserDefault* user = CCUserDefault::sharedUserDefault();
    if(user->getBoolForKey("FirstPlay",true))
    {
        m_bFirstPlay = true;
        user->setBoolForKey("FirstPlay", false);
        user->flush();
    }
    else
    {
        m_bFirstPlay = false;
    }
}

bool UserRecord::isFirstPlay()
{
    return m_bFirstPlay;
}

void UserRecord::clearCache()
{
    m_sCRCCache = "";
}

void UserRecord::generateCRC()
{
    SHA1* sha1 = new SHA1();
    sha1->addBytes(m_sCRCCache.c_str(), m_sCRCCache.length());
    unsigned char* digest = sha1->getDigest();
    string code = getDigestString(digest);
    CCUserDefault::sharedUserDefault()->setStringForKey("crc", code);
    free(digest);
    delete sha1;
}

bool UserRecord::checkCRC()
{
    SHA1* sha1 = new SHA1();
    sha1->addBytes(m_sCRCCache.c_str(), m_sCRCCache.length());
    unsigned char * digest = sha1->getDigest();
    string code = getDigestString(digest);
    free(digest);
    delete sha1;
    string crc = CCUserDefault::sharedUserDefault()->getStringForKey("crc");
    if(crc != code)
    {
        return false;
    }
    return true;
}

void UserRecord::over()
{
    CCUserDefault::sharedUserDefault()->flush();
}

void UserRecord::saveIntegerArray(const char* key,cocos2d::CCArray *array)
{
    assert(key && array);
    CCObject* pObj = NULL;
    string buffer = array->count() > 0 ? "":"null";
    CCARRAY_FOREACH(array, pObj)
    {
        CCInteger* pInt = dynamic_cast<CCInteger*>(pObj);
        string str_int = "";
        NUMBER_TO_CSTR("%d", pInt->getValue(), str_int);
        buffer += str_int;
        buffer += ",";
    }
    string base64 = base64_encode(reinterpret_cast<const unsigned char*>(buffer.c_str()),buffer.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(key, base64);
    m_sCRCCache += buffer;
}

void UserRecord::loadIntegerArray(const char* key,cocos2d::CCArray *array)
{
    assert(key && array);
    array->removeAllObjects();
    string base64 = CCUserDefault::sharedUserDefault()->getStringForKey(key);
    string buffer = base64_decode(base64);
    int ps = 0;
    for(int i = 0;i < buffer.length();i++)
    {
        if(buffer[i] == ',')
        {
            string sub = buffer.substr(ps,i-ps);
            ps = i + 1;
            int var = atoi(sub.c_str());
            array->addObject(CCInteger::create(var));
        }
    }
    m_sCRCCache += buffer;
}

void UserRecord::saveStringArray(const char *key, cocos2d::CCArray *array)
{
    assert(key && array);
    string buffer = array->count()>0?"":"null";
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        CCString* pStr = dynamic_cast<CCString*>(pObj);
        buffer += pStr->getCString();
        buffer += ",";
    }
    string base64 = base64_encode(reinterpret_cast<const unsigned char*>(buffer.c_str()),buffer.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(key, base64);
    m_sCRCCache += buffer;
}

void UserRecord::loadStringArray(const char *key, cocos2d::CCArray *array)
{
    assert(key && array);
    array->removeAllObjects();
    string base64 = CCUserDefault::sharedUserDefault()->getStringForKey(key);
    string buffer = base64_decode(base64);
    int ps = 0;
    for(int i = 0;i < buffer.length();i++)
    {
        if(buffer[i] == ',')
        {
            string sub = buffer.substr(ps,i-ps);
            ps = i + 1;
            array->addObject(CCString::createWithFormat(sub.c_str()));
        }
    }
    m_sCRCCache += buffer;
}

void UserRecord::saveBool(const char *key, bool var)
{
    assert(key);
    string buffer = var ? "true" : "false";
    CCUserDefault::sharedUserDefault()->setBoolForKey(key, var);
    m_sCRCCache += buffer;
}

void UserRecord::loadBool(const char *key, bool &var)
{
    assert(key);
    var = CCUserDefault::sharedUserDefault()->getBoolForKey(key);
    string buffer = var ? "true" : "false";
    m_sCRCCache += buffer;
}

void UserRecord::saveInt(const char *key, int var)
{
    assert(key);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key, var);
    string buffer = "";
    NUMBER_TO_CSTR("%d", var, buffer);
    m_sCRCCache += buffer;
}

void UserRecord::loadInt(const char *key, int &var)
{
    assert(key);
    string buffer = CCUserDefault::sharedUserDefault()->getStringForKey(key);
    var = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    m_sCRCCache += buffer;
}

void UserRecord::saveFloat(const char *key, float var)
{
    assert(key);
    CCUserDefault::sharedUserDefault()->setFloatForKey(key, var);
    string buffer = "";
    NUMBER_TO_CSTR("%f", var, buffer);
    m_sCRCCache += buffer;
}

string UserRecord::getDigestString(unsigned char *digest)
{
    string buffer = "";
    //sha1 digest length is 20.
    for(int i = 0;i < 20;i++)
    {
        int var = *digest;
        digest++;
        string str_int = "";
        NUMBER_TO_CSTR("%d", var, str_int);
        buffer+=str_int;
    }
    return buffer;
}







