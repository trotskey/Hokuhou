/*****************************************************************************************
 * Desc: Class containing information on the enemycreator
 *****************************************************************************************/

#ifndef _enemyfactory_h
#define _enemyfactory_h

#include "enemyTank.h"
#include "enTank2.h"
#include "EnTank3.h"
#include "Stage1Boss.h"
#include "crow.h"
#include "IND_Font.h"
#include "Timer.h"
#include <queue>
#include "SoundManager.h"

class enemyFactory {
	public: 
		static enemyFactory *instance();
		bool Move(float mDelta, Evertable * e);
		bool Build(float mDelta);
		bool Evert();
		bool Hit();
		//int Hit(const char * type, IND_Entity2d * ent, const char * str);
		EnTank * createTank(bool Evert);
		EnTank * createTank2(bool Evert);
		EnTank * createTank3(bool Evert);
		EnTank * createBoss1(bool Evert);
		//Crow   * createCrow(bool Evert);
		//Bullet * createBullet(const char * type, bool Evert);
    private:
		enemyFactory();
		bool disappear(EnTank * Winston);
		bool hold;
		bool storyhold;
		queue<EnTank*> current;
		queue<EnTank*> waiting;
		queue<string> orders;
		double time;
		double lastfire;
		CIndieLib *mI;
		SoundManager * mSm;
		Timer * mTimer;
		BulletFactory * bFactory;
		IND_Entity2d *mBanner;
		IND_Entity2d *mTextbox;
		IND_Entity2d *mText;
		IND_Font * mFont;
		IND_Surface *mSurfaceBanner;
		static enemyFactory *_pinstance;
};
#endif