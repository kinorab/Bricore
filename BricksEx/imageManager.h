#pragma once

#include <SFML/Graphics/Image.hpp>
#include <memory>

class ImageManager {
public:
	static std::shared_ptr<ImageManager> getInstance();
	virtual ~ImageManager();
	static void initialize();
protected:
	ImageManager();
private:
	static std::shared_ptr<ImageManager> instance;
};
