#pragma once
#include "../interact/container.h"
#include "../definition/diagonalPoint.h"
#include <memory>

namespace item {
	class Brick;
}
namespace sf {
	class Color;
	class Event;
}
namespace game {
	class Level;
}
class Ball;

class Wall :
	public game::Container {
public:
	explicit Wall(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void resetCopyTarget(const std::shared_ptr<Ball> ball);
	void loadTexture(const std::string & fileName);
	void setBricksColor(const sf::Color & color);
	void setFramesColor(const sf::Color & color);
	void setBricksSize(const sf::Vector2f &sideLength);
	void setInterval(const sf::Vector2f &interval);
	void setFrameSize(const float frame);
	void resettle();

	size_t getBrickAmount() const;
	sys::DPointf getDP(const size_t number) const;
	float getFrameSize(const size_t number) const;
	const sf::Vector2f & getBrickSize(const size_t number) const;
	const sf::Color & getBrickColor(const size_t number) const;
	const sf::Vector2f & getInterval() const;
	virtual ~Wall();

protected:
	void settlePlace();

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

	std::vector<std::shared_ptr<item::Brick>> bricks;
	// bricks on every row
	size_t uAmount;
	size_t uRowCount;
	float fFrameSize;
	bool bChangeEntity;
	sf::Vector2f sideLength;
	sf::Vector2f interval;
	sf::Vector2f whiteSpace;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
};
