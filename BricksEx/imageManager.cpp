#include "imageManager.h"
#include "utility.h"
#include <string>

std::shared_ptr<ImageManager> ImageManager::instance = nullptr;
static const std::vector<std::string> fileList = { "s1.wav", "bg.wav" };

std::shared_ptr<ImageManager> ImageManager::getInstance() {
	if (!instance) {
		instance.reset(new ImageManager());
	}

	return instance;
}

ImageManager::~ImageManager() {

}

void ImageManager::initialize() {

}

ImageManager::ImageManager(){

}
