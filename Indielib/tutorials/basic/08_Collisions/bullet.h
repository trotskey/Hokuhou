/*****************************************************************************************
 * Desc: Class containing information on a particular bullet
 *****************************************************************************************/

#ifndef _bullet_h
#define _bullet_h

#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Surface.h"
#include "Evertable.h"

class Bullet: 
	public Evertable{
	public:  
		Bullet(IND_Surface * surface, bool evert);
		Bullet(IND_Entity2d * ent, bool evert);
		//IND_Entity2d * getEntity();
		bool inRange();
		//bool Evert();
		//bool isEverted();
		bool setBounces(int b);
		bool setXY(float x, float y);
		bool setSpeed(float x, float y);
		bool setAccel(float x, float y);
		bool move(float mDelta);
		bool setRotateable();
		bool invertZ();
    private:
		//IND_Entity2d * Entity;
		IND_Surface * Surface;
		bool rotateable;
		//bool Everted;
		int bounces;
		float eX;
		float eY;
		int z;
		float vX;
		float vY;
		float aX;
		float aY;
};
#endif