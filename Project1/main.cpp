#include "ellipse.h"
#include "particleSystem.h"
#include "block.h"
#include "define.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

static bool start;

//void setCircleVertices(VertexArray &, const Vector2f &, float);
bool playerStart(Shape &, Window *, float, Shape &);
void controlBallMove(CircleShape &, Window *, const Vector2f &, Shape &);

void renderThread(RenderWindow *window) {// sub thread to run graphics here

	window->setActive(true);
	srand(time(NULL));
	

	ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 1;// settings graphics

	float blockLength = 50;
	float incre1 = 5;
	Block block1(Quads, 4, Vector2f((window->getSize().x - blockLength * incre1) / 2, (window->getSize().y - blockLength) / 2), blockLength * incre1, blockLength);
	block1.setVerticeColor(Color::Black, Color::Blue, Color::Black, Color::Black);

	RectangleShape mainPlayer;
	mainPlayer.setSize(Vector2f(200, 10));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y - mainPlayer.getSize().y));
	cout << "Player global bound: (" << mainPlayer.getGlobalBounds().height << ", " << mainPlayer.getGlobalBounds().left << ", " << mainPlayer.getGlobalBounds().top << ", " << mainPlayer.getGlobalBounds().width << ")" << endl;
	// 10 400 785 200
	CircleShape ball;
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(2.f);
	ball.setOutlineThickness(2.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setPosition(Vector2f(window->getSize().x / 2, mainPlayer.getPosition().y - mainPlayer.getSize().y));

	ParticleSystem mouseLight(5000);
	Vector2i localPosition;
	Clock clock;

	while (window->isOpen()) {

		window->clear(Color::White);

		localPosition = Mouse::getPosition(*window);
		mouseLight.setEmitter(window->mapPixelToCoords(localPosition));
		Time elapsed = clock.restart();
		mouseLight.update(elapsed);


		static float directX = rand() % 2 == 0 ? rand() % 9 + 1 : rand() % 9 * -1 - 1;// directX from -10 ~ 10, except for 0
		if (playerStart(mainPlayer, window, 5.f, ball)) {
			controlBallMove(ball, window, Vector2f(directX, -2), mainPlayer);
		}
		else {
			directX = rand() % 2 == 0 ? rand() % 9 + 1 : rand() % 9 * -1 - 1;// directX from -10 ~ 10, except for 0
			controlBallMove(ball, window, Vector2f(directX, -2), mainPlayer);
		}
	
		window->draw(mouseLight);
		window->draw(block1);
		window->draw(mainPlayer);
		window->draw(ball);

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
	Sound sound1;
	Music bgmusic;
	SoundBuffer buffer1;

	try {

		if (!buffer1.loadFromFile("1.wav")) {								// need file, not support mp3
																			// if memory violation happen, reset the lib connector of project (-d have something bug)
			throw out_of_range("Cannot get the sound file.");
		}// end if
		else if (!bgmusic.openFromFile("1.wav")) {							// need file, not support mp3

			throw out_of_range("Cannot get the music file.");
		}// end if
		else {
			sound1.setBuffer(buffer1);
			sound1.setVolume(50.0f);
			bgmusic.play();
			bgmusic.setLoop(true);
		}// end else
	}// end try
	catch (out_of_range &ex) {

		cout << "Exception: " << ex.what() << endl;
	}// end catch

	static float bufferVolume1 = 0.0f;
	if (sound1.getBuffer() != NULL) {
		bufferVolume1 = sound1.getVolume();
	}

	while (window.isOpen())	{// main thread to run event control, logical behavior

		Event event;

		while (window.pollEvent(event)) {// when pollEvent run all the content, will turn to false

			GlobalPosition = Vector2f(Mouse::getPosition(window));

			if (event.type == Event::TextEntered) {

				if (event.text.unicode < 128) {

					cout << "ASCII charactor typed: " << static_cast<char>(event.text.unicode)
						<< ", unicode is: " << event.text.unicode << endl;
				}// end inner if
			}// end outer if

			if (event.type == Event::KeyPressed) {// can place some option control

				switch (event.key.code) {

				case (Keyboard::Add):// incre volume
					if (sound1.getBuffer() != NULL) {
						if (bufferVolume1 < 95.0f) {
							sound1.setVolume(bufferVolume1 += 5.f);
						}// end if
						else {
							sound1.setVolume(100.0f);
						}// end else
						cout << "Now the volume is : " << sound1.getVolume() << endl;
					}// end if
					else {
						cout << "Somethings bug ,cannot change the sound volume." << endl;
					}// end else
					break;

				case (Keyboard::Subtract):// decre volume
					if (sound1.getBuffer() != NULL) {
						if (bufferVolume1 > 5.0f) {
							sound1.setVolume(bufferVolume1 -= 5.f);
						}// end if
						else {
							sound1.setVolume(0.0f);
						}// end else
						cout << "Now the volume is : " << sound1.getVolume() << endl;
					}// end if
					else {
						cout << "Somethings bug ,cannot change the sound volume." << endl;
					}// end else
					break;

				default:
					break;
				}
			}

			if (event.type == Event::MouseButtonPressed) {

				if (event.mouseButton.button == Mouse::Left) {
					start = true;// ball start
				}
				else if (event.mouseButton.button == Mouse::Right) {
					start = false;// ball reset
				}
			}

			if (event.type == Event::Closed) {

				subthread.terminate();
				bgmusic.stop();
				sound1.stop();
				sound1.~Sound();
				window.close();
			}
			else if (event.type == Event::Resized) {

				FloatRect viewResized(0, 0, event.size.width, event.size.height);
				float bufferViewX = window.getView().getSize().x;
				float bufferViewY = window.getView().getSize().y;
				window.setView(View(viewResized));// need some window control, all item need to maintain initial proportion
				float rateX = window.getView().getSize().x / bufferViewX;// item scale increment rateX
				float rateY = window.getView().getSize().y / bufferViewY;// item scale increment rateY
			}
		}
	}

	system("pause");
}


/*void setCircleVertices(VertexArray &array, const Vector2f &initial, float length) {

	try {
		if (length > 0) {
			const float outsideAngle = 360.0f / array.getVertexCount();
			for (size_t i = 0; i < array.getVertexCount(); ++i) {
				array[i].position = initial;
			}

			cout << "(" << array[0].position.x << ", " << array[0].position.y << ")" << endl;// print array vertice position
			for (size_t i = 1; i < array.getVertexCount(); ++i) {
				float countAngle = outsideAngle * i;
				float angle = PI - countAngle / 180 * PI;// place array in clockwise
				float lengthX = sin(angle) * length;
				if (countAngle == 0.0f || countAngle == 180.0f) {
					lengthX = 0.0f;
				}

				float lengthY = cos(angle) * length;
				if (countAngle == 90.0f || countAngle == 270.0f) {
					lengthY = 0.0f;
				}

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

}// end function setItemVertice*/

bool playerStart(Shape &p1, Window *win, float sp, Shape &b1) {

	void playerMove(Shape &player, Window *window, float speed);
	bool ballEnableMove(Shape &ball);

	if (!start) {

		playerMove(p1, win, sp);
		b1.setPosition(p1.getPosition().x, p1.getPosition().y - p1.getLocalBounds().height);
		return false;
	}
	else {

		playerMove(p1, win, sp);
		ballEnableMove(b1);
	}
}

void playerMove(Shape &player, Window *window, float speed) {

	if (player.getGlobalBounds().contains(Vector2f(window->getSize().x, player.getPosition().y))) {

		if (Keyboard::isKeyPressed(Keyboard::Left)) {

			player.move(Vector2f(speed * -1, 0));
		}
	}
	else if (player.getGlobalBounds().contains(Vector2f(0, player.getPosition().y))) {

		if (Keyboard::isKeyPressed(Keyboard::Right)) {

			player.move(Vector2f(speed, 0));
		}
	}
	else {

		if (Keyboard::isKeyPressed(Keyboard::Left)) {

			player.move(Vector2f(speed * -1, 0));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {

			player.move(Vector2f(speed, 0));
		}
	}

}

bool ballEnableMove(Shape &ball) {// can add extra affect

	return true;
}

void controlBallMove(CircleShape &ball, Window *window, const Vector2f &move, Shape &player) {// impact obstacle or bound and change direct(except for bottom bound)

	static int changeX = 1;
	static int changeY = 1;

	if (!start) {// reinitialize the ball
		changeX = 1;
		changeY = 1;
	}
	else {

		FloatRect playerPos = player.getGlobalBounds();

		if (ball.getPosition().x >= window->getSize().x - ball.getRadius()) {// window's right bound
			changeX *= -1;
			ball.move(move.x * changeX, move.y * changeY);
		}
		else if (ball.getPosition().x <= 0 + ball.getRadius()) {// window's left bound
			changeX *= -1;
			ball.move(move.x * changeX, move.y * changeY);
		}
		else if (ball.getPosition().y <= 0 + ball.getRadius()) {// window's top bound
			changeY *= -1;
			ball.move(move.x * changeX, move.y * changeY);
		}
		else if (ball.getGlobalBounds().intersects(playerPos)) {// the collision between ball and player

			if (move.x * changeX < 0) {// ball collide from right side

				if (ball.getPosition().x > player.getPosition().x) {
					changeX *= -1;
					changeY *= -1;
					ball.move(move.x * changeX, move.y * changeY);
				}
				else if (ball.getPosition().x < player.getPosition().x) {
					changeY *= -1;
					ball.move(move.x * changeX, move.y * changeY);
				}
			}
			else {						// ball collide from left side

				if (ball.getPosition().x > player.getPosition().x) {
					changeY *= -1;
					ball.move(move.x * changeX, move.y * changeY);
				}
				else if (ball.getPosition().x < player.getPosition().x) {
					changeX *= -1;
					changeY *= -1;
					ball.move(move.x * changeX, move.y * changeY);
				}
			}
		}
		else {
			ball.move(move.x * changeX, move.y * changeY);
		}
	}

}