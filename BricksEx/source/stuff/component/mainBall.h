#pragma once
#include "globular.h"

namespace item {
	class MainBall :
		public Globular {
	public:
		MainBall();
		virtual bool isCollidedObstacle(const Block * block) override;
		virtual bool isCollidedWall(const Brick * brick) override;
		virtual void initialize();
		virtual void resettle();
		virtual bool isSettle() const;
		virtual ~MainBall();

	private:
		virtual void determineUpdate() override;
		bool settle;
	};
}