#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

namespace game {
	class System {
	public:
		virtual ~System();
		const bool & isEnable() const;

	protected:
		explicit System(const bool enable);
		void setEnable(const bool enable);
		sf::Clock clock;

	private:
		bool bEnable;
	};
};