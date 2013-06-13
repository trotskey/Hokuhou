#include "Stage1Boss.h"
Stage1Boss::Stage1Boss(bool evert):EnTank(evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	hp = 300;
	/*for(int x=0; x<60; x++){
		fullAnglesX[x] = sinf((x*3.0f-90)/180.0f*PI);
		fullAnglesY[x] = cosf((x*3.0f-90)/180.0f*PI);
	}*/
	phase = 0;
	firecount = 0;
	numphases = 2;
	slideflip = false;
	mTimer = Timer::instance();
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(hp);
	c = 0;
	d = 0;
	lastcrow = 0;
	//e = 0;
	//Azuma = 0;
	bulletsSet = false;
	moveTime = 2.0f;
}

Stage1Boss::Stage1Boss(IND_Entity2d * e ,bool evert):EnTank(e,evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	hp = 200;
	/*for(int x=0; x<60; x++){
		fullAnglesX[x] = sinf((x*3.0f-90)/180.0f*PI);
		fullAnglesY[x] = cosf((x*3.0f-90)/180.0f*PI);
	}*/
	phase = 0;
	numphases = 2;
	firecount = 0;
	slideflip = false;
	mTimer = Timer::instance();
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(hp);
	c = 0;
	d = 0;
	//e = 0;
	//Azuma = 0;
	lastcrow = 0;
	bulletsSet = false;
	moveTime = 2.0f;
}

IND_Entity2d * Stage1Boss::getEntity(){
	return Entity;
}

bool Stage1Boss::isEverted(){
	return Everted;
}

bool Stage1Boss::setXY(float x, float y){
	eX = x;
	eY = y;
	Entity->setPosition(eX, eY, 1);
	return true;
}
bool Stage1Boss::setSpeed(float x, float y){
	vX = x;
	vY = y;
	return true;
}

bool Stage1Boss::spellN2(Evertable * ever){
	if(time-lastfire > 0.6){
		for(int x=0; x<18; x++){
			Bullet * Bob = factory->createBullet(false);
			Bob->setXY(eX,eY+20);
			float AngleX = sinf((x*20.0f-70)/180.0f*PI);
			float AngleY = cosf((x*20.0f-70)/180.0f*PI);
			float RightX = sinf((x*20.0f+20)/180.0f*PI);
			float RightY = cosf((x*20.0f+20)/180.0f*PI);
			Bob->setSpeed(AngleX*200,AngleY*200);
			Bob->setAccel(RightX*8000,RightY*8000);
			if(Everted){
				Bob->Evert();
			}
		}
		lastfire = time;
	}
	return true;
}

bool Stage1Boss::spellN3(Evertable * ever){
	if(firecount % 2 && time-lastfire > 0.4){
		int addit = (rand()%72)*5;
		for(int y=0; y<8; y++){
			for(int x=0; x<4; x++){
				Bullet * Bob = factory->createBullet("spike",false);
				Bob->setXY(eX,eY+20);
				float AngleX = sinf((addit+y*40+x*5.0f)/180.0f*PI);
				float AngleY = cosf((addit+y*40+x*5.0f)/180.0f*PI);
				Bob->setSpeed(AngleX*170,AngleY*170);
				//Bob->setBounces(3);
				if(Everted){
					Bob->Evert();
				}
			}
		}
		lastfire = time;
		firecount++;
	} else if(firecount % 2 == 0 && time-lastfire > 0.2){
		float oX = eX;
		float oY = eY+20;
		tX = ever->getEntity()->getPosX();
		tY = ever->getEntity()->getPosY();
		float hypot = sqrtf((tX-oX)*(tX-oX)+(tY-oY)*(tY-oY));
		float angle = acosf((tX-oX)/hypot);
		for(int x=0; x<4; x++){
			Bullet * Bob = factory->createBullet("spike",false);
			Bob->setXY(eX,eY+20);
			float AngleX = cosf(angle+(x*5.0f-10)/180.0f*PI);
			float AngleY = sinf(angle+(x*5.0f-10)/180.0f*PI);
			Bob->setSpeed(AngleX*170,AngleY*170);
			//Bob->setBounces(3);
			if(Everted){
				Bob->Evert();
			}
		}
		lastfire = time;
		firecount++;
	}
	return true;
}


bool Stage1Boss::spellN1(Evertable * ever){
	if(!c || !c->inRange()){
		c = new cluster(false,"scissor");
		c->setXY(0,200);
		c->setSpeed(100,10);
		c->rotate(30);
	}
	if(!d || !d->inRange()){
		d = new cluster(false,"scissor");
		d->setXY(0,200);
		d->setSpeed(100,10);
		d->setMirrorY(true);
		d->rotate(-30);
	}
	if(time > 2.0f && time - lastcrow > 2.0f){
		for(int x=0; x<2; x++){
			Crow * Azuma = new Crow(false); //ugh, circular dependancy keeping me from using enemyfactory
			/*int oX = rand()%490;
			int tX  = rand()%490;
			int oY = 0;
			int tY = 600;*/
			int oX = rand()%2*500;
			int tX  = oX? 0: 500;
			int oY = rand()%600;
			int tY = rand()%600;
			Azuma->setXY(oX,oY);
			float hypot = sqrtf((oX-tX)*(oX-tX)+(tY-oY)*(tY-oY));
			float angleX = (oX-tX)/hypot;
			float angleY = (tY-oY)/hypot;
			Azuma->setSpeed(-angleX*200,angleY*200);
			Azuma->getEntity()->setAngleXYZ(0,0,225.0f);
			//Azuma->getEntity()->setShow(false);
			cluster * e = Azuma->getBullets();
			strings.push(e);
			crows.push(Azuma);
		}
		lastcrow = time;
	}
	if(time > 5.0f && time == lastcrow){
		cluster * e = strings.front();
		strings.pop();
		q = e->getBullets();
		//bulletsSet = true;
		float tX = ever->getEntity()->getPosX();
		float tY = ever->getEntity()->getPosY();
		queue<Bullet *> temp = q;
		float GreatAngleX;
		float GreatAngleY;
		float GreatHypot = 0;
		while(!q.empty()){
			Bullet * Bob = q.front();
			q.pop();
			float oX = Bob->getEntity()->getPosX();
			float oY = Bob->getEntity()->getPosY();
			float hypot = sqrtf((oX-tX)*(oX-tX)+(tY-oY)*(tY-oY));
			float angleX = -(oX-tX)/hypot;
			float angleY = (tY-oY)/hypot;
			if(hypot > GreatHypot){
				GreatHypot  = hypot;
				GreatAngleX = angleX;
				GreatAngleY = angleY;
			}
			Bob->setSpeed(angleX*hypot/10.0f,angleY*hypot/10.0f);
			
		}
		while(!temp.empty()){
			Bullet * Bob = temp.front();
			temp.pop();
			Bob->setAccel(GreatAngleX*1000.0f,GreatAngleY*1000.0f);
		}
	}
	return true;
}

bool Stage1Boss::nextCard(){
	bool ret;
	if(phase == 0){
		while(!crows.empty()){
			Crow * Azuma = crows.front();
			Azuma->setXY(-500,-500);
			crows.pop();
		}
	}
	phase++;
	/*if(hp < 1){
		mScore->addtoScore(4000);
	}*/
	factory->ClearScreen();
	if(phase < numphases){
		Bullet * bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX-20, eY);
		bonus->setSpeed(0,70);
		bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX, eY-35);
		bonus->setSpeed(0,70);
		bonus = factory->createBullet("bonus",false);
		bonus->setXY(eX+20, eY);
		bonus->setSpeed(0,70);
		ret = false;
		hp = 300;
		mTimer->setInitHP(hp);
		mTimer->setInitTime(40.0f);
		time = 0.0f;
		lastfire = 0.0f;
	} else {
		ret = true;
		setXY(-500.0f,-500.0f);
	}
	return ret;
}

bool Stage1Boss::hit(int hits){
	bool ret = false;
	hp -= hits;
	mScore->addtoScore(hits*10);
	//mTimer->setInitHP(hp);
	
	if(!mTimer->hit(hits)){
		ret = nextCard();
	}
	return ret;
}

bool Stage1Boss::move(float mDelta, Evertable * e){
	time += mDelta;
	moveTime -= mDelta;
	if(!mTimer->decrementTime(0)){
		nextCard();
	}
	if(moveTime < 0.0f){
		vX = 0;
		vY = 0;
	} else {
		eX += mDelta*vX;
		eY += mDelta*vY;
	}
	if(phase == 0){
		if(time > 2){
			spellN3(e);
		}
		if(!crows.empty()){
			queue<Crow *> temp;
			temp = crows;
			while(!crows.empty()){
				Crow * Azuma = crows.front();
				crows.pop();
				Azuma->move(mDelta,e);
			}
			crows = temp;
		}
	}
	if(phase == 1 && time - lastfire > 0.3 ){
		fire(e);
		lastfire = time;
	}
	if (phase == 1 && moveTime < -5.0f){
		float tX = rand()%490 + 5;
		float tY = rand()%190 + 10;
		float oX = eX;
		float oY = eY;
		float hypot = sqrtf((oX-tX)*(oX-tX)+(tY-oY)*(tY-oY));
		vX = -(oX-tX)/hypot*100;
		vY = (tY-oY)/hypot*100;
		moveTime = hypot / 100;
	}
	Entity->setPosition(eX, eY, 1);
	return true;
}

bool Stage1Boss::inRange(){
	return (eX > -50) && (eY > -100) && (eX < 550) && (eY < 650);
}

bool Stage1Boss::Evert(){
	Everted = !Everted;
	if(Everted){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	return Everted;
}


bool Stage1Boss::fire(Evertable * e){
	float offset = 40;
	bCount++;
	if(bCount%2){
		for(int x=0; x<18; x++){
			Bullet * Bob = factory->createBullet(false);
			Bob->setXY(eX,eY+20);
			float AngleX = sinf((x*20.0f-90)/180.0f*PI);
			float AngleY = cosf((x*20.0f-90)/180.0f*PI);
			Bob->setSpeed(AngleX*170,AngleY*170);
			if(Everted){
				Bob->Evert();
			}
		}
	} else {
		for(int x=0; x<18; x++){
			Bullet * Bob = factory->createBullet(false);
			Bob->setXY(eX,eY+20);
			float AngleX = sinf((x*20.0f-70)/180.0f*PI);
			float AngleY = cosf((x*20.0f-70)/180.0f*PI);
			float RightX = sinf((x*20.0f+20)/180.0f*PI);
			float RightY = cosf((x*20.0f+20)/180.0f*PI);
			Bob->setSpeed(AngleX*70,AngleY*70);
			Bob->setAccel(RightX*70,RightY*70);
			if(Everted){
				Bob->Evert();
			}
		}
	}
	return true;
}