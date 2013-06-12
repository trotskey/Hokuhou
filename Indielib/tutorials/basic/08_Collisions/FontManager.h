/*****************************************************************************************
 * Desc: Class containing surfaces and fonts
 *****************************************************************************************/

#ifndef _FontManager_h
#define _FontManager_h
#include "CIndieLib_vc2008.h"
#include "IND_Entity2d.h"
#include "IND_Font.h"
#include "IND_Surface.h"

class FontManager{
	public:  
		static FontManager * instance();
		IND_Entity2d * createText(const char * type);
		IND_Surface  * getSurface(const char * type);
    private:
		FontManager();
		CIndieLib *mI;
		IND_Font * mFontSmall;
		IND_Surface  * crow;
		IND_Surface  * tank;
		static FontManager *_pinstance;
};
#endif