#include "textureManager.h"
#include "../definition/utility.h"
#include <string>

void TextureManager::initialize() {
	// load fundamental texture
}

sf::Texture * TextureManager::get(const std::string & fileName) {
	for (auto & texture : textures) {
		if (texture.first.find("/" + fileName + ".png") != std::string::npos) {
			return texture.second.get();
		}
		if (texture.first.find("/" + fileName) != std::string::npos) {
			return texture.second.get();
		}
	}
	std::cout << "Cannot find file: " << fileName << std::endl;
	// throw std::invalid_argument("File not be loaded or no such file");
	return nullptr;
}

void TextureManager::load(const std::string & directory) {
	textures.emplace(directory, new sf::Texture);
	if (!textures[directory]->loadFromFile(directory)) {
		throw std::out_of_range("File not found.");
	}
}

void TextureManager::unload(const std::string & directory) {
	if (textures.erase(directory) == 0) {
		throw std::out_of_range("Resource not found.");
	}
}

TextureManager::TextureManager() noexcept {
}

TextureManager::~TextureManager() {
}