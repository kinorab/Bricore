#pragma once

#include <SFML/Audio.hpp>

class AudioManager {
public:
	static sf::Sound sound1;
	static sf::Music bgmusic;
	static void initialize();
};
