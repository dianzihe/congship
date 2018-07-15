//
//  exMacros.h
//  SanguoHeros
//
//  Created by 伟 李 on 12-11-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#ifndef SanguoHeros_exMacros_h
#define SanguoHeros_exMacros_h
#define GET_VALUE_AS_INTEGER(dict,key) ((CCString*)dict->objectForKey(key))->intValue()
#define GET_VALUE_AS_FLOAT(dict,key) ((CCString*)dict->objectForKey(key))->floatValue()
#define GET_VALUE_AS_BOOL(dict,key) ((CCString*)dict->objectForKey(key))->boolValue()
#define GET_VALUE_AS_CSTRING(dict,key) ((CCString*)dict->objectForKey(key))->getCString()
#define GET_VALUE_AS_INTEGER_SAFE(dict,key,var,default) do{ \
CCString* __buf__ = (CCString*)dict->objectForKey(key); \
if(__buf__ && __buf__->length() > 0){ \
    var = __buf__->intValue(); \
} \
else { \
    var = default; \
} \
}while(0)
#define GET_VALUE_AS_FLOAT_SAFE(dict,key,var,default) do{ \
CCString* __buf__ = (CCString*)dict->objectForKey(key); \
if(__buf__ && __buf__->length() > 0){ \
    var = __buf__->floatValue(); \
} \
else { \
    var = default; \
} \
}while(0)
#define GET_VALUE_AS_BOOL_SAFE(dict,key,var,default) do{ \
CCString* __buf__ = (CCString*)dict->objectForKey(key); \
if(__buf__ && __buf__->length() > 0){ \
    var = __buf__->boolValue(); \
} \
else { \
    var = default; \
} \
}while(0)
#define GET_VALUE_AS_CSTRING_SAFE(dict,key,var,default) do{ \
CCString* __buf__ = (CCString*)dict->objectForKey(key); \
if(__buf__ && __buf__->length() > 0){ \
    var = __buf__; \
} \
else { \
    var = default; \
} \
}while(0)
#define CSTR_EQUAL(cstringA,cstringB) strcmp(cstringA,cstringB) == 0
#define CSTR_TO_BOOL(cstring) (CSTR_EQUAL(cstring,"True") || CSTR_EQUAL(cstring,"true"))?true:false
#define CSTR_CAT(cstringA,cstringB) (CCString::createWithFormat("%s%s",cstringA,cstringB))->getCString()
#define NUMBER_TO_CSTR(format,num,variable) do{ \
char buf[128]; \
sprintf(buf,format,num); \
variable = buf; \
}while(0)
#define SRAND_BY_TIME do{\
cc_timeval psv;\
CCTime::gettimeofdayCocos2d(&psv,NULL);\
unsigned int tsrans = psv.tv_sec + psv.tv_usec;\
srand(tsrans);\
}while(0)
#define CREATE_CCB_LAYER_LOADER(loader_class,layer_class) \
class loader_class : public CCLayerLoader \
{ \
public: \
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(loader_class, loader); \
protected: \
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(layer_class); \
} \

#define LOAD_IMAGE_AS_FRAME(__image__,__frame__) do{\
CCTexture2D* __texture__ = CCTextureCache::sharedTextureCache()->addImage(__image__);\
const CCSize& __size__ = __texture__->getContentSize();\
__frame__ = CCSpriteFrame::createWithTexture(__texture__, CCRectMake(0, 0, __size__.width, __size__.height));\
}while(0)
#endif
