#include "audioManager.h"
#include "../definition/utility.h"
#include <string>

void AudioManager::initialize() {
	loadSound("res/audio/sound/hitBoard.wav");
	loadMusic("res/audio/bgm/bg.wav");
}

void AudioManager::loadSound(const std::string & directory) {
	buffers.emplace(directory, new sf::SoundBuffer);
	if (!buffers.at(directory)->loadFromFile(directory)) {
		std::cout << "Cannot load " << directory << std::endl;
	}
	sounds.emplace(directory, new sf::Sound(*buffers.at(directory)));
}

void AudioManager::unloadSound(const std::string & directory) {
	if (sounds.erase(directory) == 0) {
		throw std::out_of_range("Sound not found.");
	}
}

void AudioManager::loadMusic(const std::string & directory) {
	musics.emplace(directory, new sf::Music);
	if (!musics.at(directory)->openFromFile(directory)) {
		std::cout << "Cannot open " << directory << std::endl;
	}
}

void AudioManager::unloadMusic(const std::string & directory) {
	if (musics.erase(directory) == 0) {
		throw std::out_of_range("Music not found.");
	}
}

const sf::SoundBuffer * AudioManager::getBuffer(const std::string & fileName) {
	for (auto & buffer : buffers) {
		if (buffer.first.find("/" + fileName + ".wav") != std::string::npos) {
			return buffer.second.get();
		}
		if (buffer.first.find("/" + fileName) != std::string::npos) {
			return buffer.second.get();
		}
	}
	throw std::invalid_argument("Sound not found.");
}

sf::Sound * AudioManager::getSound(const std::string & fileName) {
	for (auto & sound : sounds) {
		if (sound.first.find("/" + fileName + ".wav") != std::string::npos) {
			return sound.second.get();
		}
		if (sound.first.find("/" + fileName) != std::string::npos) {
			return sound.second.get();
		}
	}
	throw std::invalid_argument("Sound not found.");
}

sf::Music * AudioManager::getMusic(const std::string & fileName) {
	for (auto & music : musics) {
		if (music.first.find("/" + fileName + ".wav") != std::string::npos) {
			return music.second.get();
		}
		if (music.first.find("/" + fileName) != std::string::npos) {
			return music.second.get();
		}
	}
	throw std::invalid_argument("Music not found.");
}

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}