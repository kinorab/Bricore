#pragma once
#include "../interact/container.h"
#include "../gameSys/item/chip.h"
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Event;
}
namespace game {
	class Level;
	class SubPlayerSkill;
	class EnergyBar;
	class LifeBar;
}
class Player;
class Ball;

class SubPlayer :
	public game::Container {
public:
	enum Type {
		Prototype,
	};
	explicit SubPlayer(const std::shared_ptr<game::Level> level);
	void update(const float updateRatio);
	void resetCopyTarget(const std::shared_ptr<const Player> player, const std::shared_ptr<Ball> ball);
	void setSubPlayerControlKey(const sf::Keyboard::Key upMove, const sf::Keyboard::Key downMove
		, const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
		, const sf::Keyboard::Key attack, const sf::Keyboard::Key subSkill
		, const sf::Keyboard::Key subSkillSwap, const sf::Keyboard::Key turnSkillToTypeSkill
		, const sf::Keyboard::Key switchToPrevChargingSkill, const sf::Keyboard::Key switchToNextChargingSkill);
	void changeType(const item::Chip::Kind chip);
	void addSubPlayerSkill(game::SubPlayerSkill && subPlayerSkill);
	static void loadChipPreviews(const std::map<item::Chip::Kind, std::string> & fileName
		, const bool isSmooth = false);

	Type getType() const;
	item::Chip::Kind getChip() const;
	virtual ~SubPlayer();

protected:
	struct ControlKey {
		sf::Keyboard::Key upMove;
		sf::Keyboard::Key downMove;
		sf::Keyboard::Key leftMove;
		sf::Keyboard::Key rightMove;
		sf::Keyboard::Key attack;
	};
	struct Part {
		std::shared_ptr<sf::Sprite> context;
	};
	struct SubPlayerContent {
		Type currentType = Type::Prototype;
		std::shared_ptr<item::Chip> chip;
		std::map<std::string, Part> parts;
	};

private:
	void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void defaultKeySettle();
	static std::map<item::Chip::Kind, std::shared_ptr<sf::Texture>> chipPreviews;

	ControlKey key;
	SubPlayerContent pioneer;
	std::shared_ptr<game::EnergyBar> energyBar;
	std::shared_ptr<game::LifeBar> lifeBar;
	std::vector<std::shared_ptr<game::SubPlayerSkill>> subPlayerSkills;
	std::shared_ptr<game::Level> m_level;
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<const Player> c_player;
};