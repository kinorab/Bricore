#pragma once

#include <SFML/Audio.hpp>

class Audio {
public:
	static sf::Sound sound1;
	static sf::Music bgmusic;
	static void initialize();
private:
	static sf::SoundBuffer buffer1;
	static float bufferBgVolume;
	static float bufferVolume1;
};
