#include "definition/define.h"
#include "particleSystem.h"
#include <cmath>

using namespace sf;

constexpr float LIFETIME = 1500.f;

ParticleSystem::ParticleSystem(const unsigned int count)
	:particles(count),
	vertices(new VertexArray(Points, count)),
	maxLifeTime(LIFETIME),
	emitPosition(0, 0) {
	addChild({ vertices });
}

void ParticleSystem::setEmitPosition(const Vector2f & position) {
	emitPosition = position;
}

void ParticleSystem::update(const float & timeSpan) {
	for (size_t i = 0; i < particles.size(); ++i) {
		if (particles[i].lifeTime > 0.0f) {
			particles[i].lifeTime -= timeSpan;
		}
		else {
			if (GameState::light) {
				resetParticle(i);
			}
			else {
				particles[i].lifeTime = 0.0f;
			}
		}

		(*vertices)[i].position += particles[i].velocity * timeSpan;
		float ratio = particles[i].lifeTime / maxLifeTime;
		(*vertices)[i].color = Color(
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(ratio * 255)
		);
	}
}

void ParticleSystem::resetParticle(size_t index) {
	float angle = (rng() % 360) * PI / 180.0f;
	float speed = (rng() % 50) / 1000.0f + 0.05f;
	particles[index].velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
	particles[index].lifeTime = static_cast<float>(rand() % static_cast<int>(maxLifeTime));
	(*vertices)[index].position = emitPosition;
}
