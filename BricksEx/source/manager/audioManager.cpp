#include "audioManager.h"
#include "../definition/utility.h"
#include <string>

AudioManager::~AudioManager() {

}

void AudioManager::initialize() {
	const std::vector<std::string> fileNames = { "res/audio/sound/hitBoard.wav", "res/audio/bgm/bg.wav" };
	if (!buffer1.loadFromFile(fileNames[0])) {
		std::cout << "Cannot load " << fileNames[0] << std::endl;
	}

	if (!AudioManager::bgmusic.openFromFile(fileNames[1])) {
		std::cout << "Cannot load " << fileNames[1] << std::endl;
	}

	const float bufferBgVolume = 100.0f;
	const float bufferVolume1 = 50.0f;
	AudioManager::sound1.setBuffer(buffer1);
	AudioManager::sound1.setVolume(bufferVolume1);
}

AudioManager::AudioManager() {

}
