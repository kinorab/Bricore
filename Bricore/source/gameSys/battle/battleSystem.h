#pragma once
#include "../system.h"

namespace game {
	class BattleSystem :
		public System {
	public:
		BattleSystem() noexcept;
		virtual ~BattleSystem();
	};
}