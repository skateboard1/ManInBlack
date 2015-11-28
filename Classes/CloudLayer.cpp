#include "CloudLayer.h"
#define VELOCITY 200 
bool CloudLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto size=Director::getInstance()->getWinSize();
	width=size.width;
	height=size.height;
	cloud1=Sprite::create("cloud.png");
	cloud1->setAnchorPoint(Vec2(0.5f,1.0f));
	cloud1->setPosition(Vec2(width/2,height));
	this->addChild(cloud1);
	cloud2=Sprite::create("cloud.png");
	cloud2->setAnchorPoint(Vec2(0.5f,1.0f));
	cloud2->setPosition(Vec2(width+cloud2->getContentSize().width/2,height));
	this->addChild(cloud2);
	return true;
}

void CloudLayer::update(float t)
{   
	auto position1=cloud1->getPositionX();
	cloud1->setPositionX(position1-1);
	auto position2=cloud2->getPositionX();
	cloud2->setPositionX(position2-1);
	if((cloud1->getPositionX()+cloud1->getContentSize().width/2)<0)
	{
		cloud1->setPosition(Vec2(width+cloud1->getContentSize().width/2,height));
	}
	if((cloud2->getPositionX()+cloud1->getContentSize().width/2)<0)
	{
		cloud2->setPosition(Vec2(width+cloud2->getContentSize().width/2,height));
	}
}