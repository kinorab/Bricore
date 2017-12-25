#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public VertexArray {

public:

	Block(PrimitiveType, const int, const Vector2f &, float, int);

	Block(PrimitiveType, const int, const Vector2f &, float);

	void setIncreRate(const int);

	void setLength(float);

	void MovePosition(const Vector2f &);

	const int getVertexCount() const;

	const Vector2f & getPosition();

	const float getLength();

	const int getIncreRate();

	const enum PrimitiveType getPrimitiveType();

	//void getStatus();

private:

	void setBlockVertice(VertexArray &, const Vector2f &, float, const int);

	const int vertexCount;
	enum PrimitiveType type;
	Vector2f position;
	float length;
	int increRate = 1;
	VertexArray array;

};