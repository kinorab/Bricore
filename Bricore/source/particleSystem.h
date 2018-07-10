#pragma once

#include "interact/container.h"

class ParticleSystem :
	public game::Container {
public:
	explicit ParticleSystem(const unsigned int count);
	void update(const float updateRatio);
	void setEmitPosition(const sf::Vector2f & position);
	void startEmit();
	void stopEmit();

protected:
	void resetParticle(size_t);

private:
	struct Particle {
		sf::Vector2f velocity;
		float fLifeTime;
	};
	bool bEmit = true;
	float fMaxLifeTime;
	sf::Vector2f emitPosition{ 0, 0 };
	std::vector<Particle> particles;
	std::shared_ptr<sf::VertexArray> vertices;
};
