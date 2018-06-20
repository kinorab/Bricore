#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

namespace game {
	class System {
	public:
		virtual ~System();
		virtual const bool & isEnable() const;

	protected:
		System(const bool);
		virtual void setEnable(const bool enable);
		sf::Clock clock;

	private:
		bool enable;
	};
};