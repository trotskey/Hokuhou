#include "SoundManager.h"

/*
==================
Init singleton
==================
*/
SoundManager * SoundManager::_pinstance = 0;
SoundManager * SoundManager::instance(){
	if (_pinstance == 0) { // is it the first call?
		_pinstance = new SoundManager; // create sole instance
	}
	return _pinstance; // address of sole instance
}

SoundManager::SoundManager(){
    channel = 0;
	channel2 = 0;

    /*
        Create a System object and initialize.
    */

    result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, 0);
    //ERRCHECK(result);
	//result = system->createSound("../../resources/Hokuhou/Forest.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound[0]);
	//result = system->createSound("../../resources/Hokuhou/Fenrir_Cometh.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound[1]);
    //ERRCHECK(result);

    /*
        Play the sound.
    */
    //result = system->playSound(sound[0], 0, false, &channel);
    //ERRCHECK(result);
}

bool SoundManager::presetBM(int bmnum, const char * file){
	if(bmnum < 0 || bmnum > 4){
		return false;
	}
	result = system->createSound(file, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound[bmnum]);
	return true;
}

bool SoundManager::changeBM(int bmnum){
	if(bmnum < 0 || bmnum > 4){
		return false;
	}
	if(channel){
	  result = system->playSound(sound[bmnum], 0, false, &channel2);
	  channel->stop();
	  channel = 0;
	} else {
	  result = system->playSound(sound[bmnum], 0, false, &channel);
	  if(channel2){
	    channel2->stop();
	    channel2 = 0;
	  }
	}
	return true;
}
    /*
        Shut down
    */

int SoundManager::shutdown(){
    result = sound[0]->release();
    //ERRCHECK(result);
    result = system->close();
    //ERRCHECK(result);
    result = system->release();
    //ERRCHECK(result);
    return 0;
}