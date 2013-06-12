#include "cluster.h"
#include <fstream>
#include <sstream>
#include <string>

cluster::cluster(bool evert, const char * type){
	factory = BulletFactory::instance();
	Everted = evert;
	angle = 0;
	ifstream inf;
	if(type == "scissor"){
		inf = ifstream("../../resources/Hokuhou/scissor.txt");
	} else if(type == "string"){
		inf = ifstream("../../resources/Hokuhou/string.txt");
	} else {
		return;
	}
	while(inf){
		char str[101];
		streamsize y = 100;
		inf.getline(str, y);
		string s(str);
		orders.push(s);
	}
	inf.close();
	while(!orders.empty()){
		string s = orders.front();
		orders.pop();
		char item[30];
		sscanf(s.c_str(),"%s",item);
		string i(item);
		if(i.compare("center") == 0){
			float num;
			float num2;
			sscanf(s.c_str(),"%*s %f,%f",&num,&num2);
			eX = num;
			eY = num2;
		} else {
			float num;
			float num2;
			sscanf(s.c_str(),"%f,%f",&num,&num2);
			Bullet * Bob = factory->createBullet("sbullet",evert);
			Bob->setXY(eX,eY);
			Bob->getEntity()->setHotSpot((eX-num)/18.0f,(eY-num2)/18.0f);
			bullets.push(Bob);
		}
	}
}
bool cluster::setXY(float x, float y){
	//float dx = x-eX;
	//float dy = y-eY;
	eX = x;
	eY = y;
	queue<Bullet *> temp;
	while(!bullets.empty()){
		Bullet * Bob = bullets.front();
		bullets.pop();
		//float nX = Bob->getEntity()->getPosX() + dx;
		//float nY = Bob->getEntity()->getPosX() + dy;
		//Bob->setXY(nX,nY);
		Bob->setXY(eX,eY);
		if(Bob->inRange()){
			temp.push(Bob);
		}
	}
	bullets = temp;
	return true;
}

bool cluster::addBullet(Bullet * b){
	bullets.push(b);
	return true;
}

queue<Bullet *> cluster::getBullets(){
	return bullets;
}

bool cluster::rotate(float z){
	queue<Bullet *> temp;
	angle += z;
	while(!bullets.empty()){
		Bullet * Bob = bullets.front();
		bullets.pop();
		Bob->getEntity()->setAngleXYZ(0,0,angle);
		if(Bob->inRange()){
			temp.push(Bob);
		}
	}
	bullets = temp;
	return true;
}

bool cluster::setMirrorY(bool b){
	queue<Bullet *> temp;
	while(!bullets.empty()){
		Bullet * Bob = bullets.front();
		bullets.pop();
		float hX = Bob->getEntity()->getHotSpotX();
		float hY = Bob->getEntity()->getHotSpotY();
		Bob->getEntity()->setHotSpot(hX,-hY);
		if(Bob->inRange()){
			temp.push(Bob);
		}
	}
	bullets = temp;
	return true;
}

bool cluster::setSpeed(float x, float y){
	queue<Bullet *> temp;
	while(!bullets.empty()){
		Bullet * Bob = bullets.front();
		bullets.pop();
		Bob->setSpeed(x,y);
		if(Bob->inRange()){
			temp.push(Bob);
		}
	}
	bullets = temp;
	return true;
}
bool cluster::inRange(){
	return true;
}
bool cluster::Evert(){
	return true;
}
bool cluster::isEverted(){
	return true;
}
bool cluster::hit(int hits){
	return true;
}
/*
 *This could lead to an interesting problem if the new entity gets a location
 *Though, the encasing with a bullet should stop this from happening
 */
bool cluster::move(float mDelta, Evertable * e){
	queue<Bullet *> temp;
	while(!bullets.empty()){
		Bullet * Bob = bullets.front();
		bullets.pop();
		if(Bob->inRange()){
			temp.push(Bob);
		}
	}
	bullets = temp;
	return true;
}
bool cluster::fire(Evertable * e){
	return false;
}