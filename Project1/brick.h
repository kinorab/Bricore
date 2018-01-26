#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Brick : public RectangleShape, Window, Texture, Color {

public:

	Brick(const size_t row, const size_t column, const float width, const float height, Window *window
		, const Vector2f &interval = Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
	Brick(const size_t rowCount, const float width, const float height, Window *window
		, const Vector2f &interval = Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);

	void loadImage(Texture *);
	void setBrickColor(const Color &);
	void setFrameColor(const Color &);
	void setRowAmount(const int row, Window *window);
	void setSideLength(const Vector2f &sideLength, Window *window);
	void setSideLength(const float width, const float height, Window *window);
	void setInterval(const Vector2f &interval, Window *window);
	void setInterval(const float x, const float y, Window *window);
	void setFrameSize(const float frame, Window *window);
	void collisionBroke(CircleShape &, float &speedX, float &speedY);

	const size_t getAreaSize() const;
	const Vector2f & getSideLength() const;
	const Vector2f & getInterval() const;
	const float getFrameSize() const;


private:

	void settlePlace(Window *);
	virtual void draw(RenderTarget&, RenderStates) const;

	vector<RectangleShape> area;
	// bricks on every row
	size_t amount;
	Vector2f interval;
	Vector2f sideLength;
	float frame;
	bool changeEntity = true;
};