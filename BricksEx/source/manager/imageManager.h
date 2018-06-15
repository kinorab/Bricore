#pragma once

#include "../template/singleton.h"
#include <SFML/Graphics/Image.hpp>
#include <memory>
#include <unordered_map>

class ImageManager : 
	public Singleton<ImageManager> {
	friend class Singleton<ImageManager>;
public:
	virtual ~ImageManager();
	virtual sf::Image * get(const std::string key);
	virtual	void load(const std::string key);
	virtual void unload(const std::string key);
protected:
	ImageManager();
private:
	std::unordered_map<std::string, std::shared_ptr<sf::Image>> resources;
};
