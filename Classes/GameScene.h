#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "behaviac\behaviac.h"
#include "SecondAgent.h"
#include "ActorManager.h"
#include "Monster.h"
#include "Singleton.h"
//#include "Camera.h"
#include "GameState.h"
#include "Map.h"
USING_NS_CC;

class PlaneEnemy;
class PlaneHero;
class NPC;
class Hero;
namespace behaviac{
    class Agent;
}

enum GAME_LAYER
{
	GAME_LAYER_MAP,
	GAME_LAYER_UI
};
enum GAME_STATE
{
	GAME_STATE_NONE,
	GAME_STATE_UPDATE,
	GAME_STATE_ZHONGGAO,
	GAME_STATE_CUTSCENE,
	GAME_STATE_LOGIN,
	GAME_STATE_GAMESERVERLIST,
	GAME_STATE_CHARLOBBY,
	GAME_STATE_CREATEPLAYER,
	GAME_STATE_GAME,
	GAME_STATE_LOADING,
	GAME_STATE_DISCONNECTION_LOGIN,
	GAME_STATE_RECONNECT_LOGIN,
	GAME_STATE_BRANCHUPDATE,
};


class DQScreen : public Scene
{
public:
	bool init();

	static DQScreen* create()
	{
		DQScreen* o = new DQScreen();
		if (o && o->init()) {
			o->autorelease();
			return o;
		}
		assert(false && "DQ screen cannot be created");
		CC_SAFE_DELETE(o);
		return NULL;
	}
	DQScreen(void);
	~DQScreen(void);

};

//��Ϸ��������
class GameScene : public Scene
{
    //��������Ϸ������Ϣ
public:
	friend class Singleton<GameScene, Tag_Singleton_Auto>;
    enum NodeTag
    {
        HERO_TAG = 100,
        ENEMY_TAG = 101,
        HERO_BULLET_TAG = 102,
        SCORE_LABEL = 103,
        PAUSE_MENU = 104,
        AI_TAG = 105,
    };

    //��ײ�¼�bitλ
    enum ContactMaskBit
    {
        ENEMY_CONTACTMASKBIT = 0x01 || 0x02,
        HERO_BULLET_CONTACTMASKBIT = 0x01,
        HERO_CONTACTMASKBIT = 0x02
    };

    //��Ϸlevel������Խ��levelԽ��
    enum Level
    {
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5
    };

    ////level��������ķ���
    //enum LevelUp_Score
    //{
    //       Level1Up_Score = 0,
    //	Level2Up_Score = 200,
    //	Level3Up_Score = 500,
    //	Level4Up_Score = 1000
    //};

    static const float refresh_delay[]; //ս��ˢ�¼��

public:
	
	GameScene(void);
	~GameScene(void);
	virtual bool init();
	static GameScene* create()
	{
		GameScene* o = new GameScene();
		if (o && o->init())		{
			o->autorelease();
			return o;
		}
		assert(false && "game screen cannot be created");
		CC_SAFE_DELETE(o);
		return NULL;
	}

	static GameScene* GetScene();
	static ActorManager* GetActorManager();
	static DQMap* GetMap();
	void initBG();

	//DQCamera* GetCamera();
	//void create();
	//static GameScene* GetScene();
	//static void createScene();
    //CREATE_FUNC(GameScene);
	//bool initilize();
	//static Node* GetUI();

	virtual void onEnter();
	virtual void onExit();

	void ReadLookInfoMonster(char*& buf, LookInfoMonster& value);
public:
	Sprite* background;
	ActorManager*	m_actorManager;
	DQMap*			m_map;
	Node*			m_uiNode;
	GAME_STATE		m_eGameState;
	CRunState*		m_pRunState;
   // static GameScene* sharedGameLayer() { return m_gamelayer; } //��ȡ����Ϸ�㵥������

private:
    //static GameScene* m_gamelayer; //��Ϸ������ĵ�������
public:
	Node* GetUI();
    SpriteBatchNode* getBulletBox() { return m_bulletBox; }	 //��ȡ�ӵ���Ⱦ��
    void AdjustHeroPosition(Node* hero);
    void gameover();
private:
    SpriteBatchNode *m_bulletBox; //����ӵ�����Ⱦ��

private:
    int m_level; //��ǰ��Ϸlevel
    int m_score; //��ǰ��Ϸ����

private:
    void playBackground(); //�������ƶ���Ϸ����
    void publishScore(); //�洢��Ϸ����

    void pauseButtonCallBack(Ref* pSender); //�����ͣ��ť�ص�����
    void AIButtonCallBack(Ref* pSender); //���AI��ť�ص�����

    bool dealWithContact(PhysicsContact&); //������ײ�¼��ص�����
    void hitEnemy(PlaneEnemy* enemy);
    void hitHero(PlaneHero* hero);

    void levelUp(Level level);//��������
    //��Ϸ��schedule�Ļص�����
    void testLevel(float dt); //ÿ�����һ�Σ����ݵ�ǰ����ķ���������Ϸlevel
    //����hero Plane's position
    //void setHeroPlaneUnderPosition(CCPoint _targetPosition);
    //m_isAI��ʾ�Ƿ�ʹ��AI
    bool m_isAI;
    //ai����
    void AIAction(float level);
    //m_canBossRefresh��ʾ�ɷ�ˢ��boss��ÿ��dt�����ˢ��һ��
    void resetBoss(float dt);
    NPC * m_NPC;
    Hero* m_Hero;
	SecondAgent* g_SecondAgent = NULL;
public:
    // //create Update for behaviac
    void Update(float dt);
    static void addBehaviacAgentDeleteQueue(behaviac::Agent* pAgent);
private:
    static void cleanBehaviacAgentDeleteQueue();
private:
    /******************************************************************
    Date        : 2015-11-13 16:40:05
    Author      : Quinn Pan
    Desc        : add some behaviac into the queue , and delete it
    ******************************************************************/
    static behaviac::vector<behaviac::Agent*> m_bt_agent_delete_queue;
};

#endif

