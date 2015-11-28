#include "Hero.h"
#include "BackgroundScene.h"

bool Hero::init()
{
	if(!Node::init())
	{
		return false;
	}
	auto size=Director::getInstance()->getVisibleSize();
	width=size.width;
	height=size.height;
	//init cloud
	cloud=CloudLayer::create();
	this->addChild(cloud);
	//init flag
	isJumping=false;
	//init flag
	isRunning=false;
	isJumping=false;
	//init animation
	initJumpAnimation();
	initNormalAnimation();
	initRunAnimation();
	initDeadAnimation();
	//init hero
	hero=Sprite::create("run1.png");
	hero->setScale(height/10/hero->getContentSize().height);
	hero->setPosition(hero->getContentSize().width*hero->getScale()/2+50,height/3+hero->getContentSize().height*hero->getScale()/2);
	startNormalAnimation();
	this->addChild(hero,3);
	//init listener
	listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(Hero::myTouchBegan,this);
	listener->onTouchMoved=CC_CALLBACK_2(Hero::myTouchMove,this);
	listener->onTouchEnded=CC_CALLBACK_2(Hero::myTouchEnd,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);	
	return true;
}

void Hero::initDeadAnimation()
{
	auto deadAnimation=Animation::create();
	deadAnimation->addSpriteFrameWithFile("dead.png");
	deadAnimation->setDelayPerUnit(0.3f);
	deadAnimation->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(deadAnimation,"dead");
}

void Hero::initJumpAnimation()
{   
	auto texture=TextureCache::getInstance()->addImage("stand.png");
	auto jumpAnimation=Animation::create();
	jumpAnimation->addSpriteFrameWithFile("jump.png");
	jumpAnimation->setDelayPerUnit(0.5f);
	jumpAnimation->setRestoreOriginalFrame(true);
	auto cache=AnimationCache::getInstance();
	cache->addAnimation(jumpAnimation,"jump");
}

void Hero::initRunAnimation()
{
	//init walk animation
	auto runAnimation=Animation::create();
	for(int i=1;i<7;i++)
	{
		char name[50];
		sprintf(name,"run%d.png",i);
		runAnimation->addSpriteFrameWithFile(name);
	}
	runAnimation->setDelayPerUnit(0.1f);
    runAnimation->setRestoreOriginalFrame(true);
	auto cache=AnimationCache::getInstance();
	cache->addAnimation(runAnimation,"run");

}

void Hero::initNormalAnimation()
{   
	auto normalAnimation=Animation::create();
	normalAnimation->addSpriteFrameWithFile("stand.png");
	normalAnimation->setDelayPerUnit(0.1f);
	normalAnimation->setRestoreOriginalFrame(true);
	auto cache=AnimationCache::getInstance();
	cache->addAnimation(normalAnimation,"normal");

}

void Hero::startNormalAnimation()
{   
	cloud->unscheduleUpdate();
	hero->stopAllActions();
	auto animate=getAnimate("normal");
	hero->runAction(RepeatForever::create(animate));
}

void Hero::startRunAnimation()
{  
   cloud->scheduleUpdate();
   hero->stopAllActions();
   auto animate=getAnimate("run");
   hero->runAction(RepeatForever::create(animate));
}

void Hero::startJumpAnimation()
{  
	if(!isJumping)
  { 
	hero->stopAllActions();
	isJumping=true;
	MoveBy* moveUp=nullptr;
	EaseSineOut* out=nullptr;
	MoveBy* moveDown=nullptr;
	EaseSineOut* in=nullptr;
	if(isRunning)
	{
	  moveUp=MoveBy::create(0.45f,Vec2(0,200));
	  out=EaseSineOut::create(moveUp);
	  moveDown=MoveBy::create(0.45f,Vec2(0,-200));
	  in=EaseSineOut::create(moveDown);
	}
	else
	{ 
	  moveUp=MoveBy::create(0.3f,Vec2(0,200));
	  out=EaseSineOut::create(moveUp);
	  moveDown=MoveBy::create(0.3f,Vec2(0,-200));
	  in=EaseSineOut::create(moveDown);
	}
	auto jumpAnimation=AnimationCache::getInstance()->getAnimation("jump");
	hero->runAction((Animate::create(jumpAnimation)));
	hero->runAction(Sequence::create(out,in,CallFunc::create([&]()->void {isJumping=false;
	if(isRunning)
	{
	startRunAnimation();
	}
	else
	{
		hero->setTexture(TextureCache::getInstance()->getTextureForKey("stand.png"));
	}
	}),nullptr));
	}
}

void Hero::jumpFinished()
{
	isJumping=false;

}

Animate* Hero::getAnimate(std::string animationName)
{
	auto animation=AnimationCache::getInstance()->getAnimation(animationName);
	auto animate=Animate::create(animation);
	return animate;
}



bool Hero::myTouchBegan(Touch* touch,Event* event)
{
	begLocation=touch->getLocation();
	return true;
}

void Hero::myTouchMove(Touch* touch,Event* event)
{
	movLocation=touch->getLocation();
	auto numDistance=movLocation.distance(begLocation);
	if(abs(numDistance)>20)
	{
	auto distance=movLocation-begLocation;
	auto varx=distance.x;
	auto vary=distance.y;
	if(abs(varx)<abs(vary))
	{  
		
		if(vary>0)
		{
		     
				startJumpAnimation();
				return;
			
		}
	}

	else
	{
		
		if(varx>0)
		{
			if(isRunning || isJumping)
			{
				return;
			}

			else
			{   
				Director::getInstance()->getScheduler()->setTimeScale(1.5f);
				startRunAnimation();
				isRunning=true;
				return;
			}

		}
		else
		{
			if(isRunning && !isJumping)
			{   
				Director::getInstance()->getScheduler()->setTimeScale(1.0f);
				startNormalAnimation();
				isRunning=false;
				return;
			}
			else
			{
				return;
			}

		}

	}
 }

}
void Hero::myTouchEnd(Touch* touch,Event* event)
{

            return;
}

Sprite* Hero::getHeroSprite()
{   
	return hero;
}

void Hero::heroDead()
{   
	char buffer[90];
	char* point;
	point=&buffer[0];
	auto blood=Sprite::create("myblood.png");
	blood->setScale(0.1f);
	blood->setPosition(Vec2(width/2,height/2));
	this->addChild(blood,10);
	blood->runAction(Sequence::create(ScaleTo::create(0.2f,width/blood->getContentSize().width,height/blood->getContentSize().height),CallFunc::create(CC_CALLBACK_0(Hero::showGameOver,this)),nullptr));
}

void Hero::showGameOver()
{   
	Director::getInstance()->pause();
	auto item=MenuItemImage::create("uires_5.png","uires_5.png",CC_CALLBACK_0(Hero::restart,this));
	item->setScale(0.6f);
	item->setPosition(Vec2(width/2,height/2-item->getContentSize().height/2-40));
	auto menu=Menu::create(item,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,11);
	char buffer[100];
	sprintf(buffer,"%d",Dart::score);
	std::string score("Score:");
	score.append(buffer);
	auto finalScore=Label::createWithTTF(score,"fonts/arial.ttf",60);
	finalScore->setPosition(Vec2(width/2,height/2+finalScore->getContentSize().height));
	finalScore->setTextColor(Color4B(255,240,245,255));
	this->addChild(finalScore,11);
}

void Hero::restart()
{
	
	Director::getInstance()->replaceScene(BackgroundScene::createScene());
	Director::getInstance()->resume();

}

void Hero::stopCloud()
{
	cloud->unscheduleUpdate();

}