#pragma once
#include "globular.h"

namespace item {
	class MainBall :
		public Globular {
	public:
		MainBall();
		virtual bool isCollidedObstacle(const Block * block) override;
		virtual bool isCollidedWall(const Brick * brick) override;
		void initialize();
		void resettle();

		bool isSettle() const;
		virtual ~MainBall();

	private:
		virtual void determineHitDirect() override;
		bool bSettle;
	};
}