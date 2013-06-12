#include "FontManager.h"

/*
==================
Init singleton
==================
*/
FontManager * FontManager::_pinstance = 0;
FontManager * FontManager::instance(){
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new FontManager; // create sole instance
	}
	return _pinstance; // address of sole instance
}
IND_Entity2d * FontManager::createText(const char * type){
	if(type == "small"){
		IND_Entity2d* mText = IND_Entity2d::newEntity2d();					
		mI->_entity2dManager->add(mText);				// Entity adding
		mText->setFont(mFontSmall);
		mText->setLineSpacing	(18);
		mText->setCharSpacing	(-7);
		return mText;
	}
}
IND_Surface  * FontManager::getSurface(const char * type){
	if(type == "crow"){
		return crow;
	}
	if(type == "tank"){
		return tank;
	}
}

FontManager::FontManager(){
	mI = CIndieLib::instance();
	mFontSmall = IND_Font::newFont();
	mI->_fontManager->add(mFontSmall, "../../resources/font_small.png", "../../resources/font_small.xml", IND_ALPHA, IND_32);
	crow = IND_Surface::newSurface(); 
	mI->_surfaceManager->add(crow, "../../resources/Hokuhou/crow.png", IND_ALPHA, IND_32,0,255,0);
	tank = IND_Surface::newSurface(); 
	mI->_surfaceManager->add(tank, "../../resources/Hokuhou/EnemyTankDown.png", IND_ALPHA, IND_32);
}