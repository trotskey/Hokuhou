#ifndef _Stage1Boss_h
#define _Stage1Boss_h

#include "enemyTank.h"
#include <math.h>
#include "Timer.h"
#include "cluster.h"
#include "crow.h"
#include "claw.h"

#include "spellcard.h"
#include "spell_102.h"
#include "spell_103.h"
#include "spell_104.h"

class Stage1Boss: 
	public EnTank{
	public:  
		Stage1Boss(bool evert);
		Stage1Boss(IND_Entity2d * e, bool evert);
		IND_Entity2d * getEntity();
		bool setXY(float x, float y);
		bool setSpeed(float x, float y);
		bool inRange();
		bool Evert();
		bool isEverted();
		bool hit(int hits);
		bool move(float mDelta,Evertable * e);
    protected:
		bool nextCard();

		Timer * mTimer;
		int phase;
		float moveTime;

		float tX;
		float tY;

		queue <spellcard *> spells;
		spellcard * test;
};
#endif