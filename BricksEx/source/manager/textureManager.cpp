#include "textureManager.h"
#include "../definition/utility.h"
#include <string>

std::shared_ptr<TextureManager> TextureManager::instance = nullptr;

std::shared_ptr<TextureManager> TextureManager::getInstance() {
	if (!instance) {
		instance.reset(new TextureManager());
	}

	return instance;
}

TextureManager::~TextureManager() {

}

sf::Texture * TextureManager::get(const std::string key) {
	if (resources.find(key) == resources.end()) {
		load(key);
	}

	return resources[key].get();
}

void TextureManager::load(const std::string key) {
	resources.emplace(key, new sf::Texture());
	if (!resources[key]->loadFromFile(key)) {
		throw std::out_of_range("File not found.");
	}
}

void TextureManager::unload(const std::string key) {
	if (resources.erase(key) == 0) {
		throw std::out_of_range("Resource not found.");
	}
}

TextureManager::TextureManager() {

}
