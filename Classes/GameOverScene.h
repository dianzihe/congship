#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
	bool init();

private:
	void onBackItemCallback(Ref*);
};

class SceneTestLayer1 : public cocos2d::Layer
{
public:
	CREATE_FUNC(SceneTestLayer1);

	SceneTestLayer1();
	~SceneTestLayer1();

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;

	void testDealloc(float dt);
	void onPushScene(cocos2d::Ref* sender);
	void onPushSceneTran(cocos2d::Ref* sender);
	void onQuit(cocos2d::Ref* sender);
};
#endif