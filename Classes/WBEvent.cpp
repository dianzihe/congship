

#include "WBEvent.h"


WBEvent::WBEvent(int type,int processType):
m_End(false),
m_pData(NULL),
m_type(type),
m_processtype(processType)
{
    
}

WBEvent::WBEvent():
m_End(false),
m_pData(NULL),
m_type(-1),
m_processtype(0)
{
    
}

WBEvent::~WBEvent()
{
    if(m_pData) {delete (byte *)m_pData;}
}


bool WBEvent::isEnd()
{
    return m_End;
}


void WBEvent::End()
{
    m_End=true;
}