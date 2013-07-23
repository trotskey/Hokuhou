#include "Stage1Boss.h"
Stage1Boss::Stage1Boss(bool evert):EnTank(evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	phase = 0;
	mTimer = Timer::instance();
	moveTime = 2.0f;
	{
		spellcard * t = new spellcard(&time,this);
		spells.push(t);
		spellcard * s = new spell102(&time,this);
		spells.push(s);
		spellcard * r = new spell103(&time,this);
		spells.push(r);
	}

	test = new spell104(&time,this);
	test->init();
}

Stage1Boss::Stage1Boss(IND_Entity2d * e ,bool evert):EnTank(e,evert){
	Entity->setTint(100,100,100);
	tX = 0;
	tY = 0;
	phase = 0;
	mTimer = Timer::instance();
	moveTime = 2.0f;
	{
		spellcard * t = new spellcard(&time,this);
		spells.push(t);
		spellcard * s = new spell102(&time,this);
		spells.push(s);
		spellcard * r = new spell103(&time,this);
		spells.push(r);
	}

	test = new spell104(&time,this);
	test->init();
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

bool Stage1Boss::nextCard(){
	bool ret;
	test->cleanup();
	phase++;
	factory->ClearScreen();
	if(!spells.empty()){
		ret = false;

		test = spells.front();
		spells.pop();
		test->init();
		time = 0.0f;
		lastfire = 0.0f;
	} else {
		ret = true;
		setXY(-500.0f,-500.0f);
	}
	return ret;
}

bool Stage1Boss::hit(int hits){
	if(time < 2.0){
		return false;
	}
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
			test->move(mDelta,e);
		}
	}
	if(phase >= 1){
		test->move(mDelta,e);
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

/* ___END___
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
*/

/*
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
			int tY = 600;*//*
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
}*/