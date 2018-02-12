#pragma once

#include <memory>
#include <vector>
#include "sceneNode.h"

class ContainerNode :
	public SceneNode {
public:
	ContainerNode();
	~ContainerNode() override;
	void addChild(SceneNode * child);
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	std::vector<std::unique_ptr<SceneNode>> children;
};

