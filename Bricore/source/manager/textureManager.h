#pragma once

#include "../template/singleton.h"
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>

class TextureManager :
	public Singleton<TextureManager> {
	friend class Singleton<TextureManager>;
public:
	void initialize();
	// get fileName(.png)
	sf::Texture * get(const std::string & fileName);
	// load /directory
	void load(const std::string & directory);
	// unload /directory
	void unload(const std::string & directory);
	virtual ~TextureManager();
protected:
	TextureManager();
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};
