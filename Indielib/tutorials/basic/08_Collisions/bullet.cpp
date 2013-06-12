#include "bullet.h"

Bullet::Bullet(IND_Surface *surf, bool evert){
	Entity = IND_Entity2d::newEntity2d();
	CIndieLib *mI = CIndieLib::instance();
	mI->_entity2dManager->add(Entity);
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	if(evert){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	Entity->setBoundingCircle("Bullet", 16, 16, 10);
	Everted = evert;
	eX = -100;
	eY = -100;
	rotateable = false;
	z = 2;
	aX = 0;
	aY = 0;
	bounces = 0;
}
Bullet::Bullet(IND_Entity2d *ent, bool evert){
	Entity = ent;
	//CIndieLib *mI = CIndieLib::instance();
	//mI->_entity2dManager->add(Entity);
	//Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	if(evert){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	Entity->setBoundingCircle("Bullet", 16, 16, 13);
	Everted = evert;
	eX = -100;
	eY = -100;
	rotateable = false;
	z = 2;
	aX = 0;
	aY = 0;
	bounces = 0;
}

bool Bullet::invertZ(){
	z*=-1;
	return z > 0;
}

IND_Entity2d * Evertable::getEntity(){
	return Entity;
}

bool Bullet::setXY(float x, float y){
	eX = x;
	eY = y;
	Entity->setPosition(eX, eY, z);
	return true;
}

bool Bullet::move(float mDelta){
	if(bounces){
		if(eX < 5 || eX > 495){
			vX *= -1;
			setSpeed(vX,vY);
			bounces--;
		}
		if(eY < 5 /*|| eY > 595*/){
			vY *= -1;
			setSpeed(vX,vY);
			bounces--;
		}
	}
	vX += aX*mDelta*mDelta;
	eX += vX*mDelta;
	vY += aY*mDelta*mDelta;
	eY += vY*mDelta;
	Entity->setPosition(eX, eY, z);
	return true;
}

bool Bullet::setRotateable(){
	rotateable = true;
	return true;
}

bool Bullet::setSpeed(float x, float y){
	vX = x;
	vY = y;
	if(rotateable){
		float mAngle = atanf(vX/vY);
		if(y<0){
			mAngle = PI + mAngle;
		}
		mAngle = mAngle/PI * 180;
		Entity->setAngleXYZ(0,0,-mAngle);
	}
	return true;
}

bool Bullet::setAccel(float x, float y){
	aX = x;
	aY = y;
	return true;
}

bool Bullet::setBounces(int b){
	bounces = b;
	return true;
}

bool Bullet::inRange(){
	eX = Entity->getPosX();
	eY = Entity->getPosY();
	return (eX > -250) && (eY > -400) && (eX < 650) && (eY < 750);
}

bool Evertable::isEverted(){
	return Everted;
}

bool Evertable::Evert(){
	Everted = !Everted;
	if(Everted){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	return Everted;
}
