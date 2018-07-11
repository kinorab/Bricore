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
	enum Model {
		Classic,
	};
	enum SkillChoose {
		_Ball, 
		_Player
	};
	struct BoardFile {
		std::string board;
		std::string absorbEngine;
		std::string hitLight;
	};
	explicit Player(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void handle(const sf::Event & event);
	void resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer, const std::shared_ptr<Ball> ball);
	void setPlayerControlKey(const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
		, const sf::Keyboard::Key shot, const sf::Keyboard::Key playerSkill
		, const sf::Keyboard::Key playerSkillSwap, const sf::Keyboard::Key ballSkill
		, const sf::Keyboard::Key ballSkillSwap, const sf::Keyboard::Key switchToPrevChargingSkill
		, const sf::Keyboard::Key switchToNextChargingSkill);
	void loadPlayerModelPreview(const std::map<Model, BoardFile> & fileName, const bool isSmooth = false);
	void changeModel(const Model model);
	void addPlayerSkill(game::PlayerSkill && playerSkill);
	void addBallSkill(game::BallSkill && ballSkill);
	void setAutoUse(const SkillChoose skill, const bool autoUse);

	float getSpeed() const;
	const sf::Vector2f & getPosition() const;
	sf::Vector2f getTopCenterPos() const;
	sf::FloatRect getGlobalBounds() const;
	sys::DPointf getDP() const;
	Model getModel() const;
	virtual ~Player();

protected:
	void setFlashPosition(const sf::Vector2f & position);
	void setFlashFillColor(const sf::Color & color);
	void flashElapsed();
	void flashRange(const sf::Vector2f ballPos, const float radius);
	struct ControlKey {
		sf::Keyboard::Key leftMove;
		sf::Keyboard::Key rightMove;
		sf::Keyboard::Key shot;
	};
	struct BoardTexture {
		std::shared_ptr<sf::Texture> board;
		std::shared_ptr<sf::Texture> absorbEngine;
		std::shared_ptr<sf::Texture> hitLight;
	};
	struct PlayerContent {
		Model currentModel;
		std::shared_ptr<sf::RectangleShape> board;
		std::shared_ptr<sf::RectangleShape> absorbEngine;
		std::shared_ptr<sf::RectangleShape> hitLight;
		std::vector<std::shared_ptr<game::PlayerSkill>> playerSkills;
		std::vector<std::shared_ptr<game::BallSkill>> ballSkills;
	};

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void defaultKeySettle();

	bool bFlash;
	bool bFlashCD;
	float fSpeed;
	ControlKey key;
	sf::Clock CDTime;
	sf::Clock elapsed;
	PlayerContent defender;
	std::map<Model, std::shared_ptr<BoardTexture>> modelPreviews;
	std::shared_ptr<game::EnergyBar> energyBar;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<const SubPlayer> c_subPlayer;
};

