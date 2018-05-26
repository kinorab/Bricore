#include "audio.h"
#include <stdexcept>
#include <iostream>

sf::Sound Audio::sound1;
sf::Music Audio::bgmusic;
static sf::SoundBuffer buffer1;
static float bufferBgVolume = 100.0f;
static float bufferVolume1 = 50.0f;

// preload all audio files
void Audio::initialize() {
	// if memory violation happen, reset the lib connector of project (-d have something bug)
	if (!buffer1.loadFromFile("s1.wav")) {
		std::cout << "Cannot get the sound file." << std::endl;
	}
	if (!Audio::bgmusic.openFromFile("bg.wav")) {
		std::cout << "Cannot get the music file." << std::endl;
	}
	Audio::sound1.setBuffer(buffer1);
	Audio::sound1.setVolume(bufferVolume1);
}
