#include "spell_102.h"

spell102::spell102(float * t, Evertable * e):spellcard(t,e){
	clawcount = 0;
}

bool spell102::init(){
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(300);
	return true;
}

bool spell102::move(float mDelta, Evertable * e){
	if(clawcount % 6 == 5 && *time - lastfire > 7.0){
		clawcount++;
	}
	if(*time - lastfire > 1.0 && (clawcount % 6) < 5){
		lastfire = *time;
		clawcount++;
		if(clawcount % 6 == 1){
			for(int x=0; x<4; x++){
				Claw * paw = new Claw(false);
				paw->getEntity()->setAngleXYZ(0,0,45);
				paw->setSpeed(-353.55,353.55);
				paw->setXY(400+42*x,300+42*x);
				paw->setMaxTime(0.6);
				claws.push(paw);
			}
		} else if(clawcount % 6 == 2){
			for(int x=0; x<4; x++){
				Claw * paw = new Claw(false);
				paw->getEntity()->setAngleXYZ(0,0,-90);
				paw->setSpeed(500,0);
				paw->setXY(50,20+60*x);
				paw->setMaxTime(0.6);
				claws.push(paw);
			}
		} else if(clawcount % 6 == 3){
			for(int x=0; x<4; x++){
				Claw * paw = new Claw(false);
				paw->getEntity()->setAngleXYZ(0,0,180);
				paw->setSpeed(0,-500);
				paw->setXY(30+60*x,570);
				paw->setMaxTime(0.6);
				claws.push(paw);
			}
		} else if(clawcount % 6 == 4){
			for(int x=0; x<4; x++){
				Claw * paw = new Claw(false);
				paw->setSpeed(0,500);
				paw->setXY(320+60*x,100);
				paw->setMaxTime(0.6);
				claws.push(paw);
			}
		} else if(clawcount % 6 == 5){
			for(int x=0; x<4; x++){
				Claw * paw = new Claw(false);
				paw->setSpeed(0,500);
				paw->setXY(170+60*x,100);
				paw->setMaxTime(0.6);
				claws.push(paw);
			}
		}
	}

	if(!claws.empty()){
		queue<Claw *> temp;
		temp = claws;
		while(!claws.empty()){
			Claw * Polio = claws.front();
			claws.pop();
			Polio->move(mDelta,e);
		}
		claws = temp;
	}

	return true;
}

bool spell102::cleanup(){
	while(!claws.empty()){
		Claw * Polio = claws.front();
		Polio->getEntity()->setShow(false);
		claws.pop();
	}
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