#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public VertexArray, Color {
public:

	Block(const enum PrimitiveType type, const size_t vertexCount, const Vector2f &position, float width, float height);

	void setVerticeColor(const Color &);
	void setVerticeColor(const Color &, const Color &, const Color &, const Color &);
	void setWidth(const float width);
	void setHeight(const float height);
	void movePosition(const Vector2f &pos);
	void enable(CircleShape &ball, float &speedX, float &speedY);

	const Vector2f & getPosition() const;
	const float getWidth() const;
	const float getHeight() const;
	//void getStatus();

private:
	void setBlockVertice(const Vector2f &, const float, const float);
	Vector2f position;
	float width;
	float height;
};