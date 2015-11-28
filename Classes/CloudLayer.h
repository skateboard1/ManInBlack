#ifndef CLOUDLAYER_H_H
#define CLOUDLAYER_H_H
#include "cocos2d.h"
USING_NS_CC;
class CloudLayer:public cocos2d::Layer{
public:
	CREATE_FUNC(CloudLayer);
private:
	Sprite* cloud1;
	Sprite* cloud2;
	void update(float t);
	virtual bool init();
	float width;
	float height;
};
#endif