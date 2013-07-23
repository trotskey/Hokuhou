
#include "enemyFactory.h"
#include <fstream>
#include <sstream>
#include <string>


/*
==================
Init singleton
==================
*/
enemyFactory *enemyFactory::_pinstance = 0;// initialize pointer
enemyFactory *enemyFactory::instance() {
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new enemyFactory; // create sole instance
	}
	return _pinstance; // address of sole instance
}

bool enemyFactory::Move(float mDelta,Evertable * e){
	queue<EnTank*> temp;
	Hit();
	while(!current.empty()){
		EnTank * Winston = current.front();
		current.pop();
		Winston->move(mDelta,e);
		if(Winston->inRange()){
			temp.push(Winston);
		} else {
			disappear(Winston);
		}
	}
	current = temp;
	return true;
}

//for the hit method... later
bool enemyFactory::Hit(){
	EnTank * Winston;
	queue<EnTank*> temp;
	while(!current.empty()){
		Winston = current.front();
		current.pop();
		//IND_Entity2d * ent = Winston->getEntity();
		int hits = bFactory->Hit("pbullet",Winston,"Enemy");
		if(Winston->hit(hits)){
			disappear(Winston);
		} else {
			temp.push(Winston);
		}
	}
	current = temp;
	//int ret = 0;
	return true;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool enemyFactory::Build(float mDelta){
	time -= mDelta;
	if(storyhold){
		if(time > 0){
			if(mI->_input->onKeyPress(IND_Z)){
				time = 0.2;
			}
			return true;
		} else {
			storyhold = false;
		}
	}
	if(hold){
		if(time > 0){
			if(current.empty()){
				time = 0;
				hold = false;
			} else {
				hold = mTimer->decrementTime(mDelta);
				return true;
			}
		} else {
			hold = false;
		}
	} else {
		mTimer->decrementTime(mDelta);
	}
	if(time <= 0){
		{
			TiXmlElement * tElement = xElement->NextSiblingElement();
			if(tElement == NULL){
				return false;
			}
			xElement = tElement;
		}
		string elemName = xElement->Value();
		if(elemName.compare("tank")==0){
			int nX = atoi(xElement->Attribute("posX"));
			int nY = atoi(xElement->Attribute("posY"));;
			float nvX = atof(xElement->Attribute("vX"));
			float nvY = atof(xElement->Attribute("vY"));
			EnTank * PIV = createTank(false);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY((float)nX,(float)nY);
			PIV->setElement(xElement->FirstChildElement());
		//does not work properly yet
		} if(elemName.compare("tank2")==0){
			int nX = atoi(xElement->Attribute("posX"));
			int nY = atoi(xElement->Attribute("posY"));;
			float nvX = atof(xElement->Attribute("vX"));
			float nvY = atof(xElement->Attribute("vY"));
			EnTank * PIV = createTank2(false);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY((float)nX,(float)nY);
			PIV->setElement(xElement->FirstChildElement());
		//probably does not work properly yet
		} else if(elemName.compare("tank3")==0){
			int nX = atoi(xElement->Attribute("posX"));
			int nY = atoi(xElement->Attribute("posY"));;
			float nvX = atof(xElement->Attribute("vX"));
			float nvY = atof(xElement->Attribute("vY"));
			EnTank * PIV = createTank3(false);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY((float)nX,(float)nY);
			PIV->setElement(xElement->FirstChildElement());
		} else if(elemName.compare("boss1")==0){
			int nX = atoi(xElement->Attribute("posX"));
			int nY = atoi(xElement->Attribute("posY"));;
			float nvX = atof(xElement->Attribute("vX"));
			float nvY = atof(xElement->Attribute("vY"));
			EnTank * PIV = createBoss1(false);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY((float)nX,(float)nY);
		} else if(elemName.compare("wait") == 0){
			float num = atoi(xElement->Attribute("time"));
			time+=num;
		} else if(elemName.compare("untilclear")==0){
			float num = atoi(xElement->Attribute("time"));
			time+=num;
			hold = true;
		} else if(elemName.compare("line")==0){
			TextBG->setTransparency(175);
			mText->setTransparency(255);

			mEnemy->setTransparency(255);
			mPlayer->setTransparency(255);

			//weee
			if(dPlayer->toggleBullets()){
				dPlayer->toggleBullets();
			}

			{
				const char * attr = xElement->Attribute("wait");
				int w = atoi(attr);
				time = w;
				storyhold = true;
			}
			{
				string attr = xElement->Attribute("text");
				vector<string> lines = split(attr.c_str(),'_');
				attr.clear();
				for (std::vector<string>::iterator it = lines.begin() ; it != lines.end(); ++it){
					attr.append(*it);
					attr.append("\n");
				}
				mText->setText(attr.c_str());
			}
			{
				string attr = xElement->Attribute("side");
				if(attr[0]=='l'){
					mPlayer->setPosition(5,600,15);
					mPlayer->setTint(255,255,255);
					mEnemy->setPosition(595,600,12);
					mEnemy->setTint(210,210,210);
				} else {
					mEnemy->setPosition(495,600,15);
					mEnemy->setTint(255,255,255);
					mPlayer->setPosition(-95,600,12);
					mPlayer->setTint(210,210,210);
				}
			}
			{
				string attr = xElement->Attribute("x");
				int nX = atoi(attr.c_str());
				mText->setPosition(nX,500,22);
			}
		} else if(elemName.compare("banner")==0) {
			mSurfaceBanner = IND_Surface::newSurface();
			string attr = xElement->Attribute("file");
			int r = atoi(xElement->Attribute("r"));
			int g = atoi(xElement->Attribute("g"));
			int b = atoi(xElement->Attribute("b"));
			mI->_surfaceManager->add(mSurfaceBanner, attr.c_str(), IND_ALPHA, IND_32, r, g, b);
			mBanner->setSurface(mSurfaceBanner);					// Set the surface into the entity
			mBanner->setTint(0,0,0);
			mBanner->setHotSpot(0.5,0.5);
			mBanner->setPosition(250,200,3);
			mBanner->setTransparency(0);
		} else if(elemName.compare("hidedialog")==0){
			mText->setTransparency(0);
			TextBG->setTransparency(0);
			mPlayer->setTransparency(0);
			mEnemy->setTransparency(0);
			//teehee
			if(!dPlayer->toggleBullets()){
				dPlayer->toggleBullets();
			}
		} else if(elemName.compare("showbanner")==0){
			mBanner->setTransparency(255);
		} else if(elemName.compare("hidebanner")==0){
			mBanner->setTransparency(0);
		} else if(elemName.compare("presetBM")==0){
			string attr = xElement->Attribute("file");
			int bmnum = atoi(xElement->Attribute("num"));
			mSm->presetBM(bmnum,attr.c_str());
		} else if(elemName.compare("changeBM")==0){
			int bmnum = atoi(xElement->Attribute("num"));
			mSm->changeBM(bmnum);
		}
	}
	return true;
}
bool enemyFactory::Evert(){
	queue<EnTank*> temp;
	while(!current.empty()){
		EnTank * Winston = current.front();
		current.pop();
		Winston->Evert();
		temp.push(Winston);
	}
	current = temp;
	return true;
}

EnTank * enemyFactory::createTank(bool Evert){
	EnTank * Winston;
	if(waiting.empty()){
		Winston = new EnTank(Evert);
	} else {
		Winston = new EnTank(waiting.front()->getEntity(),Evert);
		waiting.pop();
	}
	current.push(Winston);
	return Winston;
}

EnTank * enemyFactory::createTank2(bool Evert){
	EnTank2 * Winston;
	if(waiting.empty()){
		Winston = new EnTank2(Evert);
	} else {
		Winston = new EnTank2(waiting.front()->getEntity(),Evert);
		waiting.pop();
	}
	current.push(Winston);
	return Winston;
}

EnTank * enemyFactory::createTank3(bool Evert){
	EnTank3 * Winston;
	if(waiting.empty()){
		Winston = new EnTank3(Evert);
	} else {
		Winston = new EnTank3(waiting.front()->getEntity(),Evert);
		waiting.pop();
	}
	current.push(Winston);
	return Winston;
}

EnTank * enemyFactory::createBoss1(bool Evert){
	Stage1Boss * Winston;
	if(waiting.empty()){
		Winston = new Stage1Boss(Evert);
	} else {
		Winston = new Stage1Boss(waiting.front()->getEntity(),Evert);
		waiting.pop();
	}
	current.push(Winston);
	return Winston;
}
/*
Crow * enemyFactory::createCrow(bool Evert){
	Crow * Winston;
	if(waiting.empty()){
		Winston = new Crow(Evert);
	} else {
		Winston = new Crow(waiting.front()->getEntity(),Evert);
		waiting.pop();
	}
	current.push(Winston);
	return Winston;
}
*/

bool enemyFactory::NextStage(){
	mTimer = Timer::instance();
	/*
	ifstream inf("../../resources/Hokuhou/EversionStage1.txt");
	while(inf){
		char str[101];
		streamsize y = 100;
		inf.getline(str, y);
		string s(str);
		orders.push(s);
	}
	inf.close();
	*/
	
	lastfire = -6;
	time = 0;
	hold = false;
	storyhold = false;
	return false;
}

enemyFactory::enemyFactory(){
	bFactory = BulletFactory::instance();
	mI = CIndieLib::instance();
	mSm = SoundManager::instance();
	mBanner = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mBanner);					// Entity adding
	FontsNSurfs = FontManager::instance();

	// Font
	TextBG = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(TextBG);	
	mSurfaceWhite = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceWhite, "../../resources/Hokuhou/white.png", IND_ALPHA, IND_32);
	TextBG->setSurface(mSurfaceWhite);					// Set the surface into the entity
	TextBG->setTint(0,0,0);
	TextBG->setPosition(20,490,21);
	//TextBG->setTransparency(50);
	TextBG->setScale(470,80);

	mText = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mText);				// Entity adding
	mText = FontsNSurfs->createText("small");
	mText->setPosition(200,500,22);
	mText->setAlign(IND_LEFT);


	mTimer = Timer::instance();

	mXML = new TiXmlDocument( "../../resources/Hokuhou/stage1.xml" );
	mXML->LoadFile();
	xElement = mXML->FirstChildElement()->FirstChildElement();

	//this is kinda haphazard right now
	//replace with something sturdier in the future
	string PimgDir = xElement->Attribute("file");

	//Player
	mPlayer = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer);
	mSurfacePlayer = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfacePlayer, PimgDir.c_str(), IND_ALPHA, IND_32, 0, 255, 0);
	mPlayer->setSurface(mSurfacePlayer);
	mPlayer->setHotSpot(0.0f,1.0f);
	mPlayer->setPosition(5,600,15);

	dPlayer = Player::instance();

	xElement = xElement->NextSiblingElement();

	string EimgDir = xElement->Attribute("file");

	//Enemy
	mEnemy = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mEnemy);
	mSurfaceEnemy = IND_Surface::newSurface();
	mI->_surfaceManager->add(mSurfaceEnemy, EimgDir.c_str(), IND_ALPHA, IND_32, 0, 255, 0);
	mEnemy->setSurface(mSurfaceEnemy);
	mEnemy->setHotSpot(1.0f,1.0f);
	//mEnemy->setPosition(495,600,15);
	mEnemy->setPosition(595,600,12);
	mEnemy->setTint(210,210,210);
	
	//string thisstring = xElement->Value();

	/*
	ifstream inf("../../resources/Hokuhou/EversionStage1.txt");
	while(inf){
		char str[101];
		streamsize y = 100;
		inf.getline(str, y);
		string s(str);
		orders.push(s);
	}
	inf.close();
	*/

	lastfire = -6;
	time = 0;
	hold = false;
	storyhold = false;
}

bool enemyFactory::disappear(EnTank * Winston){
	Winston->setXY(-500.0f,-500.0f);
	waiting.push(Winston);
	return true;
}