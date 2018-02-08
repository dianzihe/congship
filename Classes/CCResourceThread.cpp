#include "CCResourceThread.h"
#include "CCDirector.h"
#include "platform/CCImage.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTexturePVR.h"
#include "platform/CCFileUtils.h"
#include "CCScheduler.h"


NS_CC_BEGIN

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define CC_ASYNC_USE_NAMED_SEMAPHORE 1
#else
#define CC_ASYNC_USE_NAMED_SEMAPHORE 0
#endif


#if CC_ASYNC_USE_NAMED_SEMAPHORE
#define CC_ASYNC_SEMAPHORE "ccAsync"
#else
static sem_t s_sem;
#endif


static CCImage::EImageFormat computeImageFormatType(std::string& filename)
{
	CCImage::EImageFormat ret = CCImage::kFmtUnKnown;

	if ((std::string::npos != filename.find(".jpg")) || (std::string::npos != filename.find(".jpeg")) || (std::string::npos != filename.find(".wen")))
	{
		ret = CCImage::kFmtJpg;
	}
	else if ((std::string::npos != filename.find(".png")) || (std::string::npos != filename.find(".PNG")) || (std::string::npos != filename.find(".ttf")))
	{
		ret = CCImage::kFmtPng;
	}
	else if ((std::string::npos != filename.find(".tiff")) || (std::string::npos != filename.find(".TIFF")))
	{
		ret = CCImage::kFmtTiff;
	}

	return ret;	
}


CCResourceThread::CCResourceThread()
{

}

CCResourceThread::~CCResourceThread()
{

}

void* CCResourceThread::threadProcedure( void* data )
{
	CCResourceThread* rt = (CCResourceThread*)(data);
	
	LoadingCommand* loadingCmd = NULL;

	while (true)
	{
		int ret = sem_wait(rt->m_sem);
		if (ret < 0)
			break;

		pthread_mutex_lock(&rt->m_loadingQueueMutex);
		if (rt->m_loadingQueue.empty())
		{
			pthread_mutex_unlock(&rt->m_loadingQueueMutex);
			if (rt->m_exit)
				break;
			else
				continue;
		}
		else
		{
			loadingCmd = rt->m_loadingQueue.front();
			rt->m_loadingQueue.pop();
			pthread_mutex_unlock(&rt->m_loadingQueueMutex);
		}

		const std::string& fileName = loadingCmd->filePath;
		std::string lowerCase(fileName);
		for (size_t n = 0; n < lowerCase.size(); ++n)
		{
			lowerCase[n] = tolower(lowerCase[n]);
		}
		
		if (std::string::npos != lowerCase.find("pvr"))
		{
			CCTexturePVR *pvr = new CCTexturePVR();
			bool result = pvr->initWithContentsOfFileNotCreate(fileName.c_str());
			if (!result)
			{
				pvr->release();
				delete loadingCmd;
				continue;
			}
			
			LoadedInfo* pLoadedInfo = new LoadedInfo();
			pLoadedInfo->type = LoadedInfo::PVR;
			pLoadedInfo->data = (void*)pvr;
			pLoadedInfo->src = loadingCmd;

			pthread_mutex_lock(&rt->m_loadedQueueMutex);
			rt->m_loadedQueue.push(pLoadedInfo);
			pthread_mutex_unlock(&rt->m_loadedQueueMutex);
		}
		else
		{
			if (!loadingCmd->loader)
			{
				CCImage::EImageFormat ret = computeImageFormatType(loadingCmd->filePath);

				if (ret == CCImage::kFmtUnKnown)
				{
					delete loadingCmd;
					continue;
				}

				CCImage* pImage = new CCImage();
				if (!pImage->initWithImageFileThreadSafe(loadingCmd->filePath.c_str(), ret))
				{
					delete pImage;
					delete loadingCmd;
					continue;
				}

				LoadedInfo* pLoadedInfo = new LoadedInfo();
				pLoadedInfo->type = LoadedInfo::IMAGE;
				pLoadedInfo->data = (void*)pImage;
				pLoadedInfo->src = loadingCmd;

				pthread_mutex_lock(&rt->m_loadedQueueMutex);
				rt->m_loadedQueue.push(pLoadedInfo);	
				pthread_mutex_unlock(&rt->m_loadedQueueMutex);
				

			}
			else
			{
				unsigned long length = 0;
				char *data = (char*)CCFileUtils::sharedFileUtils()->getFileData(loadingCmd->filePath.c_str(), "rb", &length);
				if (!data)
				{
					pthread_mutex_lock(&rt->m_loadingQueueMutex);
					rt->m_loadingQueue.push(loadingCmd);
					pthread_mutex_unlock(&rt->m_loadingQueueMutex);
					continue;
				}
				if (data && loadingCmd->target && loadingCmd->loader)
				{
					(loadingCmd->target->*(loadingCmd->loader))(data);
				}
				if (data)
					delete [] data;
				
				LoadedInfo* pLoadedInfo = new LoadedInfo();
				pLoadedInfo->type = LoadedInfo::DATA;
				pLoadedInfo->data = NULL;
				pLoadedInfo->src = loadingCmd;

				pthread_mutex_lock(&rt->m_loadedQueueMutex);
				rt->m_loadedQueue.push(pLoadedInfo);
				pthread_mutex_unlock(&rt->m_loadedQueueMutex);

// 				if (loadingCmd->target)
// 					loadingCmd->target->release();
				//delete loadingCmd;
			}
		}
	}

	if (rt->m_sem)
	{
#if CC_ASYNC_USE_NAMED_SEMAPHORE
		sem_unlink(CC_ASYNC_SEMAPHORE);
		sem_close(rt->m_sem);
#else
		sem_destroy(rt->m_sem);
#endif
		rt->m_sem = NULL;
	}

	pthread_mutex_destroy(&rt->m_loadingQueueMutex);
	pthread_mutex_destroy(&rt->m_loadedQueueMutex);

	return 0;
}


static CCResourceThread* s_sharedResourceThread = NULL;

CCResourceThread* CCResourceThread::instance()
{
	if (!s_sharedResourceThread)
	{
		s_sharedResourceThread = new CCResourceThread();
		s_sharedResourceThread->initilize();
	}

	return s_sharedResourceThread;
}

void CCResourceThread::postCommand(LoadingCommand* pLoadingCmd)
{
	if (m_asyncRefCount == 0 && pLoadingCmd->afterProcess)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCResourceThread::tick), this, 0, false);
	}
	
	if (pLoadingCmd->afterProcess)
		m_asyncRefCount++;

	
	pthread_mutex_lock(&m_loadingQueueMutex);

	if (pLoadingCmd->target)/* && pLoadingCmd->afterProcess)*/
	{
		pLoadingCmd->target->retain();
	}

	m_loadingQueue.push(pLoadingCmd);

	pthread_mutex_unlock(&m_loadingQueueMutex);

	sem_post(m_sem);
}

void CCResourceThread::tick(float dt)
{
	pthread_mutex_lock(&m_loadedQueueMutex);
	if (m_loadedQueue.empty())
	{
		pthread_mutex_unlock(&m_loadedQueueMutex);
	}
	else
	{
		LoadedInfo *pInfo = m_loadedQueue.front();
		m_loadedQueue.pop();
		pthread_mutex_unlock(&m_loadedQueueMutex);

		LoadingCommand* srcCmd = pInfo->src;
		CCObject* target = srcCmd->target;
		SEL_CallFuncO afterProcess = srcCmd->afterProcess;
		std::string fileName = srcCmd->filePath;
		
		if (pInfo->type == LoadedInfo::IMAGE || pInfo->type == LoadedInfo::PVR)
		{
			CCTexture2D *texture = new CCTexture2D();

			if (pInfo->type == LoadedInfo::IMAGE)
			{
				CCImage* pImage = (CCImage*)pInfo->data; 
				texture->initWithImage(pImage);
			}
			else
			{
				CCTexturePVR* pPVR = (CCTexturePVR*)pInfo->data;
				pPVR->createGLTexture();
				texture->initWithPVRTexture(pPVR);
			}

#if CC_ENABLE_CACHE_TEXTURE_DATA
			// cache the texture file name
			if (pInfo->type == LoadedInfo::IMAGE)
			{
				CCImage::EImageFormat formatType = computeImageFormatType(pInfo->src->filePath);
				VolatileTexture::addImageTexture(texture, pInfo->src->filePath.c_str(), formatType);
			}
			else
			{
				VolatileTexture::addImageTexture(texture,  pInfo->src->filePath.c_str(), CCImage::kFmtRawData);
			}
#endif

			CCTextureCache::sharedTextureCache()->cacheTexture(texture, pInfo->src->filePath);

			if (target && afterProcess)
			{
				(target->*afterProcess)(texture);
			}

			if (target)
			{
				target->release();
			}

			if (pInfo->type == LoadedInfo::IMAGE)
			{
				((CCImage*)(pInfo->data))->release();
			}
		}
		else
		{
			if (target && afterProcess)
			{
				(target->*afterProcess)(NULL);
			}
			if (target)
			{
				target->release();
			}
		}
	
		delete srcCmd;
		delete pInfo;

		m_asyncRefCount--;
		if (m_asyncRefCount == 0)
		{
			CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCResourceThread::tick), this);
		}
	}
}

void CCResourceThread::quit()
{
	m_exit = true;
	sem_post(m_sem);
}

void CCResourceThread::initilize()
{
	m_sem = NULL;
	m_exit = false;
	m_asyncRefCount = 0;

#if CC_ASYNC_USE_NAMED_SEMAPHORE
	m_sem = sem_open(CC_ASYNC_SEMAPHORE, O_CREAT, 0644, 0);
	if(m_sem == SEM_FAILED)
	{
		m_sem = NULL;
		return;
	}
#else
	int result = sem_init(&s_sem, 0, 0);
	if (result < 0)
	{
		return;
	}
	m_sem = &s_sem;
#endif

	pthread_mutex_init(&m_loadingQueueMutex, NULL);
	pthread_mutex_init(&m_loadedQueueMutex, NULL);
	

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	struct sched_param stShedParam;
	pthread_attr_getschedparam(&attr, &stShedParam);

	stShedParam.sched_priority = sched_get_priority_min(SCHED_OTHER);
	pthread_attr_setschedparam(&attr, &stShedParam);

	pthread_create(&m_loadingThread, &attr, &CCResourceThread::threadProcedure, this);	
}

NS_CC_END