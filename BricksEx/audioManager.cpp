#include "audioManager.h"
#include "utility.h"
#include <string>

std::shared_ptr<AudioManager> AudioManager::instance = nullptr;

std::shared_ptr<AudioManager> AudioManager::getInstance() {
	if (!instance) {
		instance.reset(new AudioManager());
	}

	return instance;
}

AudioManager::~AudioManager() {

}

void AudioManager::initialize() {
	// if memory violation happen, reset the lib connector of project (-d have something bug)
	const std::vector<std::string> fileNames = { "s1.wav", "bg.wav" };
	if (!buffer1.loadFromFile(fileNames[0])) {
		std::cout << "Cannot load " << fileNames[0] <<  std::endl;
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
