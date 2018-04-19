#pragma once
#include "container.h"
#include <mutex>

class ParticleSystem;
class Stage
	: public game::Container {
public:
	static std::shared_ptr<Stage> getInstance();
	virtual ~Stage();
	virtual void update(float updateSpan, sf::Vector2f mousePosition);

protected:
	Stage();

private:
	static std::shared_ptr<Stage> instance;
	static std::mutex mutex;
	static std::shared_ptr<ParticleSystem> mouseLight;
	virtual void onKeyPressed(game::Event * event);
	virtual void onKeyReleased(game::Event * event);
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMouseButtonPressed(game::Event * event);
};
