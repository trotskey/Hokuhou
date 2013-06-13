/*****************************************************************************************
 * Desc: Class containing information on the game
 *****************************************************************************************/

#ifndef _game_h
#define _game_h

#include "Player.h" 
#include "FontManager.h"
#include "IND_Font.h"
class Game{
	public:  
		Game();
		bool run();
    private:
		CIndieLib *mI;
		IND_Surface *mSurfaceBack;
		IND_Surface *mSurfaceWhite;
		IND_Surface *mSurfaceHUD;
		IND_Surface *mSurfaceClear;
		IND_Font *mFontSmall;
		IND_Entity2d *mBack;
		IND_Entity2d *mHUD;
		IND_Entity2d *mClear;
		IND_Entity2d *mPause;
		enemyFactory *Efactory;
		BulletFactory * factory;
		FontManager * fonts;
		Timer * mTimer;
		IND_Entity2d *mTextSmallWhite;
		IND_Entity2d *mTextLives;
		IND_Entity2d *mTextPause;
		Player * mEvert;
		float mDelta;
		Score * mScore;
		bool paused;
};
#endif