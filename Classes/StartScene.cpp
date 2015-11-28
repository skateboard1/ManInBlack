#include "StartScene.h"
#include "BackgroundScene.h"

Scene* StartScene::createScene()
{

	auto scene=Scene::create();
	auto layer=StartScene::create();
	scene->addChild(layer);
	return scene;
}


bool StartScene::init()
{   
	if(!Layer::init())
	{

		return false;
	}
	auto size=Director::getInstance()->getWinSize();
	int width=size.width;
	int height=size.height;
	//init bakcground
	auto background=Sprite::create("background.png");
	background->setScaleX(width/background->getContentSize().width);
	background->setScaleY(height/background->getContentSize().height);
	background->setPosition(width/2,height/2);
	this->addChild(background);
	auto moon=Sprite::create("moon.png");
	moon->setPosition(width,height);
	moon->setScale(width/2/moon->getContentSize().width);
	this->addChild(moon);
	auto stickMan=Sprite::create("stick.png");
	stickMan->setScale(height/3/stickMan->getContentSize().height);
	stickMan->setPosition(width/2,stickMan->getContentSize().height*stickMan->getScale()/2);
	this->addChild(stickMan);
	//init start button
	auto startItem=MenuItemImage::create("start.png","start.png",CC_CALLBACK_0(StartScene::startGame,this));
	startItem->setPosition(width/2,height/2);
	startItem->setScale(width/8/startItem->getContentSize().width);
	auto menu=Menu::create(startItem,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	//init score label
	auto labelScore=Label::createWithTTF("BEST:0","fonts/arial.ttf",height/10);
	int score=UserDefault::getInstance()->getIntegerForKey("score",0);
	char buffer[100];
	sprintf(buffer,"%d",score);
	labelScore->setString("BEST:"+std::string(buffer));
	labelScore->setPosition(width/2,startItem->getPositionY()+startItem->getContentSize().height/2*startItem->getScale()+labelScore->getContentSize().height/2+20);
	this->addChild(labelScore);
	//init keyListener
	keyListener=EventListenerKeyboard::create();
	keyListener->onKeyReleased=CC_CALLBACK_2(StartScene::exit,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener,this);
	return true;
}

void StartScene::startGame()
{

	Director::getInstance()->replaceScene(BackgroundScene::createScene());
	Director::getInstance()->resume();
}

void StartScene::exit(EventKeyboard::KeyCode, Event*)
{
	Director::getInstance()->popScene();
	
}