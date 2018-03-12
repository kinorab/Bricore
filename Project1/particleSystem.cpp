#include "define.h"
#include "particleSystem.h"
#include <cmath>

using namespace std;
using namespace sf;

ParticleSystem::ParticleSystem(const unsigned int count)
	:particles(count), vertices(Points, count), lifetime(LIFETIME), emitPosition(0, 0) {

}

void ParticleSystem::setEmitPosition(const Vector2f &position) {
	emitPosition = position;
}

void ParticleSystem::update(const float &timeSpan) {

	for (size_t i = 0; i < particles.size(); ++i) {

		if (particles[i].lifetime > 0.0f) {
			particles[i].lifetime -= timeSpan;
		}
		else {
			if (GameState::light) {
				resetParticle(i);
			}
			else {
				particles[i].lifetime = 0.0f;
			}
		}

		vertices[i].position += particles[i].velocity * timeSpan;
		float ratio = particles[i].lifetime / lifetime;

		vertices[i].color = Color(
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(rng() % 256),
			static_cast<Uint8>(ratio * 255)
		);
	}
}

void ParticleSystem::draw(RenderTarget &target, RenderStates states) const {

	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(vertices, states);
}

void ParticleSystem::resetParticle(size_t index) {

	float angle = (rng() % 360) * PI / 180.0f;
	float speed = (rng() % 50) / 1000.0f + 0.05f;
	particles[index].velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
	particles[index].lifetime = static_cast<float>(rand() % static_cast<int>(lifetime));
	vertices[index].position = emitPosition;
}
