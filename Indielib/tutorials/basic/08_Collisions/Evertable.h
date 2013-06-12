/*****************************************************************************************
 * Desc: Class containing an Evertable's requirements
 *****************************************************************************************/

#ifndef _Evertable_h
#define _Evertable_h

//#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
//#include "IND_Surface.h"
//#include "BulletFactory.h"

class Evertable {
	public:  
		//Evertable(bool evert);
		virtual IND_Entity2d * getEntity();
		//bool setXY(float x, float y);
		//bool setSpeed(float x, float y);
		//bool inRange();
		virtual bool isEverted();
		virtual bool Evert();
		//bool hit(int hits);
		//bool move(float mDelta);
    protected:
		//int hp;
		//bool fire();
		IND_Entity2d * Entity;
		//IND_Surface * Surface;
		//BulletFactory * factory;
		bool Everted;
		//float time;
		//float lastfire;
		//float eX;
		//float eY;
		//float vX;
		//float vY;
};
#endif