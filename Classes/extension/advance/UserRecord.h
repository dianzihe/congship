//
//  UserRecord.h
//  SpaceWarriors
//
//  Created by Nikita on 13-7-22.
//
//

#ifndef SpaceWarriors_UserRecord_h
#define SpaceWarriors_UserRecord_h

#include "cocos2d.h"
#include "../utils/exMacros.h"

USING_NS_CC;

using namespace std;

class UserRecord
{
public:
    static UserRecord* shared();
    static void purge();
    
    bool isFirstPlay();
    void clearCache();
    void generateCRC();
    bool checkCRC();
    void over();
    
    void saveStringArray(const char* key, CCArray* array);
    void loadStringArray(const char* key, CCArray* array);
    void saveIntegerArray(const char* key, CCArray* array);
    void loadIntegerArray(const char* key, CCArray* array);
    void saveInt(const char* key, int var);
    void loadInt(const char* key, int& var);
    void saveBool(const char* key, bool var);
    void loadBool(const char* key, bool& var);
    void saveFloat(const char* key, float var);
    void loadFloat(const char* key, float& var);
protected:
    static UserRecord* m_pSingle;
    bool m_bFirstPlay;
    string m_sCRCCache;
    
    UserRecord();
    virtual ~ UserRecord();
    virtual void init();
    string getDigestString(unsigned char *digest);
};

#endif
