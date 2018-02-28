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

//游戏主场景层
class GameScene : public Scene
{
    //以下是游戏配置信息
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

    //碰撞事件bit位
    enum ContactMaskBit
    {
        ENEMY_CONTACTMASKBIT = 0x01 || 0x02,
        HERO_BULLET_CONTACTMASKBIT = 0x01,
        HERO_CONTACTMASKBIT = 0x02
    };

    //游戏level，分数越高level越高
    enum Level
    {
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
        LEVEL5
    };

    ////level提升所需的分数
    //enum LevelUp_Score
    //{
    //       Level1Up_Score = 0,
    //	Level2Up_Score = 200,
    //	Level3Up_Score = 500,
    //	Level4Up_Score = 1000
    //};

    static const float refresh_delay[]; //战机刷新间隔

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
   // static GameScene* sharedGameLayer() { return m_gamelayer; } //获取该游戏层单例对象

private:
    //static GameScene* m_gamelayer; //游戏场景层的单例对象
public:
	Node* GetUI();
    SpriteBatchNode* getBulletBox() { return m_bulletBox; }	 //获取子弹渲染器
    void AdjustHeroPosition(Node* hero);
    void gameover();
private:
    SpriteBatchNode *m_bulletBox; //存放子弹的渲染器

private:
    int m_level; //当前游戏level
    int m_score; //当前游戏分数

private:
    void playBackground(); //创建并移动游戏背景
    void publishScore(); //存储游戏分数

    void pauseButtonCallBack(Ref* pSender); //点击暂停按钮回调函数
    void AIButtonCallBack(Ref* pSender); //点击AI按钮回调函数

    bool dealWithContact(PhysicsContact&); //物理碰撞事件回调函数
    void hitEnemy(PlaneEnemy* enemy);
    void hitHero(PlaneHero* hero);

    void levelUp(Level level);//升级动画
    //游戏中schedule的回调函数
    void testLevel(float dt); //每秒调用一次，根据当前到达的分数设置游戏level
    //设置hero Plane's position
    //void setHeroPlaneUnderPosition(CCPoint _targetPosition);
    //m_isAI表示是否使用AI
    bool m_isAI;
    //ai动作
    void AIAction(float level);
    //m_canBossRefresh表示可否刷新boss，每隔dt秒可以刷新一次
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

