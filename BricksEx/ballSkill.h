#pragma once
#include "skill.h"
#include "effect.h"
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Texture;
	class Sprite;
}

namespace game {
	class BallSkill :
		public Skill
		, public sf::Drawable
		, public sf::Transformable {
	public:
		enum class SkillState {
			No_Buy,			// still on store
			None,			// no appear on stage
			OnDropping,		// drop from brick
			OnMiniField,	// on ball skill smaller field
			OnField,		// on ball skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		explicit BallSkill(const Ball skillName, const std::vector<NormalEffect> &normalEffects, const sf::Time &duration, const bool autoUse = false);
		static void loadFrame(const std::map<size_t, std::string> &fileNames);
		virtual void swapSkill(BallSkill &other);
		virtual void useSkill() override;
		virtual void upgradeSkill() override;
		virtual void loadSkillPicture(const std::map<SkillState, std::string> &fileName, const bool isSmooth = false);
		virtual void setState(const SkillState state);

		virtual SkillState getState() const;
		virtual Ball getSkillName() const;
		virtual ~BallSkill();
	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void handleSkill() override;
		static std::map<size_t, std::shared_ptr<sf::Texture>> frames;

		std::map<SkillState, std::shared_ptr<sf::Texture>> statePreviews;
		struct Picture {
			SkillState currentState;
			std::shared_ptr<sf::Sprite> frame;
			std::shared_ptr<sf::Sprite> context;
		};
		std::pair<Ball, Picture> skill;
	};
}
