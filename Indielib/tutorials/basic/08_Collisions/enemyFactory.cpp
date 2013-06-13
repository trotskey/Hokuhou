
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
		if(orders.empty()){
			return false;
		}
		string s = orders.front();
		orders.pop();
		char item[30];
		sscanf(s.c_str(),"%s",item);
		string i(item);
		if(i.compare("wait") == 0){
			float num;
			sscanf(s.c_str(),"%*s %f",&num);
			time+=num;
		} else if(i.compare("untilclear")==0){
			float num;
			sscanf(s.c_str(),"%*s %f",&num);
			time+=num;
			hold = true;
		} else if(i.compare("tank")==0){
			int nX;
			int nY;
			float nvX;
			float nvY;
			sscanf(s.c_str(),"%*s %s %d %d %f %f",item,&nX,&nY,&nvX,&nvY);
			bool nEverted = false;
			string ni(item);
			if(ni.compare("true")==0){
				nEverted = true;
			}
			EnTank * PIV = createTank(nEverted);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY(nX,nY);
		} else if(i.compare("tank2")==0){
			int nX;
			int nY;
			float nvX;
			float nvY;
			sscanf(s.c_str(),"%*s %s %d %d %f %f",item,&nX,&nY,&nvX,&nvY);
			bool nEverted = false;
			string ni(item);
			if(ni.compare("true")==0){
				nEverted = true;
			}
			EnTank * PIV = createTank2(nEverted);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY(nX,nY);
		} else if(i.compare("tank3")==0){
			int nX;
			int nY;
			float nvX;
			float nvY;
			sscanf(s.c_str(),"%*s %s %d %d %f %f",item,&nX,&nY,&nvX,&nvY);
			bool nEverted = false;
			string ni(item);
			if(ni.compare("true")==0){
				nEverted = true;
			}
			EnTank * PIV = createTank3(nEverted);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY(nX,nY);
		} else if(i.compare("boss1")==0){
			int nX;
			int nY;
			float nvX;
			float nvY;
			sscanf(s.c_str(),"%*s %s %d %d %f %f",item,&nX,&nY,&nvX,&nvY);
			bool nEverted = false;
			string ni(item);
			if(ni.compare("true")==0){
				nEverted = true;
			}
			EnTank * PIV = createBoss1(nEverted);
			PIV->setSpeed(nvX,nvY);
			PIV->setXY(nX,nY);
		}else if(i.compare("setbanner")==0){
			mSurfaceBanner = IND_Surface::newSurface();
			//char picture[50];
			//sscanf(s.c_str(),"%*s %s %*d %*d %*d",picture);
			//string ni(picture);
			mI->_surfaceManager->add(mSurfaceBanner, "../../resources/Hokuhou/stage1.png", IND_ALPHA, IND_32, 0, 255, 0);
			mBanner->setSurface(mSurfaceBanner);					// Set the surface into the entity
			mBanner->setTint(0,0,0);
			mBanner->setHotSpot(0.5,0.5);
			mBanner->setPosition(250,200,3);
			mBanner->setTransparency(0);
		} else if(i.compare("showbanner")==0){
			mBanner->setTransparency(255);
		} else if(i.compare("hidebanner")==0){
			mBanner->setTransparency(0);
		} else if(i.compare("dialog")==0){
			int nX = 200;
			sscanf(s.c_str(),"%*s %d",&nX);
			mText->setTransparency(255);
			string mString = orders.front();
			orders.pop();
			mText->setText(mString.c_str());
			mText->setPosition(nX,500,22);
		} else if(i.compare("hidedialog")==0){
			mText->setTransparency(0);
		} else if(i.compare("storyhold")==0){
			float num;
			sscanf(s.c_str(),"%*s %f",&num);
			time+=num;
			storyhold = true;
		} else if(i.compare("bmchange")==0){
			mSm->changeBM("new song");
		} else if(i.compare("end")==0){
			return false;
		}
	}
	/*time += mDelta;
	if(time > 4 && (time - lastfire) > 10){
		EnTank * PIV = createTank(false);
		PIV->setSpeed(50.0f,25.0f);
		PIV->setXY(0,70);
		PIV = createTank(true);
		PIV->setSpeed(-50.0f,25.0f);
		PIV->setXY(500,70);
		lastfire = time;
	}*/
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
enemyFactory::enemyFactory(){
	bFactory = BulletFactory::instance();
	mI = CIndieLib::instance();
	mSm = SoundManager::instance();
	mBanner = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mBanner);					// Entity adding

	// Font
	mFont = IND_Font::newFont();
	mI->_fontManager->add(mFont, "../../resources/font_small.png", "../../resources/font_small.xml", IND_ALPHA, IND_32);
	mText = IND_Entity2d::newEntity2d();					
	mI->_entity2dManager->add(mText);				// Entity adding
	mText->setFont(mFont);
	mText->setPosition(200,500,22);
	mText->setTransparency(0);
	mText->setLineSpacing	(18);
	mText->setCharSpacing	(-7);
	mText->setScale(1,1);
	mText->setAlign(IND_LEFT);


	mTimer = Timer::instance();

	ifstream inf("../../resources/Hokuhou/EversionStage1.txt");
	while(inf){
		char str[101];
		streamsize y = 100;
		inf.getline(str, y);
		string s(str);
		orders.push(s);
	}
	inf.close();
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