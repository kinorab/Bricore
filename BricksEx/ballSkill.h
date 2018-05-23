#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "skill.h"

namespace sf {
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class BallSkill :
		public Skill
		, public sf::Drawable {
	public:
		explicit BallSkill(const Ball skillName, const sf::Time &duration, const bool autoUse = false);
		static void loadFrame(const std::map<size_t, std::string> &fileNames);
		virtual void swapSkill(BallSkill &other);
		virtual void useSkill() override;
		virtual void upgradeSkill() override;
		virtual void gainSkill(const Ball skillName);
		virtual void loadSkillPicture(const std::vector<std::string> &fileName) override;

		virtual Ball getSkillName() const;
		virtual ~BallSkill();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void handleSkill() override;
		static std::map<size_t, std::shared_ptr<sf::Texture>> frames;
		enum class SkillState {
			No_Buy,			// still on store
			None,			// no appear on stage
			OnDropping,		// drop from brick
			OnMiniField,	// on ball skill smaller field
			OnField,		// on ball skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		std::map<SkillState, std::unique_ptr<sf::Texture>> statePreviews;
		struct Picture {
			SkillState currentState;
			std::unique_ptr<sf::Sprite> Frame;
			std::unique_ptr<sf::Sprite> context;
		};
		std::pair<Ball, Picture> skill;
	};
}
