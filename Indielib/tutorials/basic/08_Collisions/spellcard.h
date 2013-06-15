#ifndef _spellcard_h
#define _spellcard_h

#include "Timer.h"
#include <math.h>
#include "cluster.h"
#include "Evertable.h"

class spellcard{
	public:
		spellcard(float * t, Evertable * e);
		virtual bool init();
		virtual bool move(float mDelta, Evertable * e);
		virtual bool cleanup();

	protected:
		float * time;
		float getTime();
		BulletFactory * factory;
		float lastfire;
		Evertable * Evert;
		Timer * mTimer;
};
#endif