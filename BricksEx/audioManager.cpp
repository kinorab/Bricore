#include "audioManager.h"
#include "utility.h"
#include <string>

sf::Sound AudioManager::sound1;
sf::Music AudioManager::bgmusic;
static sf::SoundBuffer buffer1;
static float bufferBgVolume = 100.0f;
static float bufferVolume1 = 50.0f;
std::vector<std::string> fileNames = { "s1.wav", "bg.wav" };

void AudioManager::initialize() {
	// if memory violation happen, reset the lib connector of project (-d have something bug)
	if (!buffer1.loadFromFile(fileNames[0])) {
		std::cout << "Cannot load " << fileNames[0] <<  std::endl;
	}
	if (!AudioManager::bgmusic.openFromFile(fileNames[1])) {
		std::cout << "Cannot load " << fileNames[1] << std::endl;
	}
	AudioManager::sound1.setBuffer(buffer1);
	AudioManager::sound1.setVolume(bufferVolume1);
}
