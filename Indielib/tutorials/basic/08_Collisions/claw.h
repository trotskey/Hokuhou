/*****************************************************************************************
 * Desc: Class containing information on a crow spewing out a group of bullets
 *****************************************************************************************/

#ifndef _claw_h
#define _claw_h

#include <math.h>
#include "cluster.h"
//#include "IND_Entity2d.h"
//#include "FontManager.h"
#include "enemyTank.h"

class Claw:
	public EnTank{
	public:  
		Claw(bool evert);
		Claw(IND_Entity2d * e, bool evert);
		cluster * getBullets();
		bool move(float mDelta,Evertable * e);
		bool setMaxTime(float t);
		bool Done();
    protected:
		bool bSize;
		//float time;
		float maxTime;
		float pause;
		bool done;
		//FontManager * FontsNSurfs;
		//IND_Entity2d * Entity;
		cluster * bullets;
		bool fire(Evertable * e);
};
#endif