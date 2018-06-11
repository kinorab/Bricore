#pragma once

#include "../template/singleton.h"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <unordered_map>

class TextureManager :
	public Singleton<TextureManager> {
	friend class Singleton<TextureManager>;
public:
	virtual ~TextureManager();
	virtual sf::Texture * get(const std::string key);
	virtual void load(const std::string key);
	virtual void unload(const std::string key);
protected:
	TextureManager();
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> resources;
};
