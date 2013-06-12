/*****************************************************************************************
 * Desc: Class containing information on a particular bullet
 *****************************************************************************************/

#ifndef _EnTank2_h
#define _EnTank2_h

#include "enemyTank.h"
#include <math.h>

class EnTank2: 
	public EnTank{
	public:  
		EnTank2(bool evert);
		EnTank2(IND_Entity2d * e, bool evert);
		IND_Entity2d * getEntity();
		bool setXY(float x, float y);
		bool setSpeed(float x, float y);
		bool inRange();
		bool Evert();
		bool isEverted();
		bool hit(int hits);
		bool move(float mDelta,Evertable * e);
    protected:
		//int hp;
		int bCount;
		bool fire(Evertable * e);
		bool fire2(Evertable * e);
		//IND_Surface * Surface;
		//BulletFactory * factory;
		//Score * mScore;
		//float time;
		//float lastfire;
		//float eX;
		//float eY;
		float tX;
		float tY;
		//float vX;
		//float vY;
};
#endif