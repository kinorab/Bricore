#pragma once

#include <memory>
#include <vector>
#include "sceneNode.h"

class ContainerNode :
	public SceneNode {
public:
	ContainerNode();
	~ContainerNode();
	virtual void addChild(SceneNode * child) override;
private:
	std::vector<std::unique_ptr<SceneNode>> children;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

