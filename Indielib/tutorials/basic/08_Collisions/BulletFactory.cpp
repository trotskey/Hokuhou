
#include "BulletFactory.h"


/*
==================
Init singleton
==================
*/
BulletFactory *BulletFactory::_pinstance = 0;// initialize pointer
BulletFactory *BulletFactory::instance() {
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new BulletFactory; // create sole instance
	}
	return _pinstance; // address of sole instance
}

BulletFactory::BulletFactory(){
	// Loading Bullet
	mI = CIndieLib::instance();
	mSurfaceBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceBullet, "../../resources/Hokuhou/bullet.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfaceMedBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceMedBullet, "../../resources/Hokuhou/mbullet.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfacePBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfacePBullet, "../../resources/Hokuhou/pbullet.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfaceMBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceMBullet, "../../resources/Hokuhou/megabullet.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfaceBonus = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceBonus, "../../resources/Hokuhou/bonus.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfaceSBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceSBullet, "../../resources/Hokuhou/spike2.png", IND_ALPHA, IND_32, 0, 255, 0);
	mSurfaceSmallBullet = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceSmallBullet, "../../resources/Hokuhou/sbullet.png", IND_ALPHA, IND_32, 0, 255, 0);

	mScore = Score::instance();

	time = 0;
}

Bullet * BulletFactory::createBullet(bool Evert){
	return createBullet("bullet",Evert);
}

Bullet * BulletFactory::createBullet(const char * type,bool Evert){
	Bullet * Bob;
	string s(type);
	if(!waiting.empty()){
		Bob = new Bullet(waiting.front()->getEntity(),Evert);
		waiting.pop();
	} else {
		Bob = new Bullet(mSurfaceBullet,false);
	}
	if(Bob->isEverted() != Evert){
		Bob->Evert();
	}
	//IND_Surface * surf;	
	if(s.compare("bullet")==0){
		Bob->getEntity()->setSurface(mSurfaceBullet);
		Bob->getEntity()->setBoundingCircle("Bullet", 16, 16, 10);
		Bob->getEntity()->setHotSpot(0.5f,0.5f);
	} else if(s.compare("pbullet")==0){
		Bob->getEntity()->setSurface(mSurfacePBullet);
		Bob->getEntity()->setBoundingCircle("pbullet",5,6,4);
	} else if(s.compare("mbullet")==0){
		Bob->getEntity()->setSurface(mSurfaceMedBullet);
		Bob->getEntity()->setBoundingCircle("Bullet", 12,12,9);
		Bob->getEntity()->setHotSpot(0.5f,0.5f);
	} else if(s.compare("sbullet")==0){
		Bob->getEntity()->setSurface(mSurfaceSmallBullet);
		Bob->getEntity()->setBoundingCircle("Bullet",7,7,4);
		Bob->getEntity()->setHotSpot(0.5f,0.5f);
	}else if(s.compare("bonus")==0){
		Bob->getEntity()->setHotSpot(0.5f, 0.5f);
		Bob->getEntity()->setSurface(mSurfaceBonus);
		Bob->getEntity()->setBoundingCircle("bonus", 10, 10, 50);
	} else if(s.compare("megabullet")==0){
		Bob->getEntity()->setSurface(mSurfaceMBullet);
		Bob->getEntity()->setHotSpot(0.5f, 0.5f);
		Bob->getEntity()->setBoundingCircle("Bullet", 173, 375, 110);
		Bob->getEntity()->setBoundingRectangle("Bullet",63,32,220,343);
		Bob->setRotateable();
	} else if(s.compare("spike")==0){
		Bob->getEntity()->setSurface(mSurfaceSBullet);
		Bob->getEntity()->setHotSpot(0.5f,0.5f);
		Bob->getEntity()->setBoundingTriangle("Bullet",5,24,2,4,8,4);
		Bob->setRotateable();
	}

	current.push(Bob);
	return Bob;
}

bool BulletFactory::Build(float mDelta){
	time += mDelta;
	return true;
}

bool BulletFactory::ClearScreen(){
	queue<Bullet*> temp;
	while(!current.empty()){
		Bullet * Bob = current.front();
		current.pop();
		disappear(Bob);
	}
	current = temp;
	return true;
}

bool BulletFactory::Move(float mDelta){
	queue<Bullet*> temp;
	while(!current.empty()){
		Bullet * Bob = current.front();
		current.pop();
		Bob->move(mDelta);
		if(Bob->inRange()){
			temp.push(Bob);
		} else {
			disappear(Bob);
		}
	}
	current = temp;
	return true;
}

bool BulletFactory::disappear(Bullet * Bob){
	Bob->setXY(-500.0f,-500.0f);
	waiting.push(Bob);
	return true;
}

bool BulletFactory::Suck(float mDelta,Evertable * ever,const char * str){
	queue<Bullet*> temp;
	//const char * type("bonus");
	while(!current.empty()){
		Bullet * Bob = current.front();
		current.pop();
		IND_Entity2d * ent  = ever->getEntity();
		IND_Entity2d * ent2 =  Bob->getEntity();
		if((Bob->isEverted() == false) && mI->_entity2dManager->isCollision(ent,str,ent2,"bonus")){
			float ydiff = ent2->getPosY() - ent->getPosY();
			float xdiff = ent2->getPosX() - ent->getPosX();
			float strength = xdiff*xdiff+ydiff*ydiff;
			float xrate = xdiff*xdiff/strength;
			float yrate = 1-xrate;
			if(ydiff < 0){
				yrate = -yrate;
			}
			if(xdiff < 0){
				xrate = -xrate;
			}
			Bob->setXY(ent2->getPosX()-xrate*300*mDelta,ent2->getPosY()-yrate*300*mDelta);
			if(strength < 20){
				mScore->addtoScore(10);
				disappear(Bob);
			} else {
				temp.push(Bob);
			}
		} else {
			temp.push(Bob);
		}
	}
	current = temp;
	return true;
}

int BulletFactory::Hit(const char * type,Evertable * ever,const char * str){
	queue<Bullet*> temp;
	int ret = 0;
	while(!current.empty()){
		Bullet * Bob = current.front();
		current.pop();
		IND_Entity2d * ent  = ever->getEntity();
		IND_Entity2d * ent2 =  Bob->getEntity();
		if((Bob->isEverted() == ever->isEverted()) && mI->_entity2dManager->isCollision(ent,str,ent2,type)){
			ret++;
			disappear(Bob);
		} else {
			temp.push(Bob);
		}
	}
	current = temp;
	return ret;
}

bool BulletFactory::Evert(){
	queue<Bullet*> temp;
	while(!current.empty()){
		Bullet * Bob = current.front();
		current.pop();
		Bob->Evert();
		temp.push(Bob);
	}
	current = temp;
	return true;
}
    