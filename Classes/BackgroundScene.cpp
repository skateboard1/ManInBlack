#include "BackgroundScene.h"
#include "StartScene.h"

bool BackgroundScene::isFirstIn=true;
bool BackgroundScene::hasUp=false;
bool BackgroundScene::hasRight=false;
bool BackgroundScene::hasLeft=false;

Scene* BackgroundScene::createScene()
{
	auto scene=Scene::create();
	auto background=BackgroundScene::create();
	scene->addChild(background);
	return scene;
}

bool BackgroundScene::init()
{
	if(!Layer::init())
	{
	  return false;
	}
	
	Director::getInstance()->getScheduler()->setTimeScale(1.0f);
	auto size=Director::getInstance()->getVisibleSize();
    width=size.width;
	height=size.height;
	//init background
	background=Sprite::create("background.png");
	background->setScaleX(width/background->getContentSize().width);
	background->setScaleY(height/background->getContentSize().height);
	background->setPosition(width/2,height/2);
	this->addChild(background);
	//init floor
	floor=Sprite::create("floor.png");
	floor->setScaleY((height/3)/(floor->getContentSize().height));
	floor->setScaleX(width/(floor->getContentSize().width));
	floor->setAnchorPoint(Vec2(0.5f,1.0f));
	floor->setPosition(Vec2(width/2,height/3));
	this->addChild(floor);	
	//init moon
	auto moon=Sprite::create("moon.png");
	moon->setScale(width/4/moon->getContentSize().width);
	moon->setPosition(Vec2(width-moon->getContentSize().width*moon->getScale()/2-30,height-moon->getContentSize().height*moon->getScale()/2-30));
	this->addChild(moon);
	//init dart
	dart=Dart::create();
	this->addChild(dart);
	dart->unscheduleUpdate();
	//init hero
	heroLayer=Hero::create();
	this->addChild(heroLayer);
	hero=heroLayer->getHeroSprite();
	//init keylistener
	keyListener=EventListenerKeyboard::create();
	keyListener->onKeyReleased=CC_CALLBACK_2(BackgroundScene::backToStart,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener,this);
	
	//init introduce
	if(!isFirstIn)
	{   
		if(introduceListener!=nullptr)
		{

			_eventDispatcher->removeEventListener(introduceListener);
		}
	   dart->scheduleUpdate();
	   scheduleUpdate();
	}
	else
	{  
	    //init introudcueListener
	introduceListener=EventListenerTouchOneByOne::create();
	introduceListener->onTouchMoved=CC_CALLBACK_2(BackgroundScene::onIntroduceTouchMove,this);
	introduceListener->onTouchBegan=CC_CALLBACK_2(BackgroundScene::onIntrouduceTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(introduceListener,this);	
	  finger=Sprite::create("finger.png");
	  finger->setPosition(width/5*4,height/2);
	  this->addChild(finger);
	  auto moveUp=Sequence::create(MoveBy::create(1.0f,Vec2(0,80)),CallFunc::create([&](){finger->setPosition(Vec2(width/5*4,height/2));}),nullptr);	  
	  auto repeatMoveUp=RepeatForever::create(moveUp);
	  finger->runAction(repeatMoveUp);
	}
	return true;
}

bool BackgroundScene::onIntrouduceTouchBegan(Touch* touch,Event* event)
{
	beginLocation=touch->getLocation();
	return true;
}

void BackgroundScene::onIntroduceTouchMove(Touch* touch,Event* event)
{
	auto moveLocation=touch->getLocation();
	auto distance=moveLocation-beginLocation;
	if(abs(distance.distance(beginLocation))>50)
	{
	if(!hasUp && distance.y>10)
	{   
		hasUp=true;
		finger->setPosition(Vec2(width/2,height/3*2));
		finger->cleanup();
		auto moveRight=Sequence::create(MoveBy::create(1,Vec2(80,0)),CallFunc::create([&](){finger->setPosition(Vec2(width/2,height/3*2));}),nullptr);
		finger->runAction(RepeatForever::create(moveRight));
		return;
	}
	else if(!hasRight && distance.x>10)
	{
		hasRight=true;
		finger->cleanup();
		finger->setPosition(Vec2(width/2,height/3*2));
		auto moveLeft=Sequence::create(MoveBy::create(1,Vec2(-80,0)),CallFunc::create([&](){finger->setPosition(Vec2(width/2,height/3*2));}),nullptr);
		finger->runAction(RepeatForever::create(moveLeft));
		return;
	}
	else if(!hasLeft && distance.x<-10)
	{
		hasLeft=true;
		finger->cleanup();
		this->removeChild(finger);
		isFirstIn=false;
		scheduleUpdate();
		dart->scheduleUpdate();
		return;
	}
	}

}


void BackgroundScene::backToStart(EventKeyboard::KeyCode, Event*)
{
	auto director=Director::getInstance();
	director->replaceScene(StartScene::createScene());

}

void BackgroundScene::update(float dt)
{
	darts=dart->getdartVec();
	auto boundingBox=hero->getBoundingBox();
	float x=boundingBox.origin.x;
	float y=boundingBox.origin.y;
	float width=boundingBox.size.width-18;
	float height=boundingBox.size.height;
	collideRect.setRect(x,y,width,height);
	for(int i=0;i<darts.size();i++)
	{   
		auto box=darts.at(i)->getBoundingBox();
		if(box.intersectsRect(collideRect))
		{

		//	//Director::getInstance()->replaceScene(BackgroundScene::createScene());
			hero->stopAllActions();
			heroLayer->stopCloud();
			heroLayer->heroDead();
			dart->unscheduleUpdate();
			darts.at(i)->cleanup();
			int oldScore=UserDefault::getInstance()->getIntegerForKey("score");
			if(Dart::score>oldScore)
			{
			   UserDefault::getInstance()->setIntegerForKey("score",Dart::score);
			}
		//	//hero->runAction(Sequence::create(MoveTo::create(0.1f,Vec2(hero->getContentSize().width/2,hero->getPositionY())),CallFunc::create(CC_CALLBACK_0(BackgroundScene::finalHit,this)),nullptr));			
		//	//hero->runAction(MoveTo::create(0.1f,Vec2(hero->getContentSize().width/2,hero->getPositionY())));
			unscheduleUpdate();
			return;
		}
		
	}
	
}



