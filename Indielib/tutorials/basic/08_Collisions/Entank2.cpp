#include "EnTank2.h"

EnTank2::EnTank2(bool evert):EnTank(evert){
	Entity->setTint(255,0,0);
	tX = 0;
	tY = 0;
	bCount = 0;
}

EnTank2::EnTank2(IND_Entity2d * e ,bool evert):EnTank(e,evert){
	Entity->setTint(255,0,0);
	tX = 0;
	tY = 0;
	bCount = 0;
}

IND_Entity2d * EnTank2::getEntity(){
	return Entity;
}

bool EnTank2::isEverted(){
	return Everted;
}

bool EnTank2::setXY(float x, float y){
	eX = x;
	eY = y;
	Entity->setPosition(eX, eY, 1);
	return true;
}
bool EnTank2::setSpeed(float x, float y){
	vX = x;
	vY = y;
	return true;
}

bool EnTank2::hit(int hits){
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
		bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX+20, eY);
		bonus->setSpeed(0,50);
		mScore->addtoScore(50);
	}
	return ret;
}

bool EnTank2::move(float mDelta, Evertable * e){
	time += mDelta;
	if(time > 2 && time < 3){
		if(time > 2.25){
			//if(time - lastfire > 2){
			//if(time - lastfire > 0.2){
			if(time - lastfire > 0.05){
				if(time - lastfire > 1){
					tX = e->getEntity()->getPosX();
					tY = e->getEntity()->getPosY();
				}
				if(time < 2.75){
					fire(e);
				} else {
					fire2(e);
				}
				lastfire = time;
			}
		}
	} else if(time < 3 ) {
		eX += mDelta*vX;
		eY += mDelta*vY;
		bCount = 0;
	} else if(time > 6 && time < 7){
		eX += mDelta*vX;
		eY += mDelta*vY;
	} else if(time > 7.25 && time < 8){
		//if(time - lastfire > 0.2){
		if(time - lastfire > 0.05){
			if(time - lastfire > 1){
				tX = e->getEntity()->getPosX();
				tY = e->getEntity()->getPosY();
			}
			if(time < 7.75){
				fire2(e);
			} else {
				fire(e);
			}
			lastfire = time;
		}
	} else if(time > 10) {
		eX += mDelta*vX;
		eY += mDelta*vY;
	}
	Entity->setPosition(eX, eY, 1);
	return true;
}

bool EnTank2::inRange(){
	return (eX > -50) && (eY > -100) && (eX < 550) && (eY < 650);
}

bool EnTank2::Evert(){
	Everted = !Everted;
	if(Everted){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	return Everted;
}

bool EnTank2::fire2(Evertable * e){
	float mY = eY+20;
	float hypot = sqrtf((eX-tX)*(eX-tX)+(tY-mY)*(tY-mY));
	float angleX = (eX-tX)/hypot;
	float angleY = (tY-mY)/hypot;
	float angle  = acosf(angleX);
	Bullet * Bob = factory->createBullet("spike",false);
	Bob->setXY(eX,eY+20);
	Bob->setSpeed(-cosf(angle + (bCount*5.0-25.0f)/180.0f*PI) * 200,sinf(angle + (bCount*5.0-25.0f)/180.0f*PI) * 200);
	bCount--;
	if(Everted){
		Bob->Evert();
	}
	return true;
}

bool EnTank2::fire(Evertable * e){
	float mY = eY+20;
	float hypot = sqrtf((eX-tX)*(eX-tX)+(tY-mY)*(tY-mY));
	float angleX = (eX-tX)/hypot;
	float angleY = (tY-mY)/hypot;
	float angle  = acosf(angleX);
	float offset = 40;
	//for(int x=0; x<3; x++){
	//for(int x =0; x<10; x++){
		//Bullet * Bob = factory->createBullet(false);
		Bullet * Bob = factory->createBullet("spike",false);
		Bob->setXY(eX,eY+20);
		Bob->setSpeed(-cosf(angle + (bCount*5.0-25.0f)/180.0f*PI) * 200,sinf(angle + (bCount*5.0-25.0f)/180.0f*PI) * 200);
		bCount++;
		//Bob->setSpeed(-angleX * 100,angleY * 100);
		/*if(x==0){
			Bob->setSpeed(-angleX * 200,angleY * 200);
		} else if(x==1){
			//hypot = sqrtf((eX-(tX+offset))*(eX-(tX+offset))+(tY-mY)*(tY-mY));
			//angleX = (eX-(tX+offset))/hypot;
			//angleY = (tY-mY)/hypot;
			Bob->setSpeed(-cosf(angle + 10.0f/180.0f*PI) * 200,sinf(angle + 10.0f/180.0f*PI) * 200);
			//Bob->Evert();
		} else if(x==2){
			//hypot = sqrtf((eX-(tX-offset))*(eX-(tX-offset))+(tY-mY)*(tY-mY));
			//angleX = (eX-(tX-offset))/hypot;
			//angleY = (tY-mY)/hypot;
			//Bob->setSpeed(-angleX * 200,angleY * 200);
			Bob->setSpeed(-cosf(angle - 10.0f/180.0f*PI) * 200,sinf(angle - 10.0f/180.0f*PI) * 200);
		}*/
		if(Everted){
			Bob->Evert();
		}
	//}
	return true;
}