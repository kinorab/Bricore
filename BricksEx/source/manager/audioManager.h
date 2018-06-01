#pragma once

#include "../singleton.h"
#include <SFML/Audio.hpp>
#include <memory>

class AudioManager : 
	public Singleton<AudioManager> {
	friend class Singleton<AudioManager>;
public:
	sf::Sound sound1;
	sf::Music bgmusic;
	virtual ~AudioManager();
	virtual void initialize();
protected:
	AudioManager();
private:
	sf::SoundBuffer buffer1;
};
