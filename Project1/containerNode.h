#pragma once

#include <memory>
#include <vector>
#include "sceneNode.h"

class ContainerNode :
	public SceneNode {
public:
	ContainerNode();
	~ContainerNode();
private:
	std::vector<std::unique_ptr<SceneNode>> children;
};

