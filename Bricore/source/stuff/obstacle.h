#pragma once
#include "../interact/container.h"
#include "../definition/diagonalPoint.h"
#include <memory>

namespace item {
	class Block;
}

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Color;
	class Event;
}
namespace game {
	class Level;
}
class SubPlayer;
class Ball;

class Obstacle :
	public game::Container {
public:
	explicit Obstacle(const std::shared_ptr<game::Level> level);
	void resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer, const std::shared_ptr<Ball> ball);
	void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	void setBlockColor(const size_t number, const sf::Color &all);
	void setAllColor(const std::vector <sf::Color> &color);
	void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	void resetPosition();
	virtual ~Obstacle();

	size_t getBlocksAmount() const;
	sys::DPointf getDP(const size_t number) const;
	const sf::Vector2f & getSpeed(const size_t number) const;

protected:
	virtual void update(const float updateRatio) override;
	virtual void handle(const sf::Event & event) override;
	void blocksCollision(const size_t);
	void resettle();

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	std::vector <std::shared_ptr<item::Block>> blocks;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<const SubPlayer> c_subPlayer;
};