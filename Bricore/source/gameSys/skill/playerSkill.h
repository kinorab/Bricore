#pragma once
#include "skillKind.h"
#include "skillState.h"
#include "skillSystem.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Window/Keyboard.hpp>
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Texture;
	class Sprite;
}
class Player;

namespace game {
	template<typename T> class SkillHandler;
	class EnergyBar;

	class PlayerSkill :
		public SkillSystem
		, public SkillKind<PlayerSkill>
		, public SkillState<PlayerSkill>
		, public std::enable_shared_from_this<PlayerSkill>
		, public InteractiveObject {
		friend class SkillHandler<PlayerSkill>;
	public:
		explicit PlayerSkill(const Kind skillName, const sf::Time duration
			, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
			, const bool exist, const std::shared_ptr<EnergyBar> energyBar, const Player * player);
		virtual void initialize() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);
		void setOwnToPlayer(const bool giveOwn);
		static void extendCarry(const size_t number);
		static void extendField(const size_t number);

		static size_t getMaxCarry();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		bool isOwnToPlayer() const;
		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		virtual ~PlayerSkill();

	protected:
		struct SkillContent {
			Kind name;
			State currentState;
			std::shared_ptr<sf::Sprite> context;
		};
		void onKeyPressed(KeyPressedEvent & event);
		void onMousePressed(MousePressedEvent & event);
		void onGameStarted(GameStartedEvent & event);
		void onGameReady(GameReadyEvent & event);
		void onGameFinishedLevel(GameFinishedLevelEvent & event);
		void onGamePrepared(GamePreparedEvent & event);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void update() override;
		void setState(const State nextState);
		void swapSkill(const std::shared_ptr<PlayerSkill> & other);

		static size_t uMaxCarry;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static SkillHandler<PlayerSkill> handler;
		static std::map<Kind, std::map<State, std::string>> fileNames;
		bool bInitialize;
		sf::Vector2f origin;
		SkillContent skill;
		std::shared_ptr<EnergyBar> m_energyBar;
		const Player * c_player;
	};
}
