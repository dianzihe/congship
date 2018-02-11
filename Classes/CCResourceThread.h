#ifndef __CCRESOURCETHREAD_H_
#define __CCRESOURCETHREAD_H_
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "pthread/semaphore.h"
#include "pthread/pthread.h"
#include "ASprite.h"
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <semaphore.h>
#endif
#include <pthread.h>
#endif

#include <string>
#include <queue>
#include <thread>

NS_CC_BEGIN

//typedef void(*SEL_LoadDataFunc)(const char* data);

/*example class function pointer*/
/*
typedef void (T::*B)(int x, int y, int z);
B b = &T::foo;
T t;
t.*b(x, y, z); // ±ÿ–Î÷∏∂®t
*/
//class ASprite;
typedef void(*ASprite::*DQ_LoadDataFunc)(const char* data);
typedef void(*ASprite::*DQ_CallFuncO)(CCObject* data);
class CC_DLL CCResourceThread : public Ref
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
		std::string		filePath;
		ASprite*		target;
		DQ_CallFuncO	afterProcess;
		DQ_LoadDataFunc loader;
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