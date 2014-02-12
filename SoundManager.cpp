#include "SoundManager.h"


SoundManager::SoundManager()
{
	rolloffMode = SOUND_ROLLOFF_LINEAR;

	//Create system
	FMOD::System_Create(&soundSystem);
}


SoundManager::~SoundManager()
{
}

//Add a sound to the Sound Manager
void SoundManager::AddSound(char *soundFilePath, glm::vec3 position, glm::vec3 velocity)
{
	Sound newSound;
	FMOD::Sound *newFMODSound;

	soundSystem->createSound(soundFilePath, FMOD_3D, 0, &newFMODSound);
	newFMODSound->set3DMinMaxDistance(0.1f, 100.0f);
	newFMODSound->setMode(FMOD_LOOP_OFF);

	newSound.position = { position.x, position.y, position.z };
	newSound.velocity = { velocity.x, velocity.y, velocity.z };
	newSound.sound = newFMODSound;

	this->soundList.push_back(newSound);
}

//Release all sounds
void SoundManager::ReleaseAllSounds(void)
{
	for (unsigned int i = 0; i < soundList.size() ; ++i)
	{
		soundList[i].sound->release();
		delete &soundList[i];
	}
}

//Release a specific sound
void SoundManager::ReleaseSound(unsigned int index)
{
	if (soundList.size() > index)
	{
		soundList[index].sound->release();
		delete &soundList[index];
	}
}

//Play the sound
void SoundManager::PlaySound(unsigned int soundIndex)
{

}

//Update the sound system
void SoundManager::Update()
{

}
