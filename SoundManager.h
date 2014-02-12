#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>

#include <glm\glm.hpp>

#include <vector>

enum SOUND_ROLLOFF_MODE
{
	SOUND_ROLLOFF_LOG		= FMOD_3D_INVERSEROLLOFF,
	SOUND_ROLLOFF_LINEAR	= FMOD_3D_LINEARROLLOFF,
};

struct Sound
{
	FMOD::Sound *sound;
	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	//Add a sound to the manager
	void AddSound(char *soundFilePath, glm::vec3 position, glm::vec3 velocity);

	//Release all sounds
	void ReleaseAllSounds(void);

	//Release a specific sound
	void ReleaseSound(unsigned int index);

	//Play the sound
	void PlaySound(unsigned int soundIndex);

	//Update the sound system
	void Update();

private:
	FMOD::System *soundSystem;

	FMOD::Channel *channel;

	FMOD_RESULT result;

	std::vector<Sound> soundList;

	SOUND_ROLLOFF_MODE rolloffMode;
};