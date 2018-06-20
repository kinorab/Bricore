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
		virtual void setStatisticVisible(const bool visible);
		virtual void extendMaxCount(const size_t count);
		virtual bool isFull() const;
		virtual bool isExist() const;
		virtual size_t getMaxCount() const;
		virtual size_t getCurrentCount() const;
		virtual float getCountPercentage() const;
		virtual ~BarSystem();

	protected:
		BarSystem(const size_t maxCount, const bool debut, const bool numberVisible, const bool exist = true);
		virtual void setEnable(const bool enable) override;
		virtual void setExist(const bool exist);
		size_t maxCount;
		size_t currentCount;
		bool debut;

	private:
		bool statisticVisible;
		bool exist;
	};
}
