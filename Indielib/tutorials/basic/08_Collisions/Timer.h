/*****************************************************************************************
 * Desc: Class containing information on the timer
 *****************************************************************************************/

#ifndef _timer_h
#define _timer_h
#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Surface.h"
#include "FontManager.h"
class Timer{
	public:  
		static Timer *instance();
		bool setInitHP(int hp);
		bool hit(int hits);
		bool setInitTime(float time);
		bool decrementTime(float time);
    private:
		Timer();
		char tString[5];
		FontManager  * fonts;
		IND_Surface  * mSurfaceWhite;
		IND_Entity2d * health;
		IND_Entity2d * mtime;
		float time;
		int hp;
		static Timer *_pinstance;
};
#endif