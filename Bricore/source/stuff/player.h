#pragma once
#include "../event/game/gameEvent.h"
#include "../event/keyboard/keyEvent.h"
#include "../event/mouse/mouseEvent.h"
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
	enum class SkillSelect {
		_Ball,
		_Player
	};
	struct ControlKey {
		sf::Keyboard::Key leftMove;						// control defender left move
		sf::Keyboard::Key rightMove;					// control defender right move
		sf::Keyboard::Key shot;							// control defender choose ball shot direct
		sf::Keyboard::Key ballSkill;					// control defender use ball skill
		sf::Keyboard::Key ballSkillSwap;				// control defender swap ball skill(first and second field)
		sf::Keyboard::Key playerSkill;					// control defender use player skill
		sf::Keyboard::Key playerSkillSwap;				// control defender swap player skill(first and second field)
		sf::Keyboard::Key switchToPrevChargingSkill;	// control defender switch to previous order skill
		sf::Keyboard::Key switchToNextChargingSkill;	// control defender switch to next order skill 
	};
	explicit Player(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer, const std::shared_ptr<Ball> ball);
	void setPlayerControlKey(const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
		, const sf::Keyboard::Key shot, const sf::Keyboard::Key playerSkill
		, const sf::Keyboard::Key playerSkillSwap, const sf::Keyboard::Key ballSkill
		, const sf::Keyboard::Key ballSkillSwap, const sf::Keyboard::Key switchToPrevChargingSkill
		, const sf::Keyboard::Key switchToNextChargingSkill);
	void changeModel(const Model model);
	void addPlayerSkill(game::PlayerSkill && playerSkill);
	void addBallSkill(game::BallSkill && ballSkill);

	bool isAutoUse(const SkillSelect select) const;
	float getSpeed() const;
	Model getModel() const;
	sys::DPointf getDP() const;
	sf::Vector2f getTopCenterPos() const;
	sf::FloatRect getGlobalBounds() const;
	const ControlKey & getKey() const;
	const sf::Vector2f & getPosition() const;
	virtual ~Player();

protected:
	struct BoardFile {
		std::string board;
		std::string absorbEngine;
		std::string hitLight;
	};
	struct PlayerContent {
		Model currentModel = Model::Classic;
		std::shared_ptr<sf::RectangleShape> board;			// defender's core
		std::shared_ptr<sf::RectangleShape> absorbEngine;	// absort ball's energy to defender
		std::shared_ptr<sf::RectangleShape> hitLight;		// hit to ball will reflect light on board
		std::vector<std::shared_ptr<game::PlayerSkill>> playerSkills;
		std::vector<std::shared_ptr<game::BallSkill>> ballSkills;
	};
	void onGameStarted(game::GameStartedEvent & event);
	void onGameReady(game::GameReadyEvent & event);
	void onGameFinishedLevel(game::GameFinishedLevelEvent & event);
	void onGamePrepared(game::GamePreparedEvent & event);
	void onKeyPressed(game::KeyPressedEvent & event);
	void onMousePressed(game::MousePressedEvent & event);
	void setAutoUse(const SkillSelect skill, const bool isAutoUse);
	void setFlashPosition(const sf::Vector2f & position);
	void setFlashFillColor(const sf::Color & color);
	void flashElapsed();
	void resetFlash();
	void flashRange(const sf::Vector2f ballPos, const float radius);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void defaultKeySettle();

	static std::map<Model, BoardFile> modelFileNames;
	bool bFlash;
	bool bFlashCD;
	float fSpeed;
	sf::Clock CDTime;
	sf::Clock elapsed;
	PlayerContent defender;
	std::shared_ptr<game::EnergyBar> energyBar;
	const std::shared_ptr<ControlKey> key;
	std::map<SkillSelect, bool> autoUse;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<const SubPlayer> c_subPlayer;
};

