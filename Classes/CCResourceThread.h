#ifndef __CCRESOURCETHREAD_H_
#define __CCRESOURCETHREAD_H_
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
//#include "platform/platform.h"
//#include "cocoa/CCObject.h"

//#include "platform/third_party/win32/pthread/semaphore.h"
//#include "platform/third_party/win32/pthread/pthread.h"
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <semaphore.h>
#endif
#include <pthread.h>
#endif

#include <semaphore.h>
#include <pthread.h>
#include <string>
#include <queue>

NS_CC_BEGIN

class CC_DLL CCResourceThread : public CCObject
{
	static void* threadProcedure(void* data);
public:
	CCResourceThread();
	~CCResourceThread();

	class CC_DLL LoadingCommand
	{
	public:
		LoadingCommand()
			: target(NULL)
			, afterProcess(NULL)
			, loader(NULL)
		{}
		std::string		 filePath;
		CCObject*		 target;
		SEL_CallFuncO	 afterProcess;
		SEL_LoadDataFunc loader;
	};
	
	class LoadedInfo
	{
	public:
		LoadedInfo()
			: data(NULL)
			, src(NULL)
		{}
		enum TYPE
		{
			PVR,
			IMAGE,
			DATA
		};
		
		TYPE type;
		void* data;
		LoadingCommand* src;
	};

	static CCResourceThread* instance();
	
	void postCommand(LoadingCommand* pLoadingCmd);

	void tick(float dt);

	void quit();
	
private:
	void initilize();
	
private:
	std::queue<LoadingCommand*> m_loadingQueue;
	std::queue<LoadedInfo*> m_loadedQueue;
	pthread_t m_loadingThread;
	pthread_mutex_t m_loadingQueueMutex;
	pthread_mutex_t m_loadedQueueMutex;
	sem_t* m_sem;
	volatile bool m_exit;
	unsigned long m_asyncRefCount;
};

NS_CC_END

#endif