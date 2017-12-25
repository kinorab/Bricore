#include "define.h"
#include "particleSystem.h"
#include <cstdlib>
#include <cmath>

ParticleSystem::ParticleSystem(unsigned int count)
	:m_particles(count), m_vertices(Points, count), m_lifetime(seconds(2)), m_emitter(0, 0) {

}// constructor

void ParticleSystem::setEmitter(Vector2f position) {

	m_emitter = position;
}// end function setEmitter

void ParticleSystem::update(Time elapsed) {

	for (size_t i = 0; i < m_particles.size(); ++i) {

		m_particles[i].lifetime -= elapsed;

		if (m_particles[i].lifetime <= Time::Zero) {

			resetParticle(i);
		}// end if

		m_vertices[i].position += m_particles[i].velocity * elapsed.asSeconds();

		float ratio = m_particles[i].lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color = Color(static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), static_cast<Uint8>(ratio * 255));
	}// end for
}// end function update

void ParticleSystem::draw(RenderTarget &target, RenderStates states) const {

	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(m_vertices, states);

}// end function draw

void ParticleSystem::resetParticle(size_t index) {

	float angle = (rand() % 360) * PI / 180.0f;
	float speed = (rand() % 50) + 50.0f;
	m_particles[index].velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
	m_particles[index].lifetime = milliseconds(rand() % 2000);
	m_vertices[index].position = m_emitter;
}// end function resetParticle