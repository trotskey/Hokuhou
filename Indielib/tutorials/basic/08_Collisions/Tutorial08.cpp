/*****************************************************************************************
 * Desc: Tutorials a) 08 Collisions
 *****************************************************************************************/

#include "CIndieLib_vc2008.h"

#include "IND_Surface.h"
#include "IND_Animation.h"
#include "IND_Font.h"
#include "IND_Entity2d.h"
#include "../../WorkingPath.h"

#include "bullet.h"
#include "BulletFactory.h"
#include "enemyTank.h"
#include "enemyFactory.h"
#include "Player.h"

#include "Evertable.h"
#include "Score.h"
#include "Game.h"
#include "SoundManager.h"
/*
==================
Main
==================
*/
int IndieLib()
{
    //Sets the working path as the 'exe' directory. All resource paths are relative to this directory
	if (!WorkingPathSetup::setWorkingPathFromExe(NULL)) {
		std::cout<<"\nUnable to Set the working path !";
	}
	
	SoundManager * mSm = SoundManager::instance();

	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;		

	Game * mGame = new Game();
	bool quit = false;

	while (!quit && !mI->_input->quit())
	{
		// ----- Input update ----
		Sleep(10); // Take it easy, computer
		mI->_input->update();
		quit = mGame->run();

		// ----- Render  -----
		mI->_render->beginScene();
		mI->_render->clearViewPort(0, 0, 0);
		mI->_entity2dManager->renderEntities2d();
		//mI->_entity2dManager->renderCollisionAreas(255, 0, 0, 255);
		mI->_render->endScene();	
	}

	// ----- Free -----
	mSm->shutdown();
	mI->end();

	return 0;
}
