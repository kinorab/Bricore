#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public VertexArray {

public:

	Block(enum PrimitiveType, const int, const Vector2f &, float, int);

	void setIncreRate(const int);

	void setLength(float);

	void MovePosition(const Vector2f &);

	//void getStatus();


private:

	void setBlockVertice(VertexArray &, const int, const Vector2f &, float, const int);

	const int getvertexCount();

	const Vector2f & getPosition();

	const float getLength();

	const int getIncreRate();

	VertexArray array;
	const int vertexCount;
	Vector2f position;
	float length;
	int increRate = 1;

};