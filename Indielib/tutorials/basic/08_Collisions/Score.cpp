#include "Score.h"
#include <stdio.h>
/*
==================
Init singleton
==================
*/
Score *Score::_pinstance = 0;// initialize pointer
Score *Score::instance() {
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new Score; // create sole instance
	}
	return _pinstance; // address of sole instance
}

Score::Score(){
	score = 0;
	lives = 0;
	sprintf(lString,"hits taken: %d",lives);
	sprintf(sString,"score: %010.0f",score);
}

char * Score::getscore(){
	return sString;
}
char * Score::getlives(){
	return lString;
}

bool Score::hit(){
	lives++;
	sprintf(lString,"hits taken: %d",lives);
	return true;
}
bool Score::addtoScore(int add){
	score += add;
	sprintf(sString,"score: %010.0f",score);
	return true;
}