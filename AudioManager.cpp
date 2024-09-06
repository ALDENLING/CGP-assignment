#include "AudioManager.h"

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system);// create main system object 
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); // (number of channel,flags[DEFAULT],extra driver data)
}

void AudioManager::PlaySound1() // sound effect
{
	result = system->playSound(sound1, 0, false, &channel); // (file pointer ,channel group,paused or not?,channel that i want pass)
	//channel group : many channel to form a group 
}

void AudioManager::PlaySoundTrack() // bgm
{
	result = system->playSound(sound2, 0, true, &channel);
	channel->setPan(0);
	channel->setFrequency(240000);
	channel->setVolume(0.5);
	channel->setPaused(false);

}

void AudioManager::LoadSounds()
{
	result = system->createSound("gunshot.wav", FMOD_DEFAULT, 0, &sound1); // Sound is for sound effect (short wav file)
	result = sound1->setMode(FMOD_LOOP_OFF);// loop or not (if yes,FMOD_LOOP_ON)

	result = system->createStream("guitarBGM.wav", FMOD_DEFAULT, 0, &sound2); // Stream is for long wav file
	result = sound1->setMode(FMOD_LOOP_OFF);
}

void AudioManager::UpdateSound()
{
	result = system->update();
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
