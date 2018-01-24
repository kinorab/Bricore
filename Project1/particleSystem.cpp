#include "define.h"
#include "particleSystem.h"
#include <cmath>

ParticleSystem::ParticleSystem(unsigned int count)
	:m_particles(count), m_vertices(Points, count), m_lifetime(LIFETIME), m_emitter(0, 0) {

}

void ParticleSystem::setEmitter(Vector2f position) {
	m_emitter = position;
}

void ParticleSystem::update(const float &timeSpan, const bool &light) {

	for (size_t i = 0; i < m_particles.size(); ++i) {

		if (m_particles[i].lifetime > 0.0f) {
			m_particles[i].lifetime -= timeSpan;
		}
		else {
			if (light) {
				resetParticle(i);
			}
			else {
				m_particles[i].lifetime = 0.0f;
			}
		}

		m_vertices[i].position += m_particles[i].velocity * timeSpan;
		float ratio = m_particles[i].lifetime / m_lifetime;

		m_vertices[i].color = Color(
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
	target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(size_t index) {

	float angle = (rng() % 360) * PI / 180.0f;
	float speed = (rng() % 50) / 1000.0f + 0.05f;
	m_particles[index].velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
	m_particles[index].lifetime = static_cast<float>(rand() % static_cast<int>(m_lifetime));
	m_vertices[index].position = m_emitter;
}
