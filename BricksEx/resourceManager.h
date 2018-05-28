#pragma once
/*

#include <memory>
#include <map>

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
	std::map<std::string, std::shared_ptr<sf::Image>> resources;
};
*/