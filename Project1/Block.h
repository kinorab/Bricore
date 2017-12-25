#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public VertexArray, Color {
public:

	Block(const enum PrimitiveType, const int, const Vector2f &, float, float);
	void setVerticeColor(const Color &);
	void setVerticeColor(const Color &, const Color &, const Color &, const Color &);
	void setWidth(const float);
	void setHeight(const float);
	void MovePosition(const Vector2f &);
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