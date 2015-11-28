#ifndef HERO_H_
#define HERO_H_
#include "cocos2d.h"
#include "CloudLayer.h"
#define DART_SPEED 320
USING_NS_CC;

class Hero : public cocos2d::Node
{
public:
	void stopCloud();
	void heroDead();
	Sprite* getHeroSprite();
	CREATE_FUNC(Hero);
private:
	void startNormalAnimation();
	void startRunAnimation();
	void startJumpAnimation();
	Vec2 begLocation;
	Vec2 movLocation;
	bool isRunning;
	bool isJumping;
	virtual bool init();
	Sprite* hero;
	bool myTouchBegan(Touch* touch,Event* event);
	void myTouchMove(Touch* touch,Event* event);
	void myTouchEnd(Touch* touch,Event* event);
	EventListenerTouchOneByOne* listener;
	void initRunAnimation();
	void initNormalAnimation();
	void initJumpAnimation();
	Animate* getAnimate(std::string animationName);
	void jumpFinished();
	void initDeadAnimation();
	void showGameOver();
	void restart();
	float width;
	float height;
	CloudLayer* cloud;
};
#endif