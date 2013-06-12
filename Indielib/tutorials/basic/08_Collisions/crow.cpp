#include "crow.h"

Crow::Crow(bool evert):EnTank(evert){
	bullets = new cluster(false,"none");
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("crow");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	bSize = false;
}
Crow::Crow(IND_Entity2d * e, bool evert):EnTank(e,evert){
	bullets = new cluster(false,"none");
	FontsNSurfs = FontManager::instance();
	IND_Surface * surf = FontsNSurfs->getSurface("crow");
	Entity->setSurface(surf);
	Entity->setHotSpot(0.5f, 0.5f);
	bSize = false;
}
//bool setXY(float x, float y);
//bool setSpeed(float x, float y);
//bool inRange();
		//bool Evert();
		//bool isEverted();
		//bool hit(int hits);
		//cluster * getBullets()
cluster * Crow::getBullets(){
	return bullets;
}


bool Crow::move(float mDelta,Evertable * e){
	time += mDelta;
	if(time - lastfire > 0.2){
		lastfire = time;
		fire(e);
	}
	eX += mDelta*vX;
	eY += mDelta*vY;
	Entity->setPosition(eX, eY, 1);
	return true;
}
bool Crow::fire(Evertable * e){
	bSize = !bSize;
	Bullet * Bob;
	//if(bSize){
	//	Bob = factory->createBullet("sbullet",false);
	//} else {
		Bob = factory->createBullet("mbullet",false);
	//}
	bullets->addBullet(Bob);
	Bob->setXY(eX,eY);
	return true;
}
		//bool fire2(Evertable * e);
