#include "textureManager.h"
#include "../definition/utility.h"
#include <string>

void TextureManager::initialize() {
	// load frame
	load("res/graphic/module/skill/ballSkill/frame/frame_1.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_2.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_3.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_4.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_5.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_6.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_7.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_8.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_9.png");
	load("res/graphic/module/skill/ballSkill/frame/frame_10.png");
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
	// debug feature
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