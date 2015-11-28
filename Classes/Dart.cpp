#include "Dart.h"

int Dart::score=0;
bool Dart::init()
{
	if(!Layer::init())
	{
		return false;
	}
	isFirst=true;
	score=0;
	auto size=Director::getInstance()->getVisibleSize();
	width=size.width;
	height=size.height;
	dart_width=25;
	dart_speed=width/FLY_TIME;
	//init counter
	counter=Label::createWithTTF("0","fonts/arial.ttf",height/10);
	counter->setTextColor(Color4B(255,255,255,255));
	counter->setPosition(Vec2(width/2,height-counter->getContentSize().height));
	this->addChild(counter);
	scheduleUpdate();
	return true;
}


void Dart::update(float dt)
{   
	int mode=random(0,3);
	int num=-1;
	float delayTime=-1;
	float distance=width+1.5f*dart_width;
	switch(MODE_NEEDSTAY)
	{
	   case MODE_NONE:
		   {   
			  delayTime=dart_width/dart_speed*9;
		      num=random(2,5);
		      generateDart(num,delayTime);
		      break;
		   }
	   case MODE_NEEDRUN:
		   {			  
		       delayTime=dart_width/dart_speed;
		       num=4;
		       generateDart(num,delayTime);
		       break;
		   }
	   case MODE_NEEDSTAY:
		   {   
		       delayTime=dart_width/dart_speed*7;
		       num=3;
		       generateDart(num,delayTime);
		       break;
		   }
	}
	if(dartVec.size()>0)
	{
		for(int i=0;i<dartVec.size();i++)
	 {
		 if(dartVec.at(i)->getPositionX()<0)
		{
			dartVec.eraseObject(dartVec.at(i));
             
		}

	}
	}

}

void Dart::generateDart(int dartNum,float delayTime)
{   
	if(isFirst)
	{
        for(int i=0;i<dartNum;i++)
	{
		auto dart=Sprite::create("dart.png");
		dart->setScale(height/30/dart->getContentSize().height);
		dart->setPosition(Vec2(width+dart->getContentSize().width*dart->getScale()/2,height/3+dart->getContentSize().height*dart->getScale()/2+height/25));
		auto move=MoveBy::create(FLY_TIME,Vec2(-width-dart->getContentSize().width,0));
		auto rotate=RepeatForever::create(RotateBy::create(0.5f,360));
		dartVec.pushBack(dart);
		this->addChild(dart);
		dart->runAction(rotate);
        dart->runAction(Sequence::create(DelayTime::create(delayTime*i),move,CallFunc::create(CC_CALLBACK_0(Dart::addScoreAndremoveDart,this,dart)),nullptr));
	    isFirst=false;      
	}

	}
	else if((dartVec.size()>0) && (dartVec.back()->getPositionX()<width/2))
	{
	   for(int i=0;i<dartNum;i++)
	  {
		auto dart=Sprite::create("dart.png");
		dart->setScale(height/30/dart->getContentSize().height);
		dart->setPosition(Vec2(width+dart->getContentSize().width*dart->getScale()/2,height/3+dart->getContentSize().height*dart->getScale()/2+height/20));
		//auto rotate=Repeat::create(RotateBy::create(0.5f,360),300);
		auto rotate=RepeatForever::create(RotateBy::create(0.3f,180));
		auto move=MoveBy::create(FLY_TIME,Vec2(-width-dart->getContentSize().width,0));
		dartVec.pushBack(dart);
		this->addChild(dart);
		dart->runAction(rotate);
		dart->runAction(Sequence::create(DelayTime::create(delayTime*i),move,CallFunc::create(CC_CALLBACK_0(Dart::addScoreAndremoveDart,this,dart)),nullptr));
	  }
	}

}

void Dart::addScoreAndremoveDart(Sprite* dart)
{   

	dart->cleanup();
	if(dartVec.contains(dart))
	{
	  dartVec.eraseObject(dart);
	}
	dart->setVisible(false);
	score++;
	char buffer[100];
	sprintf(buffer,"%d",score);
	counter->setString(buffer);
}


Vector<Sprite*> Dart::getdartVec()
{

	return dartVec;

}