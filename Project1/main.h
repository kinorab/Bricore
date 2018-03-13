#pragma once

#include <atomic>
#include <SFML/Graphics.hpp>

void renderThread(sf::RenderWindow * window, std::atomic<bool> * done);
void handleKeyEvent(sf::Event & event);
void handleMouseEvent(sf::Event & event);
int main();