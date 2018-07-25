#pragma once

#include <string.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class AudioFx
{
public:
	AudioFx(const std::string& path);

	std::string GetPath() const;
	void SetPath(std::string val);
	bool Initialize();
	void Play();
	sf::Sound& GetSoundRef();
protected:
	std::string mPath = "";
	sf::SoundBuffer mBuffer;
	sf::Sound mSound;
	bool mIsInitialized = false;
};
