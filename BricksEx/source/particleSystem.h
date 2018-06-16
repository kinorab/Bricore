#pragma once

#include "interact/container.h"

class ParticleSystem :
	public game::Container {
public:
	explicit ParticleSystem(const unsigned int count);
	virtual void setEmitPosition(const sf::Vector2f & position);
	virtual void startEmit();
	virtual void stopEmit();
	virtual void update(const float updateSpan) override;
private:
	struct Particle {
		sf::Vector2f velocity;
		float lifeTime;
	};
	virtual void resetParticle(size_t);
	bool emitting = true;
	sf::Vector2f emitPosition{ 0, 0 };
	float maxLifeTime;
	std::vector<Particle> particles;
	std::shared_ptr<sf::VertexArray> vertices;
};
