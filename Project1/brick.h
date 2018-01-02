#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Brick : public RectangleShape, Texture{

public:

	Brick(const size_t row, const size_t column, const float width, const float height);
	void setArea(const size_t row, const size_t column);
	void setWidth(const float wid);
	void setHeight(const float hei);
	constexpr float getWidth() const;
	constexpr float getHeight() const;


private:

	vector<size_t> area;
	float width;
	float height;
};