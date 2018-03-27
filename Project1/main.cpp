#include "game.h"
#include "define.h"
#include <iostream>

int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 6;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	sf::RenderWindow window(sf::VideoMode(static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT)), "Pigject", sf::Style::Close, settings);
	window.setMouseCursorVisible(false);
	window.setPosition(sf::Vector2i(window.getPosition().x, 20));
	window.setVerticalSyncEnabled(true);
	window.setActive(false);

	Game::start(window);

	// main thread wait for event and push to queue
	sf::Event event;
	while (!Game::finished && window.waitEvent(event)) {
		Game::pushEvent(event);
	}

	// finalize...
	window.close();
	system("pause");
	return 0;
}
