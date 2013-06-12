#ifndef _Stage1Boss_h
#define _Stage1Boss_h

#include "enemyTank.h"
#include <math.h>
#include "Timer.h"
#include "cluster.h"
#include "crow.h"

class Stage1Boss: 
	public EnTank{
	public:  
		Stage1Boss(bool evert);
		Stage1Boss(IND_Entity2d * e, bool evert);
		IND_Entity2d * getEntity();
		bool setXY(float x, float y);
		bool setSpeed(float x, float y);
		bool inRange();
		bool Evert();
		bool isEverted();
		bool hit(int hits);
		bool move(float mDelta,Evertable * e);
    protected:
		bool fire(Evertable * e);
		bool nextCard();
		bool spellN1(Evertable * e);
		bool spellN2(Evertable * e);
		bool spellN3(Evertable * e);
		cluster * c;
		cluster * d;
		//cluster * e;
		queue<Crow *> crows;
		queue<cluster *> strings;
		//Crow * Azuma;
		bool bulletsSet;
		queue<Bullet*> q; 
		Timer * mTimer;
		int phase;
		int numphases;
		int firecount;
		bool slideflip;
		float moveTime;
		int bCount;
		float scissorTime;
		float lastcrow;
		float fullAnglesX[60];
		float fullAnglesY[60];
		float tX;
		float tY;
};
#endif