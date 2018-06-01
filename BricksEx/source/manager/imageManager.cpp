#include "imageManager.h"
#include "../definition/utility.h"
#include <string>

ImageManager::~ImageManager() {

}

sf::Image * ImageManager::get(const std::string key) {
	auto iterator = resources.find(key);
	if (iterator == resources.end()) {
		load(key);
	}

	return resources[key].get();
}

void ImageManager::load(const std::string key) {
	resources.emplace(key, new sf::Image());
	if (!resources[key]->loadFromFile(key)) {
		throw std::out_of_range("File not found.");
	}
}

void ImageManager::unload(const std::string key) {
	if (resources.erase(key) == 0) {
		throw std::out_of_range("Resource not found.");
	}
}

ImageManager::ImageManager(){

}
