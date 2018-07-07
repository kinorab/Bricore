#pragma once
#include "../system.h"
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace sf {
	class Event;
}

namespace game {
	class BarSystem : public System {
	public:
		virtual void handleBar(const sf::Event * const event) = 0;
		void setStatisticVisible(const bool visible);
		void extendMaxCount(const size_t count);
		bool isFull() const;
		bool isExist() const;
		size_t getMaxCount() const;
		size_t getCurrentCount() const;
		float getCountPercentage() const;
		virtual ~BarSystem();

	protected:
		BarSystem(const size_t maxCount, const bool appear, const bool numberVisible, const bool exist = true);
		void setEnable(const bool enable);
		void setExist(const bool exist);
		void clearBar();
		bool bAppear;

	private:
		size_t uMaxCount;
		size_t uCurrentCount;
		bool bStatisticVisible;
		bool bExist;
	};
}
