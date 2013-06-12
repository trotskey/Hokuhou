/*****************************************************************************************
 * Desc: Class containing information on a crow spewing out a group of bullets
 *****************************************************************************************/

#ifndef _crow_h
#define _crow_h

#include "enemyTank.h"
#include <math.h>
#include "cluster.h"

class Crow: 
	public EnTank{
	public:  
		Crow(bool evert);
		Crow(IND_Entity2d * e, bool evert);
		cluster * getBullets();
		bool move(float mDelta,Evertable * e);
    protected:
		bool bSize;
		cluster * bullets;
		bool fire(Evertable * e);
};
#endif