#include "ellipse.h"
#include "particleSystem.h"
#include "block.h"
#include "define.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
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

//void setItemVertices(VertexArray &, const Vector2f &, float);
void ballMove(CircleShape &, Window *, Shape &);
void controlBallMove(CircleShape &, Block &);
void initializeBall();
void playerMove(Shape &, Window *, float);
void ballEnableMove(Shape &);

void renderThread(RenderWindow * window, atomic<bool> * done) {

	window->setActive(true);
	srand(time(NULL));
	float blockLength = 100;
	float incre1 = 3;
	Block block1(Quads, 4, Vector2f((window->getSize().x - blockLength * incre1) / 2, (window->getSize().y - blockLength) / 2), blockLength * incre1, blockLength);
	block1.setVerticeColor(Color::Black, Color::Blue, Color::Black, Color::Black);
	cout << block1.getBounds().left + block1.getBounds().width;
	Block block2(Quads, 4, Vector2f(blockLength, blockLength), blockLength, blockLength * 2);
	block2.setVerticeColor(Color::Green, Color::Red, Color::Cyan, Color::Yellow);
	Block block3(Quads, 4, Vector2f(window->getSize().x - blockLength * 2, blockLength), blockLength, blockLength * 2);
	block3.setVerticeColor(Color::Black);

	RectangleShape mainPlayer;
	mainPlayer.setSize(Vector2f(200, 10));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(window->getSize().x / 2, window->getSize().y - mainPlayer.getSize().y));

	CircleShape ball;
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(10.f);
	ball.setOutlineThickness(2.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));
	
	ParticleSystem mouseLight(5000);
	Vector2i localPosition;
	Clock clock;
	Mouse::setPosition(Vector2i(window->getSize().x / 2, window->getSize().y / 2), *window);
	View defualtView = window->getDefaultView();
	Sound sound1;
	Music bgmusic;
	SoundBuffer buffer1;

	try {
		// if memory violation happen, reset the lib connector of project (-d have something bug)
		// need file, not support mp3
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

		Event getEvent;

		while (!gameEventQueue.empty()) {

			gameEventQueueMutex.lock();
			getEvent = gameEventQueue.front();
			gameEventQueue.pop();
			gameEventQueueMutex.unlock();

			Vector2f GlobalPosition = Vector2f(Mouse::getPosition(*window));
			if (getEvent.type == Event::TextEntered) {
				if (getEvent.text.unicode < 128) {
					cout << "ASCII charactor typed: " << static_cast<char>(getEvent.text.unicode)
						<< ", unicode is: " << getEvent.text.unicode << endl;
				}
			}
			// can place some option control
			else if (getEvent.type == Event::KeyPressed) {
				switch (getEvent.key.code) {

				case (Keyboard::Add):// volume up
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

				case (Keyboard::Subtract):// volume down
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
			else if (getEvent.type == Event::MouseButtonPressed) {
				if (getEvent.mouseButton.button == Mouse::Left && !start) {
					initializeBall();
					start = true;
				}
				else if (getEvent.mouseButton.button == Mouse::Right && start) {
					start = false;
				}
			}
			else if (getEvent.type == Event::Closed) {
				bgmusic.stop();
				sound1.stop();
				*done = true;
			}
			else if (getEvent.type == Event::Resized) {
				FloatRect viewResized(0, 0, getEvent.size.width, getEvent.size.height);
				float bufferViewX = window->getView().getSize().x;
				float bufferViewY = window->getView().getSize().y;
				// need some window control, all item need to maintain initial proportion
				window->setView(View(viewResized));
				// item scale increment rateX
				float rateX = window->getView().getSize().x / bufferViewX;
				// item scale increment rateY
				float rateY = window->getView().getSize().y / bufferViewY;
			}
		}

		window->clear(Color::White);

		localPosition = Mouse::getPosition(*window);
		mouseLight.setEmitter(window->mapPixelToCoords(localPosition));
		Time elapsed = clock.restart();
		mouseLight.update(elapsed);

		playerMove(mainPlayer, window, 5.0f);
		if (!start) {
			ball.setPosition(mainPlayer.getPosition().x, mainPlayer.getGlobalBounds().top - ball.getLocalBounds().height / 2);
		}
		else {
			controlBallMove(ball, block1);
			controlBallMove(ball, block2);
			controlBallMove(ball, block3);
			ballMove(ball, window, mainPlayer);
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
void setItemVertices(VertexArray &array, const Vector2f &initial, float length) {

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

	rand() % 2 == 0 ? speedX = rand() % 3 + 3 : speedX = -(rand() % 3 + 3);
	speedY = -(rand() % 2 + 2);
}

// all change direct by using abs() to prevent too fast speed to out of window
void ballMove(CircleShape &ball, Window *window, Shape &player) {

	FloatRect playerBounds = player.getGlobalBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	static float originX = speedX;
	static float originY = speedY;
	if (!start) {
		originX = speedX;
		originY = speedY;
	}

	// out of bottom bound, reset the ball
	if (ballBounds.top > window->getSize().y) {
		start = false;
	}
	// window's right bound
	else if (ballBounds.left + ballBounds.width >= window->getSize().x) {
		speedX = -abs(speedX);
	}
	// window's left bound
	else if (ballBounds.left <= 0) {
		speedX = abs(speedX);
	}
	// window's top bound
	else if (ballBounds.top <= 0) {
		speedY = abs(speedY);
	}
	// the collision between ball and player
	else if (ballBounds.intersects(playerBounds)) {

		if (speedX == 0) {
			speedX = originX;
		}
		speedY = -abs(speedY);
		if (ball.getPosition().y <= player.getPosition().y) {
			
			// hit center range(0.485f ~ 0.515f) will reset all speed
			// right side of player position
			if (ball.getPosition().x >= playerBounds.left + playerBounds.width) {
				speedX = abs(speedX) * 1.3f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .9f) {
				speedX = abs(speedX) * 1.2f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .75f) {
				speedX = abs(speedX) * 1.15f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .515f) {
				speedX = abs(speedX) * 1.1f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .5f) {
				speedX = abs(originX);
				speedY = originY;
			}
			// left side of player position
			else if (ball.getPosition().x <= playerBounds.left) {
				speedX = -abs(speedX) * 1.3f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .1f) {
				speedX = -abs(speedX) * 1.2f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .25f) {
				speedX = -abs(speedX) * 1.15f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .485f) {
				speedX = -abs(speedX) * 1.1f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .5f) {
				speedX = -abs(originX);
				speedY = originY;
			}
			// center position
			else if (ball.getPosition().x == playerBounds.left + playerBounds.width / 2) {
				speedX = 0;
				speedY = originY;
			}
		}
		// the collision under the half of player body, if player hit the ball with edge-side,
		// it will boost 2.5X originX to speedX(rewrite speedX whether how fast current speedX are) and plus 1.25X to speedY
		else {

			if (ballBounds.left + ballBounds.width / 2 > playerBounds.left + playerBounds.width / 2) {
				speedX = abs(originX) * 2.5f;
				speedY = -abs(speedY) * 1.25f;
			}
			else if (ballBounds.left + ballBounds.width / 2 < playerBounds.left + playerBounds.width / 2) {
				speedX = -abs(originX) * 2.5f;
				speedY = -abs(speedY) * 1.25f;
			}
		}
	}
	// prevent speed too fast
	if (abs(speedX) >= abs(originX) * 10) {
		speedX = originX * 10;
	}
	else if (abs(speedY) >= abs(originY) * 10) {
		speedY = originY * 10;
	}
	ball.move(speedX, speedY);
}

// equal above
void controlBallMove(CircleShape &ball, Block &block) {

	FloatRect blockBounds = block.getBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	FloatRect leftBlock = FloatRect(Vector2f(block[0].position.x, block[0].position.y + ball.getRadius()), Vector2f(1, blockBounds.height - ball.getRadius()));
	FloatRect rightBlock = FloatRect(Vector2f(block[1].position.x, block[1].position.y + ball.getRadius()), Vector2f(-1, blockBounds.height - ball.getRadius()));
	FloatRect topBlock = FloatRect(Vector2f(block[0].position.x + ball.getRadius(), block[0].position.y), Vector2f(blockBounds.width - ball.getRadius(), 1));
	FloatRect bottomBlock = FloatRect(Vector2f(block[3].position.x + ball.getRadius(), block[3].position.y), Vector2f(blockBounds.width - ball.getRadius(), -1));

	if (ballBounds.intersects(leftBlock)) {
		speedX = -abs(speedX);
	}
	else if (ballBounds.intersects(rightBlock)) {
		speedX = abs(speedX);
	}
	if (ballBounds.intersects(topBlock)) {
		speedY = -abs(speedY);
	}
	else if (ballBounds.intersects(bottomBlock)) {
		speedY = abs(speedY);
	}
	/*static FloatRect bufferBounds = ballBounds;

	if (ballBounds.intersects(blockBounds)) {

		// obstacle left bound
		if (bufferBounds.left- blockBounds.left <= 0)  {
			speedX = -abs(speedX);
		}
		// obstacle right bound
		else if ((bufferBounds.left + bufferBounds.width) - (blockBounds.left + blockBounds.width) >= 0){
			speedX = abs(speedX);
		}
		// obstacle top bound
		else if ((bufferBounds.top + bufferBounds.height) - (blockBounds.top + bufferBounds.height) <= 0) {
			speedY = -abs(speedY);
		}
		// obstacle bottom bound
		else if ((bufferBounds.top + bufferBounds.height) - (blockBounds.top + blockBounds.height) >= 0) {
			speedY = abs(speedY);
		}
	}

	bufferBounds = ballBounds;*/
}