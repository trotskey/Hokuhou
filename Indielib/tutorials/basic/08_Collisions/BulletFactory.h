/*****************************************************************************************
 * Desc: Class containing information on the bulletcreator
 *****************************************************************************************/

#ifndef _bulletfactory_h
#define _bulletfactory_h

#include "Bullet.h"
#include "Evertable.h"
#include "Score.h"
#include <queue>

class BulletFactory {
	public: 
		static BulletFactory *instance();
		bool Move(float mDelta);
		bool Build(float mDelta);
		bool Evert();
		bool ClearScreen();
		int Hit(const char * type, Evertable * ever, const char * str);
		bool Suck(float mDelta, Evertable * ever, const char * str);
		Bullet * createBullet(bool Evert);
		Bullet * createBullet(const char * type, bool Evert);
    private:
		BulletFactory();
		bool disappear(Bullet * Bob);
		queue<Bullet*> current;
		queue<Bullet*> waiting;
		double time;
		Score * mScore; 
		IND_Surface *mSurfaceBullet;
		IND_Surface *mSurfacePBullet;
		IND_Surface *mSurfaceMBullet;
		IND_Surface *mSurfaceMedBullet;
		IND_Surface *mSurfaceSBullet;
		IND_Surface *mSurfaceSmallBullet;
		IND_Surface *mSurfaceBonus;
		CIndieLib *mI;
		static BulletFactory *_pinstance;
};
#endif