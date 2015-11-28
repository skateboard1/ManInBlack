#ifndef DART_H_
#define DART_H_
#include "cocos2d.h"
#define MODE_NONE 0
#define MODE_NEEDRUN 1
#define MODE_NEEDSTAY 2
#define FLY_TIME 3
//#define NORMAL_TIME 4
//#define DART_WIDTH 25

USING_NS_CC;

class Dart:public cocos2d::Layer
{
public:
	static int score;
	Vector<Sprite*> getdartVec();
	CREATE_FUNC(Dart)
private:
	float dart_width;
	float dart_speed;
	int width;
	int height;
	virtual bool init();
	Vector<Sprite*> dartVec;
	void update(float dt);
	void generateDart(int dartNum,float delayTime);
	bool isFirst;
	Label* counter;
	void addScoreAndremoveDart(Sprite* dart);
};
#endif