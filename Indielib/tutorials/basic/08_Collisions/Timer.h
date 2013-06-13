/*****************************************************************************************
 * Desc: Class containing information on the timer
 *****************************************************************************************/

#ifndef _timer_h
#define _timer_h
#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Surface.h"
#include "FontManager.h"
#include "score.h"
class Timer{
	public:  
		static Timer *instance();
		bool setInitHP(int hp);
		bool hit(int hits);
		bool setInitTime(float time);
		bool decrementTime(float time);
		bool failBonus();
    private:
		Timer();
		char tString[5];
		char bString[50];
		float bonusTime;
		bool bonusFailed;
		FontManager  * fonts;
		Score * mScore;
		IND_Surface  * mSurfaceWhite;
		IND_Entity2d * health;
		IND_Entity2d * mtime;
		IND_Entity2d * mBonus;
		float time;
		int hp;
		static Timer *_pinstance;
};
#endif