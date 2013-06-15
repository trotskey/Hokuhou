#include "spell_103.h"

spell103::spell103(float * t, Evertable * e):spellcard(t,e){
	
}

bool spell103::init(){
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(300);
	return true;
}

bool spell103::move(float mDelta, Evertable * e){
	float eX = Evert->getEntity()->getPosX();
	float eY = Evert->getEntity()->getPosY();
	if(*time - lastfire > 0.05){
		for(int x=0; x<3; x++){
			lastfire = *time;
			Bullet * Bob = factory->createBullet("sbullet",false);
			float xSpeed = (rand()%1000)/10 - 50;
			Bob->setSpeed(xSpeed,-50);
			float xAccel = xSpeed * 10;
			float yAccel = 100 + (rand()%1000)*5;
			Bob->setAccel(xAccel,yAccel);
			Bob->setXY(eX,eY);
			Bob->getEntity()->setTint(0,0,120);
		}
	}
	return true;
}

bool spell103::cleanup(){
	float eX = Evert->getEntity()->getPosX();
	float eY = Evert->getEntity()->getPosY();
	Bullet * bonus = factory->createBullet("bonus",false);
	bonus->setXY(eX-20, eY);
	bonus->setSpeed(0,70);
	bonus = factory->createBullet("bonus",false);
	bonus->setXY(eX, eY-35);
	bonus->setSpeed(0,70);
	bonus = factory->createBullet("bonus",false);
	bonus->setXY(eX+20, eY);
	bonus->setSpeed(0,70);
	return true;
}