#include "EnTank3.h"


EnTank3::EnTank3(bool evert):EnTank(evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	hp = 300;
	for(int x=0; x<60; x++){
		fullAnglesX[x] = sinf((x*3.0f-90)/180.0f*PI);
		fullAnglesY[x] = cosf((x*3.0f-90)/180.0f*PI);
	}
	lastslide = 0;
	lasttrack = 0;
	risecounter = 0;
	lastrise = 0;
	phase = 0;
	firecount = 0;
	numphases = 2;
	slideflip = false;
	mTimer = Timer::instance();
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(hp);
}

EnTank3::EnTank3(IND_Entity2d * e ,bool evert):EnTank(e,evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	hp = 200;
	for(int x=0; x<60; x++){
		fullAnglesX[x] = sinf((x*3.0f-90)/180.0f*PI);
		fullAnglesY[x] = cosf((x*3.0f-90)/180.0f*PI);
	}
	lastslide = 0;
	lasttrack = 0;
	risecounter = 0;
	lastrise = 0;
	phase = 0;
	numphases = 2;
	firecount = 0;
	slideflip = false;
	mTimer = Timer::instance();
	mTimer->setInitTime(40.0f);
	mTimer->setInitHP(hp);
}

IND_Entity2d * EnTank3::getEntity(){
	return Entity;
}

bool EnTank3::isEverted(){
	return Everted;
}

bool EnTank3::setXY(float x, float y){
	eX = x;
	eY = y;
	Entity->setPosition(eX, eY, 1);
	return true;
}
bool EnTank3::setSpeed(float x, float y){
	vX = x;
	vY = y;
	return true;
}

bool EnTank3::nextCard(){
	bool ret;
	mTimer->setInitTime(40.0f);
	phase++;
	if(hp < 1){
		mScore->addtoScore(4000);
	}
	mScore->addtoScore(1000);
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
		time = 0.0f;
		lastfire = 0.0f;
		lastslide = 0.0f;
	} else {
		ret = true;
		setXY(-500.0f,-500.0f);
	}
	return ret;
}

bool EnTank3::hit(int hits){
	bool ret = false;
	hp -= hits;
	mScore->addtoScore(hits*10);
	mTimer->setInitHP(hp);
	if(hp < 1){
		ret = nextCard();
	}
	return ret;
}

bool EnTank3::move(float mDelta, Evertable * e){
	time += mDelta;
	if(time < 2 && phase == 0) {
		eX += mDelta*vX;
		eY += mDelta*vY;
		Entity->setPosition(eX, eY, 1);
		return true;
	}
	if(!mTimer->decrementTime(0)){
		nextCard();
		return true;
	}
	if(phase == 0) { 
		if(time-lastfire > 0.8){
			bloom(slideflip);
			lastfire = time;
		}
		if(time-lastslide > 6){
			slide(e);
			lastslide = time;
		}
		if(time-lasttrack > 2){
			tX = e->getEntity()->getPosX();
			tY = e->getEntity()->getPosY();
			fire(e);
			lasttrack = time;
		}
		if(time - lastrise > 0.1){
			rise(e);
			lastrise = time;
		}
	} else if(phase == 1){
		if(time - lastslide > 0.5){
			lastslide = time;
			for(int x=0; x<4; x++){
				Bullet * Bob = factory->createBullet(!Everted);
				int r = rand()%490;
				Bob->setXY(10+r,0);
				Bob->setSpeed(0,60);
				Bob->Evert();
				if(x>1){
					Bob->Evert();
					Bob->setSpeed(0,50+rand()%30);
				}
			}
		}
		if(time < 2){
			
		} else {
			if(time - lastfire > 3.5){
				lastfire = time;
				tX = e->getEntity()->getPosX();
				tY = e->getEntity()->getPosY();
				if(firecount == 0){
					firelarge(e,-10);
				} else if(firecount==1){
					firelarge(e,250);
				} else if(firecount==2){
					firelarge(e,510);
				}
				firecount++;
				if(firecount==3){
					firecount = 0;
				}
			}
		}
	}
	return true;
}

bool EnTank3::inRange(){
	return (eX > -50) && (eY > -100) && (eX < 550) && (eY < 650);
}

bool EnTank3::Evert(){
	Everted = !Everted;
	if(Everted){
		Entity->setTransparency(75);
	} else {
		Entity->setTransparency(255);
	}
	return Everted;
}

bool EnTank3::slide(Evertable * e){
	for(int x=0; x<15; x++){
		Bullet * Bob = factory->createBullet(!Everted);
		Bob->setXY(0,x*50);
		Bob->setSpeed(60,0);
		Bob->Evert();
		//slideflip = !slideflip;
	}
	slideflip = !slideflip;
	/*c = new cluster(false);
	c->setXY(0,200);
	c->setSpeed(100,10);
	c->rotate(30);
	cluster * d = new cluster(false);
	d->setXY(0,200);
	d->setSpeed(100,10);
	d->setMirrorY(true);
	d->rotate(-30);*/
	return true;
}

bool EnTank3::rise(Evertable * e){
	if(risecounter < 10){
		Bullet * Bob = factory->createBullet(false);
		Bob->setXY((risecounter-1)*60,600);
		Bob->setSpeed(5,-50);
		Bob->Evert();
		if(Everted){
			Bob->Evert();
		}
	}
	risecounter++;
	if(risecounter > 80){
		risecounter = 0;
	}
	return true;
}

bool EnTank3::bloom(bool offset){
	int y = 0;
	if (offset){
		y = 3;
	}
	for(int x=y; x<60; x+=5){
		Bullet * Bob = factory->createBullet(false);
		Bob->setXY(eX,eY+20);
		Bob->setSpeed(fullAnglesX[x] * 150.0f,fullAnglesY[x] * 150.0f);
	}
	return true;
}

bool EnTank3::firelarge(Evertable * e,float oX){
	//float oX = -10;
	float oY = -10;
	float hypot = sqrtf((oX-tX)*(oX-tX)+(tY-oY)*(tY-oY));
	float angleX = (oX-tX)/hypot;
	float angleY = (tY-oY)/hypot;
	Bullet * Bob = factory->createBullet("megabullet",false);
	Bob->setXY(oX,oY);
	Bob->setSpeed(-angleX * 200,angleY * 200);
	return true;
}

bool EnTank3::fire(Evertable * e){
	float mY = eY+20;
	float hypot = sqrtf((eX-tX)*(eX-tX)+(tY-mY)*(tY-mY));
	float angleX = (eX-tX)/hypot;
	float angleY = (tY-mY)/hypot;
	float offset = 40;
	for(int x=0; x<3; x++){
		Bullet * Bob = factory->createBullet(false);
		Bob->setXY(eX,eY+20);
		if(x==0){
			Bob->setSpeed(-angleX * 200,angleY * 200);
		} else if(x==1){
			hypot = sqrtf((eX-(tX+offset))*(eX-(tX+offset))+(tY-mY)*(tY-mY));
			angleX = (eX-(tX+offset))/hypot;
			angleY = (tY-mY)/hypot;
			Bob->setSpeed(-angleX * 200,angleY * 200);
			//Bob->Evert();
		} else if(x==2){
			hypot = sqrtf((eX-(tX-offset))*(eX-(tX-offset))+(tY-mY)*(tY-mY));
			angleX = (eX-(tX-offset))/hypot;
			angleY = (tY-mY)/hypot;
			Bob->setSpeed(-angleX * 200,angleY * 200);
		}
		if(Everted){
			Bob->Evert();
		}
	}
	return true;
}