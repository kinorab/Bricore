#include "imageManager.h"
#include "utility.h"
#include <string>

std::shared_ptr<ImageManager> ImageManager::instance = nullptr;
static std::vector<std::string> fileList = { "s1.wav", "bg.wav" };

void ImageManager::initialize() {

}
