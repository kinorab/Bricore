#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public VertexArray {
public:
	Block(const PrimitiveType, const int, const Vector2f &, float, float);
	void setWidth(const float);
	void setHeight(const float);
	void MovePosition(const Vector2f &);
	const Vector2f & getPosition() const;
	float getWidth() const;
	float getHeight() const;
	//void getStatus();
private:
	void setBlockVertice(const Vector2f &, const float, const float);
	Vector2f position;
	float width;
	float height;
};