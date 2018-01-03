#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Brick : public RectangleShape, Window, Texture, Color/*, Drawable*/{

public:

	Brick(const size_t row, const size_t column, const float width, const float height, Window *window, const Vector2f &interval = Vector2f(0.0f, 0.0f));
	Brick(const size_t rowCount, const float width, const float height, Window *window, const Vector2f &interval = Vector2f(0.0f, 0.0f));
	void loadImage(Texture *);
	void fillEntityColor(const Color &);
	void setRowAmount(const size_t row, Window *window);
	void setInterval(const Vector2f &interval, Window *window);
	void setInterval(const float x, const float y, Window *window);
	void setSideLength(const Vector2f &sideLength, Window *window);
	void setSideLength(const float width, const float height, Window *window);
	const size_t getAreaSize() const;
	const Vector2f & getSideLength() const;
	const Vector2f & getInterval() const;

private:

	void settlePlace(Window *);
	const vector<RectangleShape> getArea() const;
	virtual void draw(RenderTarget& , RenderStates) const;

	vector<RectangleShape> area;
	// brick quantities on every row
	size_t amount;
	Vector2f interval = Vector2f(0.0f, 0.0f);
	Vector2f sideLength;
	bool changeEntity = true;
};