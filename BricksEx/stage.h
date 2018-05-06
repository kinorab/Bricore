#pragma once
#include "container.h"

class ParticleSystem;
class Stage
	: public game::Container {
public:
	static std::shared_ptr<Stage> getInstance();
	static std::shared_ptr<Stage> getPredictInstance();
	static bool resetInstance();
	virtual ~Stage();
	virtual void update();
	virtual void updateMouseLight(float updateSpan, sf::Vector2f mousePosition);

protected:
	Stage();

private:
	Stage &operator =(const Stage &);
	static std::shared_ptr<Stage> instance;
	std::shared_ptr<ParticleSystem> mouseLight;
	virtual void onKeyPressed(game::Event * event);
	virtual void onKeyReleased(game::Event * event);
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMouseButtonPressed(game::Event * event);
};
