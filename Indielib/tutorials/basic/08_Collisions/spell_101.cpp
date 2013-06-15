#include "spellcard.h"

spellcard::spellcard(float * t, Evertable * e){
	time = t;
	Evert = e;
	factory = BulletFactory::instance();
	mTimer = Timer::instance();
	lastfire = 0;
}

bool spellcard::init(){
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(300);
	return true;
}

bool spellcard::move(float mDelta, Evertable * e){
	float eX = Evert->getEntity()->getPosX();
	float eY = Evert->getEntity()->getPosY();
	if(*time-lastfire > 0.4){
		int addit = (rand()%72)*5;
		//for(int y=0; y<8; y++){
			for(int x=0; x<4; x++){
				Bullet * Bob = factory->createBullet("spike",false);
				Bob->setXY(eX,eY+20);
				float AngleX = sinf((addit+x*5.0f)/180.0f*PI);
				float AngleY = cosf((addit+x*5.0f)/180.0f*PI);
				Bob->setSpeed(AngleX*170,AngleY*170);
				Bob->setBounces(3);
				if(Evert->isEverted()){
					Bob->Evert();
				}
			}
		//}
		lastfire = *time;
	}
	return true;
}

bool spellcard::cleanup(){
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

float spellcard::getTime(){
	return *time;
}