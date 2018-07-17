#pragma once
#include "../interact/container.h"
#include "../definition/diagonalPoint.h"
#include "../event/game/gameEvent.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Event;
	class Color;
}
namespace item {
	class MainBall;
	class ShadowBall;
	class Globular;
	class Block;
	class Brick;
}
namespace game {
	class Level;
}
class Player;
class SubPlayer;

class Ball :
	public game::Container {
public:
	explicit Ball(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void resetCopyTarget(const std::shared_ptr<const Player> player, const std::shared_ptr<const SubPlayer> subPlayer);
	void initializeBall();
	void ballDivided(const size_t numbers);
	bool isMainBallBroken() const;
	// return the balls of entered obstacleArea
	std::vector<std::shared_ptr<item::Globular>> enteredObstacleArea() const;
	// return the balls of entered wallArea
	std::vector<std::shared_ptr<item::Globular>> enteredWallArea() const;

	float getMainBallRadius() const;
	size_t getBallsAmount() const;
	const sf::Vector2f & getMainBallPosition() const;
	virtual ~Ball();

protected:
	void ballsCollision(const size_t);
	void onGameReady(game::GameReadyEvent & event);
	void onGameFinishedLevel(game::GameFinishedLevelEvent & event);
	void followPlayer();

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	bool bMultiple;
	bool bCollision;
	std::shared_ptr<item::MainBall> mainBall;
	std::vector<std::shared_ptr<item::ShadowBall>> shadowBalls;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<const Player> c_player;
	std::shared_ptr<const SubPlayer> c_subPlayer;
};
