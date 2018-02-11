#pragma once

#include "platform/platform.h"

class CC_DLL CCMemoryMonitor
{
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	static void* threadProcedure(void* data);
#endif
public:
	CCMemoryMonitor();
	~CCMemoryMonitor();

	static CCMemoryMonitor* sharedMemoryMonitor(void);

	bool isMemoryLackCommon();
	bool isMemoryLackEmergence();
	bool isReceivedMemoryWarning();

	double usedMemory();
	double availableMemory();

	void receivedMemoryWarning();
	void cleanMemoryWarning();

	void initilize();
	void uninitilize();
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void queryMemoryState();
#endif
private:
	bool mIsReceivedMemoryWarning;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_t s_queryThread;
	volatile bool m_exit;
	volatile double m_usedMemory;
	volatile double m_availableMemory;
#endif

};
