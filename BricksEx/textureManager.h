#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <unordered_map>

class TextureManager {
public:
	static std::shared_ptr<TextureManager> getInstance();
	virtual ~TextureManager();
	virtual sf::Texture * get(const std::string key);
	virtual void load(const std::string key);
	virtual void unload(const std::string key);
protected:
	TextureManager();
private:
	static std::shared_ptr<TextureManager> instance;
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> resources;
};
