#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Ball {

public:
	Ball();

private:
	
	sf::CircleShape mainBall;
	std::vector <sf::CircleShape> balls;
};

