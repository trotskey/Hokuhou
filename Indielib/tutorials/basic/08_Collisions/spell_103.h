#ifndef _spell103_h
#define _spell103_h

#include "spellcard.h"

class spell103:
	public spellcard{
	public:
		spell103(float * t, Evertable * e);
		bool init();
		bool move(float mDelta, Evertable * e);
		bool cleanup();
	private:
		
};

#endif