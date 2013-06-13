#include "Timer.h"
#include <stdio.h>
/*
==================
Init singleton
==================
*/
Timer *Timer::_pinstance = 0;// initialize pointer
Timer *Timer::instance() {
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new Timer; // create sole instance
	}
	return _pinstance; // address of sole instance
}

Timer::Timer(){
	time = 0.0f;
	hp = 0;
	sprintf(tString,"%2.0f",time);
	CIndieLib *mI = CIndieLib::instance();
	//health = mI->_entity2dManager(
	health = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(health);
	mtime = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mtime);
	mBonus = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBonus);

	// Font
	fonts = FontManager::instance();

	// Loading Stage Clear
	mSurfaceWhite = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceWhite, "../../resources/Hokuhou/white.png", IND_ALPHA, IND_32, 0, 0, 0);

	health->setSurface(mSurfaceWhite);
	health->setHotSpot(0.0f,0.0f);
	health->setPosition(50,20,14);
	health->setTint(255,255,255);
	health->setScale(0.0f,5.0f);
	health->setTransparency(255);

	mtime = fonts->createText("small");
	mtime->setPosition(40,7,14);
	mtime->setTransparency(0);
	mtime->setScale(1.7,2);
	mtime->setAlign(IND_RIGHT);
	mtime->setText(tString);

	mBonus = fonts->createText("small");
	mBonus->setPosition(250,300,14);
	mBonus->setTransparency(0);
	mBonus->setScale(1.7,2);
	mBonus->setAlign(IND_CENTER);
	mBonus->setText(tString);
	bonusTime = 0;
	bonusFailed = false;
	mScore = Score::instance();
}
bool Timer::setInitHP(int h){
	hp = h;
	health->setScale(hp,5.0f);
	health->setTransparency(255);
	return true;
}
bool Timer::hit(int hits){
	hp -= hits;
	health->setScale(hp,5.0f);
	if(hp <= 0){
		mtime->setTransparency(0);
		if(!bonusFailed){
			int tBonus = (int)time*1000+4000;
			sprintf(bString,"remaining %2.0f\n bonus: %d",time,tBonus);
			mScore->addtoScore(tBonus);
		} else {
			sprintf(bString,"bonus failed\n no bonus");
		}
		mBonus->setText(bString);
		mBonus->setTransparency(255);
		bonusTime = 2.0f;
	}
	return (hp > 0);
}
bool Timer::setInitTime(float t){
	time = t;
	sprintf(tString,"%2.0f",time);
	mtime->setText(tString);
	if(time > 0){
		mtime->setTransparency(255);
	} else {
		mtime->setTransparency(0);
		health->setTransparency(0);
		sprintf(bString,"bonus failed\n no bonus");
		mBonus->setText(bString);
		mBonus->setTransparency(255);
		bonusTime = 2.0f;
	}
	bonusFailed = false;
	return true;
}
bool Timer::failBonus(){
	bonusFailed = true;
	return true;
}

bool Timer::decrementTime(float t){
	time -= t;
	if(bonusTime){
		bonusTime -=t;
		if(bonusTime <= 0.0f){
			bonusTime = 0.0f;
			mBonus->setTransparency(0);
		}
	}
	if(time < 0){
		time = 0.0f;
		mtime->setTransparency(0);
		health->setTransparency(0);
		return false;
	}
	sprintf(tString,"%2.0f",time);
	mtime->setText(tString);
	return (time > 0);
}