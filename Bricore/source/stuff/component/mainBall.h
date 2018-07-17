#pragma once
#include "globular.h"

namespace game {
	class GameReadyEvent;
}

namespace item {
	class MainBall :
		public Globular {
	public:
		MainBall() noexcept;
		virtual bool isCollidedObstacle(const Block * block) override;
		virtual bool isCollidedWall(const Brick * brick) override;
		void initialize();
		void resettle();

		bool isSettle() const;
		virtual ~MainBall();

	private:
		virtual void determineHitDirect() override;
		void onGameReady(game::GameReadyEvent & event);
		bool bSettle;
	};
}