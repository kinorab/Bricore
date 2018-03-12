#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem :
	public sf::Drawable,
	public sf::Transformable {

public:

	explicit ParticleSystem(const unsigned int count);

	void setEmitPosition(const sf::Vector2f &position);
	void update(const float &timeSpan);

private:

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void resetParticle(size_t);

	struct Particle {
		sf::Vector2f velocity;
		float lifetime;
	};
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	float lifetime;
	sf::Vector2f emitPosition;
};
