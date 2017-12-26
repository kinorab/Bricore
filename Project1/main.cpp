#include "ellipse.h"
#include "particleSystem.h"
#include "block.h"
#include "define.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <atomic>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>
#include <mutex>

using namespace sf;
using namespace std;

static bool start;
static int speedX;
static int speedY;
static queue<Event> gameEventQueue;
static mutex gameEventQueueMutex;

//void setCircleVertices(VertexArray &, const Vector2f &, float);
void renderThread(RenderWindow * window, atomic<bool> * done);
void BallMove(CircleShape & ball, Window * window, Shape & player);
void controlBallMove(CircleShape &, Block &);
void initializeBall();
void playerMove(Shape & player, Window * window, float speed);
void ballEnableMove(Shape &ball);

// sub thread to run graphics here
void renderThread(RenderWindow * window, atomic<bool> * done) {
	window->setActive(true);
	srand(time(NULL));
	float blockLength = 100;
	float incre1 = 3;
	Block block1(Quads, 4, Vector2f((window->getSize().x - blockLength * incre1) / 2, (window->getSize().y - blockLength) / 2), blockLength * incre1, blockLength);
	block1.setVerticeColor(Color::Black, Color::Blue, Color::Black, Color::Black);
	Block block2(Quads, 4, Vector2f(blockLength, blockLength), blockLength, blockLength * 2);
	block2.setVerticeColor(Color::Green, Color::Red, Color::Cyan, Color::Yellow);
	Block block3(Quads, 4, Vector2f(window->getSize().x - blockLength * 2, blockLength), blockLength, blockLength * 2);
	block3.setVerticeColor(Color::Black);
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
	cout << ball.getGlobalBounds().left + ball.getGlobalBounds().width << endl;
	ParticleSystem mouseLight(5000);
	Vector2i localPosition;
	Clock clock;
	Mouse::setPosition(Vector2i(window->getSize().x / 2, window->getSize().y / 2), *window);
	View defualtView = window->getDefaultView();
	Sound sound1;
	Music bgmusic;
	SoundBuffer buffer1;
	try {
		// need file, not support mp3
		// if memory violation happen, reset the lib connector of project (-d have something bug)
		if (!buffer1.loadFromFile("1.wav")) {
			throw out_of_range("Cannot get the sound file.");
		}
		// need file, not support mp3
		else if (!bgmusic.openFromFile("1.wav")) {
			throw out_of_range("Cannot get the music file.");
		}
		else {
			sound1.setBuffer(buffer1);
			sound1.setVolume(50.0f);
			bgmusic.play();
			bgmusic.setLoop(true);
		}

	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

	static float bufferVolume1 = 0.0f;
	if (sound1.getBuffer() != NULL) {
		bufferVolume1 = sound1.getVolume();
	}

	while (!(*done)) {
		Event event;
		gameEventQueueMutex.lock();
		while (!gameEventQueue.empty()) {
			event = gameEventQueue.front();
			gameEventQueue.pop();
			gameEventQueueMutex.unlock();
			Vector2f GlobalPosition = Vector2f(Mouse::getPosition(*window));
			if (event.type == Event::TextEntered) {
				if (event.text.unicode < 128) {
					cout << "ASCII charactor typed: " << static_cast<char>(event.text.unicode)
						<< ", unicode is: " << event.text.unicode << endl;
				}

			}
			// can place some option control
			else if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
					// volume up
				case (Keyboard::Add):
					if (sound1.getBuffer() != NULL) {
						if (bufferVolume1 < 95.0f) {
							sound1.setVolume(bufferVolume1 += 5.f);
						}
						else {
							sound1.setVolume(100.0f);
						}

						cout << "Now the volume is : " << sound1.getVolume() << endl;
					}
					else {
						cout << "Somethings bug ,cannot change the sound volume." << endl;
					}

					break;
					// volume down
				case (Keyboard::Subtract):
					if (sound1.getBuffer() != NULL) {
						if (bufferVolume1 > 5.0f) {
							sound1.setVolume(bufferVolume1 -= 5.f);
						}
						else {
							sound1.setVolume(0.0f);
						}

						cout << "Now the volume is : " << sound1.getVolume() << endl;
					}
					else {
						cout << "Somethings bug ,cannot change the sound volume." << endl;
					}

					break;
				default:
					break;
				}

			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left && !start) {
					start = true;
					initializeBall();
				}
				else if (event.mouseButton.button == Mouse::Right && start) {
					start = false;
				}

			}
			else if (event.type == Event::Closed) {
				bgmusic.stop();
				sound1.stop();
				*done = true;
			}
			else if (event.type == Event::Resized) {
				FloatRect viewResized(0, 0, event.size.width, event.size.height);
				float bufferViewX = window->getView().getSize().x;
				float bufferViewY = window->getView().getSize().y;
				window->setView(View(viewResized));// need some window control, all item need to maintain initial proportion
				float rateX = window->getView().getSize().x / bufferViewX;// item scale increment rateX
				float rateY = window->getView().getSize().y / bufferViewY;// item scale increment rateY
			}

			gameEventQueueMutex.try_lock();
		}

		gameEventQueueMutex.unlock();
		window->clear(Color::White);
		localPosition = Mouse::getPosition(*window);
		mouseLight.setEmitter(window->mapPixelToCoords(localPosition));
		Time elapsed = clock.restart();
		mouseLight.update(elapsed);
		playerMove(mainPlayer, window, 5.0f);
		if (!start) {
			ball.setPosition(mainPlayer.getPosition().x, mainPlayer.getPosition().y - mainPlayer.getLocalBounds().height);
		}
		else {
			controlBallMove(ball, block1);
			controlBallMove(ball, block2);
			controlBallMove(ball, block3);
			BallMove(ball, window, mainPlayer);
		}

		window->draw(mouseLight);
		window->draw(block1);
		window->draw(block2);
		window->draw(block3);
		window->draw(mainPlayer);
		window->draw(ball);
		window->display();
	}
	// finalize...
}

int main() {
	RenderWindow window(VideoMode(1000, 800), "Pigject");
	window.setActive(false);
	atomic<bool> done(false);
	thread subthread(renderThread, &window, &done);
	// main thread wait for event and push to queue
	Event event;
	while (!done && window.waitEvent(event)) {
		gameEventQueueMutex.lock();
		gameEventQueue.push(event);
		gameEventQueueMutex.unlock();
	}

	// finalize...
	window.close();
	system("pause");
}

/*
void setCircleVertices(VertexArray &array, const Vector2f &initial, float length) {

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
				array[i].position += Vector2f(lengthX, lengthY);
				cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				for (size_t j = i + 1; j < array.getVertexCount(); ++j) {

					array[j].position = array[i].position;
				}
			}
		}
		else {
			throw out_of_range("Invalid initial side-length for item.");
		}

	}

	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

}
*/

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

void ballEnableMove(Shape &ball) {// can add extra affect

}

void initializeBall() {
	// speedX from -10 ~ 10, except for 0
	speedX = rand() % 20 - 10;
	if (speedX >= 0.0f) {
		speedX += 1;
	}

	speedY = -2;
}

// impact obstacle or bound and change direct(except for bottom bound)
void BallMove(CircleShape &ball, Window *window, Shape &player) {
	FloatRect playerPos = player.getGlobalBounds();
	// out of bottom bound, reset the ball
	if (ball.getPosition().y - ball.getRadius() >= window->getSize().y) {
		start = false;
		initializeBall();
		return;
	}

	// window's right bound
	if (ball.getPosition().x + ball.getRadius() >= window->getSize().x) {
		speedX *= -1;
	}
	// window's left bound
	else if (ball.getPosition().x <= 0 + ball.getRadius()) {
		speedX *= -1;
	}
	// window's top bound
	else if (ball.getPosition().y <= 0 + ball.getRadius()) {
		speedY *= -1;
	}
	// the collision between ball and player
	else if (ball.getGlobalBounds().intersects(playerPos)) {
		speedY *= -1;
		// not include hitting on center
		if (ball.getPosition().x > player.getPosition().x) {
			speedX = abs(speedX);
		}

		if (ball.getPosition().x < player.getPosition().x) {
			speedX = -abs(speedX);
		}

	}

	ball.move(speedX, speedY);
}

// still have something need to fix, when speedX too fast, 
void controlBallMove(CircleShape &ball, Block &block) {
	FloatRect blockBounds = block.getBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	if (ballBounds.intersects(blockBounds)) {
		// obstacle left bound
		if (ballBounds.left <= blockBounds.left) {
			speedX *= -1;
		}

		// obstacle right bound
		if (ballBounds.left + ballBounds.width >= blockBounds.left + blockBounds.width) {
			speedX *= -1;
		}

		// obstacle top bound
		if (ballBounds.top <= blockBounds.top) {
			speedY *= -1;
		}

		// obstacle bottom bound
		if (ballBounds.top + ballBounds.height >= blockBounds.top + blockBounds.height) {
			speedY *= -1;
		}

	}

}