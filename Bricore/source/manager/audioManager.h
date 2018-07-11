#pragma once

#include "../template/singleton.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

class AudioManager : 
	public Singleton<AudioManager> {
	friend class Singleton<AudioManager>;
public:
	void initialize();
	// load /directory
	void loadSound(const std::string & directory);
	// unload /directory
	void unloadSound(const std::string & directory);
	// load /directory
	void loadMusic(const std::string & directory);
	// unload /directory
	void unloadMusic(const std::string & directory);
	// get fileName(.wav)
	const sf::SoundBuffer * getBuffer(const std::string & fileName);
	// get fileName(.wav)
	sf::Sound * getSound(const std::string & fileName);
	// get fileName(.wav)
	sf::Music * getMusic(const std::string & fileName);
	virtual ~AudioManager();
protected:
	AudioManager();
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Sound>> sounds;
	std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> buffers;
	std::unordered_map<std::string, std::shared_ptr<sf::Music>> musics;
};
