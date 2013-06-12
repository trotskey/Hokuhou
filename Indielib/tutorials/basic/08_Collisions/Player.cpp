#include "player.h"

/*
==================
Init singleton
==================
*/
Player *Player::_pinstance = 0;// initialize pointer
Player *Player::instance() {
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new Player; // create sole instance
	}
	return _pinstance; // address of sole instance
}

Player::Player(){
	mI       = CIndieLib::instance();
	Efactory = enemyFactory::instance();
	factory  = BulletFactory::instance();

	// Loading Evert
	mSurfaceIdle = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceIdle, "../../resources/Hokuhou/Eversion/Evert.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert
	mSurfaceRight = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceRight, "../../resources/Hokuhou/Eversion/Right.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert
	mSurfaceLeft = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceLeft, "../../resources/Hokuhou/Eversion/Left.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert
	mSurfaceEvert = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceEvert, "../../resources/Hokuhou/Eversion/Revert.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert
	mSurfaceERight = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceERight, "../../resources/Hokuhou/Eversion/ERight.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert
	mSurfaceELeft = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceELeft, "../../resources/Hokuhou/Eversion/ELeft.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Load hitbox
	mSurfaceHitbox = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceHitbox, "../../resources/Hokuhou/hitbox.png", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Evert animation
	mEversionAnimation = IND_Animation::newAnimation();;
	mI->_animationManager->addToSurface(mEversionAnimation, "../../resources/Hokuhou/Evert.xml", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading Revert animation
	mReversionAnimation = IND_Animation::newAnimation();;
	mI->_animationManager->addToSurface(mReversionAnimation, "../../resources/Hokuhou/Revert.xml", IND_ALPHA, IND_32, 0, 255, 0);

	// Loading White pixel
	mSurfaceTimer = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceTimer, "../../resources/Hokuhou/white.png", IND_ALPHA, IND_32);
	mTimer = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mTimer);					// Entity adding
	mTimer->setSurface(mSurfaceTimer);					// Set the surface into the entity
	//mClear->setHotSpot(0.5f,0.5f);
	mTimer->setPosition(30,580,23);
	mTimer->setTint(0,0,255);
	mTimer->setTransparency(255);

	Entity = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(Entity);					// Entity adding
	Entity->setSurface(mSurfaceIdle);					// Set the surface into the entity

	mHitbox = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mHitbox);
	mHitbox->setSurface(mSurfaceHitbox);

	eMaxX = 490;
	eMaxY = 555;
	eMinX = 25;
	eMinY = 35;
	Changing = 0;
	eDir = 0;
	mSpeedmove = 300;
	mAniTime   = 0.0f;
	mCooldown  = 0.0f;
	firingtime = 0.0f;

	eX = 250;
	eY = 450;

	Entity->setHotSpot(0.5f, 0.58f);
	Entity->setPosition(eX, eY, 1);
	mHitbox->setHotSpot(0.5f, 0.58f);
	mHitbox->setPosition(eX, eY, 2);

	Everted = false;
}
IND_Entity2d * Player::getEntity(){
	return Entity;
}

bool Player::move(float mDelta){
	if(mAniTime > 0){
		mAniTime -= mDelta * 1000.0f;
		if(mAniTime > 0){
			Changing = 1;
		} else {
			Changing = 0;
		}
	}
	if(mCooldown > 0){
		mCooldown -= mDelta;
		mTimer->setScale(60.0f*mCooldown/10.0f,5);
	}

	if (mI->_input->isKeyPressed(IND_KEYRIGHT)){
		if(eDir != 1){
			if(!Changing && Everted){
				Entity->setSurface(mSurfaceERight);
			} else if(!Changing) {
				Entity->setSurface(mSurfaceRight);
			}
			Entity->setHotSpot(0.5f, 0.58f);
			Entity->setBoundingCircle("Evert", 62, 95, 5);
			eDir = 1;
		}
		if(mI->_input->isKeyPressed(IND_KEYUP) || mI->_input->isKeyPressed(IND_KEYDOWN)){
			if(eX + mSpeedmove*mDelta*FORTYFIVE < eMaxX){
				eX += mSpeedmove*mDelta*FORTYFIVE;
			}
		} else {
			if(eX + mSpeedmove*mDelta < eMaxX){
				eX += mSpeedmove*mDelta;
			}
		}
	}
	if (mI->_input->isKeyPressed(IND_KEYLEFT)){
		if(eDir != -1){
			if(!Changing && Everted){
				Entity->setSurface(mSurfaceELeft);
			} else if(!Changing){
				Entity->setSurface(mSurfaceLeft);
			}
			Entity->setHotSpot(0.5f, 0.58f);
			Entity->setBoundingCircle("Evert", 62, 95, 5);
			eDir = -1;
		}
		if(mI->_input->isKeyPressed(IND_KEYUP) || mI->_input->isKeyPressed(IND_KEYDOWN)){
			if(eX-mSpeedmove*mDelta*FORTYFIVE > eMinX){
				eX -= mSpeedmove*mDelta*FORTYFIVE;
			}
		} else {
			if(eX - mSpeedmove*mDelta > eMinX){
				eX -= mSpeedmove*mDelta;
			}
		}
	}
	if(eDir && !mI->_input->isKeyPressed(IND_KEYLEFT) && !mI->_input->isKeyPressed(IND_KEYRIGHT)){
		if(!Changing && Everted){
			Entity->setSurface(mSurfaceEvert);
		} else if(!Changing){
			Entity->setSurface(mSurfaceIdle);
		}
		Entity->setHotSpot(0.5f, 0.58f);
		Entity->setBoundingCircle("Evert", 62, 95, 5);
		eDir = 0;
	}
	if (mI->_input->isKeyPressed(IND_KEYUP)){
		if(mI->_input->isKeyPressed(IND_KEYLEFT) || mI->_input->isKeyPressed(IND_KEYRIGHT)){
			if(eY - mSpeedmove*mDelta*FORTYFIVE > eMinY){
				eY -= mSpeedmove*mDelta*FORTYFIVE;
			}
		} else {
			if(eY - mSpeedmove*mDelta > eMinY){
				eY -= mSpeedmove*mDelta;
			}
		}
	}
	if (mI->_input->isKeyPressed(IND_KEYDOWN)){
		if(mI->_input->isKeyPressed(IND_KEYLEFT) || mI->_input->isKeyPressed(IND_KEYRIGHT)){
			if(eY + mSpeedmove*mDelta*FORTYFIVE < eMaxY){
				eY += mSpeedmove*mDelta*FORTYFIVE;
			}
		} else {
			if(eY + mSpeedmove*mDelta < eMaxY){
				eY += mSpeedmove*mDelta;
			}
		}
	}
	if (mCooldown <= 0.0f && !Changing && mI->_input->isKeyPressed(IND_X)){
		if(Everted){
			Entity->setAnimation(mReversionAnimation);
			Everted = 0;
		} else {
			Entity->setAnimation(mEversionAnimation);
			Everted = 1;
		}
		factory->Evert();
		Efactory->Evert();
		mAniTime = 1600.0f;
		mCooldown = 10;
		mTimer->setScale(60.0f*mCooldown/10.0f,5);
		Entity->setSequence(0);
		Entity->setHotSpot(0.5f, 0.58f);
		Entity->setNumReplays(0);
	}
	if (mI->_input->isKeyPressed(IND_Z)){
		firingtime += mDelta;
		bool bEverted = false;
		if (mI->_input->isKeyPressed(IND_LSHIFT)){
			//bEverted = true;
		}
		
		if(firingtime > 0.05f){
			for(int x=0; x<2; x++){
				Bullet * Bill = factory->createBullet("pbullet",bEverted);
				Bill->setXY(eX-13+20*x,eY-15);
				Bill->setSpeed(0.0f,-800.0f);
				if(x){
					Bill->getEntity()->setMirrorX(true);
				}
			}
			firingtime = 0.0f;
		}
	}
	if (mI->_input->isKeyPressed(IND_LSHIFT)){
		mSpeedmove = 175;
		mHitbox->setTransparency(255);
	} else {
		mSpeedmove = 300;
		mHitbox->setTransparency(0);
	}
	Entity->setPosition(eX, eY, 1);
	mHitbox->setPosition(eX, eY, 2);
	return true;
}

bool Player::Evert(){
	return Everted;
}
bool Player::isEverted(){
	return false; //player is always in the world that they are
	              //regardless of whether it was where they started
	//return Everted;
}
//bool Player::setXY(float x, float y);