#include "ellipse.h"
#include "particleSystem.h"
#include "brick.h"
#include "define.h"
#include "obstacle.h"
#include "UIFactory.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <mutex>

using namespace sf;
using namespace std;
using namespace item;

static bool start;
static bool ready;
static bool active;
static bool light;
static float ballSpeedX;
static float ballSpeedY;
static unsigned int stage = 1;
static queue<Event> gameEventQueue;
static mutex gameEventQueueMutex;

//void setItemVertices(VertexArray &, const Vector2f &, float);
void renderThread(RenderWindow *window, atomic<bool> *done);
void playerMove(Shape &player, Shape &flash, float speed);
void initializeBall();
void resetBall();
void ballMove(CircleShape &ball, Shape &player);
inline void ballEnableMove(CircleShape &ball, Shape &player, Shape &range, Sound &sound);
void flashRange(CircleShape &ball, Shape &player, Shape &range, Sound &sound, Clock &elapsed, bool &flash);
inline void flashElapsed(Shape &range, Clock &elapsed, bool &flash);

void renderThread(RenderWindow *window, atomic<bool> *done) {

	window->setActive(true);
	static float blockLength = 100.f;
	static float incre1 = 3.f;

	Obstacle obstacles(2
		, { Vector2f(blockLength, blockLength * incre1), Vector2f(STAGE_WIDTH - blockLength * 2, blockLength * incre1) }
	, { Vector2f(blockLength, blockLength * incre1), Vector2f(blockLength, blockLength * incre1) });
	obstacles.setBlockColor(0, Color::Black, Color::Blue, Color::Black, Color::Black);
	obstacles.setBlockColor(1, Color::Green, Color::Black, Color::Cyan, Color::Black);
	obstacles.setBlockSpeed(0, 1.f);
	obstacles.setBlockSpeed(1, -1.f);

	RectangleShape mainPlayer;
	mainPlayer.setSize(Vector2f(240, 12));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(STAGE_WIDTH / 2, STAGE_HEIGHT - mainPlayer.getSize().y));
	RectangleShape yellowRange;
	yellowRange.setSize(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setFillColor(Color::Yellow);
	RectangleShape redRange;
	redRange.setSize(Vector2f(yellowRange.getSize().x / 2, mainPlayer.getSize().y));
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(mainPlayer.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));

	CircleShape ball;
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(5.f);
	ball.setOutlineThickness(2.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));

	Brick bricks(1, 180.f, 30.f, Vector2f(5.f, 5.f), 3.f);
	bricks.setBrickColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(183), static_cast<Uint8>(197)));

	ParticleSystem mouseLight(2500);
	Vector2i localPosition;
	Clock clock;
	Mouse::setPosition(Vector2i(STAGE_WIDTH / 2, STAGE_HEIGHT / 2), *window);
	Sound sound1;
	Music bgmusic;
	SoundBuffer buffer1;

	static float bufferBgVolume = 100.0f;
	static float bufferVolume1 = 50.0f;

	try {
		// if memory violation happen, reset the lib connector of project (-d have something bug)
		if (!buffer1.loadFromFile("s1.wav")) {
			throw runtime_error("Cannot get the sound file.");
		}
		else if (!bgmusic.openFromFile("bg.wav")) {
			throw runtime_error("Cannot get the music file.");
		}
		sound1.setBuffer(buffer1);
		sound1.setVolume(bufferVolume1);
		bgmusic.play();
		bgmusic.setLoop(true);
	}
	catch (runtime_error  &ex) {
		cout << "Runtime_error: " << ex.what() << endl;
	}

	Time elapsed = milliseconds(0);

	while (!(*done)) {

		Event getEvent;

		while (!gameEventQueue.empty()) {

			gameEventQueueMutex.lock();
			getEvent = gameEventQueue.front();
			gameEventQueue.pop();
			gameEventQueueMutex.unlock();

			static Keyboard::Key choice;
			Vector2f GlobalPosition = Vector2f(Mouse::getPosition(*window));

			if (getEvent.type == Event::TextEntered) {
				if (getEvent.text.unicode < 128) {
					cout << "ASCII charactor typed: " << static_cast<char>(getEvent.text.unicode)
						<< ", unicode is: " << getEvent.text.unicode << endl;
				}
			}
			if (getEvent.type == Event::KeyPressed) {

				switch (getEvent.key.code) {

				case (Keyboard::Num0):
					cout << "Choice bgm volume." << endl;
					choice = Keyboard::Num0;
					break;
				case(Keyboard::Numpad0):
					cout << "Choice bgm volume." << endl;
					choice = Keyboard::Numpad0;
					break;
				case (Keyboard::Num1):
					cout << "Choice sound1 volume." << endl;
					choice = Keyboard::Num1;
					break;
				case(Keyboard::Numpad1):
					cout << "Choice sound1 volume." << endl;
					choice = Keyboard::Numpad1;
					break;
				default:
					break;
				}

				// bgm volume
				if (choice == Keyboard::Num0 || choice == Keyboard::Numpad0) {
					switch (getEvent.key.code) {
					case (Keyboard::Add):// volume up
						if (bufferBgVolume < 95.0f) {
							bgmusic.setVolume(bufferBgVolume += 5.f);
						}
						else if (bufferBgVolume >= 95.0f) {
							bgmusic.setVolume(100.0f);
						}
						else {
							cout << "Somethings bug ,cannot change the sound volume." << endl;
						}
						cout << "Now the bgm volume is : " << bgmusic.getVolume() << endl;
						break;

					case (Keyboard::Subtract):// volume down
						if (bufferBgVolume > 5.0f) {
							bgmusic.setVolume(bufferBgVolume -= 5.f);
						}
						else if (bufferBgVolume <= 5.0f) {
							bgmusic.setVolume(0.0f);
						}
						else {
							cout << "Somethings bug ,cannot change the sound volume." << endl;
						}
						cout << "Now the bgm volume is : " << bgmusic.getVolume() << endl;
						break;

					default:
						break;
					}
				}
				// sound1 volume
				else if (choice == Keyboard::Num1 || choice == Keyboard::Numpad1) {
					switch (getEvent.key.code) {
					case (Keyboard::Add):// volume up
						if (sound1.getBuffer() != NULL) {
							if (bufferVolume1 < 95.0f) {
								sound1.setVolume(bufferVolume1 += 5.f);
							}
							else {
								sound1.setVolume(100.0f);
							}
							cout << "Now the sound1 volume is : " << sound1.getVolume() << endl;
						}
						else {
							cout << "sound1.getBuffer() failed ,cannot change the sound volume." << endl;
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
							cout << "Now the sound1 volume is : " << sound1.getVolume() << endl;
						}
						else {
							cout << "sound1.getBuffer() failed ,cannot change the sound volume." << endl;
						}
						break;

					default:
						break;
					}
				}
			}


			if (getEvent.type == Event::MouseButtonPressed) {
				if (getEvent.mouseButton.button == Mouse::Left && !start) {
					initializeBall();
					active = true;
					start = true;
				}
				else if (getEvent.mouseButton.button == Mouse::Right && start) {
					start = false;
					ready = false;
				}

			}
			else if (getEvent.type == Event::MouseLeft) {
				light = false;
			}
			else if (getEvent.type == Event::MouseEntered) {
				light = true;
			}

			if (getEvent.type == Event::Closed) {
				bgmusic.stop();
				sound1.stop();
				*done = true;
			}
			/*	else if (getEvent.type == Event::Resized) {
					FloatRect viewResized(0, 0, getEvent.size.width, getEvent.size.height);
					float bufferViewX = window->getView().getSize().x;
					float bufferViewY = window->getView().getSize().y;
					// need some window control, all item need to maintain initial proportion
					window->setView(View(viewResized));
					// item scale increment rateX
					float rateX = window->getView().getSize().x / bufferViewX;
					// item scale increment rateY
					float rateY = window->getView().getSize().y / bufferViewY;
				}*/
		}

		// update fixed 5 frames
		elapsed += clock.restart();
		if (elapsed.asSeconds() > 0.05f) {
			elapsed = seconds(0.05f);
		}

		// updateSpan: milliseconds
		static constexpr float updateSpan = 10.0f;
		while (elapsed.asSeconds() * 1000.0f > updateSpan) {
			playerMove(mainPlayer, redRange, PLAYERSPEED);
			ballEnableMove(ball, mainPlayer, redRange, sound1);
			yellowRange.setPosition(mainPlayer.getPosition());
			if (start) {

				obstacles.enable(ball, ballSpeedX, ballSpeedY);
				bricks.collisionBroke(ball, ballSpeedX, ballSpeedY);
				ballMove(ball, mainPlayer);
				if (bricks.getAreaSize() == NULL) {
					ready = false;
					start = false;
					cout << "Finished stage: " << stage++ << "!!!" << endl;
					bricks.reset(stage);
					bricks.setBrickColor(Color(static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255)));
				}
			}
			else {
				ball.setPosition(mainPlayer.getPosition().x, mainPlayer.getGlobalBounds().top - ball.getLocalBounds().height / 2);
				if (!ready) {
					obstacles.reset();
					ready = true;
				}
			}
			mouseLight.setEmitter(window->mapPixelToCoords(Mouse::getPosition(*window)));
			mouseLight.update(updateSpan, light);
			elapsed -= seconds(updateSpan / 1000.0f);
		}

		// render
		window->clear(Color::White);
		window->draw(obstacles);
		window->draw(mainPlayer);
		window->draw(yellowRange);
		window->draw(redRange);
		window->draw(ball);
		window->draw(bricks);
		window->draw(mouseLight);
		window->display();
	}
	// finalize...
}

int main() {
	ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 6;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	RenderWindow window(VideoMode(GAME_WIDTH, GAME_HEIGHT), "Pigject", Style::Titlebar | Style::Close, settings);
	window.setMouseCursorVisible(false);
	window.setPosition(Vector2i(window.getPosition().x, 20));
	window.setVerticalSyncEnabled(true);
	window.setActive(false);
	atomic <bool> done(false);
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
	return 0;
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

void playerMove(Shape &player, Shape &flash, float speed) {

	FloatRect playerBound = player.getGlobalBounds();
	if (playerBound.left > 0
		&& (Keyboard::isKeyPressed(Keyboard::Left))
		) {
		player.move(Vector2f(-abs(speed), 0));
		flash.move(Vector2f(-abs(speed), 0));
	}

	if (playerBound.left + playerBound.width < STAGE_WIDTH
		&& (Keyboard::isKeyPressed(Keyboard::Right))
		) {
		player.move(Vector2f(abs(speed), 0));
		flash.move(Vector2f(abs(speed), 0));
	}
}

void initializeBall() {

	ballSpeedX = (rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1);
	ballSpeedY = 2.f;
}

void resetBall() {

	ballSpeedX = (rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1);
	ballSpeedY = 2.f * (rng() % 100 < 50 ? 1 : -1);
}

// all change direct by using abs() to prevent too fast speed to stuck outside the window
void ballMove(CircleShape &ball, Shape &player) {

	FloatRect playerBounds = player.getGlobalBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	static float originX = ballSpeedX;
	static float originY = ballSpeedY;
	static Clock countTime;
	// when left mouse click will only set initial speed once
	if (active) {
		originX = ballSpeedX;
		originY = ballSpeedY;
		countTime.restart();
		active = false;
	}
	else if (countTime.getElapsedTime().asSeconds() > RESETTIME && start) {
		// preserve last speed then add 60% extra origin speed to new speed
		float tempX = ballSpeedX;
		float tempY = ballSpeedY;
		resetBall();
		originX = ballSpeedX;
		originY = ballSpeedY;
		ballSpeedX >= 0 ? ballSpeedX += (abs(tempX) - ballSpeedX) * .6f
			: ballSpeedX += -(abs(tempX) + ballSpeedX) * .6f;
		ballSpeedY >= 0 ? ballSpeedY += (abs(tempY) - ballSpeedY) * .6f
			: ballSpeedY += -(abs(tempY) + ballSpeedY) * .6f;
		countTime.restart();
	}

	// out of bottom bound, reset the ball
	if (ballBounds.top > STAGE_HEIGHT) {
		start = false;
		ready = false;
	}
	// window's right bound
	else if (ballBounds.left + ballBounds.width >= STAGE_WIDTH) {
		ballSpeedX = -abs(ballSpeedX);
	}
	// window's left bound
	else if (ballBounds.left <= 0) {
		ballSpeedX = abs(ballSpeedX);
	}
	// window's top bound
	else if (ballBounds.top <= 0) {
		ballSpeedY = abs(ballSpeedY);
	}
	// the collision between ball and player
	else if (ballBounds.intersects(playerBounds)) {

		countTime.restart();
		if (ballSpeedX == 0.0f) {
			ballSpeedX = originX;
		}

		ballSpeedY = -abs(ballSpeedY);
		if (ball.getPosition().y <= player.getPosition().y) {

			// right side of player position
			if (ball.getPosition().x >= playerBounds.left + playerBounds.width) {
				ballSpeedX = abs(ballSpeedX) * 1.2f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .9f) {
				ballSpeedX = abs(ballSpeedX) * 1.15f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .75f) {
				ballSpeedX = abs(ballSpeedX) * 1.1f;
			}
			else if (ball.getPosition().x > playerBounds.left + playerBounds.width * .55f) {
				ballSpeedX = abs(ballSpeedX) * 1.05f;
			}
			// left side of player position
			else if (ball.getPosition().x <= playerBounds.left) {
				ballSpeedX = -abs(ballSpeedX) * 1.2f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .1f) {
				ballSpeedX = -abs(ballSpeedX) * 1.15f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .25f) {
				ballSpeedX = -abs(ballSpeedX) * 1.1f;
			}
			else if (ball.getPosition().x < playerBounds.left + playerBounds.width * .45f) {
				ballSpeedX = -abs(ballSpeedX) * 1.05f;
			}
			// hit center range(0.45f ~ 0.55f) will reset all speed, ballSpeedX will not change direct
			// center position
			else if (ball.getPosition().x == playerBounds.left + playerBounds.width / 2) {
				ballSpeedX = 0.0f;
				ballSpeedY = -abs(originY);
			}
			else {
				ballSpeedX < 0 ? ballSpeedX = -abs(originX) : ballSpeedX = abs(originX);
				ballSpeedY = -abs(originY);
			}
		}
		// the collision under the half of player body
		else {

			// first hit
			if (abs(ballSpeedX) < BOOST) {
				if (ball.getPosition().x > playerBounds.left + playerBounds.width / 2) {
					ballSpeedX = BOOST;
				}
				else if (ball.getPosition().x < playerBounds.left + playerBounds.width / 2) {
					ballSpeedX = -BOOST;
				}
			}
			// after first hit
			else {
				if (ball.getPosition().x > playerBounds.left + playerBounds.width / 2) {
					ballSpeedX = abs(ballSpeedX) * .6f * BOOST;
				}
				else if (ball.getPosition().x < playerBounds.left + playerBounds.width / 2) {
					ballSpeedX = -abs(ballSpeedX) * .6f * BOOST;
				}
			}
			ballSpeedY = -abs(ballSpeedY) * 1.1f;
		}

		// prevent speed too fast
		if (abs(ballSpeedX) >= MAXSPEED) {
			if (ball.getPosition().x > player.getPosition().x) {
				ballSpeedX = MAXSPEED;
			}
			else if (ball.getPosition().x < player.getPosition().x) {
				ballSpeedX = -MAXSPEED;
			}
			else {
				ballSpeedX < 0 ? ballSpeedX = MAXSPEED : ballSpeedX = -MAXSPEED;
			}
		}
		else if (abs(ballSpeedY) >= abs(originY) * 5) {
			ballSpeedY = -abs(originY) * 5;
		}
	}

	ball.move(ballSpeedX, ballSpeedY);
}

inline void ballEnableMove(CircleShape &ball, Shape &player, Shape &range, Sound &sound) {// can add extra affect

	static Clock elapsed;
	static float time;
	static bool flash = false;
	if (start) {
		flashRange(ball, player, range, sound, elapsed, flash);
	}

	if (flash) {
		flashElapsed(range, elapsed, flash);
	}
}

void flashRange(CircleShape &ball, Shape &player, Shape &range, Sound &sound, Clock &elapsed, bool &flash) {

	FloatRect playerBounds = player.getGlobalBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	FloatRect rangeBounds = range.getGlobalBounds();

	if (ballBounds.intersects(playerBounds)) {
		elapsed.restart();
		sound.play();
		if (ballBounds.left <= playerBounds.left) {
			range.setPosition(playerBounds.left + rangeBounds.width / 2, player.getPosition().y);
		}
		else if (ballBounds.left + ballBounds.width >= playerBounds.left + playerBounds.width) {
			range.setPosition(playerBounds.left + playerBounds.width - rangeBounds.width / 2, player.getPosition().y);
		}
		else {
			range.setPosition(ball.getPosition().x, player.getPosition().y);
		}
		flash = true;
	}

}

inline void flashElapsed(Shape &range, Clock &elapsed, bool &flash) {

	float time = elapsed.getElapsedTime().asMilliseconds();
	if (time <= 1500.f) {
		float rate = (1.f - time / 1500.f);
		range.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(rate * 255)));
	}
	else {
		flash = false;
	}
}