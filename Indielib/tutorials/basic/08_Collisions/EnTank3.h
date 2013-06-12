#ifndef _EnTank3_h
#define _EnTank3_h

#include "enemyTank.h"
#include <math.h>
#include "Timer.h"
#include "cluster.h"

class EnTank3: 
	public EnTank{
	public:  
		EnTank3(bool evert);
		EnTank3(IND_Entity2d * e, bool evert);
		IND_Entity2d * getEntity();
		bool setXY(float x, float y);
		bool setSpeed(float x, float y);
		bool inRange();
		bool Evert();
		bool isEverted();
		bool hit(int hits);
		bool move(float mDelta,Evertable * e);
    protected:
		bool nextCard();
		bool fire(Evertable * e);
		bool firelarge(Evertable * e, float oX);
		bool slide(Evertable * e);
		bool rise(Evertable * e);
		int risecounter;
		Timer * mTimer;
		float lastslide;
		float lasttrack;
		float lastrise;
		int phase;
		int numphases;
		int firecount;
		bool slideflip;
		bool bloom(bool offset);
		float fullAnglesX[60];
		float fullAnglesY[60];
		float tX;
		float tY;

		cluster * c;
};
#endif