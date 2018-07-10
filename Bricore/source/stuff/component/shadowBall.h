#pragma once
#include "globular.h"

namespace item {
	class MainBall;

	class ShadowBall :
		public Globular  {
	public:
		explicit ShadowBall(const MainBall * main);
		virtual bool isCollidedObstacle(const Block * block) override;
		virtual bool isCollidedWall(const Brick * brick) override;
		virtual ~ShadowBall();

	private:
		virtual void determineHitDirect() override;
		const MainBall * c_main;
	};
}