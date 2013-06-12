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

    /*
        Create a System object and initialize.
    */

    result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, 0);
    //ERRCHECK(result);
	result = system->createSound("../../resources/Hokuhou/11 - The Seat of Power.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	result = system->createSound("../../resources/Hokuhou/03 - Pedestrians Crossing.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound2);
    //ERRCHECK(result);

    /*
        Play the sound.
    */
    result = system->playSound(sound, 0, false, &channel);
    //ERRCHECK(result);
}

bool SoundManager::changeBM(const char * file){
	result = system->playSound(sound2, 0, false, &channel2);
	channel->stop();
	return true;
}
    /*
        Shut down
    */

int SoundManager::shutdown(){
    result = sound->release();
    //ERRCHECK(result);
    result = system->close();
    //ERRCHECK(result);
    result = system->release();
    //ERRCHECK(result);
    return 0;
}