#ifndef _spell102_h
#define _spell102_h

#include "spellcard.h"
#include "claw.h"

class spell102:
	public spellcard{
	public:
		spell102(float * t, Evertable * e);
		bool init();
		bool move(float mDelta, Evertable * e);
		bool cleanup();
	private:
		int clawcount;
		queue<Claw *> claws;
};

#endif