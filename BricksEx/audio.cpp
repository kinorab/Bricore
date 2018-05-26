#include "audio.h"
#include "utility.h"
#include <string>
#include <stdexcept>


sf::Sound Audio::sound1;
sf::Music Audio::bgmusic;
static sf::SoundBuffer buffer1;
static float bufferBgVolume = 100.0f;
static float bufferVolume1 = 50.0f;
std::vector<std::string> fileNames = { "s1.wav", "bg.wav" };

// preload all audio files
void Audio::initialize() {
	// if memory violation happen, reset the lib connector of project (-d have something bug)
	if (!buffer1.loadFromFile(fileNames[0])) {
		std::cout << "Cannot load " << fileNames[0] <<  std::endl;
	}
	if (!Audio::bgmusic.openFromFile(fileNames[1])) {
		std::cout << "Cannot load " << fileNames[1] << std::endl;
	}
	Audio::sound1.setBuffer(buffer1);
	Audio::sound1.setVolume(bufferVolume1);
}
