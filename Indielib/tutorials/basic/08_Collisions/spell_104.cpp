#include "spell_104.h"

spell104::spell104(float * t, Evertable * e):spellcard(t,e){
	lepers = new cluster(false,"none");
}

bool spell104::init(){
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(300);
	return true;
}

bool spell104::move(float mDelta, Evertable * e){
	float uX = e->getEntity()->getPosX();
	float uY = e->getEntity()->getPosY();
	if(*time - lastfire > 0.5){
		lastfire = *time;
		Bullet * Bob = factory->createBullet("sbullet",false);
		int side = rand()%4;
		float nX;
		float nY;
		if(side % 2 == 0){
			nX = rand()%490+5;
		} else {
			nY = rand()%590+5;
		}
		if(side == 0){
			nY = 5;
		} else if(side == 2){
			nY = 595;
		} else if(side == 1){
			nX = 5;
		} else if(side == 3){
			nX = 495;
		}
		Bob->setXY(nX,nY);
		Bob->getEntity()->setTint(0,100,0);
		lepers->addBullet(Bob);
	}
	queue<Bullet *> temp = lepers->getBullets();
	while(!temp.empty()){
		Bullet * Bob = temp.front();
		temp.pop();
		float bX = Bob->getEntity()->getPosX();
		float bY = Bob->getEntity()->getPosY();
		float hypot = sqrt((uX-bX)*(uX-bX)+(uY-bY)*(uY-bY));
		float yRate = (uY-bY)/hypot;
		float xRate = (uX-bX)/hypot;
		Bob->setSpeed(xRate*50,yRate*50);
	}
	return true;
}

bool spell104::cleanup(){
	return true;
}