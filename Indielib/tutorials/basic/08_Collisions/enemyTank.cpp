/*****************************************************************************************
 * Desc: Class containing information on a particular bullet
 *****************************************************************************************/
#include "enemyTank.h"

EnTank::EnTank(bool evert){
	CIndieLib *mI = CIndieLib::instance();
	Entity = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(Entity);
	//EnTank(e, evert);
	factory = BulletFactory::instance();
	hp = 50;
	//Entity = e;
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("tank");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	if(evert){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	Entity->setBoundingCircle("Enemy", 65, 70, 20);
	Everted = evert;
	lastfire = 0.0f;
	mScore = Score::instance();
}

EnTank::EnTank(IND_Entity2d * e,bool evert){
	CIndieLib *mI = CIndieLib::instance();
	factory = BulletFactory::instance();
	hp = 20;
	Entity = e;
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("tank");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	if(evert){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	Entity->setBoundingCircle("Enemy", 65, 70, 20);
	Everted = evert;
	lastfire = 0.0f;
	mScore = Score::instance();
}

IND_Entity2d * EnTank::getEntity(){
	return Entity;
}

bool EnTank::isEverted(){
	return Everted;
}

bool EnTank::setXY(float x, float y){
	eX = x;
	eY = y;
	Entity->setPosition(eX, eY, 1);
	return true;
}
bool EnTank::setSpeed(float x, float y){
	vX = x;
	vY = y;
	return true;
}

bool EnTank::hit(int hits){
	bool ret = false;
	hp -= hits;
	mScore->addtoScore(hits*10);
	if(hp < 1){
		ret = true;
		Bullet * bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX-20, eY);
		bonus->setSpeed(0,50);
		bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX, eY-35);
		bonus->setSpeed(0,50);
		//bonus = factory->createBullet("bonus",false);
		//bonus->setXY(eX+20, eY);
		//bonus->setSpeed(0,50);
		mScore->addtoScore(20);
	}
	return ret;
}

bool EnTank::move(float mDelta, Evertable * e){
	time += mDelta;
	if(time > 1 && time < 1.5){
		if(time > 1.25){
			if(time - lastfire > 1){
				fire(e);
				lastfire = time;
			}
		}
	} else if(time < 2 ) {
		eX += mDelta*vX;
		eY += mDelta*vY;
	} else {
		time = 0;
		lastfire = 0;
	}/*else if(time > 2 && time < 3){
		eX += mDelta*vX;
		eY += mDelta*vY;
	} else if(time > 3.25 && time < 3.5){
		if(time - lastfire > 2){
			fire(e);
			lastfire = time;
		}
	} else if(time > 4) {
		eX += mDelta*vX;
		eY += mDelta*vY;
	}*/
	Entity->setPosition(eX, eY, 1);
	return true;
}

bool EnTank::inRange(){
	return (eX > -50) && (eY > -100) && (eX < 550) && (eY < 650);
}

bool EnTank::Evert(){
	Everted = !Everted;
	if(Everted){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	return Everted;
}

bool EnTank::fire(Evertable * e){
	for(int x=0; x<3; x++){
		Bullet * Bob = factory->createBullet(false);
		Bob->setXY(eX,eY+20);
		if(x==0){
			Bob->setSpeed(25.9*1,96.6*1);
		} else if(x==1){
			Bob->setSpeed(0,100*1);
			//Bob->Evert();
		} else if(x==2){
			Bob->setSpeed(-25.9*1,96.6*1);
		}
		/*Bob->getEntity()->setHotSpot(0.5,-2.0f);
		if(x==0){
			Bob->getEntity()->setAngleXYZ(0.0f,0.0f,60.0f);
		} else if(x==1){
			Bob->getEntity()->setAngleXYZ(0.0f,0.0f,180.0f);
		} else if(x==2){
			Bob->getEntity()->setAngleXYZ(0.0f,0.0f,300.0f);
		}
		Bob->setSpeed(0,100*1);*/
		if(Everted){
			Bob->Evert();
		}
	}
	return true;
}