#include "definition/gameState.h"
#include "definition/utility.h"
#include "particleSystem.h"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

constexpr float LIFETIME = 1500.f;

ParticleSystem::ParticleSystem(const unsigned int count)
	: particles(count)
	, vertices(new VertexArray(Points, count))
	, fMaxLifeTime(LIFETIME) {
	addChild({ vertices });
}

void ParticleSystem::setEmitPosition(const Vector2f & position) {
	emitPosition = position;
}

void ParticleSystem::startEmit() {
	bEmit = true;
}

void ParticleSystem::stopEmit() {
	bEmit = false;
}

void ParticleSystem::update(const float updateRatio) {
	float span = 15 * updateRatio;
	for (size_t i = 0; i < particles.size(); ++i) {
		if (particles[i].fLifeTime > 0.0f) {
			particles[i].fLifeTime -= span;
		}
		else if (bEmit){
			resetParticle(i);
		}
		else {
			particles[i].fLifeTime = 0.0;
		}

		(*vertices)[i].position += particles[i].velocity * span;
		float ratio = particles[i].fLifeTime / fMaxLifeTime;
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
	particles[index].fLifeTime = static_cast<float>(rand() % static_cast<int>(fMaxLifeTime));
	(*vertices)[index].position = emitPosition;
}
