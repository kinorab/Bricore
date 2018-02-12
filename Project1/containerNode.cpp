#include "containerNode.h"
#include <algorithm>

ContainerNode::ContainerNode() {
}

ContainerNode::~ContainerNode()
{
}

void ContainerNode::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	std::for_each(children.begin(), children.end(),
		[&](const std::unique_ptr<SceneNode> & child) {
		target.draw(*child, getTransform());
	});
}

void ContainerNode::addChild(SceneNode * child)
{
}

