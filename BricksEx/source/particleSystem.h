#pragma once

#include "interact/container.h"

class ParticleSystem :
	public game::Container {
public:
	explicit ParticleSystem(const unsigned int count);
	void setEmitPosition(const sf::Vector2f & position);
	void update(const float updateSpan) override;
private:
	struct Particle {
		sf::Vector2f velocity;
		float lifeTime;
	};
	void resetParticle(size_t);
	std::vector<Particle> particles;
	std::shared_ptr<sf::VertexArray> vertices;
	float maxLifeTime;
	sf::Vector2f emitPosition;
};
