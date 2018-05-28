#pragma once

#include <SFML/Audio.hpp>
#include <memory>

class AudioManager {
public:
	static std::shared_ptr<AudioManager> getInstance();
	virtual ~AudioManager();
	sf::Sound sound1;
	sf::Music bgmusic;
	void initialize();
protected:
	AudioManager();
private:
	static std::shared_ptr<AudioManager> instance;
	sf::SoundBuffer buffer1;
};
