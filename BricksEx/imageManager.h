#pragma once

#include <SFML/Graphics/Image.hpp>
#include <memory>

class ImageManager {
public:
	static void initialize();
private:
	static std::shared_ptr<ImageManager> instance;
};
