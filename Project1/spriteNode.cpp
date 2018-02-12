#include "spriteNode.h"

SpriteNode::SpriteNode(std::unique_ptr<sf::Drawable> sprite)
	:sprite(std::move(sprite)) {
}

SpriteNode::~SpriteNode() {

}

void SpriteNode::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(*sprite);
}
