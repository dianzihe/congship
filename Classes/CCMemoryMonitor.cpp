#include "CCMemoryMonitor.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <mach/mach.h>
#include <sys/sysctl.h>
#endif

#ifdef WIN32
#include <Windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>
#endif

CCMemoryMonitor::CCMemoryMonitor()
: mIsReceivedMemoryWarning(false)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
, m_exit(false)
, m_usedMemory(0)
, m_availableMemory(0)
#endif
{}

CCMemoryMonitor::~CCMemoryMonitor()
{}

static CCMemoryMonitor *s_sharedMemoryMonitor = NULL;

CCMemoryMonitor* CCMemoryMonitor::sharedMemoryMonitor(void)
{
	if (!s_sharedMemoryMonitor)
	{
		s_sharedMemoryMonitor = new CCMemoryMonitor();
	}
    
	return s_sharedMemoryMonitor;
}

bool CCMemoryMonitor::isMemoryLackCommon()
{
	double availableMem = availableMemory();
	double usedMem = usedMemory();
    
	if (availableMem < 30.0 && usedMem > 90.0)
		return true;
    
	return false;
}

bool CCMemoryMonitor::isMemoryLackEmergence()
{
	double availableMem = availableMemory();
	//double usedMem = usedMemory();
    
 	if (availableMem < 20.0)
 		return true;
    
	return false;
}

double CCMemoryMonitor::usedMemory()
{
	double result = 0.0;
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	task_basic_info_data_t taskInfo;
	mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
	kern_return_t kernReturn = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&taskInfo, &infoCount);
	if(kernReturn != KERN_SUCCESS) {
		return result;
	}
	result = (taskInfo.resident_size / 1024.0) / 1024.0;
#endif
    
#ifdef WIN32
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
	result = (pmc.WorkingSetSize / 1024.0) / 1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	result = m_usedMemory;
#endif

	return result;
}

double CCMemoryMonitor::availableMemory()
{
	double result = 1000.0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	vm_statistics_data_t vmStats;
	mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
	kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
	if(kernReturn != KERN_SUCCESS)
	{
		return result;
	}
	result = ((vm_page_size * vmStats.free_count) / 1024.0) / 1024.0;
#endif
    
#ifdef WIN32
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	result = (memstatus.dwAvailPhys / 1024.0) /1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	result = m_availableMemory;
#endif

	return result;
}

void CCMemoryMonitor::receivedMemoryWarning()
{
	mIsReceivedMemoryWarning = true;
}

bool CCMemoryMonitor::isReceivedMemoryWarning()
{
	return mIsReceivedMemoryWarning;
}

void CCMemoryMonitor::cleanMemoryWarning()
{
	mIsReceivedMemoryWarning = false;
}


void CCMemoryMonitor::initilize()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_create(&s_queryThread, NULL, &CCMemoryMonitor::threadProcedure, this);
#endif
}

void CCMemoryMonitor::uninitilize()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_exit = true;
#endif

}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void CCMemoryMonitor::queryMemoryState()
{
	{
		cocos2d::JniMethodInfo methodInfo;
		if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/haowan123/fanxian/FanXian", "getUseMemoryBySelf", 
				"()I"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
		}
		
		int freeMemoryKB = methodInfo.env->CallIntMethod(methodInfo.classID, methodInfo.methodID);
		
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		
		m_usedMemory = freeMemoryKB / 1024.0;
	}

	{
		cocos2d::JniMethodInfo methodInfo;
	    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/haowan123/fanxian/FanXian", "getSystemFreeMemory", 
	        "()J"))
	    {
	        CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
	    }
	
	    long freeMemoryKB = methodInfo.env->CallLongMethod(methodInfo.classID, methodInfo.methodID);
	
	    methodInfo.env->DeleteLocalRef(methodInfo.classID);
	
	   m_availableMemory = freeMemoryKB / 1024.0;
	}
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void* CCMemoryMonitor::threadProcedure(void* data)
{
	CCMemoryMonitor* mm = (CCMemoryMonitor*)(data);
	
	while (true)
	{
		if (mm->m_exit)
			break;
		
		queryMemoryState();

		sleep(2000);
	}
}
#endif


