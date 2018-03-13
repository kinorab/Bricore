#include "audio.h"
#include <stdexcept>
#include <iostream>

sf::Sound Audio::sound1;
sf::Music Audio::bgmusic;
sf::SoundBuffer Audio::buffer1;
float Audio::bufferBgVolume = 100.0f;
float Audio::bufferVolume1 = 50.0f;

void Audio::initialize() {
	try {
		// if memory violation happen, reset the lib connector of project (-d have something bug)
		if (!Audio::buffer1.loadFromFile("s1.wav")) {
			throw std::runtime_error("Cannot get the sound file.");
		}
		else if (!Audio::bgmusic.openFromFile("bg.wav")) {
			throw std::runtime_error("Cannot get the music file.");
		}
		Audio::sound1.setBuffer(Audio::buffer1);
		Audio::sound1.setVolume(Audio::bufferVolume1);
		/*
		Audio::bgmusic.play();
		Audio::bgmusic.setLoop(true);
		*/
	}
	catch (std::runtime_error &ex) {
		std::cout << "Runtime_error: " << ex.what() << std::endl;
	}
}
