#pragma once

#include <SFML/Graphics/Image.hpp>
#include <memory>
#include <unordered_map>

class ImageManager {
public:
	static std::shared_ptr<ImageManager> getInstance();
	virtual ~ImageManager();
	virtual sf::Image * get(const std::string key);
	virtual	void load(const std::string key);
	virtual void unload(const std::string key);
protected:
	ImageManager();
private:
	static std::shared_ptr<ImageManager> instance;
	std::unordered_map<std::string, std::shared_ptr<sf::Image>> resources;
};
