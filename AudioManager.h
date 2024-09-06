#pragma once
#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system; // virtual soundcard
	FMOD::Sound* sound1, * sound2; // file
	FMOD::Channel* channel = 0; // channel that modify the file 
	FMOD_RESULT result; // error code
	void* extradriverdata = 0; // extra soundcard (ignore)

	void InitializeAudio();
	void PlaySound1();
	void PlaySoundTrack();
	void LoadSounds();
	void UpdateSound();

	AudioManager();
	~AudioManager();
};

