#pragma once
#include "../interact/container.h"
#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace sf {
	class Sound;
	class RenderTarget;
	class RenderStates;
	class Color;
	class Event;
}
namespace game {
	class Level;
	class PlayerSkill;
	class BallSkill;
	class EnergyBar;
}
class Ball;
class SubPlayer;

class Player :
	public game::Container {
public:
	explicit Player(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void handle(const sf::Event & event);
	void resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer, const std::shared_ptr<Ball> ball);
	void setPlayerControlKey(const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
		, const sf::Keyboard::Key shot, const sf::Keyboard::Key playerSkill
		, const sf::Keyboard::Key playerSkillSwap, const sf::Keyboard::Key ballSkill
		, const sf::Keyboard::Key ballSkillSwap, const sf::Keyboard::Key switchToPrevChargingSkill
		, const sf::Keyboard::Key switchToNextChargingSkill);
	void addPlayerSkill(game::PlayerSkill && playerSkill);
	void addBallSkill(game::BallSkill && ballSkill);

	float getSpeed() const;
	const sf::Vector2f & getPosition() const;
	sf::Vector2f getTopCenterPos() const;
	sf::FloatRect getGlobalBounds() const;
	sys::DPointf getDP() const;
	virtual ~Player();

protected:
	void setFlashPosition(const sf::Vector2f &);
	void setFlashFillColor(const sf::Color &);
	void flashElapsed();
	void flashRange(sf::Sound & sound, const sf::Vector2f ballPos, const float radius);
	struct ControlKey {
		sf::Keyboard::Key leftMove;
		sf::Keyboard::Key rightMove;
		sf::Keyboard::Key shot;
	};

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	virtual void defaultKeySettle();

	bool bFlash;
	bool bFlashCD;
	float fSpeed;
	ControlKey key;
	sf::Clock CDTime;
	sf::Clock elapsed;
	std::shared_ptr<sf::RectangleShape> board;
	std::shared_ptr<sf::RectangleShape> redRange;
	std::shared_ptr<sf::RectangleShape> yellowRange;
	std::shared_ptr<game::EnergyBar> energyBar;
	std::vector<std::shared_ptr<game::PlayerSkill>> playerSkills;
	std::vector<std::shared_ptr<game::BallSkill>> ballSkills;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<const SubPlayer> c_subPlayer;
};

