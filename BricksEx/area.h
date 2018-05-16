#pragma once
#include <memory>
#include <vector>

namespace game {
	class Effect;

	class Area {
	public:
		enum class Item {

		};
		virtual void update();
		virtual ~Area();
	private:
		std::vector<std::unique_ptr<Effect>> areaEffects;
		std::vector<std::unique_ptr<Item>> areaItem;
	};
}