#pragma once

#include <memory>
#include "sceneNode.h"

class SpriteNode :
	public SceneNode {
public:
	SpriteNode(std::unique_ptr<sf::Drawable> sprite);
	~SpriteNode() override;
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	std::unique_ptr<sf::Drawable> sprite;
};