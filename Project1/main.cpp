#include "ellipse.h"
#include "particleSystem.h"
#include "brick.h"
#include "define.h"
#include "obstacle.h"
#include "UIFactory.h"
#include <atomic>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>

using namespace sf;
using namespace std;
using namespace item;

static queue<Event> gameEventQueue;
static mutex gameEventQueueMutex;

void renderThread(RenderWindow *window, atomic<bool> *done);
void playerMove(Shape &player, Shape &flash, float speed);

void renderThread(RenderWindow *window, atomic<bool> *done) {

	window->setActive(true);
	static float blockLength = 100.f;
	static float incre1 = 3.f;

	Obstacle obstacles(2
		, { Vector2f(blockLength, blockLength * incre1), Vector2f(STAGE_WIDTH - blockLength * 2, blockLength * incre1) }
	, { Vector2f(blockLength, blockLength * incre1), Vector2f(blockLength, blockLength * incre1) });
	obstacles.setBlockColor(0, Color::Black, Color::Blue, Color::Black, Color::Black);
	obstacles.setBlockColor(1, Color::Green, Color::Black, Color::Cyan, Color::Black);
	obstacles.setBlockSpeed(0, 1.5f);
	obstacles.setBlockSpeed(1, -1.5f);

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

	Ball ball(mainPlayer);

	Brick bricks(1, 180.f, 30.f, Vector2f(5.f, 5.f), 3.f);
	bricks.setBrickColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(183), static_cast<Uint8>(197)));

	ParticleSystem mouseLight(2000);
	Vector2i localPosition;
	Clock clock;
	Mouse::setPosition(static_cast<Vector2i>(Vector2f(STAGE_WIDTH / 2, STAGE_HEIGHT / 2)), *window);
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
				if (getEvent.mouseButton.button == Mouse::Left && !GameState::start) {
					ball.initializeBall();
					GameState::active = true;
					GameState::start = true;
				}
				else if (getEvent.mouseButton.button == Mouse::Right && GameState::start) {
					GameState::start = false;
					GameState::ready = false;
				}

			}
			else if (getEvent.type == Event::MouseLeft) {
				GameState::light = false;
			}
			else if (getEvent.type == Event::MouseEntered) {
				GameState::light = true;
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
			ball.ballEnableMove(mainPlayer, redRange, sound1);
			yellowRange.setPosition(mainPlayer.getPosition());

			if (GameState::start) {
				obstacles.enable(ball);
				bricks.enable(ball);
				if (GameState::broke) {
					GameState::ready = false;
					GameState::start = false;
					GameState::broke = false;
				}
				ball.ballMove(mainPlayer);
				if (bricks.getAreaSize() == NULL) {
					GameState::ready = false;
					GameState::start = false;
					cout << "Finished stage: " << stage++ << "!!!" << endl;
					bricks.reset(stage);
					bricks.setBrickColor(Color(static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255)));
				}
			}
			else {
				ball.followPlayer(mainPlayer);
				if (!GameState::ready) {
					obstacles.reset();
					GameState::ready = true;
				}
			}
			mouseLight.setEmitter(window->mapPixelToCoords(Mouse::getPosition(*window)));
			mouseLight.update(updateSpan);
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

	RenderWindow window(VideoMode(static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT)), "Pigject", Style::Titlebar | Style::Close, settings);
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