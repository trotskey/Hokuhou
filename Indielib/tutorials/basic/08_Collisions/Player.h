/*****************************************************************************************
 * Desc: Class containing information on the player's avatar
 *****************************************************************************************/

#ifndef _player_h
#define _player_h

#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Animation.h"
#include "IND_Surface.h"
#include "enemyFactory.h"
#include "Evertable.h"

#define FORTYFIVE 0.707

class Player: 
	public Evertable{
	public:  
		static Player *instance();
		IND_Entity2d * getEntity();
		bool Evert();
		bool isEverted();
		//bool setXY(float x, float y);
		bool move(float mDelta);
    private:
		Player();
		CIndieLib *mI;
		int Changing;
		int eDir;
		IND_Entity2d *mTimer;
		IND_Entity2d *mHitbox;
		IND_Surface *mSurfaceIdle;
		IND_Surface *mSurfaceRight;
		IND_Surface *mSurfaceLeft;
		IND_Surface *mSurfaceEvert;
		IND_Surface *mSurfaceERight;
		IND_Surface *mSurfaceELeft;
		IND_Surface *mSurfaceTimer;
		IND_Surface *mSurfaceHitbox;
		IND_Animation *mReversionAnimation;
		IND_Animation *mEversionAnimation;
		enemyFactory  * Efactory;
		BulletFactory * factory;
		float eMaxX;
		float eMaxY;
		float eMinX;
		float eMinY;
		int mSpeedmove;
		float mAniTime;
		float mCooldown;
		float firingtime;
		//bool Everted;
		float eX;
		float eY;
		static Player *_pinstance;
};
#endif