/*****************************************************************************************
 * Desc: Class containing information on a particular bullet
 *****************************************************************************************/

#ifndef _cluster_h
#define _cluster_h

#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Surface.h"
#include "BulletFactory.h"
#include "Evertable.h"
#define PI 3.14159

class cluster: 
	public Evertable {
	public:  
		cluster(bool evert,const char * type);
		virtual bool setXY(float x, float y);
		virtual bool rotate(float z);
		virtual bool setMirrorY(bool b);
		virtual bool setSpeed(float x, float y);
		bool addBullet(Bullet * b);
		queue<Bullet *> getBullets();
		bool inRange();
		bool Evert();
		bool isEverted();
		virtual bool hit(int hits);
		virtual bool move(float mDelta, Evertable * e);
    protected:
		virtual bool fire(Evertable * e);
		BulletFactory * factory;
		queue<string> orders;
		queue<Bullet*> bullets;
		float angle;
		float time;
		float lastfire;
		float eX;
		float eY;
		float vX;
		float vY;
};
#endif