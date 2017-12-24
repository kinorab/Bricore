#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "Ellipse.h"
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void setItemVertice(VertexArray &, const Vector2f &, float);
void setBlockVertice(VertexArray &, const Vector2f &, float, const int);// set Blocks
void setItemColor(VertexArray &, const Color &);
void playerMove(Shape &, Window *window, float);

void renderThread(RenderWindow *window) {

	window->setActive(true);

	ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 1;// settings graphics

	VertexArray block1(Quads, 4);
	float blockLength = 50;
	const int incre1 = 5;
	setBlockVertice(block1, Vector2f((window->getSize().x - blockLength * incre1) / 2, (window->getSize().y - blockLength) / 2), blockLength, incre1);
	setItemColor(block1, Color::Yellow);

	RectangleShape mainPlayer;
	mainPlayer.setSize(Vector2f(200, 10));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y - mainPlayer.getSize().y));
	//cout << "player's local bounds: ("<< mainPlayer.getLocalBounds().height << ", " << mainPlayer.getLocalBounds().width << ", " << mainPlayer.getLocalBounds().top << ", " << mainPlayer.getLocalBounds().width << ")" << endl; 

	ParticleSystem mouseLight(5000);
	Vector2i localPosition;
	Clock clock;

	while (window->isOpen()) {

		window->clear(Color::White);

		localPosition = Mouse::getPosition(*window);
		mouseLight.setEmitter(window->mapPixelToCoords(localPosition));
		Time elapsed = clock.restart();
		mouseLight.update(elapsed);

		playerMove(mainPlayer, window, .35f);

		window->draw(mouseLight);
		window->draw(block1);
		window->draw(mainPlayer);

		window->display();
	}
}


int main() {


	RenderWindow window(VideoMode(1000, 800), "Pigject");

	Mouse::setPosition(Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
	View defualtView = window.getDefaultView();
	window.setActive(false);

	Thread subthread(&renderThread, &window);
	subthread.launch();

	Vector2f GlobalPosition;

	while (window.isOpen())	{

		Event event;

		while (window.pollEvent(event)) {// when pollEvent run all the content, will turn to false

			GlobalPosition = Vector2f(Mouse::getPosition(window));

			if (event.type == Event::Closed) {

				subthread.terminate();
				window.close();
			}
			else if (event.type == Event::Resized) {

				FloatRect viewResized(0, 0, event.size.width, event.size.height);
				float bufferViewX = window.getView().getSize().x;
				float bufferViewY = window.getView().getSize().y;
				//window.setView(View(viewResized));
				float rateX = window.getView().getSize().x / bufferViewX;
				float rateY = window.getView().getSize().y / bufferViewY;
			}
		}
	}

	system("pause");
}




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


void setBlockVertice(VertexArray &array, const Vector2f &initial, float length, const int increRate) {

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

				if (!(i == 1 || i == 3)) {
					array[i].position += Vector2f(lengthX, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}
				else {
					array[i].position += Vector2f(lengthX * increRate, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}

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


void setItemColor(VertexArray &array, const Color &color) {

	for (size_t i = 0; i < array.getVertexCount(); ++i) {

		array[i].color = color;
	}
}


void playerMove(Shape &player, Window *window, float speed) {// speed set 0 ~ .1f

	if (player.getGlobalBounds().contains(Vector2f( window->getSize().x, player.getPosition().y))) {

		if (Keyboard::isKeyPressed(Keyboard::Left)) {

			player.move(Vector2f(speed * -1, 0));
		}
	}
	else if (player.getGlobalBounds().contains(Vector2f( 0, player.getPosition().y))) {

		if (Keyboard::isKeyPressed(Keyboard::Right)) {

			player.move(Vector2f(speed, 0));
		}
	}
	else{

		if (Keyboard::isKeyPressed(Keyboard::Left)) {

			player.move(Vector2f(speed * -1, 0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {

			player.move(Vector2f(speed, 0));
		}
	}

}