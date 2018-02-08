
#ifndef _WBEvent_include_file_
#define _WBEvent_include_file_


#include "typedefine.h"

class WBEvent
{
    CC_SYNTHESIZE(int, m_type, Type); //�¼�����
    
    CC_SYNTHESIZE(void *,m_pData,Data);//�¼�Я��������
    
    CC_SYNTHESIZE(int,m_processtype,Processtype);//�������� 0:�ȴ���һ����� 1:����ִ��
    
    bool m_End; //�Ƿ����
    
 public: 
    WBEvent();
    WBEvent(int type,int processType);
    virtual ~WBEvent();
    
    /**
    * @brief �¼��Ƿ��Ѿ����
    */
    bool isEnd(); 
    
    /**
    * @brief �����¼�����
    */
    void End();
    

    
};

#endif