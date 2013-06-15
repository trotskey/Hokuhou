#ifndef _spell104_h
#define _spell104_h

#include "spellcard.h"

class spell104:
	public spellcard{
	public:
		spell104(float * t, Evertable * e);
		bool init();
		bool move(float mDelta, Evertable * e);
		bool cleanup();
	private:
		cluster * lepers;
};

#endif