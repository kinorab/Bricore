#include "vertexArrayNode.h"
#include <SFML/Graphics.hpp>

namespace game {
	VertexArrayNode::VertexArrayNode(std::shared_ptr<sf::VertexArray> vertexArray) {
		this->vertexArray = std::move(vertexArray);
	}

	VertexArrayNode::~VertexArrayNode() {

	}

	bool VertexArrayNode::containsPoint(const sf::Vector2f & point) const {
		return vertexArray->getBounds().contains(point);
	}

	std::shared_ptr<sf::Drawable> VertexArrayNode::getDrawable() const	{
		return vertexArray;
	}
}
