#pragma once
#include "fmod.hpp"

class AudioManager
{
public:
	FMOD::System* system; // virtual soundcard
	FMOD::Sound* bgm, * jump,*footstep,* bgmmusic; // file
	FMOD::Channel* channel = 0; // channel that modify the file 
	FMOD_RESULT result; // error code
	void* extradriverdata = 0; // extra soundcard (ignore)

	void InitializeAudio();
	void PlayBgm();
	void PlayMusic();
	void Play1Jump();
	void Play2Jump();
	void Play3Jump();
	void Play4Jump();
	void Play1Footstep();
	void Play2Footstep();
	void Play3Footstep();
	void Play4Footstep();
	void LoadSounds();
	void UpdateSound();

	AudioManager();
	~AudioManager();
};

