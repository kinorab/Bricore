#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int PI = 3.1415927;

void setItemVertice(VertexArray &array, const Vector2f &initial, float length) {

	try {

		if (length > 0) {

			const float outsideAngle = 360.0f / array.getVertexCount();


			for (size_t i = 0; i < array.getVertexCount(); ++i) {

				array[i].position = initial;
			}// end for
			cout << "(" << array[0].position.x << ", " << array[0].position.y << ")" << endl;// print array vertice position

			for (size_t i = 1; i < array.getVertexCount(); ++i) {

				float countAngle = outsideAngle * i;
				float angle = PI - countAngle / 180 * PI;// place array in clockwise

				float lengthX = sin(angle) * length;
				if (countAngle == 0.0f || countAngle == 180.0f) {
					lengthX = 0.0f;
				}// end if

				float lengthY = cos(angle) * length;
				if (countAngle == 90.0f || countAngle == 270.0f) {
					lengthY = 0.0f;
				}// end if

				array[i].position += Vector2f(lengthX, lengthY);
				cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;

				for (size_t j = i + 1; j < array.getVertexCount(); ++j) {

					array[j].position = array[i].position;
				}// end inner for
			}// end outer for
		}// end if
		else {

			throw out_of_range("Invalid initial side-length for item.");
		}// end else
	}// end try
	catch (out_of_range &ex) {

		cout << "Exception: " << ex.what() << endl;
	}// end catch
}// end function setItemVertice


int main() {
	RenderWindow window(VideoMode(200, 200), "SFML works!");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	while (window.isOpen())	{
		Event event;
		Vector2f localPosition;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			localPosition = Vector2f(Mouse::getPosition(window));
		}

		shape.setPosition(localPosition);
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}