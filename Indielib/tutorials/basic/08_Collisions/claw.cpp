#include "claw.h"

Claw::Claw(bool evert):EnTank(evert){
	bullets = new cluster(false,"none");
	//time = 0;
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("claw");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	pause = 0.3;
	done = false;
}
Claw::Claw(IND_Entity2d * e, bool evert):EnTank(e,evert){
	bullets = new cluster(false,"none");
	time = 0;
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("claw");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	pause = 0.3;
	done = false;
}
cluster * Claw::getBullets(){
	return bullets;
}
bool Claw::move(float mDelta,Evertable * e){
	if(done){
		return false;
	}
	time += mDelta;
	if(time < pause){
		return true;
	}
	if(time > pause+maxTime){
		queue<Bullet*> q = bullets->getBullets();
		while(!q.empty()){
			Bullet * Bob = q.front();
			q.pop();
			float speedX = ((rand()%1000)/10.0)-50;
			float speedY = ((rand()%1000)/10.0)-50;
			if(speedY*speedY < 10){
				speedY *= 5;
			}
			if(speedX*speedX < 10){
				speedX *= 5;
			}
			Bob->setSpeed(speedX,speedY);
		}
		Entity->setShow(false);
		done = true;
		return false;
	}
	if(time - lastfire > 0.05){
		lastfire = time;
		fire(e);
	}
	eX += mDelta*vX;
	eY += mDelta*vY;
	Entity->setPosition(eX, eY, 1);
	return true;
}

bool Claw::setMaxTime(float t){
	maxTime = t;
	return true;
}

bool Claw::Done(){
	return done;
}

bool Claw::fire(Evertable * e){
	Bullet * Bob;
	Bob = factory->createBullet("sbullet",false);
	bullets->addBullet(Bob);
	Bob->setXY(eX,eY);
	return true;
}