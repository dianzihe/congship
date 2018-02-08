
#ifndef _WBEvent_include_file_
#define _WBEvent_include_file_


#include "typedefine.h"

class WBEvent
{
    CC_SYNTHESIZE(int, m_type, Type); //事件类型
    
    CC_SYNTHESIZE(void *,m_pData,Data);//事件携带的数据
    
    CC_SYNTHESIZE(int,m_processtype,Processtype);//处理类型 0:等待上一个完成 1:立即执行
    
    bool m_End; //是否完成
    
 public: 
    WBEvent();
    WBEvent(int type,int processType);
    virtual ~WBEvent();
    
    /**
    * @brief 事件是否已经完成
    */
    bool isEnd(); 
    
    /**
    * @brief 设置事件结束
    */
    void End();
    

    
};

#endif