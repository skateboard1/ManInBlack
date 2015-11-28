#ifndef STARTSCENE_H_
#define STARTSCENE_H_
#include "cocos2d.h"
USING_NS_CC;
class StartScene:public cocos2d::Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(StartScene);
private:
	virtual bool init();
	EventListenerKeyboard* keyListener;
	void startGame();
	void exit(EventKeyboard::KeyCode, Event*);
};
#endif