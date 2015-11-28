#ifndef BACKGROUNDSCENE_H_
#define BACKGROUNDSCENE_H_
#include "cocos2d.h"
#include "Hero.h"
#include "Dart.h"
#include "ui\UIText.h"
using namespace ui;
USING_NS_CC;

class BackgroundScene:public cocos2d::Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(BackgroundScene);
private:
	int width;
	int height;
	Rect collideRect;
	Hero* heroLayer;
	Sprite* hero;
	virtual bool init();
	Sprite* floor;
	Sprite* background;
	Dart* dart;
	void update(float dt);
	Vector<Sprite*> darts;
	EventListenerKeyboard* keyListener;
	EventListenerTouchOneByOne* introduceListener;
	void backToStart(EventKeyboard::KeyCode, Event*);

	Sprite* finger;
	bool onIntrouduceTouchBegan(Touch* touch,Event* event);
	void onIntroduceTouchMove(Touch* touch,Event* event);
	Vec2 beginLocation;
	static bool isFirstIn;
	static bool hasUp;
	static bool hasRight;
	static bool hasLeft;
};
#endif