/*****************************************************************************************
 * Desc: Class containing information on a particular bullet
 *****************************************************************************************/

#ifndef _EnTank_h
#define _EnTank_h

#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Surface.h"
#include "BulletFactory.h"
#include "Evertable.h"
#include "Score.h"
#include "FontManager.h"
#include "tinyxml.h"
#define PI 3.14159

class EnTank: 
	public Evertable {
	public:  
		EnTank(bool evert);
		EnTank(IND_Entity2d * e, bool evert);
		IND_Entity2d * getEntity();
		virtual bool setXY(float x, float y);
		virtual bool setSpeed(float x, float y);
		bool inRange();
		bool Evert();
		bool isEverted();
		bool setElement(TiXmlElement * start);
		virtual bool hit(int hits);
		virtual bool move(float mDelta, Evertable * e);
    protected:
		int hp;
		virtual bool fire(Evertable * e);
		bool stop;
		IND_Surface * Surface;
		BulletFactory * factory;
		FontManager * FontsNSurfs;
		TiXmlElement * xElement;
		Score * mScore;
		float time;
		float lastfire;
		float eX;
		float eY;
		float vX;
		float vY;
};
#endif