/*****************************************************************************************
 * Desc: Class managing the sound via FMOD
 *****************************************************************************************/

#ifndef _SoundManager_h
#define _SoundManager_h
#include "fmod.hpp"

//consider making this a singleton later
class SoundManager{
	public:  
		static SoundManager * instance();
		int shutdown();
		bool changeBM(int bmnum);
		bool presetBM(int bmnum, const char * file);
    protected:
		SoundManager();
		static SoundManager * _pinstance;
		FMOD::System     *system;
		FMOD::Sound      *sound[5];
		FMOD::Channel    *channel;
		FMOD::Channel    *channel2;
		FMOD_RESULT       result;
};
#endif