#include "AudioManager.h"

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system);// create main system object 
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); // (number of channel,flags[DEFAULT],extra driver data)
}

void AudioManager::PlayBgm() // sound effect
{
	result = system->playSound(bgm, 0, true, &channel); // (file pointer ,channel group,paused or not?,channel that i want pass)
	// (file pointer ,channel group,paused or not?,channel that i want pass)
	channel->setVolume(1.8);
	channel->setPaused(false);
	//channel group : many channel to form a group 
}

void AudioManager::PlayMusic() // sound effect
{
	result = system->playSound(bgmmusic, 0, false, &channel);
	channel->setVolume(0.1);
	//channel->setPaused(false);
}

void AudioManager::Play1Jump() // bgm
{
	result = system->playSound(jump, 0, true, &channel);
	channel->setPan(-0.8);
	channel->setVolume(0.5);
	channel->setPaused(false);

}
void AudioManager::Play2Jump() // bgm
{
	result = system->playSound(jump, 0, true, &channel);
	channel->setPan(-0.3);
	channel->setVolume(0.5);
	channel->setPaused(false);

}

void AudioManager::Play3Jump() // bgm
{
	result = system->playSound(jump, 0, true, &channel);
	channel->setPan(0.3);
	channel->setVolume(0.5);
	channel->setPaused(false);

}

void AudioManager::Play4Jump() // bgm
{
	result = system->playSound(jump, 0, true, &channel);
	channel->setPan(0.8);
	channel->setVolume(0.5);
	channel->setPaused(false);

}

void AudioManager::Play1Footstep() // bgm
{
	result = system->playSound(footstep, 0, true, &channel);
	channel->setVolume(0.5);
	channel->setPan(-0.8);
	channel->setPaused(false);
}

void AudioManager::Play2Footstep() // bgm
{
	result = system->playSound(footstep, 0, true, &channel);
	channel->setVolume(0.5);
	channel->setPan(-0.3);
	channel->setPaused(false);
}

void AudioManager::Play3Footstep() // bgm
{
	result = system->playSound(footstep, 0, true, &channel);
	channel->setVolume(0.5);
	channel->setPan(0.4);
	channel->setPaused(false);
}

void AudioManager::Play4Footstep() // bgm
{
	result = system->playSound(footstep, 0, true, &channel);
	channel->setVolume(0.5);
	channel->setPan(0.8);
	channel->setPaused(false);
}
void AudioManager::LoadSounds()
{
	result = system->createStream("sound/bgmMusic.wav", FMOD_DEFAULT, 0, &bgmmusic); // Stream is for long wav file
	result = bgmmusic->setMode(FMOD_LOOP_NORMAL);

	result = system->createSound("sound/jump.wav", FMOD_DEFAULT, 0, &jump); // Sound is for sound effect (short wav file)
	result = jump->setMode(FMOD_LOOP_OFF);// loop or not (if yes,FMOD_LOOP_ON)

	result = system->createSound("sound/footstep.wav", FMOD_DEFAULT, 0, &footstep); // Sound is for sound effect (short wav file)
	result = jump->setMode(FMOD_LOOP_OFF);

	result = system->createStream("sound/forestBGM.wav", FMOD_DEFAULT, 0, &bgm); // Stream is for long wav file
	result = bgm->setMode(FMOD_LOOP_NORMAL);
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
