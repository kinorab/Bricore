#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable {

public:

	explicit ParticleSystem(const unsigned int count);

	void setEmitter(const sf::Vector2f &position);
	void update(const float &timeSpan, const bool &light);

private:

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void resetParticle(size_t);

	struct Particle {
		sf::Vector2f velocity;
		float lifetime;
	};
	std::vector<Particle>m_particles;
	sf::VertexArray m_vertices;
	float m_lifetime;
	sf::Vector2f m_emitter;
};
