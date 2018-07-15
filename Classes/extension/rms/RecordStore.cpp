//
//  RMS.cpp
//  SpaceWarriors
//
//  Created by Nikita on 13-8-19.
//
//

#include "RecordStore.h"

FILE* RecordStore::fsdsdafsdsddssdsdds(const char* name,dsfasdfsdfsa op)
{
    CCString* buf = CCString::createWithFormat("%s_db",name);
    std::string full_path = CCFileUtils::sharedFileUtils()->getWriteablePath()+buf->getCString();
    CCLog(full_path.c_str());
    FILE* pfile = fopen(full_path.c_str(), op==sdffsadfsdfs?"rb":"wb");
    return pfile;
}

bool RecordStore::sdsddsdsdsdsd(const char* name)
{
    CCString* buf = CCString::createWithFormat("%s_db",name);
    std::string full_path = CCFileUtils::sharedFileUtils()->getWriteablePath()+buf->getCString();
    CCLog(full_path.c_str());
    FILE* pfile = fopen(full_path.c_str(), "r");
    if(pfile)
    {
        fclose(pfile);
        return true;
    }
    else
    {
        return false;
    }
}