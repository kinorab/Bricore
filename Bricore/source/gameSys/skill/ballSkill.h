#pragma once
#include "skillKind.h"
#include "skillState.h"
#include "skillSystem.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
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

	class BallSkill :
		public SkillSystem
		, public SkillKind<BallSkill>
		, public SkillState<BallSkill>
		, public std::enable_shared_from_this<BallSkill>
		, public InteractiveObject {
		friend class SkillHandler<BallSkill>;
	public:
		explicit BallSkill(const Kind skillName, const sf::Time duration
			, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
			, const bool exist, const Player * player);
		virtual void initialize() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);
		void setOwnToPlayer(const bool giveOwn);
		static void extendField(size_t number);
		static void extendDropping(size_t number);

		static size_t getMaxDropping();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		bool isOwnToPlayer() const;
		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		const sf::Vector2f & getPosition() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		virtual ~BallSkill();

	protected:
		struct SkillContent {
			Kind name;
			State currentState;
			std::shared_ptr<sf::Sprite> frame;
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
		void swapSkill(const std::shared_ptr<BallSkill> & other);

		static size_t uMaxDropping;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static std::map<int, std::string> frameFileNames;
		static std::map<Kind, std::map<State, std::string>> fileNames;
		static SkillHandler<BallSkill> handler;
		bool bInitialize;
		sf::Vector2f origin;
		SkillContent skill;
		const Player * c_player;
	};
}
