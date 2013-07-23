#include "Game.h"

Game::Game(){
	mI = CIndieLib::instance();
	// Loading Background
	mSurfaceBack = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceBack, "../../resources/twist.jpg", IND_OPAQUE, IND_32);

	// Loading White pixel
	mSurfaceWhite = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceWhite, "../../resources/Hokuhou/white.png", IND_ALPHA, IND_32);
	
	// Loading HUD
	mSurfaceHUD = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceHUD, "../../resources/Hokuhou/HUD.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Stage Clear
	mSurfaceClear = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceClear, "../../resources/Hokuhou/Clear.png", IND_ALPHA, IND_32, 0, 0, 0);

	// ----- Font loading -----
	fonts = FontManager::instance();

	// ----- Set the surfaces into 2d entities -----

	// Creating 2d entity for the background
	mBack = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity

	// Creating 2d entity for the HUD
	mHUD = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mHUD);					// Entity adding
	mHUD->setSurface(mSurfaceHUD);					// Set the surface into the entity
	mHUD->setHotSpot(0.5f,0.5f);
	mHUD->setScale(1.01f,1.01f);
	mHUD->setPosition(400,300,16);

	// Creating 2d entity for the Clear Message
	mClear = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mClear);					// Entity adding
	mClear->setSurface(mSurfaceClear);					// Set the surface into the entity
	mClear->setHotSpot(0.5f,0.5f);
	mClear->setPosition(250,100,23);
	mClear->setTransparency(0);


	// The paused backdrop
	mPause = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mPause);					// Entity adding
	mPause->setSurface(mSurfaceWhite);					// Set the surface into the entity
	mPause->setScale(802.0f,602.0f);
	mPause->setHotSpot(0.5f,0.5f);
	mPause->setPosition(0,0,20);
	mPause->setTint(0,0,0);
	mPause->setTransparency(0);

	// Pause Text
	mTextPause = fonts->createText("small");
	mTextPause->setPosition(250,300,22);
	mTextPause->setTransparency(0);
	mTextPause->setScale(1.7,2);
	mTextPause->setAlign(IND_CENTER);
	mTextPause->setText("Return to Game\nQuit");

	// small white text
	mTextSmallWhite = fonts->createText("small");
	mTextSmallWhite->setScale(1.7,2);
	mTextSmallWhite->setPosition(520, 200, 18);
	mTextSmallWhite->setAlign(IND_LEFT);

	// lives text
	mTextLives      = fonts->createText("small");
	mTextLives->setScale(1.7,2);
	mTextLives->setPosition(520, 240, 18);
	mTextLives->setAlign(IND_LEFT);

	Efactory = enemyFactory::instance();
	factory = BulletFactory::instance();

	// ----- Changing the attributes of the 2d entities -----

	// Background
	mBack->setHotSpot(0.5f, 0.5f);
	mBack->setPosition(400, 300, 0);
	mBack->setScale(1.7f, 1.7f);

	// ----- Main Loop -----

	//float mAngle = 0;
	mEvert = Player::instance();
	mTimer = Timer::instance();
	//int mSpeedRotation = 5;
	//float mDelta;
	//float time = 0.0f;
	mScore = Score::instance();
	paused = false;
}

bool Game::run(){
	// ----- Input ----

	mDelta = mI->_render->getFrameTime() / 1000.0f;
	//time += mDelta;
	if (mI->_input->isKeyPressed(IND_F)){
		mI->_render->toggleFullScreen();
	}
	
	//Deal with pausing
	if(paused) {
		if(mI->_input->onKeyPress(IND_ESCAPE)){
			return true;
		}
		if(mI->_input->onKeyPress(IND_Z)){
			paused = false;
			mPause->setTransparency(0);
			mTextPause->setTransparency(0);
			return false;
		}
	} else {
		if(mI->_input->onKeyPress(IND_ESCAPE)){
			paused = true;
			mPause->setTransparency(100);
			mTextPause->setTransparency(255);
			return false;
		}

		mEvert->move(mDelta);
		if(!Efactory->Build(mDelta)){
			paused = true;
			mPause->setTransparency(100);
			//mClear->setTint(255,255,255);
			mClear->setTransparency(255);
		}
		Efactory->Move(mDelta,mEvert);
		//factory->Build(mDelta);
		factory->Move(mDelta);
		factory->Suck(mDelta,mEvert,"Evert");
		//mAngle += mSpeedRotation * mDelta;
	}

	// ----- Updating entities attributes  -----

	//mBack->setAngleXYZ(0, 0, -mAngle);
	// ----- Check collisions -----
	if(factory->Hit("Bullet",mEvert,"Evert") > 0){
		//mTextSmallWhite->setText("You have been hit");
		mScore->hit();
		mTimer->failBonus();
	}
	mTextSmallWhite->setText(mScore->getscore());
	mTextLives->setText(mScore->getlives());
	return false;
}